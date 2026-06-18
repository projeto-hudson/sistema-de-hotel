#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FINANCEIRO 100
#define ARQUIVO_FINANCEIRO "financeiro.txt"

typedef struct {
    int idReserva;
    char nomeHospede[50];
    int dias;
    float valorDiaria;
    float valorTotal;
    int pago; // 0 = pendente, 1 = pago
} Financeiro;

Financeiro registros[MAX_FINANCEIRO];
int totalRegistros = 0;

// Salvar registros no arquivo
void salvarFinanceiro() {
    FILE *f = fopen(ARQUIVO_FINANCEIRO, "w");
    if (f == NULL) {
        printf("Erro ao abrir arquivo financeiro!\n");
        return;
    }
    for (int i = 0; i < totalRegistros; i++) {
        fprintf(f, "%d;%s;%d;%.2f;%.2f;%d\n",
                registros[i].idReserva,
                registros[i].nomeHospede,
                registros[i].dias,
                registros[i].valorDiaria,
                registros[i].valorTotal,
                registros[i].pago);
    }
    fclose(f);
}

// Carregar registros do arquivo
void carregarFinanceiro() {
    FILE *f = fopen(ARQUIVO_FINANCEIRO, "r");
    if (f == NULL) return;
    while (fscanf(f, "%d;%49[^;];%d;%f;%f;%d\n",
                  &registros[totalRegistros].idReserva,
                  registros[totalRegistros].nomeHospede,
                  &registros[totalRegistros].dias,
                  &registros[totalRegistros].valorDiaria,
                  &registros[totalRegistros].valorTotal,
                  &registros[totalRegistros].pago) == 6) {
        totalRegistros++;
    }
    fclose(f);
}

// Calcular hospedagem
void calcularHospedagem() {
    Financeiro f;
    printf("ID da reserva: ");
    scanf("%d", &f.idReserva);
    printf("Nome do hóspede: ");
    scanf(" %[^\n]", f.nomeHospede);
    printf("Quantidade de dias: ");
    scanf("%d", &f.dias);
    printf("Valor da diária: ");
    scanf("%f", &f.valorDiaria);

    f.valorTotal = f.dias * f.valorDiaria;
    f.pago = 0; // começa como pendente

    registros[totalRegistros++] = f;
    salvarFinanceiro();

    printf("Valor total da hospedagem: R$ %.2f\n", f.valorTotal);
}

// Registrar pagamento
void registrarPagamento() {
    int id;
    printf("Digite o ID da reserva para registrar pagamento: ");
    scanf("%d", &id);

    for (int i = 0; i < totalRegistros; i++) {
        if (registros[i].idReserva == id) {
            registros[i].pago = 1;
            salvarFinanceiro();
            printf("Pagamento registrado com sucesso!\n");
            return;
        }
    }
    printf("Registro financeiro não encontrado!\n");
}

// Emitir recibo
void emitirRecibo() {
    int id;
    printf("Digite o ID da reserva para emitir recibo: ");
    scanf("%d", &id);

    for (int i = 0; i < totalRegistros; i++) {
        if (registros[i].idReserva == id && registros[i].pago == 1) {
            printf("\n--- Recibo ---\n");
            printf("Reserva: %d\n", registros[i].idReserva);
            printf("Hóspede: %s\n", registros[i].nomeHospede);
            printf("Dias: %d\n", registros[i].dias);
            printf("Valor diária: R$ %.2f\n", registros[i].valorDiaria);
            printf("Total pago: R$ %.2f\n", registros[i].valorTotal);
            printf("-----------------\n");
            return;
        }
    }
    printf("Recibo não disponível (reserva não encontrada ou pagamento pendente).\n");
}

// Menu financeiro
void menuFinanceiro() {
    int opcao;
    do {
        printf("\n--- Módulo Financeiro ---\n");
        printf("1. Calcular hospedagem\n");
        printf("2. Registrar pagamento\n");
        printf("3. Emitir recibo\n");
        printf("4. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: calcularHospedagem(); break;
            case 2: registrarPagamento(); break;
            case 3: emitirRecibo(); break;
            case 4: printf("Saindo...\n"); break;
            default: printf("Opção inválida!\n");
        }
    } while (opcao != 4);
}

int main() {
    carregarFinanceiro();
    menuFinanceiro();
    return 0;
}
