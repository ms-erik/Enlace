#include "comunicacao.hpp"

int main() {
    comunicacao c;
    c.CamadaEnlaceDadosTransmissora();
    c.MeioDeComunicacao();
    c.CamadaEnlaceDadosReceptora();
    c.CamadaAplicacaoReceptora();
}

