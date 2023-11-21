#include "comunicacao.hpp" 


void CamadaEnlaceDadosTransmissora(int quadro[]){
   int tipoDeControleDeErro =2;

   //solicita uma mensagem ao usuário
   cout << "Digite uma mensagem: ";
   string mensagem;
   cin >> mensagem; 
   //converte para binario
   for(char caracter : mensagem){
       stringToBinary(caracter, quadro);
       CamadaEnlaceDadosTransmissoraControleDeErro(quadro, tipoDeControleDeErro);
       MeioDeComunicacao(quadro);
   }
   //CamadaEnlaceDadosTransmissoraControleDeErro(quadro, tipoDeControleDeErro);
}


void CamadaEnlaceDadosReceptora(int quadro[]){
    int tipoDeControleDeErro =2;
    CamadaEnlaceDadosReceptoraControleDeErro(quadro, tipoDeControleDeErro);

}

void CamadaEnlaceDadosTransmissoraControleDeErrorCRC(int quadro[]){
    //inicializa o aray para armazenar o resultado do CRC 
    int crcResultado[32] = {0};

    //calcula o CRC 
    calcularCRC(quadro, crcResultado);

    //adicione os bits do CRC ao final do quadro 
    for(int i=0; i <32; i++){
        quadro[i+8] = crcResultado[i];
    }

}

void CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar(int quadro[]){
    int countBits1 =0;

    //obtem a quantidade de bits 1 no quadro 
    for(int i=0; i< 8; i++){
        if(quadro[i] ==1) countBits1++;
    }
    quadro[8] = (countBits1 % 2 ==0) ? 0 : 1;
}

void CamadaEnlaceDadosTransmissoraControleDeErroBitParidadeImpar(int quadro[]){
    int countBits1 =0;

    for(int i=0; i<8; i++){
        if(quadro[i]==1) countBits1++;
    }
    quadro[8] = (countBits1 % 2 ==0) ? 1 : 0;
}

void CamadaEnlaceDadosTransmissoraControleDeErro(int quadro[], int tipoDeControleDeErro){
    switch(tipoDeControleDeErro){
        case 0:
            CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar(quadro);
            break; 
        case 1:
            CamadaEnlaceDadosTransmissoraControleDeErroBitParidadeImpar(quadro);
            break;  
        case 2:
            CamadaEnlaceDadosTransmissoraControleDeErrorCRC(quadro);
            break; 
        default: 
            std::cout << "controle de erro invalido" << endl;
    }

}


void MeioDeComunicacao(int fluxoBrutoDeBits[]) {
       // OBS: Trabalhar com BITS e não com BYTES!!!

    int erro, porcentagemDeErros;
    int fluxoBrutoDeBitsPontoA[8], fluxoBrutoDeBitsPontoB[8];

    porcentagemDeErros = 10; // 10%, 20%, 30%, 40%

    // Inicializa os fluxos brutos de bits nos pontos A e B
    for (int i = 0; i < 8; ++i) {
        fluxoBrutoDeBitsPontoA[i] = fluxoBrutoDeBits[i];
        fluxoBrutoDeBitsPontoB[i] = fluxoBrutoDeBits[i];
    }

    while (fluxoBrutoDeBitsPontoB[7] != fluxoBrutoDeBitsPontoA[7]) {
        // Probabilidade de erro (de 0 a 99)
        if ((rand() % 100) < porcentagemDeErros) {
            // Simula erro invertendo um bit (usando operador ternário)
            int posicaoErro = rand() % 8; // Escolhe uma posição aleatória para simular o erro
            fluxoBrutoDeBitsPontoB[posicaoErro] = (fluxoBrutoDeBitsPontoB[posicaoErro] == 0) ? 1 : 0;
        }

        // Chama a próxima camada (CamadaEnlaceDadosReceptora)
        CamadaEnlaceDadosReceptora(fluxoBrutoDeBitsPontoB);
    }
    // Imprime o resultado
    cout << " ";
    for (int i = 0; i < 8; ++i) {
        cout << fluxoBrutoDeBitsPontoB[i];
    }
    //cout << endl;
}

int xorPolinomios(int a,int b){
    return a ^ b;
}

void dividirPolinomios(int dividendo[], int divisor[], int resultado[]){
    for(int i=0; i <8; i++){
        if(dividendo[0]==1){
            //se o bit mais significativo do dividendo for 1, realiza a operacao XOR com o divisor 
            for(int j=0; j<8; j++){
                dividendo[j] = xorPolinomios(dividendo[j],divisor[j]);
            }
        }
      //desloca os bits do dividendo para a direita
        for(int j=0; j<7; j++){
            dividendo[j] = dividendo[j+1];
        }
            dividendo[7] =0; //o ultimo bit preenchido com 0
    }
    //0 resultado da divisão é armazenado nos ultimos 7 bits do dividendo 
    for(int i=0; i<7; i++){
        resultado[i] = dividendo[i+1];
    }
}
void calcularCRC(int mensagem[], int crcResultado[]){

    //Polinomio gerador (CRC-32)
    int polinomioGerador[] = {1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1};

    //Inicia CRC com 32 btis iguais a 0
    int crc[32] = {0};

    for(int i=0; i<8; i++){
        crc[i] = mensagem[i];
    }
    //Realiza a divisao polinomial
    dividirPolinomios(crc, polinomioGerador, crcResultado); 
    
}


void CamadaEnlaceDadosReceptoraControleDeErro(int quadro[], int tipoDeControleDeErro){
    switch(tipoDeControleDeErro){
        case 0:
            CamadaEnlaceDadosReceptoraControleDeErroBitParidadePar(quadro);
            break; 
        case 1:
            CamadaEnlaceDadosTransmissoraControleDeErroBitParidadeImpar(quadro);
            break; 
        case 2:
            CamadaEnlaceDadosTransmissoraControleDeErrorCRC(quadro);
            break; 
        default: 
            cout << "controle de erro invalido" << endl;
            break;

    }
}

void CamadaEnlaceDadosReceptoraControleDeErrorCRC(int quadro[]){
    int crcResultado[32] = {0};

    //calcula o CRC para o quadro recebido
    calcularCRC(quadro, crcResultado);

    //verifica se há erro comparando o CRC calculado com os bits de CRC no quadro 
    for(int i=0; i <32; i++){
        if(crcResultado[i] != quadro[i+8]){
            //tratamento para erro 
            cout << "Erro detectado pelo CRC" << endl;
            break;
        }
    }
    CamadaEnlaceDadosReceptora(quadro);
}

void CamadaEnlaceDadosReceptoraControleDeErroBitParidadePar(int quadro[]){
    int countBits1 =0;

    //calcula a qntd de bits 1
    for(int i=0; i<8; i++){
        if(quadro[i]==1){
            countBits1++;
        }
    }
    //verifica o bit de paridade par 
    if(countBits1 % 2 != quadro[8]){
        //tratamento de erro 
        cout << "Erro detectado pela paridade par" << endl;
    }else{
        CamadaEnlaceDadosReceptora(quadro);
    }
}

void CamadaEnlaceDadosReceptoraControleDeErroBitParidadeImpar(int quadro[]){
    int countBits1 =0;

    //calcula a quantidade de bits 0
    for(int i=0; i <8; i++){
        if(quadro[i] ==1 ){
            countBits1++;
        }
    }

    //Verifica o but de paridade impar 
    if(countBits1 % 2 == quadro[8]){
        //tratamento de erro 
        cout << "Erro detectado pela paridade impar" << endl;
    }else{
        //sem erro, chama a proxima
        CamadaEnlaceDadosReceptora(quadro);
    }
}

void stringToBinary(char caracter, int quadro[]){
  int index = 0;  // Inicializa index
        // Converte cada caractere para binário e adiciona ao array
        int asciiValue = static_cast<int>(caracter);
        for (int i = 7; i >= 0; --i) {
            quadro[index++] = (asciiValue >>i) & 1;
        }
}
