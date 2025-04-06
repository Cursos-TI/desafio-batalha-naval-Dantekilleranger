#include <stdio.h>
#include <stdlib.h>

#define TAM 10       // Tamanho do tabuleiro (10x10)
#define TAM_HAB 5    // Tamanho das matrizes de habilidade (5x5)

// Inicializa o tabuleiro com água (0) e navios (3) em posições fixas
void inicializarTabuleiro(int tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tabuleiro[i][j] = 0;
        }
    }

    // Exemplo de navios
    tabuleiro[2][2] = 3;
    tabuleiro[2][3] = 3;
    tabuleiro[2][4] = 3;
    tabuleiro[4][6] = 3;
    tabuleiro[5][6] = 3;
    tabuleiro[6][6] = 3;
}

// Exibe o tabuleiro no console
void exibirTabuleiro(int tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            if (tabuleiro[i][j] == 0) {
                printf("~ ");  // Água
            } else if (tabuleiro[i][j] == 3) {
                printf("N ");  // Navio
            } else if (tabuleiro[i][j] == 5) {
                printf("* ");  // Área afetada por habilidade
            } else {
                printf("? ");  // Valor desconhecido (por segurança)
            }
        }
        printf("\n");
    }
    printf("\n");
}

// Cria a matriz da habilidade Cone (expande de cima para baixo)
void criarCone(int habilidade[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (j >= TAM_HAB / 2 - i && j <= TAM_HAB / 2 + i) {
                habilidade[i][j] = 1;  // Dentro do cone
            } else {
                habilidade[i][j] = 0;  // Fora do cone
            }
        }
    }
}

// Cria a matriz da habilidade Cruz (linhas e colunas cruzadas)
void criarCruz(int habilidade[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (i == TAM_HAB / 2 || j == TAM_HAB / 2) {
                habilidade[i][j] = 1;  // Cruz
            } else {
                habilidade[i][j] = 0;
            }
        }
    }
}

// Cria a matriz da habilidade Octaedro (forma de losango)
void criarOctaedro(int habilidade[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (abs(i - TAM_HAB / 2) + abs(j - TAM_HAB / 2) <= TAM_HAB / 2) {
                habilidade[i][j] = 1;  // Dentro do losango
            } else {
                habilidade[i][j] = 0;
            }
        }
    }
}

// Aplica a matriz da habilidade ao tabuleiro, centrando no ponto de origem
void aplicarHabilidade(int tabuleiro[TAM][TAM], int habilidade[TAM_HAB][TAM_HAB], int linhaOrigem, int colOrigem) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            int linhaTab = linhaOrigem - TAM_HAB / 2 + i;
            int colTab = colOrigem - TAM_HAB / 2 + j;

            // Verifica se está dentro dos limites do tabuleiro
            if (linhaTab >= 0 && linhaTab < TAM && colTab >= 0 && colTab < TAM) {
                if (habilidade[i][j] == 1 && tabuleiro[linhaTab][colTab] == 0) {
                    tabuleiro[linhaTab][colTab] = 5;  // Marca como área afetada
                }
            }
        }
    }
}

// (Opcional) Exibe uma matriz de habilidade — útil para testes
void exibirMatrizHabilidade(int habilidade[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            printf("%d ", habilidade[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    int tabuleiro[TAM][TAM];
    int cone[TAM_HAB][TAM_HAB];
    int cruz[TAM_HAB][TAM_HAB];
    int octaedro[TAM_HAB][TAM_HAB];

    inicializarTabuleiro(tabuleiro);

    criarCone(cone);
    criarCruz(cruz);
    criarOctaedro(octaedro);

    // Aplicar habilidades com ponto de origem fixo
    aplicarHabilidade(tabuleiro, cone, 3, 3);       // Cone no centro superior
    aplicarHabilidade(tabuleiro, cruz, 6, 6);       // Cruz na metade inferior
    aplicarHabilidade(tabuleiro, octaedro, 5, 2);   // Octaedro na lateral esquerda

    // Exibir o tabuleiro final
    printf("Tabuleiro com habilidades aplicadas:\n");
    exibirTabuleiro(tabuleiro);

    return 0;
}
