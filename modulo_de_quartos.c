#include <stdio.h>
#include <string.h>

#define MAX_QUARTOS 100

typedef struct {
    int numero;
    char tipo[30];        // Standard, Luxo, Suite...
    float valorDiaria;
    char status[15];      // "Ocupado" ou "Livre"
} Quarto;

Quarto quartos[MAX_QUARTOS];
int totalQuartos = 0;

// Cadastro de quarto
void cadastrarQuarto(void) {
    if (totalQuartos >= MAX_QUARTOS) {
        printf("Limite de quartos atingido!\n");
        return;
    }

    Quarto q;
    printf("Número do quarto: ");
    scanf("%d", &q.numero);
    printf("Tipo do quarto (Standard, Luxo, Suite...): ");
    scanf(" %[^\n]", q.tipo);
    printf("Valor da diária: ");
    scanf("%f", &q.valorDiaria);
    strcpy(q.status, "Livre");

    quartos[totalQuartos++] = q;
    printf("Quarto cadastrado com sucesso!\n");
}

// Listagem de quartos
void listarQuartos(void) {
    printf("\n--- Lista de Quartos ---\n");
    if (totalQuartos == 0) {
        printf("Nenhum quarto cadastrado.\n");
        return;
    }
    for (int i = 0; i < totalQuartos; i++) {
        printf("Número: %d | Tipo: %s | Diária: R$ %.2f | Status: %s\n",
               quartos[i].numero, quartos[i].tipo, quartos[i].valorDiaria, quartos[i].status);
    }
}

// Busca de quarto
void buscarQuarto(void) {
    int numero;
    printf("Digite o número do quarto: ");
    scanf("%d", &numero);

    for (int i = 0; i < totalQuartos; i++) {
        if (quartos[i].numero == numero) {
            printf("Número: %d | Tipo: %s | Diária: R$ %.2f | Status: %s\n",
                   quartos[i].numero, quartos[i].tipo, quartos[i].valorDiaria, quartos[i].status);
            return;
        }
    }
    printf("Quarto não encontrado!\n");
}

// Alteração de quarto
void alterarQuarto(void) {
    int numero;
    printf("Digite o número do quarto a alterar: ");
    scanf("%d", &numero);

    for (int i = 0; i < totalQuartos; i++) {
        if (quartos[i].numero == numero) {
            printf("Novo tipo: ");
            scanf(" %[^\n]", quartos[i].tipo);
            printf("Novo valor da diária: ");
            scanf("%f", &quartos[i].valorDiaria);
            printf("Dados alterados com sucesso!\n");
            return;
        }
    }
    printf("Quarto não encontrado!\n");
}

// Exclusão de quarto
void excluirQuarto(void) {
    int numero;
    printf("Digite o número do quarto a excluir: ");
    scanf("%d", &numero);

    for (int i = 0; i < totalQuartos; i++) {
        if (quartos[i].numero == numero) {
            for (int j = i; j < totalQuartos - 1; j++) {
                quartos[j] = quartos[j + 1];
            }
            totalQuartos--;
            printf("Quarto excluído com sucesso!\n");
            return;
        }
    }
    printf("Quarto não encontrado!\n");
}

// Alteração de status do quarto
void alterarStatusQuarto(void) {
    int numero;
    printf("Digite o número do quarto: ");
    scanf("%d", &numero);

    for (int i = 0; i < totalQuartos; i++) {
        if (quartos[i].numero == numero) {
            printf("Novo status (Ocupado/Livre): ");
            scanf(" %[^\n]", quartos[i].status);
            printf("Status atualizado com sucesso!\n");
            return;
        }
    }
    printf("Quarto não encontrado!\n");
}

// Menu de quartos
void menuQuartos(void) {
    int opcao;
    do {
        printf("\n--- Módulo de Quartos ---\n");
        printf("1. Cadastrar quarto\n");
        printf("2. Listar quartos\n");
        printf("3. Buscar quarto\n");
        printf("4. Alterar quarto\n");
        printf("5. Excluir quarto\n");
        printf("6. Alterar status do quarto\n");
        printf("7. Voltar\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: cadastrarQuarto(); break;
            case 2: listarQuartos(); break;
            case 3: buscarQuarto(); break;
            case 4: alterarQuarto(); break;
            case 5: excluirQuarto(); break;
            case 6: alterarStatusQuarto(); break;
            case 7: printf("Voltando...\n"); break;
            default: printf("Opção inválida!\n");
        }
    } while(opcao != 7);
}

// Programa principal para teste
int main(void) {
    menuQuartos();
    return 0;
}
