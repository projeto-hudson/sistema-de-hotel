#ifndef FINANCEIRO_H
#define FINANCEIRO_H

#define MAX_FINANCEIRO 100
#define ARQUIVO_FINANCEIRO "financeiro.txt"

/* Estrutura de um registro financeiro */
typedef struct {
    int idReserva;
    char nomeHospede[50];
    int dias;
    float valorDiaria;
    float valorTotal;
    int pago; // 0 = pendente, 1 = pago
} Financeiro;

/* Variáveis globais */
extern Financeiro registros[MAX_FINANCEIRO];
extern int totalRegistros;

/* Funções principais */
void salvarFinanceiro(void);
void carregarFinanceiro(void);
void calcularHospedagem(void);
void registrarPagamento(void);
void emitirRecibo(void);
void menuFinanceiro(void);

#endif
