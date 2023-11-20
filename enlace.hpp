#pragma once

#include <string>
#include <vector>

#include <iostream> 
#include <cstdlib>

using namespace std;


void CamadaEnlaceDadosTransmissora(int quadro[]);
void CamadaEnlaceDadosTransmissoraControleDeErro(int quadro[], int tipoDeControleDeErro);
void CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar(int quadro[]);
void CamadaEnlaceDadosTransmissoraControleDeErroBitParidadeImpar(int quadro[]);
void CamadaEnlaceDadosTransmissoraControleDeErrorCRC(int quadro[]);
void MeioDeComunicacao(int fluxoBrutoDeBits[]);
void CamadaEnlaceDadosReceptora(int quadro[]);
void CamadaEnlaceDadosReceptoraControleDeErro(int quadro[], int tipoDeControleDeErro);
void CamadaEnlaceDadosReceptoraControleDeErrorCRC(int quadro[]);
void AplicacaoReceptora(std::string mensagem);
void dividirPolinomios(int dividendo[], int divisor[], int resultado[]);
int xorPolinomios(int a,int b);
void calcularCRC(int mensagem[], int crcResultado[]);
void CamadaEnlaceDadosReceptoraControleDeErroBitParidadePar(int quadro[]);
void CamadaEnlaceDadosReceptoraControleDeErroBitParidadeImpar(int quadro[]);
