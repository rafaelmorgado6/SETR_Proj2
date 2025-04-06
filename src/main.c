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
	int len;
	unsigned char ans[256]; 
	unsigned char ansTesttemperature[][32] = {
		{'#','p','t','+','0','0','1','1','1','!'},    // #pt+00111!
		{'#','p','t','+','1','0','1','1','2','!'},    // #pt+10112!
		{'#','p','t','-','1','0','1','1','4','!'},    // #pt-10114!
		{'#','p','t','+','3','0','1','1','4','!'},    // #pt+30114!
		{'#','p','t','-','2','5','1','2','0','!'},    // #pt-25120!
		{'#','p','t','-','5','0','1','1','8','!'},    // #pt-50118!
		{'#','p','t','+','6','0','1','1','7','!'}     // #pt+60117!
	};
	unsigned char ansTesthumidity[][32] = {
		{'#','p','h','0','0','0','1','0','4','!'},
		{'#','p','h','0','1','0','1','0','5','!'},
		{'#','p','h','0','2','0','1','0','6','!'},
		{'#','p','h','0','4','0','1','0','8','!'},
		{'#','p','h','0','6','0','1','1','0','!'},
		{'#','p','h','0','8','0','1','1','2','!'},
		{'#','p','h','1','0','0','1','0','5','!'}
	};
	unsigned char ansTestco2[][32] = {
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
    char option_sensor;

    while (1) {
		resetRxBuffer();
		resetTxBuffer();

		printf("\n ╭────────────────────────────────────╮\n");
		printf(" │ Choose the type of data to ask for │\n");
		printf(" ╰┬───────────────────────────────────╯\n");
	
        printf("  ├─> a: All\n");
        printf("  ├─> l: Last 20 samples of all\n");
        printf("  ├─> t: Temperature\n");
        printf("  ├─> h: Humidity\n");
        printf("  ├─> c: CO2\n");
        printf("  ╰─> q: Sair\n\n");
        printf("   ─> Opção: ");
        scanf(" %c", &option_sensor);

        if (option_sensor == 'q') {
            printf("A sair...\n");
            break;
        }

        else if (option_sensor == 'a') {
			rxChar('#');
			rxChar('A');
			rxChar('0');
			rxChar('6');
			rxChar('5');
			rxChar('!');
		
			printf("   ─> Request Message:   #A065!\n");

			cmdProcessor();
			getTxBuffer(ans, &len);
		
			printf("   ─> Sensor Response:   ");
			for (int i = 0; i < len; i++) {
				printf("%c", ans[i]);
			}
			printf("\n");
			t_count++;
			h_count++;
			c_count++;
		}

        else if (option_sensor == 'l') {
			//  Requests how many messages are needed to get all the historical information
			rxChar('#');
			rxChar('L');
			rxChar('0');
			rxChar('7');
			rxChar('6');
			rxChar('!');

			printf("   ─> Request Message:   #L076!\n");
		
			cmdProcessor();
			getTxBuffer(ans, &len);

			printf("   ─> Sensor Response:   ");

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

        else if (option_sensor == 't') {
			rxChar('#');
			rxChar('P');
			rxChar('t');
			rxChar('1');
			rxChar('9');
			rxChar('6');
			rxChar('!');

			printf("   ─> Request Message:   #Pt196!\n");
		
			cmdProcessor();
			getTxBuffer(ans, &len);
		
			printf("   ─> Sensor Response:   ");
			for (int i = 0; i < len; i++) {
				printf("%c", ans[i]);
			}
			printf("\n");
		
			if (t_count >= 7) {
				t_count = 0;
			}

			printf("   ─> Expected Response: ");
			for (int i = 0; ansTesttemperature[t_count][i] != '\0'; i++) {
				printf("%c", ansTesttemperature[t_count][i]);
			}
			printf("\n");
			t_count++;
		}

        else if (option_sensor == 'h') {
			rxChar('#');
			rxChar('P');
			rxChar('h');
			rxChar('1');
			rxChar('8');
			rxChar('4');
			rxChar('!');

			printf("   ─> Request Message:   #Ph184!\n");
		
			cmdProcessor();
			getTxBuffer(ans, &len);
		
			printf("   ─> Sensor Response:   ");
			for (int i = 0; i < len; i++) {
				printf("%c", ans[i]);
			}
			printf("\n");
		
			if (h_count >= 7) {
				h_count = 0;
			}

			printf("   ─> Expected Response: ");
			for (int i = 0; ansTesthumidity[h_count][i] != '\0'; i++) {
				printf("%c", ansTesthumidity[h_count][i]);
			}
			printf("\n");
			h_count++;
		}

        else if (option_sensor == 'c') {
			rxChar('#');
			rxChar('P');
			rxChar('c');
			rxChar('1');
			rxChar('7');
			rxChar('9');
			rxChar('!');

			printf("   ─> Request Message:   #Pc179!\n");
		
			cmdProcessor();
			getTxBuffer(ans, &len);
		
			printf("   ─> Sensor Response:   ");
			for (int i = 0; i < len; i++) {
				printf("%c", ans[i]);
			}
			printf("\n");
		
			if (c_count >= 7) {
				c_count = 0;
			}

			printf("   ─> Expected Response: ");
			for (int i = 0; ansTestco2[c_count][i] != '\0'; i++) {
				printf("%c", ansTestco2[c_count][i]);
			}
			printf("\n");
			c_count++;
		}
	
    }

	printf("Goodbye!\n");
	
	return 0;
}
