#ifndef MO_H
#define MO_H

// #define RC_CH_VALUE_MIN ((uint16_t)364 )
// #define RC_CH_VALUE_OFFSET ((uint16_t)1024)
// #define RC_CH_VALUE_MAX ((uint16_t)1684)

// #define RC_SW_UP ((uint16_t)1)
// #define RC_SW_MID ((uint16_t)3)
// #define RC_SW_DOWN ((uint16_t)2)

// #define KEY_PRESSED_OFFSET_W ((uint16_t)0x01<<0)
// #define KEY_PRESSED_OFFSET_S ((uint16_t)0x01<<1)
// #define KEY_PRESSED_OFFSET_A ((uint16_t)0x01<<2)
// #define KEY_PRESSED_OFFSET_D ((uint16_t)0x01<<3)
// #define KEY_PRESSED_OFFSET_Q ((uint16_t)0x01<<4)
// #define KEY_PRESSED_OFFSET_E ((uint16_t)0x01<<5)
// #define KEY_PRESSED_OFFSET_SHIFT ((uint16_t)0x01<<6)
// #define KEY_PRESSED_OFFSET_CTRL ((uint16_t)0x01<<7)

// #define RC_FRAME_LENGTH 18u
#include <Arduino.h>
#include "can.h"
#include "pid.h"

struct motor_feedback_data
{
    uint16_t ecd;
    int16_t rotor_spd;
    int16_t torque_current;
    uint8_t temperature;
};


// typedef __packed struct
// {
//  struct
//  {
//  uint16_t ch0;
//  uint16_t ch1;
//  uint16_t ch2;
//  uint16_t ch3;
//  uint8_t s1;
//  uint8_t s2;
//  }rc;
//  struct
//  {
//  int16_t x;
//  int16_t y;
//  int16_t z;
//  uint8_t press_l;
//  uint8_t press_r;
//  }mouse;
//  struct
//  {
//  uint16_t v;
//  }key;
// }RC_Ctl_t;



extern void Receive();
// extern void Transmit(float location,float velocity);
extern void Transmit(float location,float velocity);
extern void RemoteDataProcess (uint8_t *pData);
extern void setmode();
extern motor_feedback_data* get_motor_data();

// extern RC_Ctl_t getdata();

#endif