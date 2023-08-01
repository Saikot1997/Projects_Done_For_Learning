#if CONFIG_FREERTOS_UNICORE
#define ARDUINO_RUNNING_CORE 0
#else
#define ARDUINO_RUNNING_CORE 1
#endif
void sender_task(void *p);
void receiver_task(void *p);

QueueHandle_t Global_Queue_Handle = 0;
int completion_status = 0;

void setup()
{
  //set up serial monitor with 9600 baud rate
  Serial.begin(9600);

  // create a queue
  Global_Queue_Handle = xQueueCreate(10, sizeof(char));
  //crate a task
  xTaskCreate(sender_task, (const char*)"sender_task", 1024, NULL, 2, NULL);
  xTaskCreate(receiver_task, (const char*)"receiver_task", 1024, NULL, 1, NULL);
}

void loop()
{
}

void sender_task(void *p)
{
  char car1 = 'A';
  char car2 = 'B';
  char car3 = 'C';
  char car4 = 'D';
  char car5 = 'E';
  char car6 = 'F';
  char car7 = 'G';
  char car8 = 'H';
  char car9 = 'I';
  char car10 = 'J';

  xQueueSend(Global_Queue_Handle, &car1, 1000);
  Serial.println("Car A arrived and sent to queue");
  vTaskDelay(3000 / portTICK_PERIOD_MS);
  xQueueSend(Global_Queue_Handle, &car2, 1000);
  Serial.println("Car B arrived and sent to queue");
  vTaskDelay(2000 / portTICK_PERIOD_MS);
  xQueueSend(Global_Queue_Handle, &car3, 1000);
  Serial.println("Car C arrived and sent to queue");
  vTaskDelay(5000 / portTICK_PERIOD_MS);
  xQueueSend(Global_Queue_Handle, &car4, 1000);
  Serial.println("Car D arrived and sent to queue");
  vTaskDelay(4000 / portTICK_PERIOD_MS);
  xQueueSend(Global_Queue_Handle, &car5, 1000);
  Serial.println("Car E arrived and sent to queue");
  vTaskDelay(2000 / portTICK_PERIOD_MS);
  xQueueSend(Global_Queue_Handle, &car6, 1000);
  Serial.println("Car F arrived and sent to queue");
  vTaskDelay(3000 / portTICK_PERIOD_MS);
  xQueueSend(Global_Queue_Handle, &car7, 1000);
  Serial.println("Car G arrived and sent to queue");
  vTaskDelay(7000 / portTICK_PERIOD_MS);
  xQueueSend(Global_Queue_Handle, &car8, 1000);
  Serial.println("Car H arrived and sent to queue");
  vTaskDelay(1600 / portTICK_PERIOD_MS);
  xQueueSend(Global_Queue_Handle, &car9, 1000);
  Serial.println("Car I arrived and sent to queue");
  vTaskDelay(900 / portTICK_PERIOD_MS);
  xQueueSend(Global_Queue_Handle, &car10, 1000);
  Serial.println("Car J arrived and sent to queue");
  vTaskDelay(35000 / portTICK_PERIOD_MS);
}

void receiver_task(void *p)
{
  char rx;
  while(1) {

  if (xQueueReceive(Global_Queue_Handle, &rx, 1000) == pdTRUE)
  { 
    Serial.print("Car ");
    Serial.print(rx);
    Serial.print(" Received from queue");
    Serial.print('\n');

    if (completion_status == 0)
    {
      Serial.print("Sending Pass signal to the Car ");
      Serial.print(rx);
      Serial.print('\n');
      Serial.print("waiting to recive completion signal from car ");
      Serial.print(rx);
      Serial.print('\n');

      vTaskDelay(2000 / portTICK_PERIOD_MS);
      Serial.print("Completion signal received from car ");
      Serial.print(rx);
      Serial.print('\n');
    }

  }
  }

}
