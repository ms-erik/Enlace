#include "enlace.hpp"

int main() {
    // Exemplo de teste sem erros
    int quadroSemErros[8] = {0, 1, 0, 1, 1, 0, 1, 0};
    cout << "Teste sem erros:" << endl;
    MeioDeComunicacao(quadroSemErros);

    // Exemplo de teste com erro de paridade par
    int quadroComErroParidadePar[8] = {1, 1, 0, 1, 1, 0, 1, 0};
    cout << "\nTeste com erro de paridade par:" << endl;
    MeioDeComunicacao(quadroComErroParidadePar);

    // Exemplo de teste com erro de CRC
    int quadroComErroCRC[8] = {0, 1, 0, 1, 1, 0, 1, 0};
    cout << "\nTeste com erro de CRC:" << endl;
    MeioDeComunicacao(quadroComErroCRC);

    // Adicione mais testes conforme necessário...

    return 0;
}
