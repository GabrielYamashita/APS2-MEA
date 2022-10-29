#include "mbed.h"

DigitalOut enA(D2);
DigitalOut Ap(D5);
DigitalOut Am(D4);

DigitalOut enB(A4);
DigitalOut Bp(A0);
DigitalOut Bm(A1);

DigitalIn DIRECAO(D7);
DigitalIn EN(D6);

InterruptIn step(D8);

int passos = 0;


void setBobinas(int bobina) {
    enA = (bobina/100000) % 10;
    Ap  = (bobina/ 10000) % 10;
    Am  = (bobina/  1000) % 10;
    enB = (bobina/   100) % 10;
    Bp  = (bobina/    10) % 10;
    Bm  = (bobina/     1) % 10;
}

void Step() {
    if(DIRECAO == 1) {
        passos++;
        if(passos >= 4) {passos = 0;}
    }
    else if(DIRECAO == 0) {
        passos--;
        if(passos <= -1) {passos = 3;}
    }
}


int main() {
    const int valores[4] = {110110, 101110, 101101, 110101};
    
    step.rise(&Step);
    
    while(1) {
        while(EN == 1) {
            
            if(DIRECAO == 1) {
                setBobinas(valores[passos]);
            }
            
            else if(DIRECAO == 0) {
                setBobinas(valores[passos]);
            }
        }
    }
}