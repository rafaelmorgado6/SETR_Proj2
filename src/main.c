/* ******************************************************/
/* SETR 23/24, Paulo Pedreiras                          */
/* 		Sample code for Assignment 2					*/
/*   	A few tests to the cmdProcessor to illustrate	*/
/*      how the the tests can be carried out.         	*/
/*														*/
/* Note that I'm not using Unity! That is part of your 	*/
/*		work. 											*/
/*                                                      */
/* Compile with: gcc cmdproc.c main.c -o main           */
/*	Feel free to use flags such as -Wall -Wpedantic ...	*/
/*	and it is a good idea to create a makefile			*/
/*                                                      */
/* ******************************************************/
#include <stdio.h>
#include <string.h>
#include "modules/cmdproc.h"


int main(void) 
{
	int i,len, err;
	unsigned char ans[256]; 
	unsigned char ansTest1[]={'#','p','t', '+', '2', '1', '1', '1', '4','!'};
	unsigned char ansTesttemperature[][12] = {
		{'#','p','t','+','0','0','1','1','1','!'},   // #pt+0063!
		{'#','p','t','+','1','0','1','1','2','!'},    // #pt+10112!
		{'#','p','t','-','1','0','1','1','4','!'},    // #pt-10114!
		{'#','p','t','+','3','0','1','1','4','!'},    // #pt+30114!
		{'#','p','t','-','2','5','1','2','0','!'},    // #pt-25120!
		{'#','p','t','-','5','0','1','1','8','!'},    // #pt-50118!
		{'#','p','t','+','6','0','1','1','7','!'}     // #pt+60117!
	};
	unsigned char ansTesthumidity[][12] = {
		{'#','p','h','0','0','0','5','6','!'},
		{'#','p','h','1','0','0','5','7','!'},
		{'#','p','h','2','0','0','5','8','!'},
		{'#','p','h','4','0','0','6','0','!'},
		{'#','p','h','6','0','0','6','2','!'},
		{'#','p','h','8','0','0','6','4','!'},
		{'#','p','h','1','0','0','1','0','5','!'},
	};
	unsigned char ansTestco2[][12] = {
		{'#','p','c','0','0','0','5','1','!'},
		{'#','p','c','4','0','0','1','0','3','!'},
		{'#','p','c','1','0','0','0','1','4','8','!'},
		{'#','p','c','2','5','0','0','1','5','4','!'},
		{'#','p','c','5','0','0','0','1','5','2','!'},
		{'#','p','c','1','0','0','0','0','1','9','6','!'},
		{'#','p','c','2','0','0','0','0','1','9','7','!'},
	};
	int t_count = 0;
	int h_count = 0;
	int c_count = 0;
	
	printf("\n Smart Sensor interface emulation \n");
	printf(" \t - simple illustration of interface and use \n\n\r");
	
	/* Init UART RX and TX buffers */
	resetTxBuffer();
	resetRxBuffer();
	
	/* Test 0*/
    char option_sensor;
	char option_command;

    while (1) {
		printf("\nEscolha o tipo de comando:\n");
        printf("  A - Dados dos 3 sensores\n");
        printf("  P - Dados de 1 sensor\n");
        printf("  L - 20 ultimos dados de cada sensor\n");
        printf("  q - Sair\n");
        printf("Opção: ");
        scanf(" %c", &option_command);

        printf("\nEscolha o tipo de dado a simular:\n");
        printf("  t - Temperatura\n");
        printf("  h - Humidade (não implementado)\n");
        printf("  c - CO2 (não implementado)\n");
        printf("  q - Sair\n");
        printf("Opção: ");
        scanf(" %c", &option_sensor);

        if (option_sensor == 'q') {
            printf("A sair...\n");
            break;
        }

        if (option_sensor == 't') {
			
			resetRxBuffer();
			resetTxBuffer();
		
			rxChar('#');
			rxChar(option_command);
			rxChar('t');
			rxChar('1');
			rxChar('9');
			rxChar('6');
			rxChar('!');
		
			cmdProcessor();
			getTxBuffer(ans, &len);
		
			printf("Resposta do sensor: ");
			for (int i = 0; i < len; i++) {
				printf("%c", ans[i]);
			}
			printf("\n");
		
			if (t_count >= 7) {
				t_count = 0;
			}

			printf("Esperado: ");
			for (int i = 0; ansTesttemperature[t_count][i] != '\0'; i++) {
				printf("%c", ansTesttemperature[t_count][i]);
			}
			printf("\n");
			t_count++;
		}
		if (option_sensor == 'h') {
			
			resetRxBuffer();
			resetTxBuffer();
		
			rxChar('#');
			rxChar(option_command);
			rxChar('h');
			rxChar('1');
			rxChar('9');
			rxChar('6');
			rxChar('!');
		
			cmdProcessor();
			getTxBuffer(ans, &len);
		
			printf("Resposta do sensor: ");
			for (int i = 0; i < len; i++) {
				printf("%c", ans[i]);
			}
			printf("\n");
		
			if (t_count >= 7) {
				t_count = 0;
			}

			printf("Esperado: ");
			for (int i = 0; ansTesthumidity[t_count][i] != '\0'; i++) {
				printf("%c", ansTesthumidity[t_count][i]);
			}
			printf("\n");
			t_count++;
		}
		if (option_sensor == 'c') {
			
			resetRxBuffer();
			resetTxBuffer();
		
			rxChar('#');
			rxChar(option_command);
			rxChar('c');
			rxChar('1');
			rxChar('9');
			rxChar('6');
			rxChar('!');
		
			cmdProcessor();
			getTxBuffer(ans, &len);
		
			printf("Resposta do sensor: ");
			for (int i = 0; i < len; i++) {
				printf("%c", ans[i]);
			}
			printf("\n");
		
			if (t_count >= 7) {
				t_count = 0;
			}

			printf("Esperado: ");
			for (int i = 0; ansTestco2[t_count][i] != '\0'; i++) {
				printf("%c", ansTestco2[t_count][i]);
			}
			printf("\n");
			t_count++;
		}
	
    }

	/* Test 1 */
	
	printf("Test1 - check the answer to a valid Pt command\n");
	
	/* 1 - send the command */
	rxChar('#');
	rxChar('P');
	rxChar('t');
	rxChar('1');
	rxChar('9');
	rxChar('6');
	rxChar('!');
			
	/* 2 - Process the comand and check the answer */
	
	cmdProcessor();
	
	getTxBuffer(ans,&len);
	if(memcmp(ans,ansTest1,len)) {
		printf("Test 1 failed\n");
	} else {
		printf("Test 1 succeeded\n");
	}	
	
	/* You can print the answer to see what is wrong, if necessary */
	printf("\t Received answer:");
	for(i=0; i < len; i++) {
		printf("%c", ans[i]);
	}
	printf("\n\t Expected answer:");
	i=sizeof(ansTest1);
	for(i=0; i< len; i++) {
		printf("%c", ansTest1[i]);
	}
	printf("\n");
	
	
	/* Test 2 */
	
	printf("Test2 - check the answer to a transmission omission/error \n");
	
	/* 1 - send the command */
	rxChar('#');
	rxChar('P');
	// rxChar('t'); - simulates missing character, emulates a tx error 
	rxChar('1');
	rxChar('9');
	rxChar('6');
	rxChar('!');
			
	/* 2 - Process the comand and check the answer */
	
	err=cmdProcessor();
		
	if(err == -2) {
		printf("Test 2 succeeded, as omission was detected\n");
	} else {
		printf("Test 2 failed, as omission was not detected\n");
	}		
	
	/* Much more tests are needed. Unity shoul be used for it. */
	
	return 0;
}
