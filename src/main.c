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
	unsigned char ansTestT[][16] = {
		{'#','p','t','+','0','0','1','1','1','!'},    // #pt+00111!
		{'#','p','t','+','1','0','1','1','2','!'},    // #pt+10112!
		{'#','p','t','-','1','0','1','1','4','!'},    // #pt-10114!
		{'#','p','t','+','3','0','1','1','4','!'},    // #pt+30114!
		{'#','p','t','-','2','5','1','2','0','!'},    // #pt-25120!
		{'#','p','t','-','5','0','1','1','8','!'},    // #pt-50118!
		{'#','p','t','+','6','0','1','1','7','!'}     // #pt+60117!
	};
	unsigned char ansTestH[][16] = {
		{'#','p','h','0','0','0','1','0','4','!'},
		{'#','p','h','0','1','0','1','0','5','!'},
		{'#','p','h','0','2','0','1','0','6','!'},
		{'#','p','h','0','4','0','1','0','8','!'},
		{'#','p','h','0','6','0','1','1','0','!'},
		{'#','p','h','0','8','0','1','1','2','!'},
		{'#','p','h','1','0','0','1','0','5','!'}
	};
	unsigned char ansTestC[][16] = {
		{'#','p','h','0','0','0','0','0','1','9','5','!'},
		{'#','p','h','0','0','4','0','0','1','9','9','!'},
		{'#','p','h','0','1','0','0','0','1','9','6','!'},
		{'#','p','h','0','2','5','0','0','2','0','2','!'},
		{'#','p','h','0','5','0','0','0','2','0','0','!'},
		{'#','p','h','1','0','0','0','0','1','9','6','!'},
		{'#','p','h','2','0','0','0','0','1','9','7','!'}
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
    char opcao;

    while (1) {
		resetRxBuffer();
		resetTxBuffer();

        printf("\nChoose the type of data to ask for:\n");
        printf("  a - All\n");
        printf("  l - Last 20 samples of all\n");
        printf("  t - Temperature\n");
        printf("  h - Humidity\n");
        printf("  c - CO2\n");
        printf("  q - Sair\n");
        printf("Opção: ");
        scanf(" %c", &opcao);

        if (opcao == 'q') {
            printf("A sair...\n");
            break;
        }

        if (opcao == 'a') {
			rxChar('#');
			rxChar('A');
			rxChar('0');
			rxChar('6');
			rxChar('5');
			rxChar('!');
		
			cmdProcessor();
			getTxBuffer(ans, &len);
		
			printf("Resposta do sensor: ");
			for (int i = 0; i < len; i++) {
				printf("%c", ans[i]);
			}
			printf("\n");
			t_count++;
		}

        else if (opcao == 'l') {
			//  Requests how many messages are needed to get all the historical information
			rxChar('#');
			rxChar('L');
			rxChar('0');
			rxChar('7');
			rxChar('6');
			rxChar('!');
		
			cmdProcessor();
			getTxBuffer(ans, &len);

			printf("Resposta do sensor:");

			for (int i = 0; i < len; i++) {
				printf("%c", ans[i]);
			}
			printf("\n");

			int numMessages = (ans[2] - '0') * 10 + (ans[3] - '0');
		
			printf("Serão precisas %i mensagens.\n", numMessages);

			for (unsigned int messageIdx = 0; messageIdx < numMessages; messageIdx++) {
				resetRxBuffer();
				resetTxBuffer();
				//  Send the message request with the ID of the message
				char sizeStr[5];
				unsigned char checksumBuffer[256];
				int chksumIdx = 0;
				int checksum = 0;
				char checksumStr[5];

				snprintf(sizeStr, sizeof(sizeStr), "%02d", messageIdx);

                checksumBuffer[chksumIdx++] = 'L';
				checksumBuffer[chksumIdx++] = sizeStr[0];
				checksumBuffer[chksumIdx++] = sizeStr[1];
				
                for (int k = 0; k < chksumIdx; k++) {
                    checksum += checksumBuffer[k];
                }
                checksum = checksum % 256;
                
                snprintf(checksumStr, sizeof(checksumStr), "%03d", checksum);

                rxChar('#');
                for (int k = 0; k < chksumIdx; k++) {
                    rxChar(checksumBuffer[k]);
                }
                rxChar(checksumStr[0]);
                rxChar(checksumStr[1]);
                rxChar(checksumStr[2]);
                rxChar('!');

				//  Receive the data from the message and store it
				cmdProcessor();
				getTxBuffer(ans, &len);
	
				printf("%d - Resposta do sensor: ", messageIdx);
	
				for (int i = 0; i < len; i++) {
					printf("%c", ans[i]);
				}

				printf("\n");
			}



		}

        else if (opcao == 't') {
			rxChar('#');
			rxChar('P');
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
			for (int i = 0; ansTestT[t_count][i] != '\0'; i++) {
				printf("%c", ansTestT[t_count][i]);
			}
			printf("\n");
			t_count++;
		}

        else if (opcao == 'h') {
			rxChar('#');
			rxChar('P');
			rxChar('h');
			rxChar('1');
			rxChar('8');
			rxChar('4');
			rxChar('!');
		
			cmdProcessor();
			getTxBuffer(ans, &len);
		
			printf("Resposta do sensor: ");
			for (int i = 0; i < len; i++) {
				printf("%c", ans[i]);
			}
			printf("\n");
		
			if (h_count >= 7) {
				h_count = 0;
			}

			printf("Esperado: ");
			for (int i = 0; ansTestH[h_count][i] != '\0'; i++) {
				printf("%c", ansTestH[h_count][i]);
			}
			printf("\n");
			h_count++;
		}

        else if (opcao == 'c') {
			rxChar('#');
			rxChar('P');
			rxChar('c');
			rxChar('1');
			rxChar('7');
			rxChar('9');
			rxChar('!');
		
			cmdProcessor();
			getTxBuffer(ans, &len);
		
			printf("Resposta do sensor: ");
			for (int i = 0; i < len; i++) {
				printf("%c", ans[i]);
			}
			printf("\n");
		
			if (c_count >= 7) {
				c_count = 0;
			}

			printf("Esperado: ");
			for (int i = 0; ansTestC[c_count][i] != '\0'; i++) {
				printf("%c", ansTestC[c_count][i]);
			}
			printf("\n");
			c_count++;
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
