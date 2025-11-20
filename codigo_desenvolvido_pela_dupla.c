#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Macro para limpar buffer de entrada (funciona em Windows e Linux)
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/* ===========================================================
   1. LISTA SIMPLESMENTE ENCADEADA
   =========================================================== */
typedef struct NoSimples {
    int valor;
    struct NoSimples* prox;
} NoSimples;

NoSimples* novoNoSimples(int v) {
    NoSimples* n = (NoSimples*)malloc(sizeof(NoSimples));
    n->valor = v;
    n->prox = NULL;
    return n;
}

/* Inserir em ordem crescente */
NoSimples* inserirOrdenado(NoSimples* head, int v) {
    NoSimples* novo = novoNoSimples(v);
    if (!head || v < head->valor) {
        novo->prox = head;
        return novo;
    }
    NoSimples* atual = head;
    while (atual->prox && atual->prox->valor < v)
        atual = atual->prox;
    novo->prox = atual->prox;
    atual->prox = novo;
    return head;
}

/* Remover dado um valor */
NoSimples* removerValorSimples(NoSimples* head, int v) {
    if (!head) return NULL;
    if (head->valor == v) {
        NoSimples* tmp = head;
        head = head->prox;
        free(tmp);
        printf("Valor %d removido.\n", v);
        return head;
    }
    NoSimples* atual = head;
    while (atual->prox && atual->prox->valor != v)
        atual = atual->prox;
    
    if (atual->prox) {
        NoSimples* tmp = atual->prox;
        atual->prox = tmp->prox;
        free(tmp);
        printf("Valor %d removido.\n", v);
    } else {
        printf("Valor %d nao encontrado.\n", v);
    }
    return head;
}

/* Buscar valor */
void buscarSimples(NoSimples* head, int v) {
    while (head) {
        if (head->valor == v) {
            printf("Valor %d encontrado no endereco de memoria: %p\n", v, (void*)head);
            return;
        }
        head = head->prox;
    }
    printf("Valor %d nao encontrado na lista.\n", v);
}

void mostrarListaSimples(NoSimples* head) {
    printf("Lista Simples: ");
    while (head) {
        printf("%d -> ", head->valor);
        head = head->prox;
    }
    printf("NULL\n");
}

/* ===========================================================
   2. LISTA DUPLAMENTE ENCADEADA
   =========================================================== */
typedef struct NoDuplo {
    int valor;
    struct NoDuplo *ant, *prox;
} NoDuplo;

NoDuplo* novoNoDuplo(int v) {
    NoDuplo* n = (NoDuplo*)malloc(sizeof(NoDuplo));
    n->valor = v;
    n->ant = n->prox = NULL;
    return n;
}

NoDuplo* inserirInicioDuplo(NoDuplo* head, int v) {
    NoDuplo* n = novoNoDuplo(v);
    n->prox = head;
    if (head) head->ant = n;
    return n;
}

NoDuplo* inserirFimDuplo(NoDuplo* head, int v) {
    NoDuplo* n = novoNoDuplo(v);
    if (!head) return n;
    NoDuplo* tmp = head;
    while (tmp->prox) tmp = tmp->prox;
    tmp->prox = n;
    n->ant = tmp;
    return head;
}

NoDuplo* removerInicioDuplo(NoDuplo* head) {
    if (!head) { printf("Lista vazia.\n"); return NULL; }
    NoDuplo* tmp = head;
    head = head->prox;
    if (head) head->ant = NULL;
    free(tmp);
    return head;
}

NoDuplo* removerFimDuplo(NoDuplo* head) {
    if (!head) { printf("Lista vazia.\n"); return NULL; }
    NoDuplo* tmp = head;
    while (tmp->prox) tmp = tmp->prox;
    if (tmp->ant) tmp->ant->prox = NULL;
    else head = NULL;
    free(tmp);
    return head;
}

void mostrarDuplaTotal(NoDuplo* head) {
    printf("Ida: ");
    NoDuplo* cauda = head;
    while (cauda) {
        printf("%d <-> ", cauda->valor);
        if (!cauda->prox) break; // Guarda o último para a volta
        cauda = cauda->prox;
    }
    printf("NULL\n");

    printf("Volta: ");
    if (!head) { printf("NULL\n"); return; }
    while (cauda) {
        printf("%d <-> ", cauda->valor);
        cauda = cauda->ant;
    }
    printf("NULL\n");
}

/* ===========================================================
   3. LISTA CIRCULAR (Simples)
   =========================================================== */
typedef struct NoCircular {
    int valor;
    struct NoCircular* prox;
} NoCircular;

NoCircular* inserirCircular(NoCircular* head, int v) {
    NoCircular* n = (NoCircular*)malloc(sizeof(NoCircular));
    n->valor = v;
    if (!head) {
        n->prox = n;
        return n;
    }
    NoCircular* tmp = head;
    while (tmp->prox != head) tmp = tmp->prox;
    tmp->prox = n;
    n->prox = head;
    return head;
}

/* Avançar k posições a partir do head atual */
NoCircular* avancarK(NoCircular* head, int k) {
    if (!head) return NULL;
    printf("Avancando %d posicoes...\n", k);
    for(int i=0; i<k; i++) {
        head = head->prox;
    }
    printf("Novo inicio (head) agora e: %d\n", head->valor);
    return head;
}

/* Remove nó buscando pelo valor */
NoCircular* removerValorCircular(NoCircular* head, int v) {
    if (!head) return NULL;

    NoCircular *atual = head, *ant = NULL;

    // Procura o nó
    while (atual->valor != v) {
        if (atual->prox == head) { // Deu a volta e não achou
            printf("Valor %d nao encontrado.\n", v);
            return head;
        }
        ant = atual;
        atual = atual->prox;
    }

    // Caso único nó
    if (atual->prox == head && atual == head) {
        free(atual);
        return NULL;
    }

    // Se for o head, precisamos achar o último para atualizar o next dele
    if (atual == head) {
        NoCircular* ultimo = head;
        while (ultimo->prox != head) ultimo = ultimo->prox;
        head = head->prox;
        ultimo->prox = head;
        free(atual);
    } else {
        ant->prox = atual->prox;
        free(atual);
    }
    printf("Valor %d removido.\n", v);
    return head;
}

void mostrarCircular(NoCircular* head) {
    if (!head) { printf("Lista Vazia\n"); return; }
    NoCircular* tmp = head;
    printf("Circular: ");
    do {
        printf("%d -> ", tmp->valor);
        tmp = tmp->prox;
    } while (tmp != head);
    printf("(volta ao %d)\n", head->valor);
}

/* ===========================================================
   4. PILHA (STACK) - Verificação de Parênteses
   =========================================================== */
typedef struct NoPilha {
    char valor;
    struct NoPilha* prox;
} NoPilha;

NoPilha* push(NoPilha* topo, char v) {
    NoPilha* n = (NoPilha*)malloc(sizeof(NoPilha));
    n->valor = v;
    n->prox = topo;
    return n;
}

NoPilha* pop(NoPilha* topo) {
    if (!topo) return NULL;
    NoPilha* tmp = topo;
    topo = topo->prox;
    free(tmp);
    return topo;
}

char top(NoPilha* topo) { return topo ? topo->valor : '\0'; }
int isEmptyStack(NoPilha* topo) { return topo == NULL; }

/* Limpa a pilha restante */
NoPilha* limparPilha(NoPilha* topo) {
    while(topo) topo = pop(topo);
    return NULL;
}

int verificarBalanceamento(const char* exp) {
    NoPilha* pilha = NULL;
    int balanceado = 1;

    for (int i = 0; exp[i]; i++) {
        char c = exp[i];
        if (c == '(' || c == '[' || c == '{') {
            pilha = push(pilha, c);
        } else if (c == ')' || c == ']' || c == '}') {
            if (isEmptyStack(pilha)) {
                balanceado = 0; break;
            }
            char t = top(pilha);
            pilha = pop(pilha);
            if ((c == ')' && t != '(') ||
                (c == ']' && t != '[') ||
                (c == '}' && t != '{')) {
                balanceado = 0; break;
            }
        }
    }
    if (!isEmptyStack(pilha)) balanceado = 0;
    limparPilha(pilha); // Limpa memória residual
    return balanceado;
}

/* ===========================================================
   5. FILA (QUEUE) - Simulação de Atendimento
   =========================================================== */
typedef struct NoFila {
    int valor; // ID do cliente
    struct NoFila* prox;
} NoFila;

typedef struct {
    NoFila *front, *rear;
} Fila;

Fila* criarFila() {
    Fila* f = (Fila*)malloc(sizeof(Fila));
    f->front = f->rear = NULL;
    return f;
}

void enqueue(Fila* f, int v) {
    NoFila* n = (NoFila*)malloc(sizeof(NoFila));
    n->valor = v;
    n->prox = NULL;
    if (!f->rear) f->front = f->rear = n;
    else {
        f->rear->prox = n;
        f->rear = n;
    }
    printf("Cliente %d entrou na fila.\n", v);
}

void dequeue(Fila* f) {
    if (!f->front) {
        printf("Fila vazia! Ninguem para atender.\n");
        return;
    }
    NoFila* tmp = f->front;
    printf("Atendendo cliente: %d (Saindo da fila)\n", tmp->valor);
    f->front = f->front->prox;
    if (!f->front) f->rear = NULL;
    free(tmp);
}

void mostrarFila(Fila* f) {
    NoFila* tmp = f->front;
    printf("Fila de Atendimento: INICIO -> ");
    while (tmp) {
        printf("[Cli %d] -> ", tmp->valor);
        tmp = tmp->prox;
    }
    printf("FIM\n");
}

/* ===========================================================
   MENU INTERATIVO
   =========================================================== */
int main() {
    int opPrincipal, opSub, valor;
    char expressao[100];

    // Ponteiros iniciais
    NoSimples* lSimples = NULL;
    NoDuplo* lDupla = NULL;
    NoCircular* lCircular = NULL;
    Fila* filaAtendimento = criarFila();

    do {
        printf("\n=== ESTRUTURAS DE DADOS - MENU PRINCIPAL ===\n");
        printf("1. Lista Simplesmente Encadeada\n");
        printf("2. Lista Duplamente Encadeada\n");
        printf("3. Lista Circular\n");
        printf("4. Pilha (Verificar Expressoes)\n");
        printf("5. Fila (Simular Atendimento)\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opPrincipal);

        switch(opPrincipal) {
            case 1: // Simples
                do {
                    printf("\n--- Lista Simples ---\n");
                    printf("1. Inserir (Ordenado)\n2. Remover valor\n3. Buscar\n4. Mostrar\n0. Voltar\nOpcao: ");
                    scanf("%d", &opSub);
                    if(opSub == 1) {
                        printf("Valor: "); scanf("%d", &valor);
                        lSimples = inserirOrdenado(lSimples, valor);
                    } else if(opSub == 2) {
                        printf("Valor a remover: "); scanf("%d", &valor);
                        lSimples = removerValorSimples(lSimples, valor);
                    } else if(opSub == 3) {
                        printf("Valor a buscar: "); scanf("%d", &valor);
                        buscarSimples(lSimples, valor);
                    } else if(opSub == 4) {
                        mostrarListaSimples(lSimples);
                    }
                } while (opSub != 0);
                break;

            case 2: // Dupla
                do {
                    printf("\n--- Lista Dupla ---\n");
                    printf("1. Inserir Inicio\n2. Inserir Fim\n3. Remover Inicio\n4. Remover Fim\n5. Mostrar (Ida/Volta)\n0. Voltar\nOpcao: ");
                    scanf("%d", &opSub);
                    if(opSub == 1 || opSub == 2) {
                        printf("Valor: "); scanf("%d", &valor);
                        if(opSub==1) lDupla = inserirInicioDuplo(lDupla, valor);
                        else lDupla = inserirFimDuplo(lDupla, valor);
                    } else if(opSub == 3) lDupla = removerInicioDuplo(lDupla);
                      else if(opSub == 4) lDupla = removerFimDuplo(lDupla);
                      else if(opSub == 5) mostrarDuplaTotal(lDupla);
                } while (opSub != 0);
                break;

            case 3: // Circular
                do {
                    printf("\n--- Lista Circular ---\n");
                    printf("1. Inserir\n2. Avancar 'K' posicoes\n3. Remover valor\n4. Mostrar\n0. Voltar\nOpcao: ");
                    scanf("%d", &opSub);
                    if(opSub == 1) {
                        printf("Valor: "); scanf("%d", &valor);
                        lCircular = inserirCircular(lCircular, valor);
                    } else if(opSub == 2) {
                        printf("Quantas posicoes avancar (k): "); scanf("%d", &valor);
                        lCircular = avancarK(lCircular, valor);
                    } else if(opSub == 3) {
                        printf("Valor a remover: "); scanf("%d", &valor);
                        lCircular = removerValorCircular(lCircular, valor);
                    } else if(opSub == 4) mostrarCircular(lCircular);
                } while (opSub != 0);
                break;

            case 4: // Pilha
                limparBuffer(); // Limpa o enter anterior
                printf("\n--- Pilha (Balanceamento) ---\n");
                printf("Digite uma expressao ex: ((A+B)*[C]): ");
                fgets(expressao, 100, stdin);
                expressao[strcspn(expressao, "\n")] = 0; // Remove newline do fgets

                if(verificarBalanceamento(expressao)) 
                    printf(">>> Expressao BALANCEADA!\n");
                else 
                    printf(">>> Expressao NAO balanceada!\n");
                break;

            case 5: // Fila
                do {
                    printf("\n--- Fila (Atendimento) ---\n");
                    printf("1. Chegou Cliente (Enqueue)\n2. Atender Cliente (Dequeue)\n3. Ver Fila\n0. Voltar\nOpcao: ");
                    scanf("%d", &opSub);
                    if(opSub == 1) {
                        printf("ID do Cliente: "); scanf("%d", &valor);
                        enqueue(filaAtendimento, valor);
                    } else if(opSub == 2) {
                        dequeue(filaAtendimento);
                    } else if(opSub == 3) {
                        mostrarFila(filaAtendimento);
                    }
                } while (opSub != 0);
                break;
                
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while (opPrincipal != 0);

    return 0;
}