// comunicacao.h

#ifndef COMUNICACAO_H
#define COMUNICACAO_H

#define TAMANHO_MAX_QUADRO 1000

struct Comunicacao {
    char mensagem[TAMANHO_MAX_QUADRO];
    int quadro[TAMANHO_MAX_QUADRO * 8];
};

void CamadaEnlaceReceptoraControleDeErroCRC(struct Comunicacao *comunicacao);
void CamadaEnlaceReceptoraControleDeErroBitParidadeImpar(struct Comunicacao *comunicacao);
void CamadaEnlaceReceptoraControleDeErroBitParidadePar(struct Comunicacao *comunicacao);
void CamadaEnlaceReceptoraControleDeErro(struct Comunicacao *comunicacao);

void CamadaEnlaceTransmissoraControleDeErroCRC(struct Comunicacao *comunicacao);
void CamadaEnlaceTransmissoraControleDeErroBitParidadeImpar(struct Comunicacao *comunicacao);
void CamadaEnlaceTransmissoraControleDeErroBitParidadePar(struct Comunicacao *comunicacao);
void CamadaEnlaceTransmissoraControleDeErro(struct Comunicacao *comunicacao);

void convertToBits(struct Comunicacao *comunicacao);

void CamadaAplicacaoReceptora(struct Comunicacao *comunicacao);
void CamadaEnlaceDadosReceptora(struct Comunicacao *comunicacao);

void MeioDeComunicacao(struct Comunicacao *comunicacao);

void CamadaEnlaceDadosTransmissora(struct Comunicacao *comunicacao);
void CamadaAplicacaoTransmissora(struct Comunicacao *comunicacao);

#endif // COMUNICACAO_H

