#pragma once

#include <string>
#include <vector>

#include <iostream> 
#include <cstdlib>

using namespace std;

void CamadaEnlaceDadosTransmissora(int quadro[]);
void CamadaEnlaceDadosReceptora(int quadro[]);
void CamadaEnlaceDadosTransmissoraControleDeErrorCRC(int quadro[]);
void CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar(int quadro[]);
void CamadaEnlaceDadosTransmissoraControleDeErroBitParidadeImpar(int quadro[]);
void CamadaEnlaceDadosTransmissoraControleDeErro(int quadro[], int tipoDeControleDeErro);
void MeioDeComunicacao(int fluxoBrutoDeBits[]);
int xorPolinomios(int a, int b);
void dividirPolinomios(int dividendo[], int divisor[], int resultado[]);
void calcularCRC(int mensagem[], int crcResultado[]);
void CamadaEnlaceDadosReceptoraControleDeErro(int quadro[], int tipoDeControleDeErro);
void CamadaEnlaceDadosReceptoraControleDeErrorCRC(int quadro[]);
void CamadaEnlaceDadosReceptoraControleDeErroBitParidadePar(int quadro[]);
void CamadaEnlaceDadosReceptoraControleDeErroBitParidadeImpar(int quadro[]);
void stringToBinary(char caracter, int quadro[]);
