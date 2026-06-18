#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SERVICOS 200
#define ARQUIVO_SERVICOS "servicos.txt"

typedef struct {
    int idServico;
    int idReserva;
    char tipo[20];       // Café, Lavanderia, Transporte, Restaurante
    int quantidade;
    float precoUnitario;
    float valorTotal;
} Servico;

Servico servicos[MAX_SERVICOS];
int totalServicos = 0;

// Salvar serviços
void salvarServicos() {
    FILE *f = fopen(ARQUIVO_SERVICOS, "w");
    if (!f) {
        printf("Erro ao abrir arquivo!\n");
        return;
    }
    for (int i = 0; i < totalServicos; i++) {
        fprintf(f, "%d;%d;%s;%d;%.2f;%.2f\n",
                servicos[i].idServico,
                servicos[i].idReserva,
                servicos[i].tipo,
                servicos[i].quantidade,
                servicos[i].precoUnitario,
                servicos[i].valorTotal);
    }
    fclose(f);
}

// Carregar serviços
void carregarServicos() {
    FILE *f = fopen(ARQUIVO_SERVICOS, "r");
    if (!f) return;
    while (fscanf(f, "%d;%d;%19[^;];%d;%f;%f\n",
                  &servicos[totalServicos].idServico,
                  &servicos[totalServicos].idReserva,
                  servicos[totalServicos].tipo,
                  &servicos[totalServicos].quantidade,
                  &servicos[totalServicos].precoUnitario,
                  &servicos[totalServicos].valorTotal) == 6) {
        totalServicos++;
    }
    fclose(f);
}

// Registrar serviço
void registrarServico() {
    if (totalServicos >= MAX_SERVICOS) {
        printf("Limite atingido!\n");
        return;
    }
    Servico s;
    s.idServico = totalServicos + 1;
    printf("ID da reserva: ");
    scanf("%d", &s.idReserva);

    int opcao;
    printf("Escolha o serviço:\n1. Café da manhã\n2. Lavanderia\n3. Transporte\n4. Restaurante\n");
    scanf("%d", &opcao);

    switch(opcao) {
        case 1: strcpy(s.tipo, "Café da manhã"); s.precoUnitario = 25.0; break;
        case 2: strcpy(s.tipo, "Lavanderia"); s.precoUnitario = 15.0; break;
        case 3: strcpy(s.tipo, "Transporte"); s.precoUnitario = 50.0; break;
        case 4: strcpy(s.tipo, "Restaurante"); s.precoUnitario = 60.0; break;
        default: printf("Serviço inválido!\n"); return;
    }

    printf("Quantidade: ");
    scanf("%d", &s.quantidade);

    s.valorTotal = s.quantidade * s.precoUnitario;
    servicos[totalServicos++] = s;
    salvarServicos();

    printf("Serviço registrado: %s | Total: R$ %.2f\n", s.tipo, s.valorTotal);
}

// Listar serviços
void listarServicos() {
    printf("\n--- Serviços registrados ---\n");
    for (int i = 0; i < totalServicos; i++) {
        printf("ID: %d | Reserva: %d | Serviço: %s | Qtd: %d | Unitário: R$ %.2f | Total: R$ %.2f\n",
               servicos[i].idServico,
               servicos[i].idReserva,
               servicos[i].tipo,
               servicos[i].quantidade,
               servicos[i].precoUnitario,
               servicos[i].valorTotal);
    }
}

// Menu de serviços
void menuServicos() {
    int opcao;
    do {
        printf("\n--- Módulo de Serviços ---\n");
        printf("1. Registrar serviço\n");
        printf("2. Listar serviços\n");
        printf("3. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: registrarServico(); break;
            case 2: listarServicos(); break;
            case 3: printf("Saindo...\n"); break;
            default: printf("Opção inválida!\n");
        }
    } while(opcao != 3);
}

int main() {
    carregarServicos();
    menuServicos();
    return 0;
}
