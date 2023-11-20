#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "enlace.h"

#define TAMANHO_MAX_QUADRO 1000



void CamadaEnlaceReceptoraControleDeErroCRC(struct Comunicacao *comunicacao) {
    int j;
    unsigned int byte, crc, mask;
    int bits_crc[TAMANHO_MAX_QUADRO];

    crc = 0xFFFFFFFF;

    for (int i = 0; i < strlen(comunicacao->mensagem); i++) {
        byte = comunicacao->mensagem[i];
        crc = crc ^ byte;
        for (j = 0; j < 8; j++) {
            mask = -(crc & 1);
            crc = (crc >> 1) ^ (0xEDB88320 & mask); // Corrigido o deslocamento para a direita
        }
        bits_crc[i] = crc;
    }

    printf("O quadro crc é: ");
    for (int i = 0; i < strlen(comunicacao->mensagem); i++) {
        printf("%d ", bits_crc[i]);
    }
    printf("\n");

    memcpy(comunicacao->quadro, bits_crc, sizeof(bits_crc));
}

void CamadaEnlaceReceptoraControleDeErro(struct Comunicacao *comunicacao) {
    // Tipo de controle de erro definido manualmente pela variável de cima
    int tipoDeControleDeErro = 0;

    switch (tipoDeControleDeErro) {
    case 0:
        CamadaEnlaceReceptoraControleDeErroBitParidadePar(comunicacao);
        break;
    case 1:
        CamadaEnlaceReceptoraControleDeErroBitParidadeImpar(comunicacao);
        break;
    case 2:
        CamadaEnlaceReceptoraControleDeErroCRC(comunicacao);
        break;

    default:
        printf("Tipo de Controle de Erro Inválido");
        break;
    }
}
void CamadaEnlaceReceptoraControleDeErroBitParidadeImpar(struct Comunicacao *comunicacao) {
    int quadro_com_bit_paridade[TAMANHO_MAX_QUADRO];
    int paridade = 1;  // para controle paridade ímpar, começa como 1

    for (int i = 0; i < strlen(comunicacao->mensagem) * 8; i++) {
        if (comunicacao->quadro[i] == 1)
            paridade = !paridade;
        quadro_com_bit_paridade[i] = comunicacao->quadro[i];
    }

    quadro_com_bit_paridade[strlen(comunicacao->mensagem) * 8] = paridade;

    printf("\nENLACE RECEPTORA - BIT PARIDADE ÍMPAR:\n");
    for (int i = 0; i <= strlen(comunicacao->mensagem) * 8; i++) {
        printf("%d ", quadro_com_bit_paridade[i]);
    }
    printf("\n");

    if (comunicacao->quadro[strlen(comunicacao->mensagem) * 8] != paridade) {
        printf("\n>> MENSAGEM ERRADA\n");
        exit(EXIT_FAILURE);
    }

    memcpy(comunicacao->quadro, quadro_com_bit_paridade, sizeof(quadro_com_bit_paridade));
}

void CamadaEnlaceReceptoraControleDeErroBitParidadePar(struct Comunicacao *comunicacao) {
    int quadro_com_bit_paridade[TAMANHO_MAX_QUADRO];
    int paridade = 0;  // para controle paridade par, começa como 0

    for (int i = 0; i < strlen(comunicacao->mensagem) * 8; i++) {
        if (comunicacao->quadro[i] == 1)
            paridade = !paridade;
        quadro_com_bit_paridade[i] = comunicacao->quadro[i];
    }

    quadro_com_bit_paridade[strlen(comunicacao->mensagem) * 8] = paridade;

    printf("\nENLACE RECEPTORA - BIT PARIDADE PAR:\n");
    for (int i = 0; i <= strlen(comunicacao->mensagem) * 8; i++) {
        printf("%d ", quadro_com_bit_paridade[i]);
    }
    printf("\n");

    if (comunicacao->quadro[strlen(comunicacao->mensagem) * 8] != paridade) {
        printf("\n>> MENSAGEM ERRADA\n");
        exit(EXIT_FAILURE);
    }

    memcpy(comunicacao->quadro, quadro_com_bit_paridade, sizeof(quadro_com_bit_paridade));
}


void CamadaEnlaceTransmissoraControleDeErroCRC(struct Comunicacao *comunicacao) {
    int j;
    unsigned int byte, crc, mask;
    int bits_crc[TAMANHO_MAX_QUADRO];

    crc = 0xFFFFFFFF;

    for (int i = 0; i < strlen(comunicacao->mensagem); i++) {
        byte = comunicacao->mensagem[i];
        crc = crc ^ byte;
        for (j = 0; j < 8; j++) {
            mask = -(crc & 1);
            crc = (crc >> 1) ^ (0xEDB88320 & mask); // Corrigido o deslocamento para a direita
        }
        bits_crc[i] = crc;
    }

    printf("O quadro crc é: ");
    for (int i = 0; i < strlen(comunicacao->mensagem); i++) {
        printf("%d ", bits_crc[i]);
    }
    printf("\n");

    memcpy(comunicacao->quadro, bits_crc, sizeof(bits_crc));
}

void CamadaEnlaceTransmissoraControleDeErroBitParidadeImpar(struct Comunicacao *comunicacao) {
    int quadro_com_bit_paridade[TAMANHO_MAX_QUADRO];
    int paridade = 0;  // para controle paridade ímpar, começa como 0

    for (int i = 0; i < strlen(comunicacao->mensagem) * 8; i++) {
        paridade = !paridade;
        quadro_com_bit_paridade[i] = comunicacao->quadro[i];
    }
    quadro_com_bit_paridade[strlen(comunicacao->mensagem) * 8] = paridade;

    printf("\nENLACE TRANSMISSORA - BIT PARIDADE ÍMPAR:\n");
    for (int i = 0; i <= strlen(comunicacao->mensagem) * 8; i++) {
        printf("%d ", quadro_com_bit_paridade[i]);
    }
    printf("\n");

    memcpy(comunicacao->quadro, quadro_com_bit_paridade, sizeof(quadro_com_bit_paridade));
}

void CamadaEnlaceTransmissoraControleDeErroBitParidadePar(struct Comunicacao *comunicacao) {
    int quadro_com_bit_paridade[TAMANHO_MAX_QUADRO];
    int paridade = 0;  // para controle paridade par, começa como 1

    for (int i = 0; i < strlen(comunicacao->mensagem) * 8; i++) {
        if(comunicacao->quadro[i] ==1){
            paridade = !paridade;
        }
        quadro_com_bit_paridade[i] = comunicacao->quadro[i];
    }
    quadro_com_bit_paridade[strlen(comunicacao->mensagem) * 8] = paridade;

    printf("\nENLACE TRANSMISSORA - BIT PARIDADE PAR:\n");
    for (int i = 0; i <= strlen(comunicacao->mensagem) * 8; i++) {
        printf("%d ", comunicacao->quadro[i]);
    }
    printf("\n");

    memcpy(comunicacao->quadro, quadro_com_bit_paridade, sizeof(quadro_com_bit_paridade));
}


void CamadaEnlaceTransmissoraControleDeErro(struct Comunicacao *comunicacao) {
    // Tipo de controle de erro definido manualmente pela variável de cima
    int tipoDeControleDeErro = 0;

    switch (tipoDeControleDeErro) {
    case 0:
        CamadaEnlaceTransmissoraControleDeErroBitParidadePar(comunicacao);
        break;
    case 1:
        CamadaEnlaceTransmissoraControleDeErroBitParidadeImpar(comunicacao);
        break;
    case 2:
        CamadaEnlaceTransmissoraControleDeErroCRC(comunicacao);
        break;

    default:
        printf("Tipo de Controle de Erro Inválido");
        break;
    }
}

void convertToBits(struct Comunicacao *comunicacao) {
    char mensagem_binario[TAMANHO_MAX_QUADRO * 8];
    int msg_binario_array[TAMANHO_MAX_QUADRO * 8];

    for (int i = 0; i < strlen(comunicacao->mensagem); i++) {
        sprintf(&mensagem_binario[i * 8], "%08d", comunicacao->mensagem[i] - '0');
    }

    for (int j = 0; j < strlen(mensagem_binario); j++) {
        comunicacao->quadro[j] = mensagem_binario[j] - '0';
    }
}

void CamadaAplicacaoReceptora(struct Comunicacao *comunicacao) {
    printf("\nCHAMADA DA CAMADA DE APLICAÇÃO RECEPTORA...\n");
    char string_bits_incoming[TAMANHO_MAX_QUADRO * 8];
    char final_message[TAMANHO_MAX_QUADRO];

    for (int i = 0; i < strlen(comunicacao->mensagem) * 8; i++) {
        sprintf(&string_bits_incoming[i], "%d", comunicacao->quadro[i]);
    }

    for (int i = 0, j = 0; i < strlen(string_bits_incoming); i += 8, j++) {
        char byte[9];
        strncpy(byte, &string_bits_incoming[i], 8);
        byte[8] = '\0';
        final_message[j] = strtol(byte, 0, 2);
    }

    strncpy(comunicacao->mensagem, final_message, sizeof(final_message));
    printf("\n>> A mensagem recebida foi: %s\n", comunicacao->mensagem);
}

void CamadaEnlaceDadosReceptora(struct Comunicacao *comunicacao) {
    CamadaEnlaceTransmissoraControleDeErro(comunicacao);
}

void MeioDeComunicacao(struct Comunicacao *comunicacao) {
    int erro, porcentagemDeErros = 0;
    int fluxoBrutoDeBitsPontoA[TAMANHO_MAX_QUADRO * 8];
    int fluxoBrutoDeBitsPontoB[TAMANHO_MAX_QUADRO * 8];

    for (int i = 0; i < strlen(comunicacao->mensagem) * 8; i++) {
        fluxoBrutoDeBitsPontoA[i] = comunicacao->quadro[i];
    }

    for (int i = 0; i < strlen(comunicacao->mensagem) * 8; i++) {
        if ((rand() % 100) >= porcentagemDeErros) {
            fluxoBrutoDeBitsPontoB[i] = fluxoBrutoDeBitsPontoA[i];
        } else {
            fluxoBrutoDeBitsPontoB[i] = (fluxoBrutoDeBitsPontoA[i] == 0) ? 1 : 0;
        }
    }

}

void CamadaEnlaceDadosTransmissora(struct Comunicacao *comunicacao) {
    CamadaEnlaceTransmissoraControleDeErro(comunicacao);
}

void CamadaAplicacaoTransmissora(struct Comunicacao *comunicacao) {
    printf("Digite uma mensagem:\n");
    fgets(comunicacao->mensagem, TAMANHO_MAX_QUADRO, stdin);
    convertToBits(comunicacao);
}

