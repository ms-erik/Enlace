#include "enlace.hpp"

int main() {
   // Teste com paridade ímpar
    cout << "Testando paridade ímpar:" << endl;
    char caracterImpar = 'A';  // Substitua por qualquer caractere desejado
    int quadroImpar[9];
    cout << "Caracter original: " << caracterImpar << endl;
    
    // Transmitindo
    CamadaEnlaceDadosTransmissoraControleDeErroBitParidadeImpar(caracterImpar, quadroImpar);
    cout << "Quadro com paridade ímpar: ";
    for (int i = 0; i < 9; ++i) {
        cout << quadroImpar[i] << " ";
    }
    cout << endl;

    // Recebendo
    CamadaEnlaceDadosReceptoraControleDeErroBitParidadeImpar(caracterImpar);

    // Teste com paridade par
    cout << "\nTestando paridade par:" << endl;
    char caracterPar = 'B';  // Substitua por qualquer caractere desejado
    int quadroPar[9];
    cout << "Caracter original: " << caracterPar << endl;
    
    // Transmitindo
    CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar(caracterPar, quadroPar);
    cout << "Quadro com paridade par: ";
    for (int i = 0; i < 9; ++i) {
        cout << quadroPar[i] << " ";
    }
    cout << endl;

    // Recebendo
    CamadaEnlaceDadosReceptoraControleDeErroBitParidadePar(caracterPar);

    return 0;
}
