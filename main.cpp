#include "comunicacao.hpp"

int main() {
    comunicaco c;
    c.CamadaEnlaceDadosTransmissora();
    c.MeioDeComunicacao();
    c.CamadaEnlaceDadosReceptora();
    c.CamadaAplicacaoReceptora();
}

