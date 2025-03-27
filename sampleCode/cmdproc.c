#include <stdio.h>
#include <string.h>
#include <math.h>
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

                /* Check checksum */
                if(!(calcChecksum(&(UARTRxBuffer[i+1]), 2))) {
                    return -3;
                }
                
                if(UARTRxBuffer[i+6] != EOF_SYM) {
                    return -4;
                }

                unsigned char txBuffer[32];
                unsigned int txIndex = 0;

                txBuffer[txIndex++] = '#';
                txBuffer[txIndex++] = 'p';
                if (sid == 't') {
                    txBuffer[txIndex++] = 't';
                    readTempSensor();

                    if (currentTemp >= 0) {
                        txBuffer[txIndex++] = '+';
                    } else {
                        txBuffer[txIndex++] = '-';
                    }

                    transmitInteger(currentTemp, txBuffer, txIndex);

                    int checksum = calcChecksum(txBuffer, txIndex);
                    char checksumStr[4];
                    snprintf(checksumStr, sizeof(checksumStr), "%03d", checksum);

                    txBuffer[txIndex++] = checksumStr[0];
                    txBuffer[txIndex++] = checksumStr[1];
                    txBuffer[txIndex++] = checksumStr[2];
                }

                txBuffer[txIndex++] = '!';

                for(int j = 0; j < txIndex; j++) {
                    txChar(txBuffer[j]);
                }

                rxBufLen = 0;
                return 0;

            default:
                return -2;
        }
    }

    return -4;
}

int transmitInteger(int num, unsigned char arr[], int index) {
    sprintf((char *)arr + index, "%d", num);
    return 1;
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
