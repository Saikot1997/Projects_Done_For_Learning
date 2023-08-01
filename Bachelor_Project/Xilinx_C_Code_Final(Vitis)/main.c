
#include "xparameters.h"
#include "xil_printf.h"
#include "sleep.h"
#include "stdio.h"
#include "PmodOLEDrgb.h"
#include "PmodESP32.h"
#include "xiic.h"
#include "xparameters.h"
#include "xstatus.h"
#include <xiic_i.h>
#include "xintc.h"
#include "xil_exception.h"
#include <stdbool.h>
#include <stdlib.h>
#include "algorithm.h"
#include <stdint.h>


#define MAX30102_IIC_DEVICE_ID XPAR_IIC_1_DEVICE_ID // for MAX30102 sensor
#define MLX90614_IIC_DEVICE_ID XPAR_IIC_0_DEVICE_ID // for MLX90614 sensor

// Register addresses of MLX90614
#define GY906_ADDRESS 0x5A   // I2C device address of the sensor MLX90614
#define TEMP_REG_ADDRESS 0x07 // obj temperature register of MLX90614 sensor

// Register adresses of MAX30102
#define MAX30102_I2C_ADDRESS 0x57 // 7-bit slave address of MAX30102 sensor
#define MAX30102_INT_ENABLE_1 0x02
#define MAX30102_FIFO_DATA 0x07
#define REG_FIFO_CONFIG 0x08
#define MAX30102_REG_MODE_CONFIG   0x09
#define MAX30102_REG_LED1_PA       0x0C
#define MAX30102_REG_LED2_PA       0x0D
#define MAX30102_REG_FIFO_WR_PTR   0x04
#define MAX30102_REG_FIFO_RD_PTR   0x06
#define MAX30102_REG_FIFO_OVERFLOW 0x05
#define MAX30102_REG_SPO2_CONFIG   0x0A

#ifdef __MICROBLAZE__
#define HOST_UART_DEVICE_ID XPAR_AXI_UARTLITE_0_BASEADDR
#define HostUart XUartLite
#define HostUart_Config XUartLite_Config
#define HostUart_CfgInitialize XUartLite_CfgInitialize
#define HostUart_LookupConfig XUartLite_LookupConfig
#define HostUart_Recv XUartLite_Recv
#define HostUartConfig_GetBaseAddr(CfgPtr) (CfgPtr->RegBaseAddr)
#include "xuartlite.h"
#include "xil_cache.h"
#else
#define HOST_UART_DEVICE_ID XPAR_PS7_UART_1_DEVICE_ID
#define HostUart XUartPs
#define HostUart_Config XUartPs_Config
#define HostUart_CfgInitialize XUartPs_CfgInitialize
#define HostUart_LookupConfig XUartPs_LookupConfig
#define HostUart_Recv XUartPs_Recv
#define HostUartConfig_GetBaseAddr(CfgPtr) (CfgPtr->BaseAddress)
#include "xuartps.h"
#endif

HostUart myHostUart;

#define PMODESP32_UART_BASEADDR XPAR_PMODESP32_0_AXI_LITE_UART_BASEADDR
#define PMODESP32_GPIO_BASEADDR XPAR_PMODESP32_0_AXI_LITE_GPIO_BASEADDR

void EnableCaches();
void DisableCaches();
void Initialize();
void Sensor_Config();
void MAX30102_WriteReg(unsigned char reg, unsigned char value);
int MAX30102_Init();
void MLX90614_initialize();
void read_temp();
void ReadFifoData();
void UpdateData();
int ReadFifoPointers();
void displayDATA();
void wifi_Setup();
void wifi_transmission();
void DemoCleanup();


PmodOLEDrgb oledrgb;
PmodESP32 myESP32;

XIic Iic; // instance for MLX9061
XIic IicInstance; // instance for MAX30102

int Pulse = 0;
int SpO2 = 0;
float temp = 0.00;

int32_t spo2;
int8_t spo2Valid; // value 1 if valid , value 0 if not valid
int32_t heartRate;
int8_t heartRateValid;  // value 1 if valid , value 0 if not valid
int sample = 0;
u32 redData,irData; // redled data, and infrared data read from MAX30102 sensor
u32 redDataArr[100]; // raw redled data
u32 irDataArr[100]; // raw infrared data

int main() {
	Initialize(); // initialize everything except  MAX30102 and MLX90614  sensor
	MLX90614_initialize();
	MAX30102_Init(); // initialize MAX30102 sensor
	usleep(50000);
    displayDATA(); // display setting , initially all data set to NULL
    usleep(50000);
    // Filling redDataArr with 0's
    for (int i = 0; i < 100; i++) {
        redDataArr[i] = 0;
    }

    // Filling irDataArr with 0's
    for (int i = 0; i < 100; i++) {
        irDataArr[i] = 0;
    }

    wifi_Setup(); // setup wifi connection


  while(1){
	
	 // read the  temperature
	 read_temp();
	 
	 // update temperature data on Oled display
	 if(temp!= 0.00){
		 // update temperature data on display
		 OLEDrgb_SetCursor(&oledrgb, 1, 0);
		 OLEDrgb_PutString(&oledrgb, "Temperature");
		 OLEDrgb_SetCursor(&oledrgb, 2, 1);
		 char tempStr[20];
		 snprintf(tempStr, 20, "= %.1f", temp);
		 OLEDrgb_PutString(&oledrgb, tempStr);
		 OLEDrgb_PutString(&oledrgb, "^C");	
	 }

	 ReadFifoData();

    // update SpO2 and heart rate data on display
    if (spo2Valid == 1 && heartRateValid == 1)
    {
        char spo2str[4];
        char pulsestr[4];
        SpO2 = (int)spo2;
        Pulse = (int)heartRate;

        OLEDrgb_SetCursor(&oledrgb, 1, 3);
        OLEDrgb_PutString(&oledrgb, "SpO2=");
        snprintf(spo2str, 4, "%d", SpO2);
        OLEDrgb_PutString(&oledrgb, spo2str);
        OLEDrgb_PutString(&oledrgb, ".0%");

        OLEDrgb_SetCursor(&oledrgb, 1, 5);
        OLEDrgb_PutString(&oledrgb, "Pulse=");
        snprintf(pulsestr, 4, "%d", Pulse);
        OLEDrgb_PutString(&oledrgb, pulsestr);
        OLEDrgb_PutString(&oledrgb, "/m");

        u8 check_resp[128];
	    unsigned char wifi_check[] = "AT+CWJAP?\r\n";
	    ESP32_SendBuffer(&myESP32, wifi_check, strlen((char*)wifi_check));
	    xil_printf("Sent command: %s\r\n", wifi_check);
	    usleep(1000000);
	    // Receive response
	    ESP32_Recv(&myESP32, check_resp, sizeof(check_resp));
	    xil_printf("Received response:%s\r\n", check_resp);
        usleep(1000000);
        // Check the response for Wi-Fi connection status
        if (strstr((char*)check_resp, "WIFI CONNECTED") != NULL) {
          wifi_transmission();
        }
        else {
          // Wi-Fi not connected or unexpected response
          wifi_Setup();
          wifi_transmission();
          }
    }
    else
    {
    	   OLEDrgb_SetCursor(&oledrgb, 1, 3);
    	   OLEDrgb_PutString(&oledrgb, "SpO2=");
    	   OLEDrgb_PutString(&oledrgb, "Error ");

    	   OLEDrgb_SetCursor(&oledrgb, 1, 5);
    	   OLEDrgb_PutString(&oledrgb, "Pulse=");
    	   OLEDrgb_PutString(&oledrgb, "Error");
    }

    spo2Valid = 0;
    heartRateValid = 0;
}
   DemoCleanup();
	return 0;
}
// initialize everything except  MAX30102 and MLX90614  sensor
void Initialize () {
	HostUart_Config *CfgPtr2;
	EnableCaches();
	ESP32_Initialize(&myESP32, PMODESP32_UART_BASEADDR, PMODESP32_GPIO_BASEADDR);
	CfgPtr2 = HostUart_LookupConfig(HOST_UART_DEVICE_ID);
	HostUart_CfgInitialize(&myHostUart, CfgPtr2, HostUartConfig_GetBaseAddr(CfgPtr2));
	OLEDrgb_begin(&oledrgb, XPAR_PMODOLEDRGB_0_AXI_LITE_GPIO_BASEADDR,
	         XPAR_PMODOLEDRGB_0_AXI_LITE_SPI_BASEADDR);
	
}
void MLX90614_initialize(){
    XIic_Config *ConfigPtr1;    /* Pointer to configuration data */

    /* Initialize the IIC driver so that it is ready to use. */
    ConfigPtr1 = XIic_LookupConfig(MLX90614_IIC_DEVICE_ID);

    XIic_CfgInitialize(&Iic, ConfigPtr1, ConfigPtr1->BaseAddress);

    XIic_Start(&Iic);
    // Set the slave address of MLX90614
    XIic_SetAddress(&Iic, XII_ADDR_TO_SEND_TYPE, GY906_ADDRESS);
}
void read_temp() {
    for(int i = 0 ; i<10; i++) // read temperature 10 times , we take only the last reading
     {
        // Send the register address of temperature data to MLX90614
        u8 reg_address[1];
        reg_address[0] = TEMP_REG_ADDRESS;
        XIic_Send(Iic.BaseAddress, GY906_ADDRESS, reg_address, 1, XIIC_REPEATED_START);
        // Read temperature data from MLX90614
        u8 temp_data[3];
        XIic_Recv(Iic.BaseAddress, GY906_ADDRESS, temp_data, 3, XIIC_STOP);
        // Convert temperature data to Celsius
        temp = (((temp_data[1])<<8|temp_data[0]) * 0.02) - 273.15;
     }
		}

// display All default data initially
void displayDATA() {
   OLEDrgb_Clear(&oledrgb);
   OLEDrgb_SetFontColor(&oledrgb, OLEDrgb_BuildRGB(255, 255, 255));
   OLEDrgb_SetCursor(&oledrgb, 1, 0);
   OLEDrgb_PutString(&oledrgb, "Temperature");
   OLEDrgb_SetCursor(&oledrgb, 2, 1);
   OLEDrgb_PutString(&oledrgb, "= Null");

   OLEDrgb_SetCursor(&oledrgb, 1, 3);
   OLEDrgb_PutString(&oledrgb, "SpO2=");
   OLEDrgb_PutString(&oledrgb, "Null");

   OLEDrgb_SetCursor(&oledrgb, 1, 5);
   OLEDrgb_PutString(&oledrgb, "Pulse=");
   OLEDrgb_PutString(&oledrgb, "Null");
}
//establish wifi connection
void wifi_Setup() {
    u8 conn_resp[128];
    // AT command for resetting ESP32
    unsigned char wifi_reset[] = "AT+RST\r\n";
    ESP32_SendBuffer(&myESP32, wifi_reset, strlen((char*)wifi_reset));
    xil_printf("Sent command: %s\r\n", wifi_reset);
    usleep(100000);

    // AT command for setting Wi-Fi mode to Station
    unsigned char mode_cmd[] = "AT+CWMODE?\r\n";
    ESP32_SendBuffer(&myESP32, mode_cmd, strlen((char*)mode_cmd));
    xil_printf("Sent command: %s\r\n", mode_cmd);
    usleep(100000);

    // AT command for connecting to Wi-Fi
    unsigned char conn_cmd[] = "AT+CWJAP=\"saikot-das.joy@stud.hshl.de\",\"28452467MaBaba\"\r\n";
    ESP32_SendBuffer(&myESP32, conn_cmd, strlen((char*)conn_cmd));
    xil_printf("Sent command: %s\r\n", conn_cmd);
    usleep(1000000);
    // Receive response
    ESP32_Recv(&myESP32, conn_resp, sizeof(conn_resp));
    xil_printf("Received response:%s\r\n", conn_resp);
    usleep(5000000);

            u8 check_resp[64];
    	    // AT command for connecting to Wi-Fi
    	    unsigned char wifi_check[] = "AT+CWJAP?\r\n";
    	    ESP32_SendBuffer(&myESP32, wifi_check, strlen((char*)wifi_check));
    	    xil_printf("Sent command: %s\r\n", wifi_check);
    	    usleep(1000000);
    	    // Receive response
    	    ESP32_Recv(&myESP32, check_resp, sizeof(check_resp));
    	    xil_printf("Received response:%s\r\n", check_resp);
            usleep(1000000);

}
// transmit data to thingspeak
void wifi_transmission(){

    // AT commands to determine single connection mode
      unsigned char SMconMode[] = "AT+CIPMUX=0\r\n";
      ESP32_SendBuffer(&myESP32, SMconMode, strlen((char*)SMconMode));
      usleep(1000000);
      // AT command for TCP connection with Thingspeak server
      unsigned char TCP[] = "AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80\r\n";
      ESP32_SendBuffer(&myESP32, TCP, strlen((char*)TCP));
      usleep(1000000);

      // Format the string with variables using sprintf
      unsigned char ch_upd[100];
      sprintf((char*)ch_upd, "GET /update?api_key=YUXWKBKVODTNYW0R&field1=%d&field2=%d&field3=%.1f\r\n", Pulse, SpO2, temp);

      int url_length = strlen((char*)ch_upd);
      unsigned char send_thing[50];
      sprintf((char*)send_thing, "AT+CIPSEND=%d\r\n", url_length);
      ESP32_SendBuffer(&myESP32, send_thing, strlen((char*)send_thing));
      usleep(1000000);
      ESP32_SendBuffer(&myESP32, ch_upd, strlen((char*)ch_upd));
      usleep(1000000);
      unsigned char Close_TCP[] = "AT+CIPCLOSE\r\n";
      ESP32_SendBuffer(&myESP32, Close_TCP, strlen((char*)Close_TCP));

}
// this function initializes MAX30102 sensor
int MAX30102_Init() {
    // Declare a pointer to configuration data
    XIic_Config *ConfigPtr3;
    // Obtain the IIC configuration data
    ConfigPtr3 = XIic_LookupConfig(MAX30102_IIC_DEVICE_ID);
    // Configure and initialize the IIC driver
     XIic_CfgInitialize(&IicInstance, ConfigPtr3, ConfigPtr3->BaseAddress);
    // Add a delay to ensure that the sensor has enough time to stabilize
    usleep(10000);
    // Start the I2C driver
    XIic_Start(&IicInstance);
    // Set the device address in write mode
    XIic_SetAddress(&IicInstance, XII_ADDR_TO_SEND_TYPE, MAX30102_I2C_ADDRESS);
    usleep(10000);
    Sensor_Config();
    return XST_SUCCESS;
}

// set up MAX30102 sensor configuration
void Sensor_Config(){
    // Clear the fifo Data Buffer if there is something
    MAX30102_WriteReg(MAX30102_REG_FIFO_WR_PTR, 0x00);
    MAX30102_WriteReg(MAX30102_REG_FIFO_RD_PTR, 0x00);
    MAX30102_WriteReg(MAX30102_REG_FIFO_OVERFLOW, 0x00);


    // Now, we will configure the sensor
    /*
     Set LedMode (Options, Red Only, IR ONly , Red+IR both)
     0x03= 00000011, B7= 0 (0 for normal mode,1 for power saving mode),B6 (1 for power rest , 0 if reset is done)
     B5,B4,B3 = No significance , B2,B1,B0 = 011 = to set in both led+IR mode
    */
    MAX30102_WriteReg(MAX30102_REG_MODE_CONFIG, 0x03); // SET led mode to Red+IR

    //Configure the SpO2-related settings
	/*
    B7= No significance, B6,B5 = ADC Range , B4,B3,B2 = Sample Rate , B1,B0 = PulseWidth
     SpO2 ADCRange =4096 (Binary = 01), sample rate = 100 Hz(Binary = 001), PulseWidth 411(Binary = 11)
     So, final Binary Value to be written = 0 01 001 11 = 0x27 (in hexadecimal)
    */
    MAX30102_WriteReg(MAX30102_REG_SPO2_CONFIG, 0x27);

    /*
     * Sample Average = 4 , B7,B6,B5 = Sample Average[2,0]
     * B4 = FIFO_Rollover_enable
     * B3,B2,B1,B0 = FIFO_A_FULL[3,0]
     */
    MAX30102_WriteReg(REG_FIFO_CONFIG, 0x50); // in arduino code its 0x40 setting fifo rollover enable to 0 (disabling it)


    // Enable interrupt 1
    MAX30102_WriteReg(MAX30102_INT_ENABLE_1, 0x40);


    /*
     * Set led current for Red led and IR led
     */
    MAX30102_WriteReg(MAX30102_REG_LED1_PA, 0x1F);     // 6.2 mA
    MAX30102_WriteReg(MAX30102_REG_LED2_PA, 0x1F);     // 6.2 mA
}

// this function is for writing data to register .
void MAX30102_WriteReg(u8 reg, u8 value) {
    u8 buf[2];
    buf[0] = reg;
    buf[1] = value;
    XIic_Send(IicInstance.BaseAddress, MAX30102_I2C_ADDRESS, buf, 2, XIIC_STOP);
}
// read data from fifo data register of max30102 sensor
void ReadFifoData() {
	int num_sample_to_read;
	int lim = 0;

    u8 fifo_data[6];
    u8 fifo_data_reg_addr[1];
    fifo_data_reg_addr[0] = MAX30102_FIFO_DATA;
    usleep(500000);
    // Call the function to calculate heart rate and oxygen saturation level
    num_sample_to_read =  ReadFifoPointers();
    while(sample<100 && lim <= 300) {
    	if (num_sample_to_read ==0)
    	{
    		usleep(150000);
    	}
    	else if((100-sample) >= num_sample_to_read){
			for (int i = 0; i<num_sample_to_read; i++) {
								// Read the FIFO data registers
								XIic_Send(IicInstance.BaseAddress, MAX30102_I2C_ADDRESS, fifo_data_reg_addr, 1, XIIC_REPEATED_START);
								XIic_Recv(IicInstance.BaseAddress, MAX30102_I2C_ADDRESS, fifo_data, 6, XIIC_STOP);
								// Parse the raw data into red and IR values
								redData = (fifo_data[0] << 16) | (fifo_data[1] << 8) | fifo_data[2];
								irData = (fifo_data[3] << 16) | (fifo_data[4] << 8) | fifo_data[5];

								// Store the data in arrays
								redDataArr[sample] = redData;
								irDataArr[sample] = irData;

				                if (redData > 9000 || irData > 9000) {
									redDataArr[sample] = redData;
									irDataArr[sample] = irData;
									sample+=1 ;
				                }
                             lim+=1;
							usleep(100000);
			}
			usleep(150000);
		    num_sample_to_read =  ReadFifoPointers();
    	}
    	else {
			for (int i = 0; i<(100-sample); i++) {
								// Read the FIFO data registers
								XIic_Send(IicInstance.BaseAddress, MAX30102_I2C_ADDRESS, fifo_data_reg_addr, 1, XIIC_REPEATED_START);
								XIic_Recv(IicInstance.BaseAddress, MAX30102_I2C_ADDRESS, fifo_data, 6, XIIC_STOP);

								// Parse the raw data into red and IR values
								redData = (fifo_data[0] << 16) | (fifo_data[1] << 8) | fifo_data[2];
								irData = (fifo_data[3] << 16) | (fifo_data[4] << 8) | fifo_data[5];

								// Store the data in arrays
				                if (redData > 9000 || irData > 9000) {
									redDataArr[sample] = redData;
									irDataArr[sample] = irData;
									sample+=1 ;
				                }
				                lim+=1;
							usleep(100000);
			}
			usleep(150000);
		    num_sample_to_read =  ReadFifoPointers();
    	}
    }
/*
    if (lim >=290) {
    	lim = 0;
    	sample = 0;
    }
    else
    {
    	maxim_heart_rate_and_oxygen_saturation(irDataArr, 100, redDataArr, &spo2, &spo2Valid, &heartRate, &heartRateValid);
	     if (spo2Valid != 1 || heartRateValid != 1)
	     {
	    	 UpdateData();
	     }
        lim = 0;
        sample = 0;
    }
   */
    maxim_heart_rate_and_oxygen_saturation(irDataArr, 100, redDataArr, &spo2, &spo2Valid, &heartRate, &heartRateValid);
    lim = 0;
    sample = 0;
}

// Update Fifo data of MAX30102 sensor , there is 100 sample , and this function drops first 25 samples
// and add 25 more sample at the end . so there is now 100 sample , and it's updated
void UpdateData(){
	int num_sample_to_read;
    u8 fifo_data[6];
    u8 fifo_data_reg_addr[1];
    fifo_data_reg_addr[0] = MAX30102_FIFO_DATA;
    usleep(500000);
    num_sample_to_read =  ReadFifoPointers();
    int cnt = 0;
    int lim_ex =0;
    while ((spo2Valid != 1 || heartRateValid != 1) && cnt < 5) {

	 while(sample<25 && lim_ex <= 75 ){

		 // shift last 75 samples to first 75 samples
		 for (int i = 0; i < 75; i++) {
		 	redDataArr[i] = redDataArr[i+25];
		 	irDataArr[i] = irDataArr[i+25];
		 }

	    	if (num_sample_to_read == 0){usleep(150000);}
	    	else if((25-sample) >= num_sample_to_read){
				for (int i = 0; i<num_sample_to_read; i++) {
									// Read the FIFO data registers
									XIic_Send(IicInstance.BaseAddress, MAX30102_I2C_ADDRESS, fifo_data_reg_addr, 1, XIIC_REPEATED_START);
									XIic_Recv(IicInstance.BaseAddress, MAX30102_I2C_ADDRESS, fifo_data, 6, XIIC_STOP);
									// Parse the raw data into red and IR values
									redData = (fifo_data[0] << 16) | (fifo_data[1] << 8) | fifo_data[2];
									irData = (fifo_data[3] << 16) | (fifo_data[4] << 8) | fifo_data[5];
									// Store the data in arrays
					                if (redData > 9000 || irData > 9000) {
										redDataArr[sample+75] = redData;
										irDataArr[sample+75] = irData;
										sample+=1 ;
					                }
					                lim_ex+=1;
								usleep(100000);
				}
				usleep(150000);
			    num_sample_to_read =  ReadFifoPointers();
	    	}
	    	else {
				for (int i = 0; i<(25-sample); i++) {
									// Read the FIFO data registers
									XIic_Send(IicInstance.BaseAddress, MAX30102_I2C_ADDRESS, fifo_data_reg_addr, 1, XIIC_REPEATED_START);
									XIic_Recv(IicInstance.BaseAddress, MAX30102_I2C_ADDRESS, fifo_data, 6, XIIC_STOP);
									// Parse the raw data into red and IR values
									redData = (fifo_data[0] << 16) | (fifo_data[1] << 8) | fifo_data[2];
									irData = (fifo_data[3] << 16) | (fifo_data[4] << 8) | fifo_data[5];
									// Store the data in arrays
					                if (redData > 9000 || irData > 9000) {
										redDataArr[sample+75] = redData;
										irDataArr[sample+75] = irData;
										sample+=1 ;
					                }
					                lim_ex+=1;
								usleep(100000);
				}
				usleep(150000);
			    num_sample_to_read =  ReadFifoPointers();
	    	}
	    }
		maxim_heart_rate_and_oxygen_saturation(irDataArr, 100, redDataArr, &spo2, &spo2Valid, &heartRate, &heartRateValid);
		sample = 0;
		cnt += 1 ;
		lim_ex =0 ;
 }
    cnt = 0;
}
// read fifo pointer register of max30102 sensor to determine how many sample available to read
int ReadFifoPointers() {
    u8 fifo_write_ptr;
    u8 write_ptr_reg_addr = MAX30102_REG_FIFO_WR_PTR;
    // Read the FIFO write pointer
    XIic_Send(IicInstance.BaseAddress, MAX30102_I2C_ADDRESS, &write_ptr_reg_addr, 1, XIIC_REPEATED_START);
    XIic_Recv(IicInstance.BaseAddress, MAX30102_I2C_ADDRESS, &fifo_write_ptr, 1, XIIC_STOP);
    int diff = fifo_write_ptr;
    return diff;
}
void DemoCleanup() {
	DisableCaches();
}
void EnableCaches() {
#ifdef __MICROBLAZE__
#ifdef XPAR_MICROBLAZE_USE_DCACHE
   Xil_DCacheEnable();
#endif
#ifdef XPAR_MICROBLAZE_USE_ICACHE
   Xil_ICacheEnable();
#endif
#endif
}
void DisableCaches() {
#ifdef __MICROBLAZE__
#ifdef XPAR_MICROBLAZE_USE_DCACHE
   Xil_DCacheDisable();
#endif
#ifdef XPAR_MICROBLAZE_USE_ICACHE
   Xil_ICacheDisable();
#endif
#endif
}
