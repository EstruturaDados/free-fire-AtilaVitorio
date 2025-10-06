#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10

typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;


void inserirItem(Item mochila[], int *qtdItens) {
    if (*qtdItens >= MAX_ITENS) {
        printf("Mochila cheia! Não é possível adicionar mais itens.\n");
        return;
    }

    printf("\nDigite o nome do item: ");
    fgets(mochila[*qtdItens].nome, 30, stdin);
    mochila[*qtdItens].nome[strcspn(mochila[*qtdItens].nome, "\n")] = '\0';  

    printf("Digite o tipo do item (ex: arma, munição, cura): ");
    fgets(mochila[*qtdItens].tipo, 20, stdin);
    mochila[*qtdItens].tipo[strcspn(mochila[*qtdItens].tipo, "\n")] = '\0';  

    printf("Digite a quantidade: ");
    scanf("%d", &mochila[*qtdItens].quantidade);
    getchar();  // Limpar o '\n' deixado pelo scanf

    (*qtdItens)++;
    printf("Item adicionado com sucesso!\n");
}



void removerItem(Item mochila[], int *qtdItens, const char *nome) {
    int i, encontrado = 0;
    
    for (i = 0; i < *qtdItens; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            encontrado = 1;
            for (int j = i; j < *qtdItens - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            (*qtdItens)--;
            printf("Item %s removido com sucesso!\n", nome);
            break;
        }
    }
    
    if (!encontrado) {
        printf("Item não encontrado na mochila.\n");
    }
}



void listarItens(Item mochila[], int qtdItens) {
    if (qtdItens == 0) {
        printf("Mochila vazia!\n");
        return;
    }

    printf("\nItens na mochila:\n");
    for (int i = 0; i < qtdItens; i++) {
        printf("%d. Nome: %s | Tipo: %s | Quantidade: %d\n", i + 1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
}



void buscarItemComComparacoes(Item mochila[], int qtdItens, const char *nome, int *comparacoes) {
    int i;
    *comparacoes = 0;
    for (i = 0; i < qtdItens; i++) {
        (*comparacoes)++;
        if (strcmp(mochila[i].nome, nome) == 0) {
            printf("Item encontrado! Nome: %s | Tipo: %s | Quantidade: %d\n",
                   mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
            
            return;
        }
    }
    printf("Item não encontrado.\n");
    printf("Comparações realizadas: %d\n", *comparacoes);
}



int main() {
    Item mochila[MAX_ITENS];
    int qtdItens = 0;
    int opcao;
    char nomeBusca[30];

    do {
        printf("\n===== MENU =====\n");
        printf("1. Cadastrar item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Buscar item \n");
        printf("5. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();  

        switch(opcao) {
            case 1:
                inserirItem(mochila, &qtdItens);
                break;
            case 2:
                printf("\nDigite o nome do item a ser removido: ");
                fgets(nomeBusca, 30, stdin);
                nomeBusca[strcspn(nomeBusca, "\n")] = '\0';  
                removerItem(mochila, &qtdItens, nomeBusca);
                break;
            case 3:
                listarItens(mochila, qtdItens);
                break;
            case 4:
                printf("\nDigite o nome do item a ser buscado: ");
                fgets(nomeBusca, 30, stdin);
                nomeBusca[strcspn(nomeBusca, "\n")] = '\0';  
                int comparacoes;
                buscarItemComComparacoes(mochila, qtdItens, nomeBusca, &comparacoes);
                break;
            case 5:
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while(opcao != 5);

    return 0;
}