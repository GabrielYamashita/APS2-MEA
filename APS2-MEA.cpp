#include "mbed.h"

DigitalOut enA(D2); // Enable A
DigitalOut Ap(D5);  // A+
DigitalOut Am(D4);  // A-

DigitalOut enB(A4); // Enable B
DigitalOut Bp(A0);  // A+
DigitalOut Bm(A1);  // A-

DigitalIn DIRECAO(D7); // Botão Direção
DigitalIn EN(D6);      // Botão Enable

InterruptIn step(D8);  // Sinal de Entrada do Gerador de Onda

int passos = 0; // Contagem de Passos

void setBobinas(int bobina) { // Função para Atribuir os Bits em cada Variável
    enA = (bobina/100000) % 10;
    Ap  = (bobina/ 10000) % 10;
    Am  = (bobina/  1000) % 10;
    enB = (bobina/   100) % 10;
    Bp  = (bobina/    10) % 10;
    Bm  = (bobina/     1) % 10;
}

void Step() { // Função para Contar os Passos
    if(DIRECAO == 1) { // Horário
        passos++;
        if(passos >= 4) {passos = 0;}
    }
    else if(DIRECAO == 0) { // Anti-Horário
        passos--;
        if(passos <= -1) {passos = 3;}
    }
}


int main() {
    const int valores[4] = {110110, 101110, 101101, 110101}; // Bits de Ativação de Acionamento do Motor para Cada Passo
    
    while(1) {
        step.rise(&Step); // Cada Borda de Subida, aciona a Função Step()
        
        while(EN == 1) { // Habilita o Motor
            setBobinas(valores[passos]); // Aciona o Motor, a partir da Lista de Bits, dependendo do Passo
        }
    }
}
