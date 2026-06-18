#include <stdio.h>
#include "financeiro.h"
#include "modulo_de_hospedes.h"
#include "modulo_de_quartos.h"
#include "modulo_de_reservas.h"
#include "modulo_de_servicos.h"
#include "relatorios.h"

int main() {
    int opcao;
    do {
        printf("\n===== SISTEMA DE HOTEL =====\n");
        printf("1 - Módulo de Hóspedes\n");
        printf("2 - Módulo de Quartos\n");
        printf("3 - Módulo de Reservas\n");
        printf("4 - Módulo de Serviços\n");
        printf("5 - Módulo Financeiro\n");
        printf("6 - Relatórios\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: menuHospedes(); break;
            case 2: menuQuartos(); break;
            case 3: menuReservas(); break;
            case 4: menuServicos(); break;
            case 5: menuFinanceiro(); break;
            case 6: menuRelatorios(quartos, totalQuartos, reservas, totalReservas, servicos, totalServicos); break;
            case 0: printf("Encerrando sistema...\n"); break;
            default: printf("Opção inválida!\n");
        }
    } while(opcao != 0);

    return 0;
}
