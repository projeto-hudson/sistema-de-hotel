#ifndef HOSPEDES_H
#define HOSPEDES_H

#define MAX_HOSPEDES 100

typedef struct {
    int id;
    char nome[50];
    char cpf[15];
    char telefone[20];
} Hospede;

void menuHospedes();
void cadastrarHospede();
void buscarHospede();
void alterarHospede();
void excluirHospede();

#endif
