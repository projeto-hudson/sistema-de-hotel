#ifndef RESERVAS_H
#define RESERVAS_H

#define MAX_RESERVAS   100
#define TAM_NOME       50
#define TAM_DATA       16   /* formato DD/MM/AAAA + folga para '\n' e '\0' */
#define ARQUIVO        "reservas.dat"

/* Status possíveis de uma reserva */
typedef enum {
    RESERVADO = 0,
    CHECKIN   = 1,
    CHECKOUT  = 2
} Status;

/* Estrutura de uma reserva */
typedef struct {
    int  codigo;                 /* identificador único da reserva */
    int  numeroQuarto;
    char nomeHospede[TAM_NOME];
    char dataEntrada[TAM_DATA];
    char dataSaida[TAM_DATA];
    Status status;
    int  ativa;                  /* 1 = existe / 0 = removida (cancelada) */
} Reserva;

/* Variáveis globais */
extern Reserva reservas[MAX_RESERVAS];
extern int totalReservas;
extern int proximoCodigo;

/* Funções auxiliares */
void limparBufferEntrada(void);
void lerTexto(const char *mensagem, char *destino, int tamanho);
int lerInteiro(const char *mensagem);
const char *statusParaTexto(Status s);

/* Persistência */
void salvarDados(void);
void carregarDados(void);

/* Busca */
int buscarIndicePorCodigo(int codigo);
int quartoOcupado(int numeroQuarto, int codigoIgnorar);

/* Operações principais */
void criarReserva(void);
void listarReservas(void);
void cancelarReserva(void);
void alterarReserva(void);
void fazerCheckin(void);
void fazerCheckout(void);

/* Menu */
void menuReservas(void);

#endif
