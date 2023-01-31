#include <Arduino.h>
#include "mo.h"

static motor_feedback_data motor_data;
void setmode()
{
    can_frame_data tx_data;
    //最大电压±30000
    tx_data.identifier = 0x101;
    tx_data.flags = TWAI_MSG_FLAG_NONE;
    tx_data.data_length_code = 8;
    tx_data.data[0] = 0xFF;
	tx_data.data[1] = 0xFF;
	tx_data.data[2] = 0xFF;
	tx_data.data[3] = 0xFF;
	tx_data.data[4] = 0xFF;
	tx_data.data[5] = 0xFF;
	tx_data.data[6] = 0xFF;
	tx_data.data[7] = 0xFC;
    ESP_CAN::CAN_Transmit(tx_data, 1);
}

void Transmit(float location,float velocity)
{
    can_frame_data tx_data;

    //最大电压±30000
    tx_data.identifier = 0x101;
    tx_data.flags = TWAI_MSG_FLAG_NONE;
    tx_data.data_length_code = 8;
    // float location = 0.0;
    // float velocity = 0.0;
    uint8_t *pbuf,*vbuf;
	pbuf=(uint8_t*)&location;
	vbuf=(uint8_t*)&velocity;
    tx_data.data[0] = *pbuf;
	tx_data.data[1] = *(pbuf+1);
	tx_data.data[2] = *(pbuf+2);
	tx_data.data[3] = *(pbuf+3);
	tx_data.data[4] = *vbuf;
	tx_data.data[5] = *(vbuf+1);
	tx_data.data[6] = *(vbuf+2);
	tx_data.data[7] = *(vbuf+3);
    int res=ESP_CAN::CAN_Transmit(tx_data, 10);
    // Serial.printf("return:%x",res);
    // float fdata[2] ;
    // fdata[0] = location;
    // fdata[1] = velocity;
    // memcpy((void*)tx_data.data,(void*)fdata,8);
    // int res=ESP_CAN::CAN_Transmit(tx_data, 100);
    // Serial.printf("return:%x",res);
    
}
void Receive()
{
    can_frame_data rx_data;
    twai_status_info_t twai_state;
    rx_data.identifier = 0x01;

    twai_get_status_info(&twai_state);
    if (twai_state.msgs_to_rx != 0)
    {
        ESP_CAN::CAN_Receive(&rx_data, 2);
        motor_data.ecd = (uint16_t)(rx_data.data[1] << 8) | rx_data.data[2];
        motor_data.rotor_spd = (uint16_t)(rx_data.data[3]<<4) | (rx_data.data[4] >> 4);
        motor_data.torque_current = (uint16_t)((rx_data.data[4] & 0x0f)<<8) | rx_data.data[5];
        motor_data.temperature = rx_data.data[6];
    }
    float a=float(motor_data.torque_current);
    float b= float(motor_data.rotor_spd);
    float c=float(motor_data.ecd);
    float vel = 60.0*(b-2048.0)/4096.0;
    float current = 20.0*(a-2048.0)/4096.0;
    float pos= 25.0*(motor_data.ecd-32768.0)/65536.0;
     Serial.printf("Encoder: %f\tRotor Speed: %f rad/s\tTorque current: %f mA\tTemp: %d Celus\n",
                   pos,
                   vel,
                   current,
                   motor_data.temperature);
}




