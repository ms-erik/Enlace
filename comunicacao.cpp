#include "comunicacao.hpp" 
#include <bitset>

std::string binaryToAscii(const std::vector<int>& binary) {
    std::string asciiString;

    // Certifique-se de que o vetor binário tenha um número de bits múltiplo de 8
    size_t padding = 8 - (binary.size() % 8);
    std::vector<int> paddedBinary(padding, 0);
    paddedBinary.insert(paddedBinary.end(), binary.begin(), binary.end());

    // Itera sobre o vetor binário em incrementos de 8 bits
    for (size_t i = 0; i < paddedBinary.size(); i += 8) {
        // Obtém um bloco de 8 bits
        std::vector<int> block(paddedBinary.begin() + i, paddedBinary.begin() + i + 8);

        // Converte o bloco de 8 bits para um caractere ASCII
        char asciiChar = static_cast<char>(std::bitset<8>(
            block[0] << 7 | block[1] << 6 | block[2] << 5 | block[3] << 4 |
            block[4] << 3 | block[5] << 2 | block[6] << 1 | block[7]
        ).to_ulong());

        // Adiciona o caractere à string ASCII resultante
        asciiString.push_back(asciiChar);
    }

    return asciiString;
}

void comunicaco::CamadaEnlaceDadosTransmissora(){
    cout << "Insira o tipo de erro:" << endl << "Tipo 0: Paridade par;" << endl << "Tipo 1: Paridade Impar;" << endl << "Tipo 2: CRC" << endl;
    cin >> tipoDeControleDeErro;

   //solicita uma mensagem ao usuário
   cout << "Digite uma mensagem: ";
   string mensagem;
   cin >> mensagem; 

   //converte para binario
   for(char caracter : mensagem){
       stringToBinary(caracter);
   }

   cout << "A mensagem em bits eh:" << endl;
   for(auto bit : quadro){
       cout << bit;
   }
   cout << endl;
   //escolhe o tipo de erro
   CamadaEnlaceDadosTransmissoraControleDeErro();
}

void  comunicaco::CamadaEnlaceDadosTransmissoraControleDeErro(){
    switch(tipoDeControleDeErro){
        case 0:
            CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar();
            break; 
        case 1:
            CamadaEnlaceDadosTransmissoraControleDeErroBitParidadeImpar();
            break;  
        case 2:
            CamadaEnlaceDadosTransmissoraControleDeErrorCRC();
            break; 
        default: 
            std::cout << "controle de erro invalido" << endl;
    }

}

void comunicaco::CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar(){
    int countBits1 =0;

    //conta o numero de bits 1
    for(auto n:quadro){
        if(n ==1) countBits1++;
    }
    //se o numero de bits 1 for par, adiciona um 0, se nao adiciona um 1
    quadro.push_back((countBits1 % 2 == 0) ? 0 : 1);
}

void comunicaco::CamadaEnlaceDadosTransmissoraControleDeErroBitParidadeImpar(){
    int countBits1 =0;

    //conta o numero de bits 1
    for(auto bit : quadro){
        if(bit ==1) countBits1++;
    }
    //se o numero de bits 1 for par, adiciona um 1, se nao adiciona um 0
    quadro.push_back((countBits1 % 2 == 0) ? 1 : 0);
}

void  comunicaco::CamadaEnlaceDadosTransmissoraControleDeErrorCRC(){
    //inicializa o aray para armazenar o resultado do CRC 
    int crcResultado[32] = {0};

    //calcula o CRC 
    calcularCRC(quadro.data(), crcResultado);

    //adicione os bits do CRC ao final do qd 
    for(int i=0; i <32; i++){
      //  quadro.push_back(crcResultado[i]);
        quadro.insert(quadro.end(), crcResultado, crcResultado +32);
        //qd[i+8] = crcResultado[i];
    }

}


void comunicaco::MeioDeComunicacao() {

    int porcentagemDeErros;

    //Inicia o fluxo de bits no segundo ponto
    //Consideremos que o do primeiro eh o proprio quadro
    vector<int> fluxoBrutoDeBitsPontoA;
    //porcentagem de erro na transferencia de bits
    porcentagemDeErros = 40; // 10%, 20%, 30%, 40%

    // Inicializa os fluxos brutos de bits nos pontos A e B
    for(int i =0; i < quadro.size(); i++){
        //caso o rand seja maior que o erro, adiciona o elemento certo
       if((rand() % 100) > porcentagemDeErros){
           fluxoBrutoDeBitsPontoA.push_back(quadro[i]); 
       }else{
           //adiciona um elemento errado
           fluxoBrutoDeBitsPontoA.push_back((quadro[i]==0) ? 1 : 0);
       }
    }
    //atualiza o quadro com os valores no segundo ponto
    quadro = fluxoBrutoDeBitsPontoA;
}

void comunicaco::CamadaAplicacaoReceptora(){
    cout << "resultado da comunicacao: " << endl;
    //imprime o resultado da comunicacao
    for(auto bit : quadro){
        cout << bit;
    }
    vector<int> aux = quadro;
    aux.pop_back();
    string saida = binaryToAscii(aux);
    cout << endl << saida;
    cout << endl;
}

void comunicaco::CamadaEnlaceDadosReceptora(){
    //chama as rotinas de erro
    CamadaEnlaceDadosReceptoraControleDeErro();
}

void  comunicaco::CamadaEnlaceDadosReceptoraControleDeErro(){
    switch(tipoDeControleDeErro){
        case 0:
            CamadaEnlaceDadosReceptoraControleDeErroBitParidadePar();
            break; 
        case 1:
            CamadaEnlaceDadosReceptoraControleDeErroBitParidadeImpar();
            break; 
        case 2:
            CamadaEnlaceDadosTransmissoraControleDeErrorCRC();
            break; 
        default: 
            cout << "controle de erro invalido" << endl;
            break;

    }
}

void comunicaco::CamadaEnlaceDadosReceptoraControleDeErrorCRC(){
    int crcResultado[32] = {0};

    //calcula o CRC para o qd recebido
    calcularCRC(quadro.data(), crcResultado);

    //verifica se há erro comparando o CRC calculado com os bits de CRC no qd 
    for(int i=0; i <32; i++){
        if(crcResultado[i] != quadro[i+8]){
            //tratamento para erro 
            cout << "Erro detectado pelo CRC" << endl;
            break;
        }
    }
    CamadaEnlaceDadosReceptora();
}

void comunicaco::CamadaEnlaceDadosReceptoraControleDeErroBitParidadePar(){
    int countBits1 =0;

    //calcula a qntd de bits 1
    for(auto bit : quadro){
        if(bit == 1) countBits1++;
    }
    //verifica o bit de paridade par 
    if(countBits1 % 2 != quadro.back()){
        //tratamento de erro 
        cout << "Erro detectado pela paridade par" << endl;
    }else{
    //    CamadaEnlaceDadosReceptora();
    }
}

void  comunicaco::CamadaEnlaceDadosReceptoraControleDeErroBitParidadeImpar(){
    int countBits1 =0;

    //calcula a quantidade de bits 0
    for(auto bit : quadro){
        if(bit == 1) countBits1++;
    }

    //Verifica o but de paridade impar 
    if(countBits1 % 2 == quadro.back()){
        //tratamento de erro 
        cout << "Erro detectado pela paridade impar" << endl;
    }else{
        //sem erro, chama a proxima
     //   CamadaEnlaceDadosReceptora();
    }
}

void  comunicaco::stringToBinary(char caracter){
        // Converte cada caractere para binário e adiciona ao array
        int asciiValue = static_cast<int>(caracter);
        for (int i = 7; i >= 0; --i) {
            //qd[index++] = (asciiValue >>i) & 1;
            quadro.push_back((asciiValue >>i) & 1);
        }
}

int comunicaco::xorPolinomios(int a,int b){
    // xor logico
    return a ^ b;
}

void comunicaco::dividirPolinomios(int dividendo[], int divisor[], int resultado[]){
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
void comunicaco::calcularCRC(int mensagem[], int crcResultado[]){

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

