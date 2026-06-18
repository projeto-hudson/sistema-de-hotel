#ifndef RELATORIOS_H
#define RELATORIOS_H

#include "modulo_de_quartos.h"
#include "modulo_de_reservas.h"
#include "modulo_de_servicos.h"

/* Funções principais do módulo de relatórios */
void menuRelatorios(Quarto quartos[], int totalQuartos,
                    Reserva reservas[], int totalReservas,
                    Servico servicos[], int totalServicos);

void relatorioQuartosOcupados(Quarto quartos[], int totalQuartos);
void relatorioQuartosLivres(Quarto quartos[], int totalQuartos);
void reservasPorPeriodo(Reserva reservas[], int totalReservas,
                        const char dataInicio[], const char dataFim[]);
void relatorioFaturamento(Reserva reservas[], int totalReservas);
void servicoMaisUtilizado(Servico servicos[], int totalServicos);

/* Funções auxiliares */
int validarData(const char data[]);
int dataParaInteiro(const char data[]);
void lerDataValidada(const char mensagem[], char destino[]);
int lerOpcaoInteira(void);

#endif
