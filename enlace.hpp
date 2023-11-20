#pragma once

#include <string>
#include <vector>

#include <iostream> 
#include <cstdlib>

using namespace std;

void CamadaEnlaceDadosTransmissora(const std::string& mensagem);
void CamadaEnlaceDadosTransmissoraControleDeErro(char caracter, int tipoDeControleDeErro);
void CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar(char caracter, int quadro[]);
void CamadaEnlaceDadosTransmissoraControleDeErroBitParidadeImpar(char caracter, int quadro[]);
void CamadaEnlaceDadosTransmissoraControleDeErrorCRC(int quadro[]);
void MeioDeComunicacao(int fluxoBrutoDeBits[]);
void CamadaEnlaceDadosReceptora(const std::string& mensagem);
void CamadaEnlaceDadosReceptoraControleDeErro(char caracter, int tipoDeControleDeErro);
void CamadaEnlaceDadosReceptoraControleDeErrorCRC(int quadro[]);
void AplicacaoReceptora(std::string mensagem);
void dividirPolinomios(int dividendo[], int divisor[], int resultado[]);
int xorPolinomios(int a, int b);
void calcularCRC(int mensagem[], int crcResultado[]);
void CamadaEnlaceDadosReceptoraControleDeErroBitParidadePar(char caracter);
void CamadaEnlaceDadosReceptoraControleDeErroBitParidadeImpar(char caracter);
