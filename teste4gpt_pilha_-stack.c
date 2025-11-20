#include <stdio.h>
#include <stdlib.h>

// =====================
// Estrutura da Pilha
// =====================
typedef struct No {
    char valor;
    struct No* prox;
} No;

// Verifica se pilha está vazia
int isEmpty(No* topo) {
    return topo == NULL;
}

// Push: insere elemento no topo
void push(No** topo, char valor) {
    No* novo = (No*)malloc(sizeof(No));
    novo->valor = valor;
    novo->prox = *topo;
    *topo = novo;
}

// Pop: remove e retorna o elemento do topo
char pop(No** topo) {
    if (isEmpty(*topo)) {
        return '\0'; // erro: pilha vazia
    }
    No* temp = *topo;
    char valor = temp->valor;
    *topo = temp->prox;
    free(temp);
    return valor;
}

// Top: retorna o topo sem remover
char top(No* topo) {
    if (isEmpty(topo)) {
        return '\0';
    }
    return topo->valor;
}


// =====================
// Função para verificar expressão balanceada
// =====================

int corresponde(char abre, char fecha) {
    return (abre == '(' && fecha == ')') ||
           (abre == '[' && fecha == ']') ||
           (abre == '{' && fecha == '}');
}

int isBalanced(const char* expr) {
    No* pilha = NULL; // pilha vazia

    for (int i = 0; expr[i] != '\0'; i++) {
        char c = expr[i];

        // Se for abertura, empilha
        if (c == '(' || c == '[' || c == '{') {
            push(&pilha, c);
        }
        // Se for fechamento
        else if (c == ')' || c == ']' || c == '}') {
            if (isEmpty(pilha)) {
                return 0; // não existe abertura correspondente
            }

            char topo = pop(&pilha);
            if (!corresponde(topo, c)) {
                return 0; // ordem errada
            }
        }
    }

    int balanced = isEmpty(pilha);

    // limpa qualquer resto da pilha
    while (!isEmpty(pilha)) pop(&pilha);

    return balanced;
}


// =====================
// Exemplo de uso
// =====================

int main() {
    char expr1[] = "{[()]}";
    char expr2[] = "([{}]))";
    char expr3[] = "([a + b] * {c / d})";

    printf("Expressão 1: %s -> %s\n", expr1, isBalanced(expr1) ? "BALANCEADA" : "NÃO balanceada");
    printf("Expressão 2: %s -> %s\n", expr2, isBalanced(expr2) ? "BALANCEADA" : "NÃO balanceada");
    printf("Expressão 3: %s -> %s\n", expr3, isBalanced(expr3) ? "BALANCEADA" : "NÃO balanceada");

    return 0;
}
