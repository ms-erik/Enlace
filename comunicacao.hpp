#pragma once

#include <string>
#include <vector>
#include <bitset>
#include <iostream> 
#include <cstdlib>

using namespace std;

class comunicacao{
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
        void AplicacaoReceptora();
        void AplicacaoTransmissora();
    private:
        int tipoDeControleDeErro;
        vector<int> quadro;
        void stringToBinary(char caracter);
        std::string binaryToAscii(const std::vector<int>& binary);
};
