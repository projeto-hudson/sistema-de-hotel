#ifndef SERVICOS_H
#define SERVICOS_H

#define MAX_SERVICOS 200
#define ARQUIVO_SERVICOS "servicos.txt"

/* Estrutura de um serviço */
typedef struct {
    int idServico;
    int idReserva;
    char tipo[20];       /* Café da manhã, Lavanderia, Transporte, Restaurante */
    int quantidade;
    float precoUnitario;
    float valorTotal;
} Servico;

/* Variáveis globais */
extern Servico servicos[MAX_SERVICOS];
extern int totalServicos;

/* Funções principais */
void salvarServicos(void);
void carregarServicos(void);
void registrarServico(void);
void listarServicos(void);
void menuServicos(void);

#endif
