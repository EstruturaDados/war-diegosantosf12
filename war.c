#include <stdio.h>
#include <string.h>

// parte1_struct.c

#define MAX 50
#define NUM_TERRITORIOS 5

typedef struct {
    char nome[MAX];
    char corExercito[MAX];
    int tropas;
} Territorio;

int main() {
    Territorio mapa[NUM_TERRITORIOS]; // apenas declaração para esta parte
    printf("Parte 1 ok: struct Territorio e vetor static criados.\n");
    return 0;
}