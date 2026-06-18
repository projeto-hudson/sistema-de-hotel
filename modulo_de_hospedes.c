#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_HOSPEDES 100
#define ARQUIVO "hospedes.txt"

typedef struct {
    int id;
    char nome[50];
    char cpf[15];
    char telefone[20];
} Hospede;

Hospede hospedes[MAX_HOSPEDES];
int totalHospedes = 0;

// Função para salvar hóspedes no arquivo
void salvarHospedes() {
    FILE *f = fopen(ARQUIVO, "w");
    if (f == NULL) {
        printf("Erro ao abrir arquivo para salvar!\n");
        return;
    }
    for (int i = 0; i < totalHospedes; i++) {
        fprintf(f, "%d;%s;%s;%s\n",
                hospedes[i].id,
                hospedes[i].nome,
                hospedes[i].cpf,
                hospedes[i].telefone);
    }
    fclose(f);
}

// Função para carregar hóspedes do arquivo
void carregarHospedes() {
    FILE *f = fopen(ARQUIVO, "r");
    if (f == NULL) {
        return; // Se não existir, começa vazio
    }
    while (fscanf(f, "%d;%49[^;];%14[^;];%19[^\n]\n",
                  &hospedes[totalHospedes].id,
                  hospedes[totalHospedes].nome,
                  hospedes[totalHospedes].cpf,
                  hospedes[totalHospedes].telefone) == 4) {
        totalHospedes++;
    }
    fclose(f);
}

// Cadastrar hóspede
void cadastrarHospede() {
    if (totalHospedes >= MAX_HOSPEDES) {
        printf("Limite de hóspedes atingido!\n");
        return;
    }
    Hospede h;
    h.id = totalHospedes + 1;
    printf("Nome: ");
    scanf(" %[^\n]", h.nome);
    printf("CPF: ");
    scanf(" %[^\n]", h.cpf);
    printf("Telefone: ");
    scanf(" %[^\n]", h.telefone);

    hospedes[totalHospedes] = h;
    totalHospedes++;
    salvarHospedes();
    printf("Hóspede cadastrado com sucesso!\n");
}

// Buscar hóspede por CPF
void buscarHospede() {
    char cpf[15];
    printf("Digite o CPF do hóspede: ");
    scanf(" %[^\n]", cpf);

    for (int i = 0; i < totalHospedes; i++) {
        if (strcmp(hospedes[i].cpf, cpf) == 0) {
            printf("ID: %d\nNome: %s\nCPF: %s\nTelefone: %s\n",
                   hospedes[i].id, hospedes[i].nome, hospedes[i].cpf, hospedes[i].telefone);
            return;
        }
    }
    printf("Hóspede não encontrado!\n");
}

// Alterar hóspede por CPF
void alterarHospede() {
    char cpf[15];
    printf("Digite o CPF do hóspede que deseja alterar: ");
    scanf(" %[^\n]", cpf);

    for (int i = 0; i < totalHospedes; i++) {
        if (strcmp(hospedes[i].cpf, cpf) == 0) {
            printf("Novo nome: ");
            scanf(" %[^\n]", hospedes[i].nome);
            printf("Novo CPF: ");
            scanf(" %[^\n]", hospedes[i].cpf);
            printf("Novo telefone: ");
            scanf(" %[^\n]", hospedes[i].telefone);
            salvarHospedes();
            printf("Dados alterados com sucesso!\n");
            return;
        }
    }
    printf("Hóspede não encontrado!\n");
}

// Excluir hóspede por CPF
void excluirHospede() {
    char cpf[15];
    printf("Digite o CPF do hóspede a excluir: ");
    scanf(" %[^\n]", cpf);

    for (int i = 0; i < totalHospedes; i++) {
        if (strcmp(hospedes[i].cpf, cpf) == 0) {
            for (int j = i; j < totalHospedes - 1; j++) {
                hospedes[j] = hospedes[j + 1];
            }
            totalHospedes--;
            salvarHospedes();
            printf("Hóspede excluído com sucesso!\n");
            return;
        }
    }
    printf("Hóspede não encontrado!\n");
}

// Menu principal
int main() {
    carregarHospedes(); // Carrega dados ao iniciar
    int opcao;
    do {
        printf("\n--- Módulo de Hóspedes ---\n");
        printf("1. Cadastrar\n");
        printf("2. Buscar\n");
        printf("3. Alterar\n");
        printf("4. Excluir\n");
        printf("5. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: cadastrarHospede(); break;
            case 2: buscarHospede(); break;
            case 3: alterarHospede(); break;
            case 4: excluirHospede(); break;
            case 5: printf("Saindo...\n"); break;
            default: printf("Opção inválida!\n");
        }
    } while (opcao != 5);

    return 0;
}
