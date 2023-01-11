/*
 * main.c
 *
 *  Created on: Jun 11, 2018
 *      Author:Nirojan N
 */

#include "xparameters.h"
#include "xil_printf.h"
#include "sleep.h"
#include "xiic.h"
#include "xintc.h"
#include "xil_exception.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "PmodESP32.h"

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


//----------------------OLED---------------------------------


#include "bitmap.h"
#include "PmodOLEDrgb.h"
#include "sleep.h"
#include "xil_cache.h"
#include "xparameters.h"

void Oled_Initialize();
void Oled_Run();
void DemoCleanup();
void EnableCaches();
void DisableCaches();

PmodOLEDrgb oledrgb;

u8 rgbUserFont[] = {
   0x00, 0x04, 0x02, 0x1F, 0x02, 0x04, 0x00, 0x00, // 0x00
   0x0E, 0x1F, 0x15, 0x1F, 0x17, 0x10, 0x1F, 0x0E, // 0x01
   0x00, 0x1F, 0x11, 0x00, 0x00, 0x11, 0x1F, 0x00, // 0x02
   0x00, 0x0A, 0x15, 0x11, 0x0A, 0x04, 0x00, 0x00, // 0x03
   0x07, 0x0C, 0xFA, 0x2F, 0x2F, 0xFA, 0x0C, 0x07  // 0x04
}; // This table defines 5 user characters, although only one is used


//-------------------------------------------------------


#define PMODESP32_UART_BASEADDR XPAR_PMODESP32_0_AXI_LITE_UART_BASEADDR
#define PMODESP32_GPIO_BASEADDR XPAR_PMODESP32_0_AXI_LITE_GPIO_BASEADDR

void EnableCaches();
void DisableCaches();
void DemoInitialize();
void DemoRun();
void DemoCleanup();



/************************** Constant Definitions *****************************/

/*
 * The following constants map to the XPAR parameters created in the
 * xparameters.h file. They are defined here such that a user can easily
 * change all the needed parameters in one place.
 */
#define IIC_DEVICE_ID		XPAR_IIC_0_DEVICE_ID
#define INTC_DEVICE_ID		XPAR_INTC_0_DEVICE_ID
#define INTC_IIC_INTERRUPT_ID	XPAR_INTC_0_IIC_0_VEC_ID


/*s
 * The following constant defines the address of the IIC
 * temperature sensor device on the IIC bus. Note that since
 * the address is only 7 bits, this  constant is the address divided by 2.
 */
#define TEMP_SENSOR_ADDRESS	0x4B /* The actual address is 0x30 */


/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ****************************/

int TempSensorExample(u16 IicDeviceId, u8 TempSensorAddress,
						  u8 *TemperaturePtr);

static int SetupInterruptSystem(XIic *IicPtr);

static void RecvHandler(void *CallbackRef, int ByteCount);

static void StatusHandler(void *CallbackRef, int Status);


/************************** Variable Definitions **************************/

XIic Iic;		  /* The instance of the IIC device */

XIntc InterruptController;  /* The instance of the Interrupt controller */

/*
 * The following structure contains fields that are used with the callbacks
 * (handlers) of the IIC driver. The driver asynchronously calls handlers
 * when abnormal events occur or when data has been sent or received. This
 * structure must be volatile to work when the code is optimized.
 */
volatile struct {
	int  EventStatus;
	int  RemainingRecvBytes;
	int EventStatusUpdated;
	int RecvBytesUpdated;
} HandlerInfo;

/*****************************************************************************/
/**
*
* The purpose of this function is to illustrate how to use the IIC driver to
* read the temperature.
*
*
* @return	XST_SUCCESS if successful, XST_FAILURE if unsuccessful
*
* @note		None
*
*******************************************************************************/
int temp_init(){

	int Status;
		u8 TemperaturePtr;

		/*
		 * Call the TempSensorExample.
		 */
		Status =  TempSensorExample(IIC_DEVICE_ID, TEMP_SENSOR_ADDRESS,
		                          &TemperaturePtr);
		xil_printf("Temp :%d °C \r\n",TemperaturePtr);

		if (Status != XST_SUCCESS) {
			xil_printf("IIC tempsensor connection Failed\r\n");
			return XST_FAILURE;
		}

		xil_printf("Successfully ran IIC tempsensor on board\r\n");
		return XST_SUCCESS;


}

int global_temp; // declaring a global variable

int print_temp_reading(){
	int Status;
		u8 TemperaturePtr;

		/*
		 * Call the TempSensor.
		 */
		Status =  TempSensorExample(IIC_DEVICE_ID, TEMP_SENSOR_ADDRESS,
		                          &TemperaturePtr);
		xil_printf("Temp :%d °C \r\n",TemperaturePtr);

		global_temp=TemperaturePtr;  // assigning temp to a gloabal variable to be ablt to access in the esp sending

		if (Status != XST_SUCCESS) {
			xil_printf("IIC tempsensor Failed\r\n");
			return XST_FAILURE;
		                            }

		//xil_printf("Successfully ran IIC tempsensor \r\n");
		//  original    return XST_SUCCESS;
		return TemperaturePtr;
}

PmodESP32 myESP32;
HostUart myHostUart;

void DemoInitialize () {
	HostUart_Config *CfgPtr;
	EnableCaches();
	ESP32_Initialize(&myESP32, PMODESP32_UART_BASEADDR, PMODESP32_GPIO_BASEADDR);
	CfgPtr = HostUart_LookupConfig(HOST_UART_DEVICE_ID);
	HostUart_CfgInitialize(&myHostUart, CfgPtr, HostUartConfig_GetBaseAddr(CfgPtr));
}


void DemoRun() {
    u8 recv_buffer;
    u32 num_received;

    u8 buffer[] = "AT+CIPSTART=\"TCP\",\"192.168.173.222\",80\r\n";
    u8 buffer_09[] = "AT+CIPSEND=8\r\n";

    xil_printf("Requesting if ESp32 is ready to send Data\r\n");
    ESP32_SendBuffer(&myESP32, buffer, 45);
    xil_printf("Connecting to TCp Server Rostock\r\n");

    int a = 39; // testing with a dummy value
    char msg[5];
    itoa(a, msg, 10); // converting the recieved temperature value to string to send over the TCP IP protocol to server

    int j = 0;
    int i = 0;

    while (1) {
        // TODO: add exit functionality (ctrl-Z?)
        num_received = ESP32_Recv(&myESP32, &recv_buffer, 1);
        if (num_received > 0) {
            xil_printf("%c", recv_buffer);
        }

        num_received = HostUart_Recv(&myHostUart, &recv_buffer, 1);
        if (num_received > 0) {
            xil_printf("%c", recv_buffer);

            while (0 == ESP32_Send(&myESP32, &recv_buffer, 1));
        }

        i++;
        j++;

        if (j == 100000) {
            // print_temp_reading();
            // int store=TemperaturePtr;
            j = 0;
            if (i == 100000) {
                ESP32_SendBuffer(&myESP32, buffer_09, 14);
            }

            if (i == 200000) {
                print_temp_reading();
                itoa(global_temp, msg, 10);
                char temp_data_string[] = "\r\n ";
                char msg_temp[] = " ^C\r\n";
                char nxt_line[] = "\r\n";
                strcat(msg, msg_temp);
                ESP32_SendBuffer(&myESP32, msg, 25);
                ESP32_SendBuffer(&myESP32, nxt_line, 4);
                i = 0;
            }
        }
    }
}




void DemoCleanup() {
	DisableCaches();
}


int main() {
	DemoInitialize();
	// Oled_Initialize();

	temp_init();

	DemoRun();
	DemoCleanup();
	return 0;
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

/*****************************************************************************/
/**
* The function reads the temperature of the IIC temperature sensor on the
* IIC bus. It initializes the IIC device driver and sets it up to communicate
* with the temperature sensor. This function does contain a loop that polls
* for completion of the IIC processing such that it may not return if
* interrupts or the hardware are not working.
*
* @param	IicDeviceId is the XPAR_<IIC_instance>_DEVICE_ID value from
*		xparameters.h for the IIC Device
* @param	TempSensorAddress is the address of the Temperature Sensor device
*		on the IIC bus
* @param	TemperaturePtr is the data byte read from the temperature sensor
*
* @return	XST_SUCCESS to indicate success, else XST_FAILURE to indicate
*		a Failure.
*
* @note		None.
*
*******************************************************************************/
int TempSensorExample(u16 IicDeviceId, u8 TempSensorAddress, u8 *TemperaturePtr)
{
	int Status;
	static int Initialized = FALSE;
	XIic_Config *ConfigPtr;	/* Pointer to configuration data */

	if (!Initialized) {
		Initialized = TRUE;

		/*
		 * Initialize the IIC driver so that it is ready to use.
		 */
		ConfigPtr = XIic_LookupConfig(IicDeviceId);
		if (ConfigPtr == NULL) {
			return XST_FAILURE;
		}

		Status = XIic_CfgInitialize(&Iic, ConfigPtr,
						ConfigPtr->BaseAddress);
		if (Status != XST_SUCCESS) {
			return XST_FAILURE;
		}


		/*
		 * Setup handler to process the asynchronous events which occur,
		 * the driver is only interrupt driven such that this must be
		 * done prior to starting the device.
		 */
		XIic_SetRecvHandler(&Iic, (void *)&HandlerInfo, RecvHandler);
		XIic_SetStatusHandler(&Iic, (void *)&HandlerInfo,
						StatusHandler);

		/*
		 * Connect the ISR to the interrupt and enable interrupts.
		 */
		Status = SetupInterruptSystem(&Iic);
		if (Status != XST_SUCCESS) {
			return XST_FAILURE;
		}

		/*
		 * Start the IIC driver such that it is ready to send and
		 * receive messages on the IIC interface, set the address
		 * to send to which is the temperature sensor address
		 */
		XIic_Start(&Iic);
		XIic_SetAddress(&Iic, XII_ADDR_TO_SEND_TYPE, TempSensorAddress);
	}

	/*
	 * Clear updated flags such that they can be polled to indicate
	 * when the handler information has changed asynchronously and
	 * initialize the status which will be returned to a default value
	 */
	HandlerInfo.EventStatusUpdated = FALSE;
	HandlerInfo.RecvBytesUpdated = FALSE;
	Status = XST_FAILURE;

	/*
	 * Attempt to receive a byte of data from the temperature sensor
	 * on the IIC interface, ignore the return value since this example is
	 * a single master system such that the IIC bus should not ever be busy
	 */
	(void)XIic_MasterRecv(&Iic, TemperaturePtr, 1);

	/*
	 * The message is being received from the temperature sensor,
	 * wait for it to complete by polling the information that is
	 * updated asynchronously by interrupt processing
	 */
	while(1) {
		if(HandlerInfo.RecvBytesUpdated == TRUE) {
			/*
			 * The device information has been updated for receive
			 * processing,if all bytes received (1), indicate
			 * success
			 */
			if (HandlerInfo.RemainingRecvBytes == 0) {
				Status = XST_SUCCESS;
			}
			break;
		}

		/*
		 * Any event status which occurs indicates there was an error,
		 * so return unsuccessful, for this example there should be no
		 * status events since there is a single master on the bus
		 */
		if (HandlerInfo.EventStatusUpdated == TRUE) {
			break;
		}
	}

	return Status;
}

/*****************************************************************************/
/**
*
* This function setups the interrupt system such that interrupts can occur
* for IIC. This function is application specific since the actual system may
* or may not have an interrupt controller. The IIC device could be directly
* connected to a processor without an interrupt controller. The user should
* modify this function to fit the application.
*
* @param	IicPtr contains a pointer to the instance of the IIC component
*		which is going to be connected to the interrupt controller.
*
* @return	XST_SUCCESS if successful, otherwise XST_FAILURE.
*
* @notes	None.
*
****************************************************************************/
 int SetupInterruptSystem(XIic *IicPtr)  /////  static was removed from before INT
{
	int Status;

	/*
	 * Initialize the interrupt controller driver so that it's ready to use,
	 * specify the device ID that is generated in xparameters.h
	 */
	Status = XIntc_Initialize(&InterruptController, INTC_DEVICE_ID);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}


	/*
	 * Connect a device driver handler that will be called when an interrupt
	 * for the device occurs, the device driver handler performs the
	 * specific interrupt processing for the device
	 */
	Status = XIntc_Connect(&InterruptController, INTC_IIC_INTERRUPT_ID,
					XIic_InterruptHandler, IicPtr);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/*
	 * Start the interrupt controller such that interrupts are recognized
	 * and handled by the processor.
	 */
	Status = XIntc_Start(&InterruptController, XIN_REAL_MODE);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/*
	 * Enable the interrupts for the IIC device.
	 */
	XIntc_Enable(&InterruptController, INTC_IIC_INTERRUPT_ID);

	/*
	 * Initialize the exception table.
	 */
	Xil_ExceptionInit();

	/*
	 * Register the interrupt controller handler with the exception table.
	 */
	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT,
				 (Xil_ExceptionHandler) XIntc_InterruptHandler,
				 &InterruptController);

	/*
	 * Enable non-critical exceptions.
	 */
	Xil_ExceptionEnable();

	return XST_SUCCESS;

}


/*****************************************************************************/
/**
* This receive handler is called asynchronously from an interrupt context and
* and indicates that data in the specified buffer was received. The byte count
* should equal the byte count of the buffer if all the buffer was filled.
*
* @param	CallBackRef is a pointer to the IIC device driver instance which
*		the handler is being called for.
* @param	ByteCount indicates the number of bytes remaining to be received of
*		the requested byte count. A value of zero indicates all requested
*		bytes were received.
*
* @return	None.
*
* @notes	None.
*
****************************************************************************/
 void RecvHandler(void *CallbackRef, int ByteCount)  /////  static was removed from before INT
{
	HandlerInfo.RemainingRecvBytes = ByteCount;
	HandlerInfo.RecvBytesUpdated = TRUE;
}

/*****************************************************************************/
/**
* This status handler is called asynchronously from an interrupt context and
* indicates that the conditions of the IIC bus changed. This  handler should
* not be called for the application unless an error occurs.
*
* @param	CallBackRef is a pointer to the IIC device driver instance which the
*		handler is being called for.
* @param	Status contains the status of the IIC bus which changed.
*
* @return	None.
*
* @notes	None.
*
****************************************************************************/
 void StatusHandler(void *CallbackRef, int Status) /////  static was removed from before INT
{
	HandlerInfo.EventStatus |= Status;
	HandlerInfo.EventStatusUpdated = TRUE;

}

//-----------------------OLED----------------------------


 void Oled_Initialize() {
    EnableCaches();
    OLEDrgb_begin(&oledrgb, XPAR_PMODOLEDRGB_0_AXI_LITE_GPIO_BASEADDR,
          XPAR_PMODOLEDRGB_0_AXI_LITE_SPI_BASEADDR);
 }

 void Oled_Run() {
    char ch;

    // Define the user definable characters
    for (ch = 0; ch < 5; ch++) {
       OLEDrgb_DefUserChar(&oledrgb, ch, &rgbUserFont[ch * 8]);
    }

    OLEDrgb_SetCursor(&oledrgb, 2, 1);
    OLEDrgb_PutString(&oledrgb, "Digilent"); // Default color (green)
    OLEDrgb_SetCursor(&oledrgb, 4, 4);
    OLEDrgb_SetFontColor(&oledrgb, OLEDrgb_BuildRGB(0, 0, 255)); // Blue font
    OLEDrgb_PutString(&oledrgb, "OledRGB");

    OLEDrgb_SetFontColor(&oledrgb, OLEDrgb_BuildRGB(200, 200, 44));
    OLEDrgb_SetCursor(&oledrgb, 1, 6);
    OLEDrgb_PutChar(&oledrgb, 4);

    OLEDrgb_SetFontColor(&oledrgb, OLEDrgb_BuildRGB(200, 12, 44));
    OLEDrgb_SetCursor(&oledrgb, 5, 6);
    OLEDrgb_PutString(&oledrgb, "Demo");
    OLEDrgb_PutChar(&oledrgb, 0);

    sleep(5); // Wait 5 seconds

    OLEDrgb_DrawBitmap(&oledrgb, 0, 0, 95, 63, (u8*) tommy);
 }



 //------------------------------------------------------

