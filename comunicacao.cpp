#include "comunicacao.hpp" 
#include <bitset>

#define TAMANHO_CRC 32

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

void comunicacao::CamadaEnlaceDadosTransmissora(){
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

void  comunicacao::CamadaEnlaceDadosTransmissoraControleDeErro(){
    switch(tipoDeControleDeErro){
        case 0:
            CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar();
            break; 
        case 1:
            CamadaEnlaceDadosTransmissoraControleDeErroBitParidadeImpar();
            break;  
        case 2:
            //CamadaEnlaceDadosTransmissoraControleDeErrorCRC();
            TErroCRC();
            break; 
        default: 
            std::cout << "controle de erro invalido" << endl;
    }

}

void comunicacao::CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar(){
    int countBits1 =0;

    //conta o numero de bits 1
    for(auto n:quadro){
        if(n ==1) countBits1++;
    }
    //se o numero de bits 1 for par, adiciona um 0, se nao adiciona um 1
    quadro.push_back((countBits1 % 2 == 0) ? 0 : 1);
}

void comunicacao::CamadaEnlaceDadosTransmissoraControleDeErroBitParidadeImpar(){
    int countBits1 =0;

    //conta o numero de bits 1
    for(auto bit : quadro){
        if(bit ==1) countBits1++;
    }
    //se o numero de bits 1 for par, adiciona um 1, se nao adiciona um 0
    quadro.push_back((countBits1 % 2 == 0) ? 1 : 0);
}

void  comunicacao::CamadaEnlaceDadosTransmissoraControleDeErrorCRC(){
    //inicializa o aray para armazenar o resultado do CRC 
    int *crcResultado = new int[TAMANHO_CRC+quadro.size()];
    //calcula o CRC 
    calcularCRC(crcResultado);

    //adicione os bits do CRC ao final do qd 
        quadro.insert(quadro.end(), crcResultado, crcResultado +32);

        delete[] crcResultado;
}


void comunicacao::MeioDeComunicacao() {

    int porcentagemDeErros;

    //Inicia o fluxo de bits no segundo ponto
    //Consideremos que o do primeiro eh o proprio quadro
    vector<int> fluxoBrutoDeBitsPontoA;
    //porcentagem de erro na transferencia de bits
    cout << "Digite a porcentagem de erro" << endl;
    cin >> porcentagemDeErros; // valor de 0 a 100

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

void comunicacao::CamadaAplicacaoReceptora(){
    cout << "resultado da comunicacao: " << endl;
    //imprime o resultado da comunicacao
    for(auto bit : quadro){
        cout << bit;
    }
    vector<int> aux = quadro;
    if(tipoDeControleDeErro == 0 || tipoDeControleDeErro ==1){
        aux.pop_back();
    }
    string saida = binaryToAscii(aux);
    cout << endl << saida;
    cout << endl;
}

void comunicacao::CamadaEnlaceDadosReceptora(){
    //chama as rotinas de erro
    CamadaEnlaceDadosReceptoraControleDeErro();
}

void  comunicacao::CamadaEnlaceDadosReceptoraControleDeErro(){
    switch(tipoDeControleDeErro){
        case 0:
            CamadaEnlaceDadosReceptoraControleDeErroBitParidadePar();
            break; 
        case 1:
            CamadaEnlaceDadosReceptoraControleDeErroBitParidadeImpar();
            break; 
        case 2:
           // CamadaEnlaceDadosTransmissoraControleDeErrorCRC();
            EErroCRC();
            break; 
        default: 
            cout << "controle de erro invalido" << endl;
            break;

    }
}

void comunicacao::CamadaEnlaceDadosReceptoraControleDeErrorCRC(){
    int *crcResultado = new int[TAMANHO_CRC + quadro.size()];

    //calcula o CRC para o qd recebido
    calcularCRC(crcResultado);

    //verifica se há erro comparando o CRC calculado com os bits de CRC no qd 
    for(int i =0; i < TAMANHO_CRC; i++){
        if(crcResultado[i] != quadro[TAMANHO_CRC + i]){
            //tratamento para erro 
            cout << "Erro detectado pelo CRC" << endl;
            break;
        }
    }
    delete[] crcResultado;
}

void comunicacao::CamadaEnlaceDadosReceptoraControleDeErroBitParidadePar(){
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

void  comunicacao::CamadaEnlaceDadosReceptoraControleDeErroBitParidadeImpar(){
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

void  comunicacao::stringToBinary(char caracter){
        // Converte cada caractere para binário e adiciona ao array
        int asciiValue = static_cast<int>(caracter);
        for (int i = 7; i >= 0; --i) {
            //qd[index++] = (asciiValue >>i) & 1;
            quadro.push_back((asciiValue >>i) & 1);
        }
}

int comunicacao::xorPolinomios(int a,int b){
    // xor logico
    return a ^ b;
}

void comunicacao::dividirPolinomios(int dividendo[], int divisor[], int resultado[]){
    for(int i=0; i <quadro.size(); i++){
        if(dividendo[0]==1){
            //se o bit mais significativo do dividendo for 1, realiza a operacao XOR com o divisor 
            for(int j=0; j<quadro.size(); j++){
                dividendo[j] = xorPolinomios(dividendo[j],divisor[j]);
            }
        }
      //desloca os bits do dividendo para a direita
        for(int j=0; j<quadro.size()-1; j++){
            dividendo[j] = dividendo[j+1];
        }
            dividendo[quadro.size()-1] =0; //o ultimo bit preenchido com 0
    }
    //0 resultado da divisão é armazenado nos ultimos 7 bits do dividendo 
    for(int i=0; i<quadro.size()-1; i++){
        resultado[i] = dividendo[i+1];
    }
}
void comunicacao::calcularCRC( int crcResultado[]){

    //Polinomio gerador (CRC-32)
    int polinomioGerador[TAMANHO_CRC] = {0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1};

    //Inicia CRC com 32 btis iguais a 0
    int *crc = new int[TAMANHO_CRC];

    for(int i=0; i < TAMANHO_CRC; i++){
        crc[i] = quadro[i];
    }
    //Realiza a divisao polinomial
    dividirPolinomios(crc, polinomioGerador, crcResultado); 
    
}


void comunicacao::TErroCRC(){
    int polinomio[32] = {0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1};
    
    // adiciona (grau do polinomio - 1) 0 ao novo quadro
    vector<int> novo_quadro;
    novo_quadro = this->quadro;
    for (int i = 0; i < size(polinomio) - 1; i++){
        novo_quadro.emplace_back(0);
    }

    for (int i = 0; i < this->quadro.size(); i++){
        if (novo_quadro[i] == 1){
            //Faz o XOR com todos os elementos do polinomio
            for (int j = 0; j < size(polinomio) - 1; j++){
                novo_quadro[j + i] ^= polinomio[j];
            }
        }
    }
    cout << endl;
   
    int i = 0;
    for (auto bit : this->quadro){
        novo_quadro[i] = bit;
        i++;
    }

    cout << "* crc: ";
    for (auto bit : novo_quadro){
        cout << bit;
    }

    cout << endl; 
    this->quadro = novo_quadro; 
}

void comunicacao::EErroCRC(){
    int polinomio[32] = {0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1};
    
    // Adiciona (grau do polinomio - 1) zeros ao novo quadro
    vector<int> novo_quadro;
    novo_quadro = this->quadro;
    for (int i = 0; i < size(polinomio) - 1; i++){
        novo_quadro.emplace_back(0);
    }

    for (int i = 0; i < this->quadro.size(); i++){
        if (novo_quadro[i] == 1){
            // Faz o XOR com todos os elementos do polinômio
            for (int j = 0; j < size(polinomio) - 1; j++){
                novo_quadro[j + i] ^= polinomio[j];
            }
        }
    }

    // Verifica se há erro comparando o resultado do CRC com os bits de CRC no quadro
    for (int i = 0; i < size(polinomio) - 1; i++){
        if (novo_quadro[i + this->quadro.size() - size(polinomio) + 1] != 0){
            // Tratamento para erro
            cout << "Erro detectado pelo CRC" << endl;
            break;
        }
    }

    cout << endl;
   
    int i = 0;
    for (auto bit : this->quadro){
        novo_quadro[i] = bit;
        i++;
    }

    cout << "* crc: ";
    for (auto bit : novo_quadro){
        cout << bit;
    }

    cout << endl; 
    this->quadro = novo_quadro; 
}
