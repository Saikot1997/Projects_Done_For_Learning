/* 
 Copyright 2022 Moataz Elbayaa (moataz.elbayaa@stud.hshl.de) or (moatazelbayaa9610@gmail.com)
*/

#include <ArduinoMqttClient.h>
#include <WiFiNINA.h>
#include <OneWire.h>
#include <DallasTemperature.h>   
#include "arduino_secrets.h"

// Please enter your network SSID and password in the file "arduino_secrets.h"
char ssid[] = SECRET_SSID;        // your network SSID
char pass[] = SECRET_PASS;    // your network password

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

// Please enter your IP address of Rasberry pi
const char broker[] = "192.168.137.69";
//Network protocol is TCP , so Port number is 1883
int port = 1883;

// Please enter the name of the topic
const char topic[]  = "desired_temperature";

// Setting Stepper Motor Pins to be connected on Arduino pins 9,10,11,and 12
#define STEPPER_PIN_1 9
#define STEPPER_PIN_2 10
#define STEPPER_PIN_3 11
#define STEPPER_PIN_4 12

// Here the input pin is declared to which the sensor module is connected
#define KY001_Signal_PIN 4
// Libraries for temperature sensor are configured
OneWire oneWire(KY001_Signal_PIN);          
DallasTemperature sensors(&oneWire);

// Defining the variables which will be used to control the project and to save reading data
int step_number = 0;
int a=0;
int x=1;
int oldtemp=0;
float temperature=0; 
int temp=0; 
char desired=0;
int desired_temperature=0;
int newest_desired_temperature=0;
const int on= 1;
const int off= 0;
int Heater_status=0;
int Air_conditioner_status=0;
int flag=0; 


void setup() 
{
  // Initialize serial and wait for port to open:
  Serial.begin(9600);

  // Sensor is initialized
  sensors.begin(); 

  // Setting the Motor Pins as Output Pins
  pinMode(STEPPER_PIN_1, OUTPUT);
  pinMode(STEPPER_PIN_2, OUTPUT);
  pinMode(STEPPER_PIN_3, OUTPUT);
  pinMode(STEPPER_PIN_4, OUTPUT); 
   
  // wait for serial port to connect.
  while (!Serial) 
  {
    ;  // wait for serial port to connect.Needed for native USB port only
  }
  
  // Attempt to connect to Wifi network:
  Serial.print("Attempting to connect to SSID : ");
  Serial.println(ssid);
  while (WiFi.begin(ssid, pass) != WL_CONNECTED) 
  {
    // Failed to connect to WiFi Network, retry
    Serial.print(".");
    delay(1000);
  }
  
  // Once it has been connected to Wifi network
  Serial.print("You're connected to the WiFi network : ");
  Serial.println(ssid);
  Serial.println();

  // Attempt to connect to the MQTT broker
  Serial.print("Attempting to connect to the MQTT broker: ");
  Serial.println(broker);
  if (!mqttClient.connect(broker, port)) 
  {
    // Failed to connect to MQTT broker, retry
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqttClient.connectError());

    while (1);
  }
  
  // Once it has been connected to the MQTT broker
  Serial.println("You're connected to the MQTT broker!");
  Serial.println();

  // set the message receive callback
  mqttClient.onMessage(onMqttMessage);

  // Subscribe to a topic
  Serial.print("Subscribing to topic: ");
  Serial.println(topic);
  Serial.println();

  // subscribe to a topic statement
  mqttClient.subscribe(topic);

  Serial.print("Topic: ");
  Serial.println(topic);
  Serial.println();
  
  Serial.println("KY-001 temperature/ Room Temperature measurement started!");

}

void loop() 
{
    // call poll() regularly to allow the library to receive MQTT messages and
    // send MQTT keep alive which avoids being disconnected by the broker
    mqttClient.poll();
  
    // Temperature measurement is started...
    sensors.requestTemperatures();
    sensors.getTempCByIndex(0);
    
    // Store measured temperature in variable
    // We have to store the measured temperature in a float variable "temperature"
    temperature=sensors.getTempCByIndex(0); 
    // Then coverting the measured temperature from float to int 
    temp=(int) temperature;
    
    // Printing the current Room Temperature,if it has been changed
    if(temp!=oldtemp)
    {
    Serial.print("Room Temperature now is : ");
    Serial.print(temp);
    Serial.println(" °C");
    oldtemp=temp;
    }

    /* Checking if the desired_temperature has been reached :
     *  If it has been reached turn off the Heater off the Air-conditioner
    */
    if(flag==0)
    {
    // if the Heater is on and the desired_temperature has been reached, turn off the Heater
    if(Heater_status==on)
    {
      /* check if the current Room temperature "temp" is less than or 
          equal to the last_desired_temperature "newest_desired_temperature"
      */
      if(temp>=newest_desired_temperature)
      {
        // Turn off the heater
        for(a=0;a<512;a++) //Rotation: //2048=360° //1024=180° //512=90° //256=45° 
       {
        OneStep(false); //Counterclockwise Rotation 
        delay(2); //the delay time specify the time of one rotation step of the motor
        //The Lower the delay is , the faster the rotatation becomes //The Higher the delay is, the slower the rotation becomes
       }
       Heater_status=off;
       Serial.println("Heater_status is : Off");
       Serial.println();
       //set the flag to 1
       flag=1;
      }
    }

    // if the Air Conditioner is on and the desired_temperature has been reached, turn off the Air Conditioner
    if(Air_conditioner_status==on)
    {
       /* check if the current Room temperature "temp" is less than or 
          equal to the last_desired_temperature "newest_desired_temperature"
       */
       if(temp<=newest_desired_temperature) 
       {
          // turn off the Air Conditioner
          for(a=0;a<512;a++) //Rotation: //2048=360° //1024=180° //512=90° //256=45° 
         {
         OneStep(true); //Clockwise Rotation
         delay(2); //the delay time specify the time of one rotation step of the motor
         //The Lower the delay is , the faster the rotatation becomes //The Higher the delay is, the slower the rotation becomes
         }
         Air_conditioner_status=off;
         Serial.println("Air_conditioner_status is : Off");
         Serial.println();
         //set the flag to 1
         flag=1;
       }
    }

    }
    
    /* After the desired Room Temperature has been acheived ,and the Heater and The Air_conditioner have been  
       turned off
     * To keep the Room temperature at the "newest_desired_temperature":
     *  check if the current Room temperature "temp" is not equal to 
        the last_desired_temperature "newest_desired_temperature"
     *  If it is not the desired room temperature , Then we will turn the Heater or the conditioner On to
        achieve the desired Room temperature
    */
    if(flag==1)
    {
      /*
      If Rooom temperature is less than or equal to (the desired temperature - 2°c)
      Then Heater should be turned On
     */
     if(temp<=(newest_desired_temperature-2)&&(Heater_status==off)) 
     {
       // Now, Turn on the Heater
       for(a=0;a<512;a++) //Rotation: //2048=360° //1024=180° //512=90° //256=45° 
       {
         OneStep(true); //Clockwise Rotation
         delay(2); //the delay time specify the time of one rotation step of the motor
         //The Lower the delay is , the faster the rotatation becomes //The Higher the delay is, the slower the rotation becomes
       }
       
       Heater_status=on;
       Serial.println("Heater_status is : On");

       // Then clear the flag 
       flag=0;
     }
     
     /*
      Else If Rooom temperature is greater than or equal to (the desired temperature+2°c)
      Then Air-Conditioner should be turned On
    */
    else if (temp>=(newest_desired_temperature+2)&&(Air_conditioner_status==off)) //Turn on Air-Conditioner
    {
      
     //Now, Turn on The Air-Conditioner
     for(a=0;a<512;a++) //Rotation: //2048=360° //1024=180° //512=90° //256=45° 
     {
        OneStep(false); //Counterclockwise Rotation 
        delay(2); //the delay time specify the time of one rotation step of the motor
        //The Lower the delay is , the faster the rotatation becomes //The Higher the delay is, the slower the rotation becomes
     }
     
     Air_conditioner_status=on;
     Serial.println("Air_conditioner_status is : ON");

     // Then clear the flag 
       flag=0;
     
     
    }

     
    }
    
    
    
    
   
}

void onMqttMessage(int messageSize) 
{
  /* Once we received a message of "desired temperature" from the phone,
    print out the topic and contents*/
  Serial.println();
  Serial.print("Received a message with topic : ");
  Serial.println(mqttClient.messageTopic());
  

  // use the Stream interface to print the contents
  while (mqttClient.available()) 
  {
    /* mqttClient.read() is reading char by char
      ,so we will store the every char in the char data type variable "desired".
      Then we will check the value of it and store in int varible "desired_temperature"
    */
    desired=mqttClient.read();

    /* check the value of char variable "desired" of position (*10^1) of desired temperature
       and store in int varible "desired_temperature"*/
    if(x==1)
    {
      if(desired=='0')
        desired_temperature+=0;
      else if(desired=='1')
        desired_temperature+=10;
      else if(desired=='2')
        desired_temperature+=20;
      else if(desired=='3')
        desired_temperature+=30;
      else if(desired=='4')
        desired_temperature+=40;
      else if(desired=='5')
        desired_temperature+=50;
      else if(desired=='6')
        desired_temperature+=60;
      else if(desired=='7')
        desired_temperature+=70;
      else if(desired=='8')
        desired_temperature+=80;
      else if(desired=='9')
        desired_temperature+=90;

      /*now we have stored the position (*10^1) 
      and setting x to 2 to store the upcoming read 
      which is of position (*10^0) of desired temperature
      */ 
      x=2; 
    }

    /* check the value of char variable "desired" of position (*10^0) of desired temperature
       and store in int varible "desired_temperature"*/
    else if(x==2)
    {
      if(desired=='0')
        desired_temperature+=0;
      else if(desired=='1')
        desired_temperature+=1;
      else if(desired=='2')
        desired_temperature+=2;
      else if(desired=='3')
        desired_temperature+=3;
      else if(desired=='4')
        desired_temperature+=4;
      else if(desired=='5')
        desired_temperature+=5;
      else if(desired=='6')
        desired_temperature+=6;
      else if(desired=='7')
        desired_temperature+=7;
      else if(desired=='8')
        desired_temperature+=8;
      else if(desired=='9')
        desired_temperature+=9;
     
     /*now we have stored the position (*10^0) 
      and setting x to 2 to store the upcoming read 
      which is of position (*10^1) of desired temperature for upcoming Read
      */ 
     x=1;
    }
    
    if(x==1)
     break;
    
    
  }
  /*
    if x is still equal to 2,then we have to a one digit number 
    so the desired temperature is less than 10
    so we will devide "the number which we have stored" by 10  
  */
  if(x==2)
    desired_temperature/=10;

  //print the current Rooom Temperature 
  temp=(int) temperature;
  Serial.print("Room Temperature now is : ");
  Serial.print(temp);
  Serial.println(" °C");

  //print the desired Temperature 
  Serial.print("Desired Temperature is : ");
  Serial.print(desired_temperature);
  Serial.println(" °c");

  
  /*once we got the desired_temperature we should reset the variable x 
  to begin to store a new-readed desired temperature*/   
  x=1; 

  
     //Now, we will check the desired temperature with respect to the Room temperature

    /*
      If Rooom temperature is less than the desired temperature 
      Then Heater should be turned On
    */
    if((temp<desired_temperature)&&(Heater_status==off)) 
    {
       /*
         Firstly, we chould check if the Air conditioner is On or not.
         If it is on we should firstly turn it off
       */
       if(Air_conditioner_status==on) 
       {
         //Turn Off The Air-Conditioner
         for(a=0;a<512;a++) //Rotation: //2048=360° //1024=180° //512=90° //256=45° 
         {
         OneStep(true); //Clockwise Rotation
         delay(2); //the delay time specify the time of one rotation step of the motor
         //The Lower the delay is , the faster the rotatation becomes //The Higher the delay is, the slower the rotation becomes
         }
         Air_conditioner_status=off;
         Serial.println("Air_conditioner_status is : Off");
         
         delay(1000);
       }

       // Now, Turn on the Heater
       for(a=0;a<512;a++) //Rotation: //2048=360° //1024=180° //512=90° //256=45° 
       {
         OneStep(true); //Clockwise Rotation
         delay(2); //the delay time specify the time of one rotation step of the motor
         //The Lower the delay is , the faster the rotatation becomes //The Higher the delay is, the slower the rotation becomes
       }
       
       /* Then setting the "newest_desired_temperature" to "desired_temperature" 
          which we have just received few milliseconds ago to check if the Room-
          temperature has became to this "newest_desired_temperature" 
       */
       newest_desired_temperature=desired_temperature;
       
       /*
        Then we should clear the "desired_temperature" to store new desired_temperature in it
       */
       desired_temperature=0;
       Heater_status=on;
       Serial.println("Heater_status is : On");
       
       
    }

    /*
      Else If Rooom temperature is greater than the desired temperature 
      Then Air-Conditioner should be turned On
    */
    else if ((temp>desired_temperature)&&(Air_conditioner_status==off)) //Turn on Air-Conditioner
    {
      
     /*
       Firstly, we chould check if the Heater is On or not.
       If it is on we should firstly turn it off
     */
     if(Heater_status==on) 
     {
       //Turn Off The Heater 
       for(a=0;a<512;a++) //Rotation: //2048=360° //1024=180° //512=90° //256=45° 
       {
        OneStep(false); //Counterclockwise Rotation 
        delay(2); //the delay time specify the time of one rotation step of the motor
        //The Lower the delay is , the faster the rotatation becomes //The Higher the delay is, the slower the rotation becomes
       }
       Heater_status=off;
       Serial.println("Heater_status is : Off");
       
       delay(1000);
       
      
     }

     //Now, Turn on The Air-Conditioner
     for(a=0;a<512;a++) //Rotation: //2048=360° //1024=180° //512=90° //256=45° 
     {
        OneStep(false); //Counterclockwise Rotation 
        delay(2); //the delay time specify the time of one rotation step of the motor
        //The Lower the delay is , the faster the rotatation becomes //The Higher the delay is, the slower the rotation becomes
     }
     
     /* Then setting the "newest_desired_temperature" to "desired_temperature" 
        which we have just received few milliseconds ago to check if the Room-
        temperature has became to this "newest_desired_temperature" 
     */
     newest_desired_temperature=desired_temperature;

     /*
        Then we should clear the "desired_temperature" to store new desired_temperature in it
     */
     desired_temperature=0;
     
     Air_conditioner_status=on;
     Serial.println("Air_conditioner_status is : ON");
     
     
    }

    /*
      Else case:
      If Rooom temperature is equal to the desired temperature 
      Then Air-Conditioner and Heater both should be turned Off
    */
    else //if (temp==desired_temperature)
    {
     /*
       Firstly, we chould check if the Heater is On or not.
       If it is on we should firstly turn it off
     */
     if(Heater_status==on) 
     {
       //Turn Off The Heater 
       for(a=0;a<512;a++) //Rotation: //2048=360° //1024=180° //512=90° //256=45° 
       {
        OneStep(false); //Counterclockwise Rotation
        delay(2); //the delay time specify the time of one rotation step of the motor
        //The Lower the delay is , the faster the rotatation becomes //The Higher the delay is, the slower the rotation becomes
       }
       Heater_status=off;
       Serial.println("Heater_status is : Off");
       
       delay(1000);
      
     }
     /*
       If the Heater is off, Then we check if the Air_conditioner is On or not.
       If it is on we should turn it off
     */
     else if(Air_conditioner_status==on)
       {
         //Turn Off the Air_conditioner
         for(a=0;a<512;a++) //Rotation: //2048=360° //1024=180° //512=90° //256=45° 
         {
         OneStep(true); //Clockwise Rotation
         delay(2); //the delay time specify the time of one rotation step of the motor
         //The Lower the delay is , the faster the rotatation becomes //The Higher the delay is, the slower the rotation becomes
         }
         Air_conditioner_status=off;
         Serial.println("Air_conditioner_status is : Off");
         
         delay(1000);
       }
       Air_conditioner_status=off;
       Heater_status=off;
       
       /* Then setting the "newest_desired_temperature" to "desired_temperature" 
        which we have just received few milliseconds ago to check if the Room-
        temperature has became to this "newest_desired_temperature" 
       */
       newest_desired_temperature=desired_temperature;
       flag=1;

       /*
        Then we should clear the "desired_temperature" to store new desired_temperature in it
       */
       desired_temperature=0;
     
    }


    delay(1000); // 1 second Delay until next measurement
    
    Serial.println();
}

//Direction control Function of the Motor for controlling the Heater and the Air-Conditioner
void OneStep(bool dir)
{
    /*
      if dir is True , then it is a Clockwise Rotation
      if dir is False, then it is a Counterclockwise Rotation 
    */

    if(dir)
    {
      //Clockwise Rotation
      switch(step_number)
      {
        case 0:
         digitalWrite(STEPPER_PIN_1, HIGH);
         digitalWrite(STEPPER_PIN_2, LOW);
         digitalWrite(STEPPER_PIN_3, LOW);
         digitalWrite(STEPPER_PIN_4, LOW);
          break;
       case 1:
         digitalWrite(STEPPER_PIN_1, LOW);
         digitalWrite(STEPPER_PIN_2, HIGH);
         digitalWrite(STEPPER_PIN_3, LOW);
         digitalWrite(STEPPER_PIN_4, LOW);
         break;
       case 2:
         digitalWrite(STEPPER_PIN_1, LOW);
         digitalWrite(STEPPER_PIN_2, LOW);
         digitalWrite(STEPPER_PIN_3, HIGH);
         digitalWrite(STEPPER_PIN_4, LOW);
         break;
       case 3:
         digitalWrite(STEPPER_PIN_1, LOW);
         digitalWrite(STEPPER_PIN_2, LOW);
         digitalWrite(STEPPER_PIN_3, LOW);
         digitalWrite(STEPPER_PIN_4, HIGH);
         break;
     } 
    }
    
  else
  {
    //Counterclockwise Rotation 
    switch(step_number)
    {
      case 0:
         digitalWrite(STEPPER_PIN_1, LOW);
         digitalWrite(STEPPER_PIN_2, LOW);
         digitalWrite(STEPPER_PIN_3, LOW);
         digitalWrite(STEPPER_PIN_4, HIGH);
         break;
      case 1:
         digitalWrite(STEPPER_PIN_1, LOW);
         digitalWrite(STEPPER_PIN_2, LOW);
         digitalWrite(STEPPER_PIN_3, HIGH);
         digitalWrite(STEPPER_PIN_4, LOW);
         break;
      case 2:
         digitalWrite(STEPPER_PIN_1, LOW);
         digitalWrite(STEPPER_PIN_2, HIGH);
         digitalWrite(STEPPER_PIN_3, LOW);
         digitalWrite(STEPPER_PIN_4, LOW);
         break;
      case 3:
         digitalWrite(STEPPER_PIN_1, HIGH);
         digitalWrite(STEPPER_PIN_2, LOW);
         digitalWrite(STEPPER_PIN_3, LOW);
         digitalWrite(STEPPER_PIN_4, LOW);
 
  
    } 
  }
  
  step_number++;
  
  if(step_number > 3)
  {
    step_number = 0;
  }
  
}
