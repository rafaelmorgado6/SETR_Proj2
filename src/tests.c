//gcc tests.c modules/cmdproc.c Unity/src/unity.c -o test
#include "Unity/src/unity.h"
#include "modules/cmdproc.h"


/** \file tests.c
*   \brief Unit tests for Assignment 2
**
*        This file tests all the funtions on the 
*       CMD_Proc module developped for this assignment
**
* \author Pedro Ramos, n.º 107348
* \author Rafael Morgado, n.º 104277
* \date 06/04/2025
*/

/**
 * @brief Set up function executed before each test.
 */
void setUp(void) {
    resetTxBuffer();
    resetRxBuffer();
}

/**
 * @brief Tear down function executed after each test.
 */
void tearDown(void) {
}  

/**
 * @brief Test the temperature command processor.
 */
void test_Temperature(void){

    printf("\n");
    printf(" ╭─────────────────────────────────────────────╮\n");
    printf(" │  - == ===    Test Temperature    === == -   │\n");
    printf(" ╰─────────────────────────────────────────────╯\n");
    
	unsigned char ansTest[][32] = {
		{'#','p','t','+','0','0','1','1','1','!'},    // #pt+00111!
		{'#','p','t','+','1','0','1','1','2','!'},    // #pt+10112!
		{'#','p','t','-','1','0','1','1','4','!'},    // #pt-10114!
		{'#','p','t','+','3','0','1','1','4','!'},    // #pt+30114!
		{'#','p','t','-','2','5','1','2','0','!'},    // #pt-25120!
		{'#','p','t','-','5','0','1','1','8','!'},    // #pt-50118!
	};

    for (int n = 0; n < 6; n++) {
        resetTxBuffer();
        resetRxBuffer();

        rxChar('#');
        rxChar('P');
        rxChar('t');
        rxChar('1');
        rxChar('9');
        rxChar('6');
        rxChar('!');

        // chama cmdProcessor()
        int result = cmdProcessor();
        
        // verifica que a função cmdProcessor() retorna 0 (sucesso)
        TEST_ASSERT_EQUAL(0, result);

        // obter a resposta gerada
        unsigned char ans[32];
        int len;
        getTxBuffer(ans, &len);

        // resposta esperada: '#pt+10112!' (sensor lẽ +10)
        // Imprimir a resposta esperada e gerada
        printf("   ─> Expected response:  ");
        for (int i=0; i < sizeof(ansTest[n]); i++){
            printf("%c", ansTest[n][i]);
        }   
        printf("\n   ─> Generated response: ");
        for (int i = 0; i < len; i++) {
            printf("%c", ans[i]); 
        }
        printf("\n\n");

        // verifica se a resposta gerada é igual à resposta esperada
        TEST_ASSERT_EQUAL_MEMORY(ansTest[n], ans, len);
    }
}

/**
 * @brief Test the humidity command processor.
 */
void test_Humidity(void){

    printf("\n");
    printf(" ╭─────────────────────────────────────────────╮\n");
    printf(" │  - == ===     Test Humidity      === == -   │\n");
    printf(" ╰─────────────────────────────────────────────╯\n");
    
	unsigned char ansTest[][32] = {
		{'#','p','h','0','0','0','1','0','4','!'},
		{'#','p','h','0','1','0','1','0','5','!'},
		{'#','p','h','0','2','0','1','0','6','!'},
		{'#','p','h','0','4','0','1','0','8','!'},
		{'#','p','h','0','6','0','1','1','0','!'},
		{'#','p','h','0','8','0','1','1','2','!'},
	};

    for (int n = 0; n < 6; n++) {
        resetTxBuffer();
        resetRxBuffer();
        
        rxChar('#');
        rxChar('P');
        rxChar('h');
        rxChar('1');
        rxChar('8');
        rxChar('4');
        rxChar('!');

        // chama cmdProcessor()
        int result = cmdProcessor();
        
        // verifica que a função cmdProcessor() retorna 0 (sucesso)
        TEST_ASSERT_EQUAL(0, result);

        // obter a resposta gerada
        unsigned char ans[32];
        int len;
        getTxBuffer(ans, &len);

        // resposta esperada: '#pt+10112!' (sensor lẽ +10)
        // Imprimir a resposta esperada e gerada
        printf("   ─> Expected response:  ");
        for (int i=0; i < sizeof(ansTest[n]); i++){
            printf("%c", ansTest[n][i]);
        }   
        printf("\n   ─> Generated response: ");
        for (int i = 0; i < len; i++) {
            printf("%c", ans[i]); 
        }
        printf("\n\n");

        // verifica se a resposta gerada é igual à resposta esperada
        TEST_ASSERT_EQUAL_MEMORY(ansTest[n], ans, len);
    }
}

/**
 * @brief Test the CO2 command processor.
 */
void test_CO2(void){

    printf("\n");
    printf(" ╭─────────────────────────────────────────────╮\n");
    printf(" │  - == ===        Test CO2        === == -   │\n");
    printf(" ╰─────────────────────────────────────────────╯\n");
    
	unsigned char ansTest[][32] = {
		{'#','p','c','0','0','0','0','0','1','9','5','!'},
		{'#','p','c','0','0','4','0','0','1','9','9','!'},
		{'#','p','c','0','1','0','0','0','1','9','6','!'},
		{'#','p','c','0','2','5','0','0','2','0','2','!'},
		{'#','p','c','0','5','0','0','0','2','0','0','!'},
		{'#','p','c','1','0','0','0','0','1','9','6','!'},
	};

    for (int n = 0; n < 6; n++) {
        resetTxBuffer();
        resetRxBuffer();
        
        rxChar('#');
        rxChar('P');
        rxChar('c');
        rxChar('1');
        rxChar('7');
        rxChar('9');
        rxChar('!');

        // chama cmdProcessor()
        int result = cmdProcessor();
        
        // verifica que a função cmdProcessor() retorna 0 (sucesso)
        TEST_ASSERT_EQUAL(0, result);

        // obter a resposta gerada
        unsigned char ans[32];
        int len;
        getTxBuffer(ans, &len);

        // resposta esperada: '#pt+10112!' (sensor lẽ +10)
        // Imprimir a resposta esperada e gerada
        printf("   ─> Expected response:  ");
        for (int i=0; i < sizeof(ansTest[n]); i++){
            printf("%c", ansTest[n][i]);
        }   
        printf("\n   ─> Generated response: ");
        for (int i = 0; i < len; i++) {
            printf("%c", ans[i]); 
        }
        printf("\n\n");

        // verifica se a resposta gerada é igual à resposta esperada
        TEST_ASSERT_EQUAL_MEMORY(ansTest[n], ans, len);
    }
}

/**
 * @brief Test the "all" command processor.
 */
void test_all(void){

    printf("\n");
    printf(" ╭─────────────────────────────────────────────╮\n");
    printf(" │  - == ===    Test All command    === == -   │\n");
    printf(" ╰─────────────────────────────────────────────╯\n");

    unsigned char ansTest[32] = {'#','a','t','+','6','0','h','1','0','0','c','2','0','0','0','0','1','8','0','!'};

    resetTxBuffer();
    resetRxBuffer();
    rxChar('#');
    rxChar('A');
    rxChar('0');
    rxChar('6');
    rxChar('5');
    rxChar('!');

    int result = cmdProcessor();
    printf("   ─> cmdProcessor returned -> %d\n\n", result);
    TEST_ASSERT_EQUAL(0, result); // checks if returns 0

    // obter a resposta gerada
    unsigned char ans[32];
    int len;
    getTxBuffer(ans, &len);

    // Imprimir a resposta esperada e gerada
    printf("   ─> Expected response:  ");
    for (int i=0; i < sizeof(ansTest); i++){
        printf("%c", ansTest[i]);
    }   
    printf("\n   ─> Generated response: ");
    for (int i = 0; i < len; i++) {
        printf("%c", ans[i]); 
    }
    printf("\n\n");

    // verifica se a resposta gerada é igual à resposta esperada
    TEST_ASSERT_EQUAL_MEMORY(ansTest, ans, len);
}

/**
 * @brief Test the history command processor.
 */
void test_history(void){

    printf("\n");
    printf(" ╭─────────────────────────────────────────────╮\n");
    printf(" │  - == === Test L History command === == -   │\n");
    printf(" ╰─────────────────────────────────────────────╯\n");

    //  Answer for size message
    unsigned char ansTest[32] = {'#','l','0','6','2','1','0','!'};

    unsigned char ansFollowUp[][32] = {
        {'#', 'l', 't', '+', '0', '0', '+', '1', '0', '-', '1', '0', '+', '3', '0', '-', '0', '6', '4', '!'}, // Message 0
        {'#', 'l', '2', '5', '-', '5', '0', '+', '6', '0', 'h', '0', '0', '0', '0', '1', '0', '7', '9', '!'}, // Message 1
        {'#', 'l', '0', '0', '2', '0', '0', '4', '0', '0', '6', '0', '0', '8', '0', '1', '0', '3', '3', '!'}, // Message 2
        {'#', 'l', '0', '0', 'c', '0', '0', '0', '0', '0', '0', '0', '4', '0', '0', '0', '0', '6', '7', '!'}, // Message 3
        {'#', 'l', '1', '0', '0', '0', '0', '2', '5', '0', '0', '0', '5', '0', '0', '0', '0', '2', '5', '!'}, // Message 4
        {'#', 'l', '1', '0', '0', '0', '0', '2', '0', '0', '0', '0', '0', '7', '9', '!'}                      // Message 5
    };
        
    
    resetTxBuffer();
    resetRxBuffer();
    rxChar('#');
    rxChar('L');
    rxChar('0');
    rxChar('7');
    rxChar('6');
    rxChar('!');

    int result = cmdProcessor();
    printf("   ─> cmdProcessor returned -> %d\n\n", result);
    TEST_ASSERT_EQUAL(0, result); // checks if returns 0

    // obter a resposta gerada
    unsigned char ans[32];
    int len;
    getTxBuffer(ans, &len);

    int numMessages = (ans[2] - '0') * 10 + (ans[3] - '0');


    // Imprimir a resposta esperada e gerada
    printf("   ─> Expected response:  ");
    for (int i=0; i < sizeof(ansTest); i++){
        printf("%c", ansTest[i]);
    }   
    printf("\n   ─> Generated response: ");
    for (int i = 0; i < len; i++) {
        printf("%c", ans[i]); 
    }

    TEST_ASSERT_EQUAL_MEMORY(ansTest, ans, len);
    printf("\n");


    for (int n = 0; n < numMessages; n++) {
        resetTxBuffer();
        resetRxBuffer();

        rxChar('#');
        rxChar('L');
        rxChar('0');
        rxChar(n + '0');
        rxChar('1');
        rxChar('7');
        rxChar(n + '2');
        rxChar('!');

        int result = cmdProcessor();
        TEST_ASSERT_EQUAL(0, result); // checks if returns 0

        // obter a resposta gerada
        unsigned char ans[32];
        int len;
        getTxBuffer(ans, &len);

        // Imprimir a resposta esperada e gerada
        printf("\n   ─> Expected response:  ");
        for (int i=0; i < sizeof(ansFollowUp[n]); i++){
            printf("%c", ansFollowUp[n][i]);
        }   
        printf("\n   ─> Generated response: ");
        for (int i = 0; i < len; i++) {
            printf("%c", ans[i]); 
        }

        // verifica se a resposta gerada é igual à resposta esperada
        TEST_ASSERT_EQUAL_MEMORY(ansFollowUp[n], ans, len);
    }
    printf("\n\n");
}

/**
 * @brief Test the reset command processor.
 */
void test_reset(void){

    printf("\n");
    printf(" ╭─────────────────────────────────────────────╮\n");
    printf(" │  - == ===   Test Reset command   === == -   │\n");
    printf(" ╰─────────────────────────────────────────────╯\n");

    //  Answer for size message
    unsigned char ansTest[32] = {'#','r','1','1','4','!'};
    unsigned char ansMessage[32] = {'#','l','0','0','2','0','4','!'};

    resetTxBuffer();
    resetRxBuffer();
    rxChar('#');
    rxChar('R');
    rxChar('0');
    rxChar('8');
    rxChar('2');
    rxChar('!');

    int result = cmdProcessor();
    printf("   ─> Reset returned -> %d\n\n", result);
    TEST_ASSERT_EQUAL(0, result); // checks if returns 0


    // obter a resposta gerada
    unsigned char ans[32];
    int len;
    getTxBuffer(ans, &len);

    // Imprimir a resposta esperada e gerada
    printf("   ─> Expected response:  ");
    for (int i=0; i < sizeof(ansTest); i++){
        printf("%c", ansTest[i]);
    }   
    printf("\n   ─> Generated response: ");
    for (int i = 0; i < len; i++) {
        printf("%c", ans[i]); 
    }

    TEST_ASSERT_EQUAL_MEMORY(ansTest, ans, len);
    printf("\n");

    resetTxBuffer();
    resetRxBuffer();

    rxChar('#');
    rxChar('L');
    rxChar('0');
    rxChar('7');
    rxChar('6');
    rxChar('!');

    result = cmdProcessor();

    getTxBuffer(ans, &len);

    printf("   ─> List all history returned -> %d\n\n", result);
    TEST_ASSERT_EQUAL(0, result); // checks if returns 0


    // Imprimir a resposta esperada e gerada
    printf("   ─> Expected response:  ");
    for (int i=0; i < sizeof(ansMessage); i++){
        printf("%c", ansMessage[i]);
    }   
    printf("\n   ─> Generated response: ");
    for (int i = 0; i < len; i++) {
        printf("%c", ans[i]); 
    }

    TEST_ASSERT_EQUAL_MEMORY(ansMessage, ans, len);
    printf("\n");

    int numMessages = (ans[2] - '0') * 10 + (ans[3] - '0');

    TEST_ASSERT_EQUAL(0, numMessages);

    printf("\n\n");
}

/**
 * @brief Test an invalid command.
 */
void test_invalidcommand(void){

    printf("\n");
    printf(" ╭─────────────────────────────────────────────╮\n");
    printf(" │  - == ===  Test invalid command  === == -   │\n");
    printf(" ╰─────────────────────────────────────────────╯\n");

    resetTxBuffer();
    resetRxBuffer();
    rxChar('#');
    rxChar('X'); // invalid command
    rxChar('t');
    rxChar('1');
    rxChar('9');
    rxChar('6');
    rxChar('!');

    int result = cmdProcessor();
    printf("cmdProcessor returned -> %d\n\n", result);
    TEST_ASSERT_EQUAL(-2, result); // checks if returns -2 (invalid command)
}

/**
 * @brief Test checksum calculation with valid data.
 */
void test_calcChecksum_valid(void) {

    printf("\n");
    printf(" ╭─────────────────────────────────────────────╮\n");
    printf(" │  - == ===  Test valid checksum   === == -   │\n");
    printf(" ╰─────────────────────────────────────────────╯\n");

    unsigned char buf[] = {'P', 't'};
    
    int nbytes = sizeof(buf);

    int result = calcChecksum(buf, nbytes);

    printf("Result of calcChecksum: %d\n", result);  
    
    TEST_ASSERT_EQUAL(196, result);  
}


/**
 * @brief Test checksum calculation with invalid data.
 */
void test_calcChecksum_invalid(void) {

    printf("\n");
    printf(" ╭─────────────────────────────────────────────╮\n");
    printf(" │  - == === Test invalid checksum  === == -   │\n");
    printf(" ╰─────────────────────────────────────────────╯\n");

    unsigned char buf[] = {'P', 'u'};  //t->116
                                      // u->117  

    int nbytes = sizeof(buf);

    int result = calcChecksum(buf, nbytes);

    printf("Result of calcChecksum: %d\n", result);
    
    TEST_ASSERT_NOT_EQUAL(196, result); 
}

/**
 * @brief Test reset of buffers.
 */
void test_reset_buffers(void){
    printf("\n");
    printf(" ╭─────────────────────────────────────────────╮\n");
    printf(" │  - == ===  Test  reset buffers   === == -   │\n");
    printf(" ╰─────────────────────────────────────────────╯\n");
    
    resetTxBuffer();
    resetRxBuffer();
    rxChar('#');
    rxChar('P');
    rxChar('t');
    rxChar('1');
    rxChar('9');
    rxChar('6');
    rxChar('!');

    cmdProcessor(); 

    resetRxBuffer();
    resetTxBuffer();

    if (getRxBufferSize() == 0 && getTxBufferSize() == 0) {
        printf("Test succeeded, buffers reseted successfuly\n");
    }else {
        printf("Test failed, buffers did not reseted successfuly\n");
    }
    
    TEST_ASSERT_EQUAL(0, getRxBufferSize());
    TEST_ASSERT_EQUAL(0, getTxBufferSize());
}

/**
 * @brief Test for missing characters in the command.
 */
void test_incomplete_command(void) {
    printf("\n");
    printf(" ╭─────────────────────────────────────────────╮\n");
    printf(" │ - = =Test missing character in command= = - │\n");
    printf(" ╰─────────────────────────────────────────────╯\n");
    
    resetTxBuffer();
    resetRxBuffer();
    // 1 - Envia o comando
    rxChar('#');
    rxChar('P');
    // rxChar('t');
    rxChar('1');
    rxChar('9');
    rxChar('6');
    rxChar('!');

    int err = cmdProcessor();
        
    if (err == -2) {
        printf("Test succeeded, an omission was detected\n");
    }else {
        printf("Test failed, as omission was not detected\n");
    }

    TEST_ASSERT_EQUAL(-2, err);
}


/**
 * @brief Test buffer overflow in RX buffer.
 */
 void test_RxBufferOverflow(void) {
    printf("\n");
    printf(" ╭─────────────────────────────────────────────╮\n");
    printf(" │  - == ===   Test RX Buffer Overflow === == -│\n");
    printf(" ╰─────────────────────────────────────────────╯\n");
    
    // Fill buffer to capacity (should succeed)
    for (int i = 0; i < UART_RX_SIZE; i++) {
        TEST_ASSERT_EQUAL(0, rxChar('A'));
    }
    
    // Next character should fail (buffer full)
    TEST_ASSERT_EQUAL(-1, rxChar('B'));
    
    // Verify buffer size
    TEST_ASSERT_EQUAL(UART_RX_SIZE, getRxBufferSize());
    
    resetRxBuffer();
    printf("   ─> Test passed: RX buffer overflow handled correctly\n\n");
}

/**
 * @brief Test buffer overflow in TX buffer.
 */
void test_TxBufferOverflow(void) {
    printf("\n");
    printf(" ╭─────────────────────────────────────────────╮\n");
    printf(" │  - == ===   Test TX Buffer Overflow === == -│\n");
    printf(" ╰─────────────────────────────────────────────╯\n");
    
    // Fill buffer to capacity (should succeed)
    for (int i = 0; i < UART_TX_SIZE; i++) {
        TEST_ASSERT_EQUAL(0, txChar('A'));
    }
    
    // Next character should fail (buffer full)
    TEST_ASSERT_EQUAL(-1, txChar('B'));
    
    // Verify buffer size
    TEST_ASSERT_EQUAL(UART_TX_SIZE, getTxBufferSize());
    
    resetTxBuffer();
    printf("   ─> Test passed: TX buffer overflow handled correctly\n\n");
}

/**
 * @brief Test command with invalid checksum.
 */
void test_InvalidChecksum(void) {
    printf("\n");
    printf(" ╭─────────────────────────────────────────────╮\n");
    printf(" │  - == ===  Test Invalid Checksum  === == -  │\n");
    printf(" ╰─────────────────────────────────────────────╯\n");
    
    resetTxBuffer();
    resetRxBuffer();
    // Send command with invalid checksum (changed last digit)
    rxChar('#');
    rxChar('P');
    rxChar('t');
    rxChar('1');
    rxChar('9');
    rxChar('7'); // Changed from 6 to 7 to make checksum invalid
    rxChar('!');

    int result = cmdProcessor();
    printf("   ─> cmdProcessor returned -> %d\n\n", result);
    
    // Should return -3 (checksum error)
    TEST_ASSERT_EQUAL(-3, result);
    
    printf("   ─> Test passed: Invalid checksum detected\n\n");
}

/**
 * @brief Test command missing EOF symbol.
 */
void test_MissingEOF(void) {
    printf("\n");
    printf(" ╭─────────────────────────────────────────────╮\n");
    printf(" │  - == ===    Test Missing EOF     === == -  │\n");
    printf(" ╰─────────────────────────────────────────────╯\n");
    
    resetTxBuffer();
    resetRxBuffer();
    // Send command without '!'
    rxChar('#');
    rxChar('P');
    rxChar('t');
    rxChar('1');
    rxChar('9');
    rxChar('6'); // Missing '!'

    int result = cmdProcessor();
    printf("   ─> cmdProcessor returned -> %d\n\n", result);
    
    // Should return -4 (format error)
    TEST_ASSERT_EQUAL(-4, result);
    
    printf("   ─> Test passed: Missing EOF detected\n\n");
}

/**
 * @brief Test lowercase command handling
 */
void test_LowercaseCommands(void) {
    printf("\n");
    printf(" ╭─────────────────────────────────────────────╮\n");
    printf(" │  - == === Test Lowercase Commands  === == - │\n");
    printf(" ╰─────────────────────────────────────────────╯\n");

    // Try lowercase 'p' instead of 'P'
    rxChar('#');
    rxChar('p'); // Lowercase
    rxChar('t');
    rxChar('1');
    rxChar('9');
    rxChar('6');
    rxChar('!');

    int result = cmdProcessor();
    printf("   ─> cmdProcessor returned: %d\n", result);
    
    // Should reject lowercase commands
    TEST_ASSERT_EQUAL(-2, result); 
    printf("   ─> Test passed: Lowercase commands rejected\n\n");
}

int main(void){

    // inicia a Unity
    UNITY_BEGIN();

    
    RUN_TEST(test_Temperature);
    RUN_TEST(test_Humidity);
    RUN_TEST(test_CO2);
    RUN_TEST(test_all);
    RUN_TEST(test_history);
    RUN_TEST(test_reset);
    RUN_TEST(test_invalidcommand);
    RUN_TEST(test_calcChecksum_valid);
    RUN_TEST(test_calcChecksum_invalid);
    RUN_TEST(test_reset_buffers);
    RUN_TEST(test_incomplete_command);
    
    // New tests
    RUN_TEST(test_RxBufferOverflow);
    RUN_TEST(test_TxBufferOverflow);
    RUN_TEST(test_InvalidChecksum);
    RUN_TEST(test_MissingEOF);
    RUN_TEST(test_LowercaseCommands);

    // finaliza e retorna os resultados
    return UNITY_END();

}