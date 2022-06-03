#include <iostream>
#include <ncurses.h>
#include<stdio.h>
#include<math.h>
#include<stdlib.h>

#define BitsVar1 21
#define BitsVar2 18
#define Chromosomes 39
#define NO 0
#define YES 1
#define POPULATION_SIZE 25
#define INDIVIDUALS_SIZE 39

float x1, x2;

float x1decVal, x2decVal;
float eval;


struct individual{
    char chromo[Chromosomes];
    float aptitude;
}father[POPULATION_SIZE],child[POPULATION_SIZE];

void gen_Pop(void){
    int i=0, j=0, jump=0;
    double num;
    move(3,10);
    printw("\n Generando poblacion inicial\n");
        srand(time(NULL));
    for(i=0; i<POPULATION_SIZE; i++){
        printw("\t Padre(%d) = [",i);
        jump = 0;
        for(j=Chromosomes-1;j>=0;j--) {
            if(jump == 21) printw(" ");
            father[i].chromo[j] = rand()%2;
            printw("%d", father[i].chromo[j]);
            jump++;
        }
        printw("] \n");
    }
}

float calcDecX1(int numfather){
    int i, j;
    float v_Dec = 0.0;
    for(i=0;i<BitsVar1;i++) {
        if (father[numfather].chromo[i] == 0)
        v_Dec = v_Dec+0;
        else if (father[numfather].chromo[i] == 1) {
            v_Dec = v_Dec + pow(2,i);
        }
    }
    return v_Dec;
}

float calcDecX2(int numfather){
    int i, j;
    float v_Dec = 0.0;
    for(i=0;i<BitsVar2;i++) {
        if (father[numfather].chromo[i+21] == 0)
        v_Dec = v_Dec+0;
        else if (father[numfather].chromo[i+21] == 1) {
            v_Dec = v_Dec + pow(2,i);
        }
    }
    return v_Dec;
}

void calc_aptitude(void) {
    int numfather;
    float x1aj = -3.0, x2aj = -4.1;
    float x1bj = 12.1, x2bj = 5.8;
    float x1mj = 21, x2mj = 18;
    float eval = 0, seno = 0, CuadX = 0;

    clear();
    printw("\n Evaluación de la función de aptitud: \n");
    for (numfather=0;numfather<POPULATION_SIZE;numfather++) {
        x1decVal = calcDecX1(numfather);
        x2decVal = calcDecX2(numfather);
        x1 = x1aj + x1decVal * ((x1bj - x1aj)/(pow(2,x1mj)-1));
        x2 = x2aj + x2decVal * ((x2bj - x2aj)/(pow(2,x1mj)-1));

        printw("\n [ %d ] Bin a Dec --> x1d= %f, x2d = %f, x1=%f, x2=%f", numfather, x1decVal, x2decVal, x1, x2);

        eval = 21.5 + (x1*(sin(3.1416*4*x1))) + (sin(3.1416*20*x2));
        father[numfather].aptitude = eval;
        printw(" Eval = %f", eval);

    }
}

void viewList(void){
    int i;
    clear();
    printw("\n Lista de reproducción");

}



int main () {

    /* Genera Población */
    initscr();
    gen_Pop();
    getch ();

    /* Conversión binario a decimal */

    calc_aptitude();
    getch ();
    endwin();
}
