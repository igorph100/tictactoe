#include <stdio.h>
#include <stdlib.h>

/* Jogo da velha para dois jogadores no terminal. */

char tabuleiro[3][3];

void inicializar(void) {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            tabuleiro[i][j] = ' ';
}

void imprimir(void) {
    printf("\n     1   2   3\n");
    for (int i = 0; i < 3; i++) {
        printf("%d    %c | %c | %c\n", i + 1,
               tabuleiro[i][0], tabuleiro[i][1], tabuleiro[i][2]);
        if (i < 2) printf("    ---+---+---\n");
    }
    printf("\n");
}

/* Retorna 1 se o jogador (X ou O) venceu. */
int venceu(char jogador) {
    for (int i = 0; i < 3; i++) {
        if (tabuleiro[i][0] == jogador && tabuleiro[i][1] == jogador && tabuleiro[i][2] == jogador)
            return 1; /* linha */
        if (tabuleiro[0][i] == jogador && tabuleiro[1][i] == jogador && tabuleiro[2][i] == jogador)
            return 1; /* coluna */
    }
    if (tabuleiro[0][0] == jogador && tabuleiro[1][1] == jogador && tabuleiro[2][2] == jogador)
        return 1; /* diagonal principal */
    if (tabuleiro[0][2] == jogador && tabuleiro[1][1] == jogador && tabuleiro[2][0] == jogador)
        return 1; /* diagonal secundária */
    return 0;
}

int tabuleiro_cheio(void) {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (tabuleiro[i][j] == ' ')
                return 0;
    return 1;
}

/* Lê a jogada com validação (evita travar com letras ou posição ocupada). */
void jogar(char jogador) {
    int linha, coluna;
    while (1) {
        printf("Jogador %c, digite linha e coluna (ex: 2 3): ", jogador);
        if (scanf("%d %d", &linha, &coluna) != 2) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF); /* limpa o buffer */
            printf("Entrada inválida. Use dois números.\n");
            continue;
        }
        linha--;
        coluna--;
        if (linha < 0 || linha > 2 || coluna < 0 || coluna > 2) {
            printf("Posição fora do tabuleiro. Use valores de 1 a 3.\n");
            continue;
        }
        if (tabuleiro[linha][coluna] != ' ') {
            printf("Essa posição já está ocupada.\n");
            continue;
        }
        tabuleiro[linha][coluna] = jogador;
        break;
    }
}

int main(void) {
    char jogador = 'X';
    char resposta;

    do {
        inicializar();
        while (1) {

            //Limpar console a cada jogada
            system("cls");
            //
            imprimir();
            jogar(jogador);

            if (venceu(jogador)) {
                imprimir();
                printf("Jogador %c venceu!\n", jogador);
                break;
            }
            if (tabuleiro_cheio()) {
                imprimir();
                printf("Empate!\n");
                break;
            }
            jogador = (jogador == 'X') ? 'O' : 'X';
        }

        printf("Jogar de novo? (s/n): ");
        scanf(" %c", &resposta);
        jogador = 'X';
    } while (resposta == 's' || resposta == 'S');

    return 0;
}
