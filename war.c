#include <stdio.h>
#include <string.h>

#define MAX 50
#define NUM_TERRITORIOS 5

// Definição da struct
typedef struct {
    char nome[MAX];
    char corExercito[MAX];
    int tropas;
} Territorio;

int main() {
    Territorio mapa[NUM_TERRITORIOS];
    
    for (int i = 0; i < NUM_TERRITORIOS; i++) {
        printf("\n--- Cadastro do Território %d ---\n", i+1);

        printf("Nome do território: ");
        fgets(mapa[i].nome, MAX, stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0'; // remove \n

        printf("Cor do exército: ");
        fgets(mapa[i].corExercito, MAX, stdin);
        mapa[i].corExercito[strcspn(mapa[i].corExercito, "\n")] = '\0';

        printf("Número de tropas: ");
        scanf("%d", &mapa[i].tropas);
        getchar(); // limpa o \n deixado pelo scanf
    }

    // Exibição organizada
    printf("\n=== Estado Atual do Mapa ===\n");
    printf("%-20s %-15s %-10s\n", "Território", "Cor do Exército", "Tropas");
    printf("---------------------------------------------------\n");

    for (int i = 0; i < NUM_TERRITORIOS; i++) {
        printf("%-20s %-15s %-10d\n", mapa[i].nome, mapa[i].corExercito, mapa[i].tropas);
    }

    return 0;
}
