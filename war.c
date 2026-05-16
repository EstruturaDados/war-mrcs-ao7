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

void cadastrarTerritorio(Territorio *Territorios ,int *totalLista, int tamTerritorios);
void exibirMapa(Territorio *territorios, int *totalLista);
void faseAtaque(Territorio *territorios, int tamTerritorios, int *continuar);
void ataque(Territorio *atacante, Territorio *defensor);
void atribuirMissao(char *destino, char *missoes[], int totalMissoes);
int verificarMissao(char *missao, Territorio *mapa, int tamanho);
void limparBufferEntrada();
void ler(char *destino, int tamanho);
void liberarMemoria(void *memoria);

int main() {
    int tamTerritorios = 0, totalLista = 0;
    int continuar = 1;
    char *listarMissoes[] = {
        "Controlar 3 territorios",
        "Controlar 5 territorios",
        "Eliminar o exercito vermelho",
        "Ter 50 tropas no total",
        "Dominar todos os territorios"
    };
    char *missaoJogador = malloc(100 * sizeof(char));

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

    cadastrarTerritorio(territorios, &totalLista, tamTerritorios);
    atribuirMissao(missaoJogador, listarMissoes, 5);

    // Exibição dos dados cadastrados
    do
    {
        exibirMapa(territorios, &totalLista);
        printf("\n| ---------- FASE DE ATAQUE ---------- |");
        faseAtaque(territorios, tamTerritorios, &continuar);

        if(verificarMissao(missaoJogador, territorios, tamTerritorios)){
        printf("\nPARABÉNS! VOCÊ CUMPRIU SUA MISSÃO!");
        printf("\nFIM DE JOGO...");
        break;
}

    } while (continuar != 0);
    
    liberarMemoria(territorios);
    liberarMemoria(missaoJogador);
    return 0;
}

void cadastrarTerritorio(Territorio *territorios, int *totalLista, int tamTerritorios){
    // Entrada de dados dos territórios
    do
    {
        printf("========================================\n");
        printf("TERRITÓRIO %d\n", *totalLista + 1);
        printf("Nome: ");
        ler(territorios[*totalLista].nome, TAM_NOME);

        printf("Cor: ");
        ler(territorios[*totalLista].cor, TAM_COR);

        printf("Número de Tropas: ");
        scanf("%d", &territorios[*totalLista].tropas);
        limparBufferEntrada();

        (*totalLista)++;
        

    } while (*totalLista != tamTerritorios);
}

void exibirMapa(Territorio *territorios, int *totalLista){
    printf("\n========================================\n");
    printf("----- MAPA DO MUNDO | ESTADO ATUAL -----\n");
    printf("========================================\n");
    
    for(int i = 0; i < *totalLista; i++){
        printf("%d. TERRITÓRIO %s\n", i + 1, territorios[i].nome);
        printf("Exercíto %s\n", territorios[i].cor);
        printf("Número de Tropas: %d\n", territorios[i].tropas);
        printf("---------------------------------\n");
    }

}

void faseAtaque(Territorio *territorios, int tamTerritorios, int *continuar){
    int opcao1 = 0, opcao2 = 0;

    printf("\nEscolha o territótio atacante (ou 0 para sair): "); // escolha do atacante
    scanf("%d", &opcao1);
    limparBufferEntrada();

    if(opcao1 == 0){
        
        printf("\nSaindo do programa...");
        *continuar = 0;
        return;
    }
        
    if(opcao1 < 0 || opcao1 > tamTerritorios){ // validação básica
        printf("\nOpção Inválida. Tente novamente.");
        printf("\nPressione Enter para continuar... ");
        getchar();
        return;
    }

    if(territorios[opcao1 - 1].tropas == 0){ // evita atacar território já destruído
        printf("\nEsse território já foi derrotado. Não pode mais lutar.");
        printf("\nPressione Enter para continuar... ");
        getchar();
        return;
    }

    printf("Escolha o territótio defensor (ou 0 para sair): ");
    scanf("%d", &opcao2);
    limparBufferEntrada();

    if(opcao2 ==  0){
        printf("\nSaindo do programa...");
        *continuar = 0;
        return;
    }
        
    if(opcao2 < 0 || opcao2 > tamTerritorios){
        printf("\nOpção Inválida. Tente novamente.");
        printf("\nPressione Enter para continuar... ");
        getchar();
        printf("\n");
        return;
    }

    // impede ataque entre mesmos exércitos
    if(strcmp(territorios[opcao1 - 1].cor, territorios[opcao2 - 1].cor) == 0){
        printf("\nEsses territórios são da mesma cor. Tente novamente.");
        printf("\nPressione Enter para continuar... ");
        getchar();
        return;
        printf("\n");
    }

    if(territorios[opcao2 - 1].tropas == 0){
        printf("\nEsse território já foi derrotado. Não pode mais lutar.");
        printf("\nPressione Enter para continuar... ");
        getchar();
        printf("\n");
        return;
    }

    // Executa combate entre os dois territórios escolhidos
    ataque(&territorios[opcao1 - 1], &territorios[opcao2 - 1]);
}

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

        // atacante dá metade das tropas e envia para o defensor
        atacante->tropas /= 2;
        defensor->tropas += atacante->tropas;

        // território conquistado muda de cor
        strcpy(defensor->cor, atacante->cor);
        printf("VITÓRIA DO ATAQUE! %s se tornou %s e perdeu %d tropas.\n", defensor->nome, atacante->cor, defensor->tropas);

    } else if(def > atk){  // Caso defensor vença
        
        // atacante perde uam tropa
        atacante->tropas--;
        printf("VITÓRIA DA DEFESA!! %s perdeu uma tropa.\n", atacante->nome);

    } else {
        printf("EMPATE! Nenhum dos dois venceu.\n");
    }

    printf("\nPressione Enter para continuar para o próximo turno... ");
    getchar();
    printf("\n");
}

void atribuirMissao(char *destino, char *missoes[], int totalMissoes){

    int qual = rand() % totalMissoes;
    strcpy(destino, missoes[qual]);

    printf("\n< MISSÃO: %s >\n", destino);
    printf("\nPressione Enter para continuar... ");
    getchar();
    printf("\n");
}

int verificarMissao(char *missao, Territorio *mapa, int tamanho){
    // 1) contar cores e tropas
    int totalTropas = 0;
    int iguais = 1;

    char corBase[10];
    strcpy(corBase, mapa[0].cor);

    for(int i = 0; i < tamanho; i++){
        totalTropas += mapa[i].tropas;

        if(strcmp(mapa[i].cor, corBase) != 0){
            iguais = 0;
        }
    }

    // 2) regras simples baseadas na string da missão
    if(strcmp(missao, "Controlar 3 territorios") == 0){
        int count = 0;
        for(int i = 0; i < tamanho; i++){
            if(strcmp(mapa[i].cor, corBase) == 0) count++;
        }
        return count >= 3;
    }

    if(strcmp(missao, "Controlar 5 territorios") == 0){
        int count = 0;
        for(int i = 0; i < tamanho; i++){
            if(strcmp(mapa[i].cor, corBase) == 0) count++;
        }
        return count >= 5;
    }

    if(strcmp(missao, "Ter 50 tropas no total") == 0){
        return totalTropas >= 50;
    }

    if(strcmp(missao, "Dominar todos os territorios") == 0){
        return iguais;
    }

    if(strcmp(missao, "Eliminar o exercito vermelho") == 0){
        for(int i = 0; i < tamanho; i++){
            if(strcmp(mapa[i].cor, "Vermelho") == 0){
                return 0;
            }
        }
        return 1;
    }

    return 0;
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
void liberarMemoria(void *memoria){
    if(memoria != NULL){
        free(memoria);
    }
}