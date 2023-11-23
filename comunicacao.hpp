#pragma once

#include <string>
#include <vector>

#include <iostream> 
#include <cstdlib>

using namespace std;

class comunicaco{
    public:
        void CamadaEnlaceDadosTransmissora();
        void CamadaEnlaceDadosReceptora();
        void CamadaEnlaceDadosTransmissoraControleDeErrorCRC();
        void CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar();
        void CamadaEnlaceDadosTransmissoraControleDeErroBitParidadeImpar();
        void CamadaEnlaceDadosTransmissoraControleDeErro();
        void MeioDeComunicacao();
        void CamadaEnlaceDadosReceptoraControleDeErro();
        void CamadaEnlaceDadosReceptoraControleDeErrorCRC();
        void CamadaEnlaceDadosReceptoraControleDeErroBitParidadePar();
        void CamadaEnlaceDadosReceptoraControleDeErroBitParidadeImpar();
        void CamadaAplicacaoReceptora();
    private:
        int tipoDeControleDeErro;
        vector<int> quadro;
        int xorPolinomios(int a, int b);
        void stringToBinary(char caracter);
        void dividirPolinomios(int dividendo[], int divisor[], int resultado[]);
        void calcularCRC(int mensagem[], int crcResultado[]);
};
