#include "comunicacao.hpp" 

#define TAMANHO_CRC 33

void comunicacao::AplicacaoTransmissora(){
    cout << "Insira o tipo de erro:" << endl << "Tipo 0: Paridade par;" << endl << "Tipo 1: Paridade Impar;" << endl << "Tipo 2: CRC" << endl;
    //insere o tipo de controle de erro
    cin >> tipoDeControleDeErro;
    // caso o usuario digite um numero indevido, sai do programa
    if(tipoDeControleDeErro != 0 && tipoDeControleDeErro != 1 && tipoDeControleDeErro !=2){
        cout << "controle de erro invalido, tente novamente" << endl;
        exit(-1);
    }

   //solicita uma mensagem ao usuário
   cout << "Digite uma mensagem: ";
   cin.ignore(); // só pra garantir que não vai ter um \n no buffer
   string mensagem;
   //Pega a linha
   getline(cin, mensagem);

   //converte para binario
   for(char caracter : mensagem){
       stringToBinary(caracter);
   }

   cout << "A mensagem em bits eh:" << endl;
   //printa a mensagem em binario para fins de comparacao
   for(auto bit : quadro){
       cout << bit;
   }
   cout << endl;
   CamadaEnlaceDadosTransmissora();
}

void comunicacao::CamadaEnlaceDadosTransmissora(){
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
            CamadaEnlaceDadosTransmissoraControleDeErrorCRC();
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

     // Polinômio gerador (CRC-32)
        int polinomioGerador[TAMANHO_CRC] = {1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1};
        
        //cria um vetor auxiliar para nao modificar o quadro diretamente
        vector<int> crc(quadro.begin(), quadro.end());
        //adiciona os 32 0's no final do vetor
        crc.resize(crc.size() + TAMANHO_CRC, 0);

        for (int i = 0; i < quadro.size(); i++) {
            if(crc[i]  ==1){
                // Se o bit é 1, realiza o XOR com os bits do polinômio gerador
                for(int j=0; j < TAMANHO_CRC; j++){
                    crc[i+j] = (crc[i+j] ^ polinomioGerador[j]);
                }
            }
        }

        //insere o resto da divisão no quadro 
        //levando em conta que sao apenas os 32 bits finais do crc, o resto dele eh 0
        quadro.insert(quadro.end(), crc.end() - TAMANHO_CRC, crc.end());

        //imprime o quadro após o processo
        cout << "quadro apos crc" << endl;
        for(auto n : quadro){
            cout << n;
        }
        cout << endl;
}


void comunicacao::MeioDeComunicacao() {

    int porcentagemDeErros;

    //Inicia o fluxo de bits no segundo ponto
    //Consideremos que o do primeiro eh o proprio quadro
    vector<int> fluxoBrutoDeBitsPontoB;
    //porcentagem de erro na transferencia de bits
    cout << "Digite a porcentagem de erro" << endl;
    cin >> porcentagemDeErros; // valor de 0 a 100

    // Inicializa os fluxos brutos de bits nos pontos B
    for(int i =0; i < quadro.size(); i++){
        //caso o rand seja maior que o erro, adiciona o elemento certo
       if((rand() % 100) > porcentagemDeErros){
           fluxoBrutoDeBitsPontoB.push_back(quadro[i]); 
       }else{
           //adiciona um elemento errado
           fluxoBrutoDeBitsPontoB.push_back((quadro[i]==0) ? 1 : 0);
       }
    }
    //atualiza o quadro com os valores no segundo ponto
    quadro = fluxoBrutoDeBitsPontoB;
}

void comunicacao::AplicacaoReceptora(){
    //chama a camada de enlace
    CamadaEnlaceDadosReceptora();

    cout << "resultado da comunicacao: " << endl;
    //imprime o resultado da comunicacao
    for(auto bit : quadro){
        cout << bit;
    }
    vector<int> aux = quadro;
    //remove os bits de paridade ou o código de verificação CRC para printar a saida final
    if(tipoDeControleDeErro == 0 || tipoDeControleDeErro ==1){
        aux.pop_back();//remove os bits de paridade
    }else{
        for(int i=0; i < TAMANHO_CRC; i++){
            aux.pop_back();// remove os bits de verificacao CRC
        }
    }
    //converte os bits para ascii e imprime o resultado da comunicao
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
            CamadaEnlaceDadosReceptoraControleDeErrorCRC();
            break; 
        default: 
            cout << "controle de erro invalido" << endl;
            break;

    }
}

void comunicacao::CamadaEnlaceDadosReceptoraControleDeErrorCRC(){
        // Calcula o CRC para o quadro recebido
        int polinomioGerador[TAMANHO_CRC] = {1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1};

        // vetor crc auxiliar, agora com o mesmo tamanho do quadro
        vector<int> crc(quadro.begin(), quadro.end());
        for (int i = 0; i < quadro.size(); i++) {
            if(crc[i]  ==1){        
                // Se o bit é 1, realiza o XOR com os bits do polinômio gerador
                for(int j=0; j < TAMANHO_CRC; j++){
                    crc[i+j] = (crc[i+j] ^ polinomioGerador[j]);
                }
            }
        }
        // CRC representa o resto da divisao, se nenhum bit foi alterado, deve ser tudo 0
        for (int i = 0; i < TAMANHO_CRC; ++i) {
            if (crc[i] != 0) {
                // Tratamento para erro
                std::cout << "Erro detectado pelo CRC" << std::endl;
                break;
            }
        }
        // caso queira ver como ficou o resto da divisao
        
        /*
        cout << "imprimindo o valor do crc" << endl;
        for(auto n : crc){
            cout << n;
        }
        cout << endl;
        */
        
        
}

void comunicacao::CamadaEnlaceDadosReceptoraControleDeErroBitParidadePar(){
    int countBits1 =0;

    //calcula a qntd de bits 1
    for(auto bit : quadro){
        if(bit == 1) countBits1++;
    }
    //verifica o bit de paridade par 
    if(countBits1 % 2 != 0){
        //tratamento de erro 
        cout << "Erro detectado pela paridade par" << endl;
    }
}

void  comunicacao::CamadaEnlaceDadosReceptoraControleDeErroBitParidadeImpar(){
    int countBits1 =0;

    //calcula a quantidade de bits 0
    for(auto bit : quadro){
        if(bit == 1) countBits1++;
    }

    //Verifica o but de paridade impar 
    if(countBits1 % 2 == 0){
        //tratamento de erro 
        cout << "Erro detectado pela paridade impar" << endl;
    }
}

void  comunicacao::stringToBinary(char caracter){
        // Converte cada caractere para binário e adiciona ao array
        int asciiValue = static_cast<int>(caracter);
        for (int i = 7; i >= 0; --i) {
            //adiciona no quadro o valor em binario
            quadro.push_back((asciiValue >>i) & 1);
        }
}


std::string comunicacao::binaryToAscii(const std::vector<int>& binary) {
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
