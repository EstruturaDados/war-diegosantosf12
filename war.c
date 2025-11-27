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

    //Parte2_entrada.c

    for (int i = 0; i < NUM_TERRITORIOS; i++) {
        printf("\n--- Cadastro do Território %d ---\n", i + 1);

        printf("Nome do território: ");
        fgets(mapa[i].nome, MAX, stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0';

        printf("Cor do exército: ");
        fgets(mapa[i].corExercito, MAX, stdin);
        mapa[i].corExercito[strcspn(mapa[i].corExercito, "\n")] = '\0';

        printf("Número de tropas: ");
        while (scanf("%d", &mapa[i].tropas) != 1) {
            printf("Valor inválido. Digite um número inteiro: ");
            int c;
            while ((c = getchar()) != '\n' && c != EOF) { }
        }
        int c;
        while ((c = getchar()) != '\n' && c != EOF) { } // limpa buffer
    }

    return 0;

// parte3_saida.c

    // Saída organizada
    printf("\n=== Estado Atual do Mapa ===\n");
    printf("%-20s %-18s %-10s\n", "Território", "Cor do Exército", "Tropas");
    printf("--------------------------------------------------------\n");
    for (int i = 0; i < NUM_TERRITORIOS; i++) {
        printf("%-20s %-18s %-10d\n",
               mapa[i].nome, mapa[i].corExercito, mapa[i].tropas);
    }

    return 0;
}