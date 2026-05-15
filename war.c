#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAM_NOME 30 
#define TAM_COR 10

// Estrutura que representa um território no sistema
typedef struct{
    char nome[TAM_NOME];
    char cor[TAM_COR];
    int tropas;
} Territorio;

/*
    Função que simula um ataque entre dois territórios.
    Usa ponteiros para modificar diretamente os dados reais.
*/
void ataque(Territorio *atacante, Territorio *defensor){
    int atk = (rand() % 6) + 1; // dado do atacante
    int def = (rand() % 6) + 1; // dado do defensor

    printf("\n --- RESULTADO DA BATALHA ---\n");
    printf("O atacante %s rolou o dado e tirou: %d\n", atacante->nome, atk);
    printf("O defensor %s rolou o dado e tirou: %d\n", defensor->nome, def);

    if(atk > def){  // Caso atacante vença

        // atacante perde metade das tropas e envia para o defensor
        atacante->tropas /= 2;
        defensor->tropas += atacante->tropas;

        // território conquistado muda de cor
        strcpy(defensor->cor, atacante->cor);
        printf("VITÓRIA DO ATAQUE! %s se tornou %s e ganhou %d tropas.\n", defensor->nome, defensor->cor, atacante->tropas);

    } else if(def > atk){  // Caso defensor vença
        
        defensor->tropas /= 2;
        atacante->tropas += defensor->tropas;
        strcpy(atacante->cor, defensor->cor);
        printf("VITÓRIA DA DEFESA!! %s se tornou %s e ganhou %d tropas.\n", atacante->nome, atacante->cor, defensor->tropas);

    } else {
        printf("EMPATE! Nenhum dos dois venceu.\n");
    }

    printf("\nPressione Enter para continuar para o próximo turno... ");
    getchar();
    printf("\n");
}

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

// Libera a memória alocada dinamicamente para o mapa de territórios
void liberarMemoria(Territorio *memoria){
    free(memoria);
}

int main() {
    int tamTerritorios = 0;
    int totalLista = 0;
    int opcao1 = 0;
    int opcao2 = 0;

    // Usuário define quantos territórios serão criados
    printf("\n----------------| WAR |-----------------");
    printf("\nQuantos territórios deseja cadastrar? ");
    scanf("%d", &tamTerritorios);
    limparBufferEntrada();

    // alocação dinâmica dos territórios
    Territorio *territorios;
    territorios = (Territorio *) calloc(tamTerritorios, sizeof(Territorio));
    srand(time(0));

    if(territorios == NULL){
        printf("Erro! Falha ao alocar a memória.");
    }

    // Entrada de dados dos territórios
    do
    {
        printf("========================================\n");
        printf("TERRITÓRIO %d\n", totalLista + 1);
        printf("Nome: ");
        ler(territorios[totalLista].nome, TAM_NOME);

        printf("Cor: ");
        ler(territorios[totalLista].cor, TAM_COR);

        printf("Número de Tropas: ");
        scanf("%d", &territorios[totalLista].tropas);
        limparBufferEntrada();

        totalLista++;
        

    } while (totalLista != tamTerritorios);

    // Exibição dos dados cadastrados
    do
    {
        printf("\n========================================\n");
        printf("----- MAPA DO MUNDO | ESTADO ATUAL -----\n");
        printf("========================================\n");
    
        for(int i = 0; i < totalLista; i++){
            printf("%d. TERRITÓRIO %s\n", i + 1, territorios[i].nome);
            printf("Exercíto %s\n", territorios[i].cor);
            printf("Número de Tropas: %d\n", territorios[i].tropas);
            printf("---------------------------------\n");
        }

        printf("\n| ---------- FASE DE ATAQUE ---------- |");
        printf("\nEscolha o territótio atacante (ou 0 para sair): "); // escolha do atacante
        scanf("%d", &opcao1);
        limparBufferEntrada();

        if(opcao1 == 0){
            printf("\nSaindo do programa...");
            break;
        }
        
        if(opcao1 < 0 || opcao1 > 5){ // validação básica
            printf("\nOpção Inválida. Tente novamente.");
            printf("\nPressione Enter para continuar... ");
            getchar();
            continue;
        }

        if(territorios[opcao1 - 1].tropas == 0){ // evita atacar território já destruído
            printf("\nEsse território já foi derrotado. Não pode mais lutar.");
            printf("\nPressione Enter para continuar... ");
            getchar();
            continue;
        }

        printf("Escolha o territótio defensor (ou 0 para sair): ");
        scanf("%d", &opcao2);
        limparBufferEntrada();

        if(opcao2 ==  0){
            printf("\nSaindo do programa...");
            break;
        }
        
        if(opcao2 < 0 || opcao2 > 5){
            printf("\nOpção Inválida. Tente novamente.");
            printf("\nPressione Enter para continuar... ");
            getchar();
            printf("\n");
            continue;
        }

        // impede ataque entre mesmos exércitos
        if(strcmp(territorios[opcao1 - 1].cor, territorios[opcao2 - 1].cor) == 0){
            printf("\nEsses territórios são da mesma cor. Tente novamente.");
            printf("\nPressione Enter para continuar... ");
            getchar();
            printf("\n");
        }

        if(territorios[opcao2 - 1].tropas == 0){
            printf("\nEsse território já foi derrotado. Não pode mais lutar.");
            printf("\nPressione Enter para continuar... ");
            getchar();
            printf("\n");
            continue;
        }

        // Executa combate entre os dois territórios escolhidos
        ataque(&territorios[opcao1 - 1], &territorios[opcao2 - 1]);


        // Determinar se o jogo acabou.
        int controle = 0;
        char vencedor[TAM_COR];
        strcpy(vencedor, territorios[0].cor);

        // Passa pelas lista usando como base a cor da lista 0 
        // para determinar se todas as outras cores são iguais
        for(int i = 1; i < tamTerritorios; i++){ 
            if(strcmp(territorios[i].cor, vencedor) == 0){
                controle++;
            }
        }

        if(controle == tamTerritorios - 1){
            printf("\nPARABÉNS! O exército %s ganhou o jogo!", vencedor);
            printf("\nFIM DE JOGO...");
            break;
        }

    } while (opcao1 != 0 || opcao2 != 0);
    
    liberarMemoria(territorios);
    return 0;
}