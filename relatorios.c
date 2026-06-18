#include <stdio.h>
#include <string.h>
 
#define MAX 100
 
/* ------------------------------------------------------------
   STRUCTS
   ------------------------------------------------------------ */
 
typedef struct {
    int numero;
    char tipo[30];        /* Standard, Luxo, Suite...        */
    float valorDiaria;
    char status[15];      /* "Ocupado" ou "Livre"             */
} Quarto;
 
typedef struct {
    int codigo;
    char hospede[50];
    int numeroQuarto;
    char dataCheckIn[15];   /* formato dd/mm/aaaa */
    char dataCheckOut[15];  /* formato dd/mm/aaaa */
    char status[15];        /* "Ativa", "Cancelada", "Concluida" */
    float valorTotal;
} Reserva;
 
typedef struct {
    char nome[40];         /* Cafe da manha, Lavanderia...     */
    int vezesUtilizado;
    float valorUnitario;
} Servico;
 
/* ------------------------------------------------------------
   PROTOTIPOS
   ------------------------------------------------------------ */
 
void menuRelatorios(Quarto quartos[], int totalQuartos,
                     Reserva reservas[], int totalReservas,
                     Servico servicos[], int totalServicos);
 
void relatorioQuartosOcupados(Quarto quartos[], int totalQuartos);
void relatorioQuartosLivres(Quarto quartos[], int totalQuartos);
void reservasPorPeriodo(Reserva reservas[], int totalReservas,
                         const char dataInicio[], const char dataFim[]);
void relatorioFaturamento(Reserva reservas[], int totalReservas);
void servicoMaisUtilizado(Servico servicos[], int totalServicos);
 
int validarData(const char data[]);
int dataParaInteiro(const char data[]);
void lerDataValidada(const char mensagem[], char destino[]);
int lerOpcaoInteira(void);
 
/* ============================================================
   MAIN DE TESTE
   (remover na integracao final com o grupo)
   ============================================================ */
 
int main(void)
{
    Quarto quartos[MAX] = {
        {101, "Standard", 150.00, "Ocupado"},
        {102, "Standard", 150.00, "Livre"},
        {201, "Luxo",      250.00, "Ocupado"},
        {202, "Luxo",      250.00, "Livre"},
        {301, "Suite",     400.00, "Ocupado"}
    };
    int totalQuartos = 5;
 
    Reserva reservas[MAX] = {
        {1, "Joao Silva",    101, "10/06/2026", "15/06/2026", "Concluida", 750.00},
        {2, "Maria Souza",   201, "12/06/2026", "18/06/2026", "Ativa",     1500.00},
        {3, "Pedro Lima",    301, "20/06/2026", "25/06/2026", "Ativa",     2000.00},
        {4, "Ana Costa",     102, "01/06/2026", "03/06/2026", "Cancelada", 300.00},
        {5, "Carlos Rocha",  202, "05/06/2026", "07/06/2026", "Concluida", 500.00}
    };
    int totalReservas = 5;
 
    Servico servicos[MAX] = {
        {"Cafe da manha", 12, 25.00},
        {"Lavanderia",     5, 40.00},
        {"Transporte",     8, 60.00},
        {"Restaurante",   15, 80.00}
    };
    int totalServicos = 4;
 
    menuRelatorios(quartos, totalQuartos,
                   reservas, totalReservas,
                   servicos, totalServicos);
 
    return 0;
}
 
/* ============================================================
   MENU PRINCIPAL DE RELATORIOS
   ============================================================ */
 
void menuRelatorios(Quarto quartos[], int totalQuartos,
                     Reserva reservas[], int totalReservas,
                     Servico servicos[], int totalServicos)
{
    int opcao;
    char dataInicio[15];
    char dataFim[15];
 
    do
    {
        printf("\n");
        printf("===== MENU RELATORIOS =====\n");
        printf("1 - Quartos Ocupados\n");
        printf("2 - Quartos Livres\n");
        printf("3 - Reservas por Periodo\n");
        printf("4 - Faturamento\n");
        printf("5 - Servico Mais Utilizado\n");
        printf("0 - Voltar\n");
        printf("Escolha uma opcao: ");
 
        opcao = lerOpcaoInteira();
 
        switch (opcao)
        {
            case 1:
                relatorioQuartosOcupados(quartos, totalQuartos);
                break;
 
            case 2:
                relatorioQuartosLivres(quartos, totalQuartos);
                break;
 
            case 3:
                lerDataValidada("Digite a data inicial (dd/mm/aaaa): ", dataInicio);
                lerDataValidada("Digite a data final   (dd/mm/aaaa): ", dataFim);
                reservasPorPeriodo(reservas, totalReservas, dataInicio, dataFim);
                break;
 
            case 4:
                relatorioFaturamento(reservas, totalReservas);
                break;
 
            case 5:
                servicoMaisUtilizado(servicos, totalServicos);
                break;
 
            case 0:
                printf("Voltando ao menu anterior...\n");
                break;
 
            default:
                printf("Opcao invalida! Tente novamente.\n");
                break;
        }
 
    } while (opcao != 0);
}
 
/* ============================================================
   FUNCOES AUXILIARES DE LEITURA / VALIDACAO
   ============================================================ */
 
/* Le a opcao do menu de forma segura, mesmo se o usuario digitar
   uma letra ou um caractere invalido (evita loop infinito). */
int lerOpcaoInteira(void)
{
    int valor;
    int resultado = scanf("%d", &valor);
 
    if (resultado != 1)
    {
        /* limpa o buffer de entrada em caso de erro */
        int c;
        while ((c = getchar()) != '\n' && c != EOF) { }
        return -1; /* opcao invalida, cai no "default" do switch */
    }
 
    return valor;
}
 
/* Valida se a string esta no formato dd/mm/aaaa e com valores
   plausiveis de dia, mes e ano. */
int validarData(const char data[])
{
    int dia, mes, ano;
 
    if (sscanf(data, "%d/%d/%d", &dia, &mes, &ano) != 3)
        return 0;
 
    if (dia < 1 || dia > 31)
        return 0;
 
    if (mes < 1 || mes > 12)
        return 0;
 
    if (ano < 1900 || ano > 2100)
        return 0;
 
    return 1;
}
 
/* Pede repetidamente uma data ao usuario ate que ela seja valida. */
void lerDataValidada(const char mensagem[], char destino[])
{
    int valida;
 
    do
    {
        printf("%s", mensagem);
        scanf("%14s", destino);
 
        valida = validarData(destino);
 
        if (!valida)
            printf("Data invalida! Use o formato dd/mm/aaaa.\n");
 
    } while (!valida);
}
 
/* Converte uma data dd/mm/aaaa para um inteiro no formato
   aaaammdd, facilitando a comparacao entre datas. */
int dataParaInteiro(const char data[])
{
    int dia, mes, ano;
    sscanf(data, "%d/%d/%d", &dia, &mes, &ano);
    return (ano * 10000) + (mes * 100) + dia;
}
 
/* ============================================================
   RELATORIO 1 - QUARTOS OCUPADOS
   ============================================================ */
 
void relatorioQuartosOcupados(Quarto quartos[], int totalQuartos)
{
    int contador = 0;
 
    printf("\n--- QUARTOS OCUPADOS ---\n");
 
    for (int i = 0; i < totalQuartos; i++)
    {
        if (strcmp(quartos[i].status, "Ocupado") == 0)
        {
            printf("Quarto %d | Tipo: %-10s | Diaria: R$ %.2f\n",
                   quartos[i].numero,
                   quartos[i].tipo,
                   quartos[i].valorDiaria);
            contador++;
        }
    }
 
    if (contador == 0)
        printf("Nenhum quarto ocupado no momento.\n");
 
    printf("Total de quartos ocupados: %d\n", contador);
}
 
/* ============================================================
   RELATORIO 2 - QUARTOS LIVRES
   ============================================================ */
 
void relatorioQuartosLivres(Quarto quartos[], int totalQuartos)
{
    int contador = 0;
 
    printf("\n--- QUARTOS LIVRES ---\n");
 
    for (int i = 0; i < totalQuartos; i++)
    {
        if (strcmp(quartos[i].status, "Livre") == 0)
        {
            printf("Quarto %d | Tipo: %-10s | Diaria: R$ %.2f\n",
                   quartos[i].numero,
                   quartos[i].tipo,
                   quartos[i].valorDiaria);
            contador++;
        }
    }
 
    if (contador == 0)
        printf("Nenhum quarto livre no momento.\n");
 
    printf("Total de quartos livres: %d\n", contador);
}
 
/* ============================================================
   RELATORIO 3 - RESERVAS POR PERIODO
   Lista as reservas cuja estadia (check-in a check-out) tem
   alguma intersecao com o periodo informado pelo usuario.
   ============================================================ */
 
void reservasPorPeriodo(Reserva reservas[], int totalReservas,
                         const char dataInicio[], const char dataFim[])
{
    int inicioBusca = dataParaInteiro(dataInicio);
    int fimBusca = dataParaInteiro(dataFim);
    int contador = 0;
 
    printf("\n--- RESERVAS ENTRE %s E %s ---\n", dataInicio, dataFim);
 
    for (int i = 0; i < totalReservas; i++)
    {
        int checkin = dataParaInteiro(reservas[i].dataCheckIn);
        int checkout = dataParaInteiro(reservas[i].dataCheckOut);
 
        /* ha intersecao se o inicio da estadia for antes do fim
           da busca E o fim da estadia for depois do inicio da busca */
        if (checkin <= fimBusca && checkout >= inicioBusca)
        {
            printf("Reserva %d | Hospede: %-15s | Quarto: %d | %s a %s | Status: %s\n",
                   reservas[i].codigo,
                   reservas[i].hospede,
                   reservas[i].numeroQuarto,
                   reservas[i].dataCheckIn,
                   reservas[i].dataCheckOut,
                   reservas[i].status);
            contador++;
        }
    }
 
    if (contador == 0)
        printf("Nenhuma reserva encontrada nesse periodo.\n");
 
    printf("Total de reservas no periodo: %d\n", contador);
}
 
/* ============================================================
   RELATORIO 4 - FATURAMENTO
   Considera apenas reservas Ativas ou Concluidas (reservas
   canceladas nao entram no faturamento).
   ============================================================ */
 
void relatorioFaturamento(Reserva reservas[], int totalReservas)
{
    float faturamentoTotal = 0;
    int totalConsideradas = 0;
    int totalCanceladas = 0;
 
    printf("\n--- RELATORIO DE FATURAMENTO ---\n");
 
    for (int i = 0; i < totalReservas; i++)
    {
        if (strcmp(reservas[i].status, "Cancelada") == 0)
        {
            totalCanceladas++;
            continue;
        }
 
        faturamentoTotal += reservas[i].valorTotal;
        totalConsideradas++;
    }
 
    printf("Reservas consideradas no faturamento: %d\n", totalConsideradas);
    printf("Reservas canceladas (nao contabilizadas): %d\n", totalCanceladas);
    printf("Faturamento total: R$ %.2f\n", faturamentoTotal);
}
 
/* ============================================================
   RELATORIO 5 - SERVICO MAIS UTILIZADO
   ============================================================ */
 
void servicoMaisUtilizado(Servico servicos[], int totalServicos)
{
    if (totalServicos == 0)
    {
        printf("\nNenhum servico cadastrado.\n");
        return;
    }
 
    int indiceMax = 0;
 
    for (int i = 1; i < totalServicos; i++)
    {
        if (servicos[i].vezesUtilizado > servicos[indiceMax].vezesUtilizado)
            indiceMax = i;
    }
 
    printf("\n--- SERVICO MAIS UTILIZADO ---\n");
    printf("Servico: %s\n", servicos[indiceMax].nome);
    printf("Quantidade de utilizacoes: %d\n", servicos[indiceMax].vezesUtilizado);
    printf("Valor unitario: R$ %.2f\n", servicos[indiceMax].valorUnitario);
}
