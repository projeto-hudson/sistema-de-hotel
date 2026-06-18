#ifndef QUARTOS_H
#define QUARTOS_H

#define MAX_QUARTOS 100

/* Estrutura de um quarto */
typedef struct {
    int numero;
    char tipo[30];        /* Standard, Luxo, Suite... */
    float valorDiaria;
    char status[15];      /* "Ocupado" ou "Livre" */
} Quarto;

/* Variáveis globais */
extern Quarto quartos[MAX_QUARTOS];
extern int totalQuartos;

/* Funções principais do módulo de quartos */
void cadastrarQuarto(void);
void listarQuartos(void);
void buscarQuarto(void);
void alterarQuarto(void);
void excluirQuarto(void);
void alterarStatusQuarto(void);
void menuQuartos(void);

#endif
