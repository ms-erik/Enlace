#include <stdio.h>
#include "enlace.h"

int main() {
    struct Comunicacao comunicacao;

    // Simule a aplicação transmissora
    printf("Digite uma mensagem: ");
    scanf("%s", comunicacao.mensagem);

    // Chamada da camada de aplicação transmissora
    CamadaAplicacaoTransmissora(&comunicacao);

    // Chamada da camada de enlace de dados transmissora
    CamadaEnlaceDadosTransmissora(&comunicacao);

    // Simule o meio de comunicação
    MeioDeComunicacao(&comunicacao);

    // Chamada da camada de enlace de dados receptora
    CamadaEnlaceDadosReceptora(&comunicacao);

    // Chamada da camada de aplicação receptora
    CamadaAplicacaoReceptora(&comunicacao);

    return 0;
}

