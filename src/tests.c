// To compile: gcc -o test_cmdProcessor test_cmdProcessor.c modules/cmdproc.c Unity/src/unity.c -I./unity


#include "Unity/src/unity.h"
#include "modules/cmdproc.h"

void setUp(void) {
    resetTxBuffer();
    resetRxBuffer();
}

void tearDown(void) {
}   

// Test cmdProcessor()
void test_cmdProcessor(void){

    printf("\n");
    printf(" ╭───────────────────────────────────────────────╮\n");
    printf(" │  - == ===    Test  cmdProcessor    === == -   │\n");
    printf(" ╰───────────────────────────────────────────────╯\n\n");
    
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
    unsigned char ans[30];
    int len;
    getTxBuffer(ans, &len);

    // resposta esperada: '#pt+10112!' (sensor lẽ +10)
    unsigned char expected[] = {'#','p','t','+','0','0','1','1','1','!'};

    // Imprimir a resposta esperada e gerada
    printf("\n\nExpected response: ");
    for (int i=0; i<sizeof(expected); i++){
        printf("%c", expected[i]);
    }   
    printf("\nGenerated response: ");
    for (int i = 0; i < len; i++) {
        printf("%c", ans[i]); 
    }
    printf("\n\n");


    // verifica se a resposta gerada é igual à resposta esperada
    TEST_ASSERT_EQUAL_MEMORY(expected, ans, len);
}

// Test invalid command
void test_invalidcommand(void){

    printf("\n");
    printf(" ╭───────────────────────────────────────────────╮\n");
    printf(" │  - == ===   Test invalid command   === == -   │\n");
    printf(" ╰───────────────────────────────────────────────╯\n\n");

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


// Teste para a função calcChecksum() com dados válidos
void test_calcChecksum_valid(void) {

    printf("\n");
    printf(" ╭───────────────────────────────────────────────╮\n");
    printf(" │  - == ===   Test valid checksum    === == -   │\n");
    printf(" ╰───────────────────────────────────────────────╯\n\n");

    unsigned char buf[] = {'P', 't'};
    
    int nbytes = sizeof(buf);

    int result = calcChecksum(buf, nbytes);

    printf("Result of calcChecksum: %d\n", result);  
    
    TEST_ASSERT_EQUAL(196, result);  
}

// Teste para a função calcChecksum() com dados inválidos
void test_calcChecksum_invalid(void) {

    printf("\n");
    printf(" ╭───────────────────────────────────────────────╮\n");
    printf(" │  - == ===  Test invalid checksum   === == -   │\n");
    printf(" ╰───────────────────────────────────────────────╯\n\n");

    unsigned char buf[] = {'P', 'u'};  //t->116
                                      // u->117  

    int nbytes = sizeof(buf);

    int result = calcChecksum(buf, nbytes);

    printf("Result of calcChecksum: %d\n", result);
    
    TEST_ASSERT_EQUAL(196, result); 
}

// Teste de reset de buffers
void test_reset_buffers(void){
    printf("\n");
    printf(" ╭───────────────────────────────────────────────╮\n");
    printf(" │  - == ===   Test  reset buffers    === == -   │\n");
    printf(" ╰───────────────────────────────────────────────╯\n\n");
    
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

// Teste para erro de omissão de caractere (comando incompleto)
void test_incomplete_command(void) {
    printf("\n");
    printf(" ╭───────────────────────────────────────────────╮\n");
    printf(" │ - = = Test missing character in command = = - │\n");
    printf(" ╰───────────────────────────────────────────────╯\n\n");
    
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

int main(void){

    // inicia a Unity
    UNITY_BEGIN();

    
    RUN_TEST(test_cmdProcessor);
    RUN_TEST(test_invalidcommand);
    RUN_TEST(test_calcChecksum_valid);
    RUN_TEST(test_calcChecksum_invalid);
    RUN_TEST(test_reset_buffers);
    RUN_TEST(test_incomplete_command);

    // finaliza e retorna os resultados
    return UNITY_END();

}