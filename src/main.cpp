#include <Arduino.h>
#include "can.h"
#include "pid.h"
#include "mo.h"
//DM-J4310-2EC电机
can_frame_data rx_data;

void transmit(void *pt)
{
  while (1)
  {
  Transmit(200,5);
  vTaskDelay(50);
  }
  
}

void receive(void *pt)
{
  while (1)
  {
  Receive();
  vTaskDelay(50);
  }
  
}

void setup() {
  Serial.begin(115200);
  ESP_CAN::CAN can;
  can.CAN_Setup(GPIO_NUM_33, GPIO_NUM_35, b1000k);
  can.CAN_Start();
  setmode();
  xTaskCreate(transmit,"transmit",4096,NULL,1,NULL);
  xTaskCreate(receive,"receive",4096,NULL,2,NULL);
  vTaskStartScheduler();

}

void loop() {
   
   vTaskDelay(50);
}