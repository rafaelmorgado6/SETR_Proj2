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

static unsigned int possHumidArray[] = {0, 10, -10, 30, -25, -50, 60};
static unsigned int currentHumidIndex = 0;

static unsigned int possCO2Array[] = {0, 10, -10, 30, -25, -50, 60};
static unsigned int currentCO2Index = 0;

static int currentTemp = 0;  // Variável global para armazenar a temperatura atual

/* Function implementation */

/* 
 * cmdProcessor
 */ 
int cmdProcessor(void)
{
    int i;
    unsigned char sid;
    
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


                txChar('#');
                txChar('p');
                txChar('t');

                if (sensorValue >= 0) {
                    txChar('+');
                } else {
                    txChar('-');
                    sensorValue = -sensorValue;
                }

                char sensorStr[12];
                sprintf(sensorStr, "%d", sensorValue);
                for (int k = 0; sensorStr[k] != '\0'; k++) {
                    txChar(sensorStr[k]);
                }

                unsigned char checksumBuffer[20];
                int chksumIdx = 0;
                checksumBuffer[chksumIdx++] = 'p';
                checksumBuffer[chksumIdx++] = sid;
                checksumBuffer[chksumIdx++] = (sensorValue >= 0) ? '+' : '-';

                for (int k = 0; sensorStr[k] != '\0'; k++) {
                    checksumBuffer[chksumIdx++] = sensorStr[k];
                }

                int checksum = 0;
                for (int k = 0; k < chksumIdx; k++) {
                    checksum += checksumBuffer[k];
                }
                checksum = checksum % 256;

                char checksumStr[5];
                snprintf(checksumStr, sizeof(checksumStr), "%03d", checksum);

                txChar(checksumStr[0]);
                txChar(checksumStr[1]);
                txChar(checksumStr[2]);

                txChar('!');

                rxBufLen = 0;
                return 0;

            default:
                return -2;
        }
    }

    return -4;
}

int transmitInteger(int value, unsigned char *buffer, int *index) {
    char tempStr[10];
    sprintf(tempStr, "%d", value);

    for (int i = 0; tempStr[i] != '\0'; i++) {
        buffer[*index] = tempStr[i];
        (*index)++;
    }

    return 0;
}


int readTempSensor() {
    if (++currentTempIndex >= sizeof(possTempArray) / sizeof(int)) {
        currentTempIndex = 0;
    }
    currentTemp = possTempArray[currentTempIndex];
    return currentTemp;
}

int calcChecksum(unsigned char * buf, int nbytes) {
    unsigned int checksum = 0;

    for(int i = 0; i < nbytes; i++){
        checksum += buf[i];
    }

    checksum = checksum % 256;

    unsigned char checksumStr[4];
    snprintf((char *)checksumStr, sizeof(checksumStr), "%03u", checksum);

    if(buf[nbytes] == checksumStr[0] && buf[nbytes+1] == checksumStr[1] && buf[nbytes+2] == checksumStr[2]){
        return 1;  // Checksum válida
    }

    return 0;  // Checksum inválida       
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
    return;
}

void resetTxBuffer(void)
{
    txBufLen = 0;        
    return;
}

void getTxBuffer(unsigned char * buf, int * len)
{
    *len = txBufLen;
    if(txBufLen > 0) {
        memcpy(buf,UARTTxBuffer,*len);
    }        
    return;
}
