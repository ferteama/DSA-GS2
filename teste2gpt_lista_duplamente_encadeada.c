#include <stdio.h>
#include <stdlib.h>

// Estrutura de um nó da lista duplamente encadeada
typedef struct No {
    int valor;
    struct No* prox;
    struct No* ant;
} No;

// Insere no início
void inserirInicio(No** head, No** tail, int valor) {
    No* novo = (No*)malloc(sizeof(No));
    novo->valor = valor;
    novo->prox = *head;
    novo->ant = NULL;

    if (*head == NULL) {  
        // Lista vazia
        *head = *tail = novo;
    } else {
        (*head)->ant = novo;
        *head = novo;
    }
}

// Insere no final
void inserirFim(No** head, No** tail, int valor) {
    No* novo = (No*)malloc(sizeof(No));
    novo->valor = valor;
    novo->prox = NULL;
    novo->ant = *tail;

    if (*tail == NULL) {  
        // Lista vazia
        *head = *tail = novo;
    } else {
        (*tail)->prox = novo;
        *tail = novo;
    }
}

// Remove do início
int removerInicio(No** head, No** tail) {
    if (*head == NULL)
        return 0; // Lista vazia

    No* temp = *head;

    if (*head == *tail) {  
        // Apenas 1 elemento
        *head = *tail = NULL;
    } else {
        *head = (*head)->prox;
        (*head)->ant = NULL;
    }

    free(temp);
    return 1;
}

// Remove do final
int removerFim(No** head, No** tail) {
    if (*tail == NULL)
        return 0; // Lista vazia

    No* temp = *tail;

    if (*head == *tail) {  
        // Apenas 1 elemento
        *head = *tail = NULL;
    } else {
        *tail = (*tail)->ant;
        (*tail)->prox = NULL;
    }

    free(temp);
    return 1;
}

// Percorre head → tail
void imprimirFrente(No* head) {
    printf("Head → Tail: ");
    while (head != NULL) {
        printf("%d ", head->valor);
        head = head->prox;
    }
    printf("\n");
}

// Percorre tail → head
void imprimirTras(No* tail) {
    printf("Tail → Head: ");
    while (tail != NULL) {
        printf("%d ", tail->valor);
        tail = tail->ant;
    }
    printf("\n");
}

// Exemplo de uso
int main() {
    No *head = NULL, *tail = NULL;

    inserirInicio(&head, &tail, 10);
    inserirInicio(&head, &tail, 5);
    inserirFim(&head, &tail, 20);
    inserirFim(&head, &tail, 30);

    imprimirFrente(head);
    imprimirTras(tail);

    removerInicio(&head, &tail);
    imprimirFrente(head);

    removerFim(&head, &tail);
    imprimirFrente(head);

    return 0;
}
