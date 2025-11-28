#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 50
#define NUM_TERRITORIOS 5

typedef struct {
    char nome[MAX];
    char corExercito[MAX];
    int tropas;
} Territorio;

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

Territorio* inicializarMapa() {
    Territorio *mapa = (Territorio *)calloc(NUM_TERRITORIOS, sizeof(Territorio));
    if (!mapa) {
        printf("Erro ao alocar memoria.\n");
        exit(1);
    }

    for (int i = 0; i < NUM_TERRITORIOS; i++) {
        printf("\nCadastro do Territorio %d\n", i + 1);

        printf("Nome: ");
        fgets(mapa[i].nome, MAX, stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0';

        printf("Cor do exercito: ");
        fgets(mapa[i].corExercito, MAX, stdin);
        mapa[i].corExercito[strcspn(mapa[i].corExercito, "\n")] = '\0';

        printf("Numero de tropas: ");
        scanf("%d", &mapa[i].tropas);
        limparBuffer();
    }

    return mapa;
}

void exibirMapa(Territorio *mapa) {
    printf("\nEstado Atual do Mapa\n");
    for (int i = 0; i < NUM_TERRITORIOS; i++) {
        printf("%d - %s | Cor: %s | Tropas: %d\n",
               i + 1, mapa[i].nome, mapa[i].corExercito, mapa[i].tropas);
    }
}

void simularBatalha(Territorio *mapa) {
    int atacante, defensor;
    int dadoAtaque, dadoDefesa;

    printf("\nEscolha o territorio atacante (1 a %d): ", NUM_TERRITORIOS);
    scanf("%d", &atacante);
    printf("Escolha o territorio defensor (1 a %d): ", NUM_TERRITORIOS);
    scanf("%d", &defensor);
    limparBuffer();

    atacante--; defensor--;

    if (atacante == defensor || atacante < 0 || defensor < 0 ||
        atacante >= NUM_TERRITORIOS || defensor >= NUM_TERRITORIOS) {
        printf("Escolha invalida.\n");
        return;
    }

    dadoAtaque = rand() % 6 + 1;
    dadoDefesa = rand() % 6 + 1;

    printf("\nDados sorteados:\n");
    printf("Ataque (%s): %d\n", mapa[atacante].nome, dadoAtaque);
    printf("Defesa (%s): %d\n", mapa[defensor].nome, dadoDefesa);

    if (dadoAtaque >= dadoDefesa) {
        mapa[defensor].tropas--;
        printf("O atacante venceu.\n");

        if (mapa[defensor].tropas <= 0) {
            printf("O territorio %s foi conquistado por %s.\n",
                   mapa[defensor].nome, mapa[atacante].corExercito);
            strcpy(mapa[defensor].corExercito, mapa[atacante].corExercito);
            mapa[defensor].tropas = 1;
        }
    } else {
        printf("O defensor resistiu.\n");
    }
}

int main() {
    srand(time(NULL));
    Territorio *mapa = inicializarMapa();
    char continuar;

    do {
        simularBatalha(mapa);
        exibirMapa(mapa);
        printf("\nDeseja realizar outra batalha? (s/n): ");
        scanf(" %c", &continuar);
        limparBuffer();
    } while (continuar == 's' || continuar == 'S');

    free(mapa);
    return 0;
}