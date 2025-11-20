#include <stdio.h>
#include <stdlib.h>

// Nó da lista circular
typedef struct No {
    int valor;
    struct No* prox;
} No;


// Insere no final da lista circular
void inserir(No** head, int valor) {
    No* novo = (No*)malloc(sizeof(No));
    novo->valor = valor;

    if (*head == NULL) {
        // Primeiro nó aponta para ele mesmo
        novo->prox = novo;
        *head = novo;
        return;
    }

    // Percorre até o último nó (que aponta para o head)
    No* atual = *head;
    while (atual->prox != *head) {
        atual = atual->prox;
    }

    atual->prox = novo;
    novo->prox = *head;
}


// Avança K posições a partir de um nó
No* avancarK(No* inicio, int k) {
    if (inicio == NULL || k <= 0) return inicio;

    while (k--) {
        inicio = inicio->prox;
    }
    return inicio;
}


// Remove um nó específico mantendo a circularidade
int removerNo(No** head, No* alvo) {
    if (*head == NULL || alvo == NULL) return 0;

    No* atual = *head;
    No* anterior = NULL;

    // Caso o único nó da lista seja o alvo
    if (*head == alvo && (*head)->prox == *head) {
        free(alvo);
        *head = NULL;
        return 1;
    }

    // Encontra o nó anterior ao alvo
    do {
        if (atual == alvo) break;
        anterior = atual;
        atual = atual->prox;
    } while (atual != *head);

    if (atual != alvo) return 0; // não encontrado

    // Se o alvo é o head
    if (alvo == *head) {
        // Encontrar o último nó para atualizar o ponteiro
        No* ultimo = *head;
        while (ultimo->prox != *head) {
            ultimo = ultimo->prox;
        }
        *head = alvo->prox;
        ultimo->prox = *head;
    } else {
        anterior->prox = alvo->prox;
    }

    free(alvo);
    return 1;
}


// Imprime a lista circular
void imprimir(No* head) {
    if (head == NULL) {
        printf("Lista vazia.\n");
        return;
    }

    No* atual = head;
    printf("Lista circular: ");
    do {
        printf("%d ", atual->valor);
        atual = atual->prox;
    } while (atual != head);
    printf("\n");
}


// Exemplo de uso
int main() {
    No* head = NULL;

    inserir(&head, 1);
    inserir(&head, 2);
    inserir(&head, 3);
    inserir(&head, 4);
    inserir(&head, 5);

    imprimir(head);

    // Avançar 7 posições a partir do nó head
    No* kpos = avancarK(head, 7);
    printf("Avançando 7 posições a partir do head: %d\n", kpos->valor);

    // Remover o nó retornado
    removerNo(&head, kpos);
    imprimir(head);

    return 0;
}
