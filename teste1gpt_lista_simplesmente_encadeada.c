#include <stdio.h>
#include <stdlib.h>

// Estrutura do nó
typedef struct No {
    int valor;
    struct No* prox;
} No;

// Insere em ordem crescente
void inserirOrdenado(No** lista, int valor) {
    No* novo = (No*)malloc(sizeof(No));
    novo->valor = valor;
    novo->prox = NULL;

    // Caso a lista esteja vazia ou o novo valor seja o menor
    if (*lista == NULL || (*lista)->valor >= valor) {
        novo->prox = *lista;
        *lista = novo;
        return;
    }

    No* atual = *lista;
    while (atual->prox != NULL && atual->prox->valor < valor) {
        atual = atual->prox;
    }

    novo->prox = atual->prox;
    atual->prox = novo;
}

// Busca um valor e retorna o ponteiro para o nó
No* buscar(No* lista, int valor) {
    while (lista != NULL) {
        if (lista->valor == valor) {
            return lista;
        }
        lista = lista->prox;
    }
    return NULL;
}

// Remove um nó pelo valor
int remover(No** lista, int valor) {
    if (*lista == NULL) {
        return 0; // lista vazia
    }

    No* atual = *lista;
    No* anterior = NULL;

    // Caso seja o primeiro nó
    if (atual->valor == valor) {
        *lista = atual->prox;
        free(atual);
        return 1;
    }

    // Percorre a lista
    while (atual != NULL && atual->valor != valor) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL) {
        return 0; // valor não encontrado
    }

    anterior->prox = atual->prox;
    free(atual);
    return 1;
}

// Imprime a lista
void imprimir(No* lista) {
    printf("Lista: ");
    while (lista != NULL) {
        printf("%d ", lista->valor);
        lista = lista->prox;
    }
    printf("\n");
}

// Exemplo de uso
int main() {
    No* lista = NULL;

    inserirOrdenado(&lista, 5);
    inserirOrdenado(&lista, 1);
    inserirOrdenado(&lista, 9);
    inserirOrdenado(&lista, 3);

    imprimir(lista);

    No* achou = buscar(lista, 3);
    if (achou != NULL)
        printf("Valor %d encontrado no endereço %p\n", achou->valor, (void*)achou);
    else
        printf("Valor não encontrado.\n");

    remover(&lista, 5);
    imprimir(lista);

    return 0;
}
