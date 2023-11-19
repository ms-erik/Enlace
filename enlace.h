#ifndef ENLACE_H
#define ENLACE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Defina as constantes necessárias, como o tamanho máximo do quadro, etc.
#define TAMANHO_MAX_QUADRO 1000

// Defina as funções principais
void AplicacaoTransmissora();
void CamadaDeAplicacaoTransmissora(char *mensagem);
void CamadaEnlaceDadosTransmissora(int *quadro);
void CamadaEnlaceDadosTransmissoraControleDeErro(int *quadro);

void MeioDeComunicacao(int *fluxoBrutoDeBits);
void CamadaFisicaTransmissora(int *fluxoBrutoDeBits);

void CamadaFisicaReceptora(int *fluxoBrutoDeBits);
void CamadaEnlaceDadosReceptora(int *quadro);
void CamadaEnlaceDadosReceptoraControleDeErro(int *quadro);

void AplicacaoReceptora(char *mensagem);
void CamadaDeAplicacaoReceptora(int *quadro);

#endif /* ENLACE_H */

