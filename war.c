#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_NOME 30 
#define TAM_COR 10
#define MAX_TERRITORIOS 5

// Estrutura que representa um território no sistema
typedef struct{
    char nome[TAM_NOME];
    char cor[TAM_COR];
    int tropas;
} Territorio;

// Limpa o buffer do teclado após uso do scanf
// Evita problemas com '\n' em leituras com fgets
void limparBufferEntrada() {
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

// Lê uma string com segurança usando fgets e remove '\n'
void ler(char *destino, int tamanho) {
    fgets(destino, tamanho, stdin);
    destino[strcspn(destino, "\n")] = '\0';
}

int main() {
    Territorio territorios[MAX_TERRITORIOS];
    int totalLista = 0;
    int opcao = 0;

    printf("\n----------------| WAR |-----------------\n");
    printf("========================================\n");

    // Entrada de dados dos 5 territórios
    do
    {
        printf("Nome do Território: ");
        ler(territorios[totalLista].nome, TAM_NOME);

        printf("Cor do Território: ");
        ler(territorios[totalLista].cor, TAM_COR);

        printf("Número de Tropas do Território: ");
        scanf("%d", &territorios[totalLista].tropas);
        limparBufferEntrada();

        totalLista++;
        printf("========================================\n");

    } while (totalLista != MAX_TERRITORIOS);

    // Exibição dos dados cadastrados
    printf("--------- LISTA DE TERRIRÓRIOS ---------\n");
    printf("========================================\n");

    printf("---------------------------------\n");
    for(int i = 0; i < totalLista; i++){
        printf("TERRITÓRIO %d\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor: %s\n", territorios[i].cor);
        printf("Número de Tropas: %d\n", territorios[i].tropas);
        printf("---------------------------------\n");
        }
    
    return 0;
}