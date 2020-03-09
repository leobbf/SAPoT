#include "SAPoTClient.h"


void GetIDfromMAC(char* MAC, uint8_t ID[6]);

/*
 * Função: Construtor do cliente SAPoT
 *  @parâmetros: Identificador da Central, tipo do cliente SAPoT, Quantidade de sensores, Quantidade de atuadores, vetor para os tipos de sensores e atuadores que estão em operação no cliente.
 *  @retorno: sem retorno.
 */
SAPoTcleint::SAPoTClient(char* centralId, uint8_t clientType, uint8_t howManySensors, uint8_t howManyActuators, uint16_t* whichSA){

	 GetIDfromMAC(WiFi.macAddress().c_str(), id);
	 type = clientType;
	 status = FALSE;
	 error = SAPOTCLIENT_SUCESS;
	 amountOfSA[0] = howManySensors;
	 amountOfSA[1] = howManyActuators;
	 SAVector = whichSA;
	 ops = 0;
	 cid = centralId;
	 timeVector = malloc((1+howManySensors+howManyActuators) * sizeof(unsigned long));
	 timeVector[0] = millis();
	 int i;
	 for(i=1; i<(1+howManySensors+howManyActuators); i++) timeVector[i] = 0;
	 requestTime[0] = 0;
	 requestTime[1] = 0;
	 requestId[0] = NON;
	 requestId[1] = NON;

}

/*
 * Função: Executa as operações com os sensores e/ou atuadores de acordo com o que for solicitado pela Central
 *  @parâmetros: float* sensorHandling(uint16 sensorID), void actuatorHandling(uint16_t actuatorID, uint16_t degreeOfPerformance), int sendingChannel(char* ServerURI , char* message, int messageLen).  
 *  @retorno: #CRIAR TABELA DE RETORNO#
 */
SAPoTcleint::InLoop(float* (*sensorHandling)(uint16_t), void (*actuatorHandling)(uint16_t, uint16_t), int (*sendingChannel)(char*, char*, int)){

	float* sensorInfo;
	int duty;
	struct msg{
		void* data;
		uint16_t length;
	};

	//Current time é definido recebendo o valor de milllis()
	timeVector[0] = millis(); 

	//Bloco de Operação referente aos sensores
	if(requestId[0] != NON){
		//CurrentTime - PreviousTime[SensorID] >= SensorRequestTime
		if((timeVector[0] - timeVector[requestId[0]]+1) >= requestTime[0]){
			//Serial de operação é acrescentado em uma unidade
			ops++;
			//A informação do sensor requisitado é recebida através sensorHandling
			sensorInfo = sensorHandling(requestId[0]);
			//Definindo o tamanho da mensagem de resposta
			if(requestId[0] == ALL) msg.length = sizeof(fixed_header_SAPoT) + amountOfSA[0] * sizeof(float);


		}

	}

	//Current time é definido recebendo o valor de milllis()
	timeVector[0] = millis(); 

	//Bloco de Operação referente aos atuadores
	if(requestId[0] != NON){

	}

}

void GetIDfromMAC(const char* MAC, uint8_t ID[6]){

  int i;
  int j=0;
  uint8_t bff[12];
    
  for(i=0; i<(strlen(MAC)); i++){
    
    if(MAC[i] == ':');
    else if(MAC[i] >= 'A'){
      bff[j] = (uint8_t) (MAC[i]- 55);
      //Serial.println(bff[j], HEX);
      j++;
    }
    else{
      bff[j] =(uint8_t) (MAC[i]-0x30);
      //Serial.println(bff[j], HEX);
      j++;    
    }
    
  } 
  
  j=0;
  for(i=0; i<11; i++){
   ID[j] =  (uint8_t)((bff[i]<<4) | (bff[++i]));
   //Serial.println(thingID[j], HEX);
   j++;
  }
  
} 