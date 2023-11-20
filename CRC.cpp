#include <iostream>

// Função que realiza a operação XOR de dois polinômios
int xorPolinomios(int a, int b) {
    return a ^ b;
}

// Função que realiza a operação de divisão polinomial
void dividirPolinomios(int dividendo[], int divisor[], int resultado[]) {
    // Loop para cada bit do dividendo
    for (int i = 0; i < 8; ++i) {
        // Se o bit mais significativo do dividendo for 1, realiza a operação XOR
        if (dividendo[0] == 1) {
            for (int j = 0; j < 8; ++j) {
                dividendo[j] = xorPolinomios(dividendo[j], divisor[j]);
            }
        }

        // Desloca os bits do dividendo para a direita
        for (int j = 0; j < 7; ++j) {
            dividendo[j] = dividendo[j + 1];
        }
        dividendo[7] = 0;  // O último bit é preenchido com 0
    }

    // O resultado da divisão é armazenado nos últimos 7 bits do dividendo
    for (int i = 0; i < 7; ++i) {
        resultado[i] = dividendo[i + 1];
    }
}

// Função principal para calcular o CRC
void calcularCRC(int mensagem[], int crcResultado[]) {
    // Polinômio gerador (CRC-32)
    int polinomioGerador[] = {1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1};
    
    // Inicializa o CRC com 32 bits (todos 0)
    int crc[32] = {0};

    // Copia a mensagem para o CRC
    for (int i = 0; i < 8; ++i) {
        crc[i] = mensagem[i];
    }

    // Realiza a divisão polinomial
    dividirPolinomios(crc, polinomioGerador, crcResultado);
}

int main() {
    // Exemplo de mensagem de 8 bits (pode ser ajustada conforme necessário)
    int mensagem[8] = {1, 0, 1, 1, 0, 1, 0, 0};

    // Resultado final do CRC (32 bits)
    int crcResultado[32] = {0};

    // Calcula o CRC
    calcularCRC(mensagem, crcResultado);

    // Exibe o resultado
    std::cout << "CRC Resultante: ";
    for (int i = 0; i < 32; ++i) {
        std::cout << crcResultado[i];
    }
    std::cout << std::endl;

    return 0;
}

