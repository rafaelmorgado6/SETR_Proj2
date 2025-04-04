#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>  
#include <time.h>    
#include "cmdproc.h"

/* Internal variables */
/* Used as part of the UART emulation */
static unsigned char UARTRxBuffer[UART_RX_SIZE];
static unsigned char rxBufLen = 0; 

static unsigned char UARTTxBuffer[UART_TX_SIZE];
static unsigned char txBufLen = 0; 

static unsigned int possTempArray[] = {0, 10, -10, 30, -25, -50, 60};
static unsigned int currentTempIndex = 0;

static unsigned int possHumidArray[] = {0, 10, 20, 40, 60, 80, 100};
static unsigned int currentHumidIndex = 0;

static unsigned int possCO2Array[] = {0, 400, 1000, 2500, 5000, 10000, 20000};
static unsigned int currentCO2Index = 0;

/* Function implementation */

/* 
 * cmdProcessor
 */ 
int cmdProcessor(void) {
    int i;
    unsigned char sid;


    char sensorStr[12];
    unsigned char checksumBuffer[32];
    int chksumIdx = 0;
    int checksum = 0;
    char checksumStr[5];

    
    /* Detect empty cmd string */
    if(rxBufLen == 0)
        return -1;

    /* Find index of SOF */
    for(i = 0; i < rxBufLen; i++) {
        if(UARTRxBuffer[i] == SOF_SYM) {
            break;
        }
    }

    /* If a SOF was found, look for commands */
    if(i < rxBufLen) {
        
        switch(UARTRxBuffer[i+1]) { 
            
            //  Responds as #at+22h020c01000CKS!
            case 'A':

                // Checksum de entrada: apenas sobre CMD ('P') + DATA ('t')
                if(!(calcChecksum(&(UARTRxBuffer[i+1]), 2))) {
                    return -3;
                }

                if(UARTRxBuffer[i+6] != EOF_SYM) {
                    return -4;
                }

                checksumBuffer[chksumIdx++] = 'a';


                // Simular leitura de sensor
                int sensorValueT = readTempSensor();
                int sensorValueH = readHumidSensor();
                int sensorValueC = readCO2Sensor();

                sprintf(sensorStr, "%02d", abs(sensorValueT));

                checksumBuffer[chksumIdx++] = 't';
                checksumBuffer[chksumIdx++] = (sensorValueT >= 0) ? '+' : '-';

                for (int k = 0; sensorStr[k] != '\0'; k++) {
                    checksumBuffer[chksumIdx++] = sensorStr[k];
                }

                sprintf(sensorStr, "%03d", abs(sensorValueH));

                checksumBuffer[chksumIdx++] = 'h';

                for (int k = 0; sensorStr[k] != '\0'; k++) {
                    checksumBuffer[chksumIdx++] = sensorStr[k];
                }

                sprintf(sensorStr, "%05d", abs(sensorValueH));

                checksumBuffer[chksumIdx++] = 'c';

                for (int k = 0; sensorStr[k] != '\0'; k++) {
                    checksumBuffer[chksumIdx++] = sensorStr[k];
                }

                for (int k = 0; k < chksumIdx; k++) {
                    checksum += checksumBuffer[k];
                }
                checksum = checksum % 256;
                
                snprintf(checksumStr, sizeof(checksumStr), "%03d", checksum);

                txChar('#');
                for (int k = 0; k < chksumIdx; k++) {
                    txChar(checksumBuffer[k]);
                }
                txChar(checksumStr[0]);
                txChar(checksumStr[1]);
                txChar(checksumStr[2]);
                txChar('!');

                rxBufLen = 0;
                return 0;


            case 'P':  
                sid = UARTRxBuffer[i+2];

                if(sid != 't' && sid != 'h' && sid != 'c') {
                    return -2;
                }

                // Checksum de entrada: apenas sobre CMD ('P') + DATA ('t')
                if(!(calcChecksum(&(UARTRxBuffer[i+1]), 2))) {
                    return -3;
                }

                if(UARTRxBuffer[i+6] != EOF_SYM) {
                    return -4;
                }

                // Simular leitura de sensor
                int sensorValue = 0;
                if (sid == 't') {
                    sensorValue = readTempSensor();
                }
                if (sid == 'h') {
                    sensorValue = readHumidSensor();
                }
                if (sid == 'c') {
                    sensorValue = readCO2Sensor();
                }

                sprintf(sensorStr, "%02d", abs(sensorValue));
                //fprintf(stderr, "HERE");
                checksumBuffer[chksumIdx++] = 'p';
                //fprintf(stderr, "HERE0");

                checksumBuffer[chksumIdx++] = sid;
                checksumBuffer[chksumIdx++] = (sensorValue >= 0) ? '+' : '-';

                // Adicionar o valor do sensor (formatado como string)
                char sensorStr[12];
                sprintf(sensorStr, "%02d", abs(sensorValue));
                for (int k = 0; sensorStr[k] != '\0'; k++) {
                    checksumBuffer[chksumIdx++] = sensorStr[k];
                }

                // Calcular o checksum com base no buffer completo
                checksum = calcChecksum(checksumBuffer, chksumIdx);

                // Formatar o checksum como uma string de 3 caracteres
                snprintf(checksumStr, sizeof(checksumStr), "%03d", checksum);

                // Enviar a resposta
                txChar('#');
                for (int k = 0; k < chksumIdx; k++) {
                    txChar(checksumBuffer[k]);
                }
                txChar(checksumStr[0]);
                txChar(checksumStr[1]);
                txChar(checksumStr[2]);
                txChar('!');

                rxBufLen = 0;  // Limpar o buffer de recepção
                return 0;

            default:
                return -2;
        }
    }

    return -4;
}


int readTempSensor() {
    if (currentTempIndex >= sizeof(possTempArray) / sizeof(int)) {
        currentTempIndex = 0;
    }
    int currentTemp = possTempArray[currentTempIndex++];
    return currentTemp;
}


int readHumidSensor() {
    if (currentHumidIndex >= sizeof(possHumidArray) / sizeof(int)) {
        currentHumidIndex = 0;
    }
    int currentHumid = possHumidArray[currentHumidIndex++];
    return currentHumid;
}
    

int readCO2Sensor() {
    if (currentCO2Index >= sizeof(possCO2Array) / sizeof(int)) {
        currentCO2Index = 0;
    }
    int currentCO2 = possCO2Array[currentCO2Index++];
    return currentCO2;
}

int calcChecksum(unsigned char *buf, int nbytes) {
    unsigned int checksum = 0;

    // Soma dos valores dos bytes do buffer
    for (int i = 0; i < nbytes; i++) {
        //printf("\nbuff: %c\n", buf[i]);
        checksum += buf[i];
    }

    // Garantir que o checksum seja um valor de 8 bits (0-255)
    checksum = checksum % 256;

    // Retorna o checksum calculado
    return checksum;
}


int rxChar(unsigned char car)
{
    if (rxBufLen < UART_RX_SIZE) {
        UARTRxBuffer[rxBufLen] = car;
        rxBufLen += 1;
        return 0;        
    }    
    return -1;
}

int txChar(unsigned char car)
{
    if (txBufLen < UART_TX_SIZE) {
        UARTTxBuffer[txBufLen] = car;
        txBufLen += 1;
        return 0;        
    }    
    return -1;
}

void resetRxBuffer(void)
{
    rxBufLen = 0;        
}

void resetTxBuffer(void)
{
    txBufLen = 0;        
}

void getTxBuffer(unsigned char * buf, int * len)
{
    *len = txBufLen;
    if(txBufLen > 0) {
        memcpy(buf,UARTTxBuffer,*len);
    }        
    return;
}

int getRxBufferSize(void){
    return rxBufLen;
}

int getTxBufferSize(void){
    return txBufLen;
}