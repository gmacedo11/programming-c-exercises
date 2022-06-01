#include <iostream>
#include <ncurses.h>
#include<stdio.h>
#include<math.h>
#include<stdlib.h>

#define BitsVar1 25
#define BitsVar2 25
#define Chromosomes 50
#define NO 0
#define YES 1
#define POPULATION_SIZE 100
#define INDIVIDUALS_SIZE 20

float x1, x2;

float x1decVal, x2decVal;


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
    for(i=0; i<INDIVIDUALS_SIZE ;i++){
        if (i<51) printw("\t Padre(%d) = [",i);
        jump = 0;
        for(j=50;j>=0;j--) {
            if(jump == 25) printw(" ");
            father[i].chromo[j] = rand()%2;
            if(i<51) printw("%d", father[i].chromo[j]);
            if(i<51) jump++;
        }
        if (i<51) printw("] \n");
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
        if (father[numfather].chromo[i+25] == 0)
        v_Dec = v_Dec+0;
        else if (father[numfather].chromo[i+25] == 1) {
            v_Dec = v_Dec + pow(2,i);
        }
    }
    return v_Dec;
}

void calc_aptitude(void) {
    int numfather;
    float x1aj = -100, x2aj = -100;
    float x1bj = 100, x2bj = 100;
    float x1mj = 25, x2mj = 25;


    for (numfather=0;numfather<INDIVIDUALS_SIZE;numfather++) {
        x1decVal = calcDecX1(numfather);
        x2decVal = calcDecX2(numfather);
        x1 = x1aj + x1decVal * ((x1bj - x1aj)/(pow(2,x1mj)-1));
        x2 = x2aj + x2decVal * ((x2bj - x2aj)/(pow(2,x1mj)-1));


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
    printw("\n Bin a Dec --> x1d= %f, x2d = %f, x1=%f, x2=%f", x1decVal, x2decVal, x1, x2);
    getch ();
    endwin();
}
