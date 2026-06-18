#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RESERVAS   100
#define TAM_NOME       50
#define TAM_DATA       16   /* formato DD/MM/AAAA + folga para '\n' e '\0' no fgets */
#define ARQUIVO        "reservas.dat"

/* Status possíveis de uma reserva */
typedef enum {
    RESERVADO = 0,
    CHECKIN   = 1,
    CHECKOUT  = 2
} Status;

typedef struct {
    int  codigo;                 /* identificador único da reserva */
    int  numeroQuarto;
    char nomeHospede[TAM_NOME];
    char dataEntrada[TAM_DATA];
    char dataSaida[TAM_DATA];
    Status status;
    int  ativa;                  /* 1 = existe / 0 = removida (cancelada) */
} Reserva;

Reserva reservas[MAX_RESERVAS];
int totalReservas = 0;
int proximoCodigo = 1;

/* ---------------------- Funções de apoio ---------------------- */

void limparBufferEntrada(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        /* descarta o restante da linha */
    }
}

void lerTexto(const char *mensagem, char *destino, int tamanho) {
    printf("%s", mensagem);
    if (fgets(destino, tamanho, stdin) != NULL) {
        size_t len = strlen(destino);
        if (len > 0 && destino[len - 1] == '\n') {
            destino[len - 1] = '\0';
        }
    }
}

int lerInteiro(const char *mensagem) {
    int valor;
    while (1) {
        printf("%s", mensagem);
        if (scanf("%d", &valor) == 1) {
            limparBufferEntrada();
            return valor;
        }
        printf("Entrada invalida. Digite apenas numeros.\n");
        limparBufferEntrada();
    }
}

const char *statusParaTexto(Status s) {
    switch (s) {
        case RESERVADO: return "Reservado";
        case CHECKIN:   return "Check-in realizado";
        case CHECKOUT:  return "Check-out realizado";
        default:        return "Desconhecido";
    }
}

/* ---------------------- Persistência em arquivo ---------------------- */

void salvarDados(void) {
    FILE *f = fopen(ARQUIVO, "w");
    if (f == NULL) {
        printf("Erro: nao foi possivel salvar os dados em '%s'.\n", ARQUIVO);
        return;
    }

    fprintf(f, "%d %d\n", totalReservas, proximoCodigo);
    for (int i = 0; i < totalReservas; i++) {
        fprintf(f, "%d|%d|%s|%s|%s|%d|%d\n",
                reservas[i].codigo,
                reservas[i].numeroQuarto,
                reservas[i].nomeHospede,
                reservas[i].dataEntrada,
                reservas[i].dataSaida,
                reservas[i].status,
                reservas[i].ativa);
    }
    fclose(f);
}

void carregarDados(void) {
    FILE *f = fopen(ARQUIVO, "r");
    if (f == NULL) {
        /* Arquivo ainda nao existe: comeca com lista vazia */
        return;
    }

    if (fscanf(f, "%d %d\n", &totalReservas, &proximoCodigo) != 2) {
        fclose(f);
        totalReservas = 0;
        proximoCodigo = 1;
        return;
    }

    for (int i = 0; i < totalReservas; i++) {
        int status, ativa;
        if (fscanf(f, "%d|%d|%49[^|]|%15[^|]|%15[^|]|%d|%d\n",
                   &reservas[i].codigo,
                   &reservas[i].numeroQuarto,
                   reservas[i].nomeHospede,
                   reservas[i].dataEntrada,
                   reservas[i].dataSaida,
                   &status,
                   &ativa) != 7) {
            break;
        }
        reservas[i].status = (Status) status;
        reservas[i].ativa  = ativa;
    }
    fclose(f);
}

/* ---------------------- Busca ---------------------- */

int buscarIndicePorCodigo(int codigo) {
    for (int i = 0; i < totalReservas; i++) {
        if (reservas[i].ativa && reservas[i].codigo == codigo) {
            return i;
        }
    }
    return -1;
}

int quartoOcupado(int numeroQuarto, int codigoIgnorar) {
    for (int i = 0; i < totalReservas; i++) {
        if (reservas[i].ativa &&
            reservas[i].codigo != codigoIgnorar &&
            reservas[i].numeroQuarto == numeroQuarto &&
            reservas[i].status != CHECKOUT) {
            return 1;
        }
    }
    return 0;
}

/* ---------------------- Operacoes principais ---------------------- */

void criarReserva(void) {
    if (totalReservas >= MAX_RESERVAS) {
        printf("\nLimite maximo de reservas atingido.\n");
        return;
    }

    printf("\n--- Criar Reserva ---\n");

    int numeroQuarto = lerInteiro("Numero do quarto: ");

    if (quartoOcupado(numeroQuarto, -1)) {
        printf("Este quarto ja esta reservado/ocupado no momento.\n");
        return;
    }

    Reserva r;
    r.codigo = proximoCodigo++;
    r.numeroQuarto = numeroQuarto;
    lerTexto("Nome do hospede: ", r.nomeHospede, TAM_NOME);
    lerTexto("Data de entrada (DD/MM/AAAA): ", r.dataEntrada, TAM_DATA);
    lerTexto("Data de saida   (DD/MM/AAAA): ", r.dataSaida, TAM_DATA);
    r.status = RESERVADO;
    r.ativa  = 1;

    reservas[totalReservas++] = r;
    salvarDados();

    printf("\nReserva criada com sucesso! Codigo da reserva: %d\n", r.codigo);
}

void listarReservas(void) {
    printf("\n--- Lista de Reservas ---\n");

    int existeAlguma = 0;
    for (int i = 0; i < totalReservas; i++) {
        if (reservas[i].ativa) {
            existeAlguma = 1;
            printf("Codigo: %d | Quarto: %d | Hospede: %s | Entrada: %s | "
                   "Saida: %s | Status: %s\n",
                   reservas[i].codigo,
                   reservas[i].numeroQuarto,
                   reservas[i].nomeHospede,
                   reservas[i].dataEntrada,
                   reservas[i].dataSaida,
                   statusParaTexto(reservas[i].status));
        }
    }

    if (!existeAlguma) {
        printf("Nenhuma reserva cadastrada.\n");
    }
}

void cancelarReserva(void) {
    printf("\n--- Cancelar Reserva ---\n");
    listarReservas();

    int codigo = lerInteiro("\nDigite o codigo da reserva a cancelar: ");
    int idx = buscarIndicePorCodigo(codigo);

    if (idx == -1) {
        printf("Reserva nao encontrada.\n");
        return;
    }

    if (reservas[idx].status == CHECKIN) {
        printf("Atencao: hospede ja fez check-in. ");
    }

    char confirmacao[10];
    lerTexto("Confirma o cancelamento? (s/n): ", confirmacao, sizeof(confirmacao));

    if (confirmacao[0] == 's' || confirmacao[0] == 'S') {
        reservas[idx].ativa = 0;
        salvarDados();
        printf("Reserva %d cancelada com sucesso.\n", codigo);
    } else {
        printf("Cancelamento abortado.\n");
    }
}

void alterarReserva(void) {
    printf("\n--- Alterar Reserva ---\n");
    listarReservas();

    int codigo = lerInteiro("\nDigite o codigo da reserva a alterar: ");
    int idx = buscarIndicePorCodigo(codigo);

    if (idx == -1) {
        printf("Reserva nao encontrada.\n");
        return;
    }

    if (reservas[idx].status == CHECKOUT) {
        printf("Esta reserva ja teve check-out e nao pode ser alterada.\n");
        return;
    }

    printf("\nDeixe em branco (apenas Enter) para manter o valor atual.\n");

    int novoQuarto;
    char buffer[TAM_NOME];

    printf("Quarto atual: %d\n", reservas[idx].numeroQuarto);
    printf("Novo numero do quarto (ou Enter para manter): ");
    if (fgets(buffer, sizeof(buffer), stdin) != NULL && buffer[0] != '\n') {
        novoQuarto = atoi(buffer);
        if (novoQuarto > 0 && !quartoOcupado(novoQuarto, codigo)) {
            reservas[idx].numeroQuarto = novoQuarto;
        } else if (novoQuarto > 0) {
            printf("Quarto indisponivel. Mantendo o quarto atual.\n");
        }
    }

    printf("Hospede atual: %s\n", reservas[idx].nomeHospede);
    printf("Novo nome do hospede (ou Enter para manter): ");
    if (fgets(buffer, sizeof(buffer), stdin) != NULL && buffer[0] != '\n') {
        buffer[strcspn(buffer, "\n")] = '\0';
        strncpy(reservas[idx].nomeHospede, buffer, TAM_NOME - 1);
        reservas[idx].nomeHospede[TAM_NOME - 1] = '\0';
    }

    char bufferData[TAM_DATA];

    printf("Data de entrada atual: %s\n", reservas[idx].dataEntrada);
    printf("Nova data de entrada (ou Enter para manter): ");
    if (fgets(bufferData, sizeof(bufferData), stdin) != NULL && bufferData[0] != '\n') {
        bufferData[strcspn(bufferData, "\n")] = '\0';
        strncpy(reservas[idx].dataEntrada, bufferData, TAM_DATA - 1);
        reservas[idx].dataEntrada[TAM_DATA - 1] = '\0';
    }

    printf("Data de saida atual: %s\n", reservas[idx].dataSaida);
    printf("Nova data de saida (ou Enter para manter): ");
    if (fgets(bufferData, sizeof(bufferData), stdin) != NULL && bufferData[0] != '\n') {
        bufferData[strcspn(bufferData, "\n")] = '\0';
        strncpy(reservas[idx].dataSaida, bufferData, TAM_DATA - 1);
        reservas[idx].dataSaida[TAM_DATA - 1] = '\0';
    }

    salvarDados();
    printf("\nReserva %d atualizada com sucesso.\n", codigo);
}

void fazerCheckin(void) {
    printf("\n--- Check-in ---\n");
    listarReservas();

    int codigo = lerInteiro("\nDigite o codigo da reserva para check-in: ");
    int idx = buscarIndicePorCodigo(codigo);

    if (idx == -1) {
        printf("Reserva nao encontrada.\n");
        return;
    }

    if (reservas[idx].status == CHECKIN) {
        printf("Esta reserva ja possui check-in realizado.\n");
        return;
    }
    if (reservas[idx].status == CHECKOUT) {
        printf("Esta reserva ja teve check-out e nao pode mais fazer check-in.\n");
        return;
    }

    reservas[idx].status = CHECKIN;
    salvarDados();

    printf("Check-in realizado com sucesso para %s (quarto %d).\n",
           reservas[idx].nomeHospede, reservas[idx].numeroQuarto);
}

void fazerCheckout(void) {
    printf("\n--- Check-out ---\n");
    listarReservas();

    int codigo = lerInteiro("\nDigite o codigo da reserva para check-out: ");
    int idx = buscarIndicePorCodigo(codigo);

    if (idx == -1) {
        printf("Reserva nao encontrada.\n");
        return;
    }

    if (reservas[idx].status == CHECKOUT) {
        printf("Esta reserva ja possui check-out realizado.\n");
        return;
    }
    if (reservas[idx].status != CHECKIN) {
        printf("Nao e possivel fazer check-out sem check-in previo.\n");
        return;
    }

    reservas[idx].status = CHECKOUT;
    salvarDados();

    printf("Check-out realizado com sucesso para %s (quarto %d).\n",
           reservas[idx].nomeHospede, reservas[idx].numeroQuarto);
}

/* ---------------------- Menu principal ---------------------- */

void exibirMenu(void) {
    printf("\n===========================================\n");
    printf("      SISTEMA DE RESERVAS DE QUARTOS\n");
    printf("===========================================\n");
    printf("1. Criar reserva\n");
    printf("2. Cancelar reserva\n");
    printf("3. Alterar reserva\n");
    printf("4. Check-in\n");
    printf("5. Check-out\n");
    printf("6. Listar reservas\n");
    printf("0. Sair\n");
    printf("===========================================\n");
}

int main(void) {
    carregarDados();

    int opcao;
    do {
        exibirMenu();
        opcao = lerInteiro("Escolha uma opcao: ");

        switch (opcao) {
            case 1: criarReserva();   break;
            case 2: cancelarReserva(); break;
            case 3: alterarReserva(); break;
            case 4: fazerCheckin();   break;
            case 5: fazerCheckout();  break;
            case 6: listarReservas(); break;
            case 0: printf("\nSaindo do sistema. Ate logo!\n"); break;
            default: printf("\nOpcao invalida. Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}
