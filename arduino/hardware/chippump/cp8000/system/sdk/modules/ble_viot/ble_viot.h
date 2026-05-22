/****************************************************************************
@FILENAME:	ble_viot.h
@FUNCTION:	encoder/decoder for ble iot packet
@AUTHOR:	flege.zhang
@DATE:		2020.05.20
@COPYRIGHT(C) ZXW 2020
*****************************************************************************/

#ifndef _BLE_VIOT__H_
#define _BLE_VIOT__H_

#include <stdint.h>

/********************************MACRO DEFINE********************************/
enum en_ble_viot_ret
{
	BLE_VIOT_SUCCESS			= 0x00,
    BLE_VIOT_SAMEPACK_ERROR     = 0x01,
    BLE_VIOT_CRC_ERROR          = 0x02,
};


/*******************************STRUCT DEFINE********************************/
typedef struct
{
	uint16_t ManufactoryID;
	uint8_t PackNumber;
	uint8_t CmdType;
	uint16_t remoter_id;
	uint8_t keyValue;
	uint8_t repeat;
}str_ble_lz_viot_para;


typedef struct
{
	uint8_t		rfu[5];
	uint8_t		relay;
	uint8_t 	type;
	uint8_t 	version;
	uint8_t 	count;
	uint32_t 	addr;
	uint8_t 	group_index;
	uint8_t 	cmd;
	uint16_t 	para[3];
}str_ble_viot_para;


uint8_t ble_viot_encoder(str_ble_viot_para* opcode_para,uint8_t rand_seed,uint8_t* out_data,uint8_t* out_data_len);
uint8_t is_ble_viot_pdu(uint8_t* ble_payload,uint8_t payload_len);
uint8_t ble_viot_decoder(uint8_t* ble_payload,uint8_t payload_len,str_ble_viot_para* opcode_para);

#endif
