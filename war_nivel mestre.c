#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 50
#define NUM_TERRITORIOS 5

/* Estrutura que representa um territorio do jogo */
typedef struct {
    char nome[MAX];
    char corExercito[MAX];
    int tropas;
} Territorio;

/* Estrutura que representa a missao atribuida ao jogador */
typedef struct {
    char objetivo[MAX];
    int concluida;
} Missao;

/* Etapa: utilitario
   Funcao para limpar o buffer do teclado apos uso de scanf */
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

/* Etapa: inicializacao
   Cria e preenche o mapa com 5 territorios fixos, cada um com 10 tropas */
Territorio* inicializarMapa() {
    Territorio *mapa = (Territorio *)calloc(NUM_TERRITORIOS, sizeof(Territorio));
    if (!mapa) {
        printf("Erro ao alocar memoria.\n");
        exit(1);
    }

    /* Cadastro fixo dos territorios com nomes e cores e 10 tropas cada */
    strcpy(mapa[0].nome, "America");
    strcpy(mapa[0].corExercito, "Azul");
    mapa[0].tropas = 10;

    strcpy(mapa[1].nome, "Africa");
    strcpy(mapa[1].corExercito, "Verde");
    mapa[1].tropas = 10;

    strcpy(mapa[2].nome, "Oceania");
    strcpy(mapa[2].corExercito, "Vermelho");
    mapa[2].tropas = 10;

    strcpy(mapa[3].nome, "Asia");
    strcpy(mapa[3].corExercito, "Amarelo");
    mapa[3].tropas = 10;

    strcpy(mapa[4].nome, "Europa");
    strcpy(mapa[4].corExercito, "Preto");
    mapa[4].tropas = 10;

    return mapa;
}

/* Etapa: visualizacao
   Exibe o estado atual de todos os territorios do mapa */
void exibirMapa(Territorio *mapa) {
    printf("\nEstado Atual do Mapa\n");
    for (int i = 0; i < NUM_TERRITORIOS; i++) {
        printf("%d - %s | Cor: %s | Tropas: %d\n",
               i + 1, mapa[i].nome, mapa[i].corExercito, mapa[i].tropas);
    }
}

/* Etapa: combate
   Simula uma batalha entre um territorio atacante e um defensor */
void simularBatalha(Territorio *mapa) {
    int atacante, defensor;
    int dadoAtaque, dadoDefesa;

    /* Escolha de atacante e defensor */
    printf("\nEscolha o territorio atacante (1 a %d): ", NUM_TERRITORIOS);
    scanf("%d", &atacante);
    printf("Escolha o territorio defensor (1 a %d): ", NUM_TERRITORIOS);
    scanf("%d", &defensor);
    limparBuffer();

    /* Ajusta para indices baseados em zero */
    atacante--;
    defensor--;

    /* Validacao das escolhas */
    if (atacante == defensor || atacante < 0 || defensor < 0 ||
        atacante >= NUM_TERRITORIOS || defensor >= NUM_TERRITORIOS) {
        printf("Escolha invalida.\n");
        return;
    }

    /* Verifica se os territorios possuem tropas para batalhar */
    if (mapa[atacante].tropas <= 0 || mapa[defensor].tropas <= 0) {
        printf("Um dos territorios nao tem tropas suficientes.\n");
        return;
    }

    /* Sorteio dos dados de ataque e defesa no intervalo [1,6] */
    dadoAtaque = rand() % 6 + 1;
    dadoDefesa = rand() % 6 + 1;

    /* Exibicao dos dados sorteados */
    printf("\nDados sorteados:\n");
    printf("Ataque (%s): %d\n", mapa[atacante].nome, dadoAtaque);
    printf("Defesa (%s): %d\n", mapa[defensor].nome, dadoDefesa);

    /* Logica da batalha:
       - atacante vence em empate
       - defensor perde 1 tropa quando atacante vence
       - se tropas do defensor chegam a zero, territorio e conquistado */
    if (dadoAtaque >= dadoDefesa) {
        mapa[defensor].tropas--;
        printf("O atacante venceu. Tropas do defensor reduzidas.\n");

        if (mapa[defensor].tropas <= 0) {
            printf("O territorio %s foi conquistado por %s.\n",
                   mapa[defensor].nome, mapa[atacante].corExercito);
            /* Transferencia de cor do exercito para indicar conquista */
            strcpy(mapa[defensor].corExercito, mapa[atacante].corExercito);
            /* Define tropas minimas apos conquista */
            mapa[defensor].tropas = 1;
        }
    } else {
        printf("O defensor resistiu.\n");
    }
}

/* Etapa: missoes
   Gera uma missao aleatoria para o jogador */
Missao gerarMissao() {
    Missao m;
    int tipo = rand() % 2; /* 0 ou 1 */
    m.concluida = 0;

    if (tipo == 0) {
        strcpy(m.objetivo, "Destruir o exercito Verde");
    } else {
        strcpy(m.objetivo, "Conquistar 3 territorios");
    }

    return m;
}

/* Etapa: verificacao de missoes
   Checa se a missao atual foi cumprida com base no estado do mapa */
void verificarMissao(Missao *m, Territorio *mapa) {
    if (m->concluida) {
        printf("\nMissao ja concluida: %s\n", m->objetivo);
        return;
    }

    /* Missao: destruir exercito verde */
    if (strcmp(m->objetivo, "Destruir o exercito Verde") == 0) {
        int verdeExiste = 0;
        for (int i = 0; i < NUM_TERRITORIOS; i++) {
            if (strcmp(mapa[i].corExercito, "Verde") == 0 && mapa[i].tropas > 0) {
                verdeExiste = 1;
                break;
            }
        }
        if (!verdeExiste) {
            m->concluida = 1;
            printf("\nMissao cumprida: %s\n", m->objetivo);
        } else {
            printf("\nMissao pendente: ainda ha tropas verdes no mapa.\n");
        }
    }
    /* Missao: conquistar 3 territorios (pela cor informada) */
    else if (strcmp(m->objetivo, "Conquistar 3 territorios") == 0) {
        int conquistas = 0;
        char jogador[MAX];

        printf("Digite sua cor de exercito para verificar conquistas: ");
        fgets(jogador, MAX, stdin);
        jogador[strcspn(jogador, "\n")] = '\0';

        for (int i = 0; i < NUM_TERRITORIOS; i++) {
            if (strcmp(mapa[i].corExercito, jogador) == 0) {
                conquistas++;
            }
        }

        if (conquistas >= 3) {
            m->concluida = 1;
            printf("\nMissao cumprida: %s\n", m->objetivo);
        } else {
            printf("\nMissao pendente: voce possui %d territorios.\n", conquistas);
        }
    }
}

/* Etapa: controle principal
   Menu interativo que orquestra ataques, verificacao de missao e saida */
int main() {
    srand(time(NULL)); /* Inicializa gerador de numeros aleatorios */

    Territorio *mapa = inicializarMapa(); /* Cria e preenche o mapa */
    Missao missao = gerarMissao();        /* Atribui uma missao ao jogador */
    int opcao;

    /* Mensagens iniciais */
    printf("Bem-vindo ao Desafio WAR Estruturado\n");
    printf("Missao atribuida: %s\n", missao.objetivo);

    /* Loop principal do jogo com menu */
    do {
        printf("\nMenu Principal\n");
        printf("1 - Atacar\n");
        printf("2 - Verificar Missao\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1:
                simularBatalha(mapa);
                exibirMapa(mapa);
                break;
            case 2:
                verificarMissao(&missao, mapa);
                break;
            case 0:
                printf("\nSaindo do jogo. Ate a proxima.\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while (opcao != 0 && !missao.concluida);

    /* Mensagem de vitoria ao concluir a missao */
    if (missao.concluida) {
        printf("\nParabens. Voce venceu o Desafio WAR Estruturado.\n");
    }

    /* Libera memoria alocada e encerra */
    free(mapa);
    return 0;
}
//Trabalho concluido_JOSÉ_DIEGO_DOS_SANTOS_FONSECA