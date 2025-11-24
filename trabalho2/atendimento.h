// ===============================================
// atendimento.h
// Autor: Leonardo
// Módulo de controle de atendimento e estatísticas
// ===============================================

#ifndef ATENDIMENTO_H
#define ATENDIMENTO_H

#include "fila.h"

// Estrutura para armazenar o atendimento
typedef struct {
    // Contadores de atendimento
    int total_atendidos_comum;
    int total_atendidos_preferencial;

    // Contadores de itens
    int total_itens_comum;
    int total_itens_preferencial;

    // Contadores de tempo
    int tempo_total_comum;
    int tempo_total_preferencial;

    // Fila para guardar o histórico de clientes já atendidos
    Fila historico_atendimentos;

    // Variável para controlar a regra de alternância (2 comuns -> 1 preferencial)
    int contador_atendimento_comum;
} Atendimento;

// Funções de gerenciamento de atendimento e estatísticas

Atendimento* inicializarAtendimento();
void liberarAtendimento(Atendimento* a);
void atenderProximoCliente(Fila* fComum, Fila* fPreferencial, Atendimento* a);
void exibirHistoricoAtendimentos(Atendimento* a);
void exibirEstatisticasFinais(Atendimento* a);

#endif