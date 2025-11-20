#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ======================
// Estrutura da Fila
// ======================

typedef struct No {
    char nome[50];
    struct No* prox;
} No;

typedef struct {
    No* inicio;
    No* fim;
} Fila;

// Cria fila
void inicializar(Fila* f) {
    f->inicio = NULL;
    f->fim = NULL;
}

// Verifica se fila está vazia
int isEmpty(Fila* f) {
    return f->inicio == NULL;
}

// Enqueue: insere no final da fila
void enqueue(Fila* f, const char* nome) {
    No* novo = (No*)malloc(sizeof(No));
    strcpy(novo->nome, nome);
    novo->prox = NULL;

    if (isEmpty(f)) {
        f->inicio = f->fim = novo;
    } else {
        f->fim->prox = novo;
        f->fim = novo;
    }
}

// Dequeue: remove e retorna o primeiro da fila
char* dequeue(Fila* f) {
    if (isEmpty(f)) {
        return NULL;
    }

    No* temp = f->inicio;
    f->inicio = f->inicio->prox;

    if (f->inicio == NULL)
        f->fim = NULL;

    char* nome = (char*)malloc(50);
    strcpy(nome, temp->nome);

    free(temp);
    return nome;
}

// Front: retorna o primeiro sem remover
char* front(Fila* f) {
    if (isEmpty(f)) return NULL;
    return f->inicio->nome;
}

// Imprimir toda a fila (apenas para debug)
void imprimirFila(Fila* f) {
    No* atual = f->inicio;
    printf("Fila: ");
    while (atual != NULL) {
        printf("[%s] ", atual->nome);
        atual = atual->prox;
    }
    printf("\n");
}


// ======================
// Simulação de atendimento FIFO
// ======================

int main() {
    Fila fila;
    inicializar(&fila);

    // Clientes chegando
    enqueue(&fila, "João");
    enqueue(&fila, "Maria");
    enqueue(&fila, "Carlos");
    enqueue(&fila, "Ana");

    imprimirFila(&fila);

    // Atendimento FIFO
    printf("\n--- Iniciando atendimento ---\n");

    while (!isEmpty(&fila)) {
        char* cliente = dequeue(&fila);
        printf("Atendendo: %s\n", cliente);
        free(cliente);
    }

    printf("\nTodos os clientes foram atendidos!\n");

    return 0;
}
