#ifndef SAPOTCLIENT_H
#define SAPOTCLIENT_H

#include <Arduino.h>
#include <stdint.h>

#define SAPOTCLIENT_SUCESS 0;
#define SAPOTCLIENT_FAILURE -1;

#define TRUE 1
#define FALSE 0
//Versão
#define SAPOT_VERSION 1
//Thing Type
#define CMD 0x00
#define SMCAI 0x01
#define SMCAE 0x02
#define SMRE 0x03
#define SMRH 0x04
#define SRF 0x05 
//Sensor Type
#define TMP 0x0000
#define UMD 0x0001 
#define LUX 0x0002 
#define DTP 0x0003
#define CAM 0x0004
#define VCA 0x0005
#define IAC 0x0006
#define PAC 0x0007
#define FP 0x0008
#define KWH 0x0009
//Actuator Type
#define CAC 0x0000
#define CDC 0x0001
//Request Type
#define ALL 0x0000
#define NON 0xffff

class SAPoTClient {

public:
	SAPoTClient(char* centralId, uint8_t type, uint8_t howManySensors, uint8_t howManyActuators, uint16_t* whichSA);
	int InLoop(float* (*sensorHandling)(uint16_t), void (*actuatorHandling)(uint16_t, uint16_t), int (*sendingChannel)(char*, char*, int));
	int UnpackMessage(char* message);
	void PrintError();

private:
	uint8_t id[6] // Client ID
	uint8_t type; // Client Type
	bool status; // Connection Status
	int error;
	uint8_t amountOfSA[2]; //[0] = Amount of Sensors, [1] = Amount of Actuator 
	uint16_t* SAVector; // Pointer for Sensors and Actuators Vector 
	uint16_t ops; // Operation Serial
	char* cid; //Central ID
	unsigned long* timeVector; //[0] = currentTime, [1~(amountOfSensor+amountOfActuator-1)] = previousTime
	uint32_t requestTime[2]; //[0] = sensorRequestTime, [1] = actuatorRequestTime
	uint16_t requestId[2]; // [0] = sensorRequestID, [1] = actuatorRequestID

};

#endif