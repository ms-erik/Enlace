#include "c2.hpp"

int main() {
    const int TAMANHO_QUADRO = 40;  // Tamanho do quadro (8 bits para cada caractere)

    // Aloca espaço para o quadro
    int quadro[TAMANHO_QUADRO];

    // Chama a camada de enlace de dados transmissora
    CamadaEnlaceDadosTransmissora(quadro);

    return 0;
}

