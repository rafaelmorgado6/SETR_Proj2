#include "Unity/src/unity.h"
#include "cmdproc.h"

void setUp(void) {
    resetTxBuffer();
    resetRxBuffer();
}

void tearDown(void) {
}   

void test_cmdProcessor(void){
    
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
    unsigned char expected[] = {'#','p','t','+','1','0','1','1','2','!'};

    // verifica se a resposta gerada é igual à resposta esperada
    TEST_ASSERT_EQUAL_MEMORY(expected, ans, len);

}

int main(void){
    
    // inicia a Unity
    UNITY_BEGIN();

    // executa o teste test_cmdProcessor()
    RUN_TEST(test_cmdProcessor);

    // finaliza e retorna os resultados
    return UNITY_END();

}