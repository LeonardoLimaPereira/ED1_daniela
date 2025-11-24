// ===============================================
// atendimento.c
// Autor: Leonardo
// Implementa a lógica de atendimento 
// ===============================================

#include <stdio.h>
#include <stdlib.h>
#include "atendimento.h"

/**
 * Aloca memória para a estrutura de estatísticas e zera todos os seus
 * contadores. Também inicializa a fila que servirá como histórico.
 */
Atendimento* inicializarAtendimento() {
    Atendimento* a = (Atendimento*) malloc(sizeof(Atendimento));
    if (a == NULL) {
        printf("Erro de alocação de memoria para estatisticas.\n");
        exit(1);
    }

    a->total_atendidos_comum = 0;
    a->total_atendidos_preferencial = 0;
    a->total_itens_comum = 0;
    a->total_itens_preferencial = 0;
    a->tempo_total_comum = 0;
    a->tempo_total_preferencial = 0;
    a->contador_atendimento_comum = 0;

    inicializarFila(&a->historico_atendimentos);

    return a;
}

/**
 * Libera a fila de histórico e, em seguida, a própria estrutura de estatísticas.
 */
void liberarAtendimento(Atendimento* a) {
    if (a) {
        liberarFila(&a->historico_atendimentos);
        free(a);
    }
}

/**
 * Implementa a regra de alternância: 2 clientes comuns para 1 preferencial.
 * Prioriza a fila preferencial.
 * Após desenfileirar o cliente, atualiza os contadores e o adiciona ao histórico.
 */
void atenderProximoCliente(Fila* fComum, Fila* fPreferencial, Atendimento* a) {
    Cliente cliente_atendido;
    int atendeu = 0;

    // Regra de atendimento:
    // 1. Atende preferencial se a fila comum estiver vazia e a preferencial não
    // 2. Atende preferencial se for a vez dele (após 2 comuns) e a fila não estiver vazia.
    // 3. Caso contrário, atende comum se a fila não estiver vazia.
    if (!filaVazia(fPreferencial) && (filaVazia(fComum) || a->contador_atendimento_comum >= 2)) {
        cliente_atendido = desenfileirar(fPreferencial);
        a->total_atendidos_preferencial++;
        a->total_itens_preferencial += cliente_atendido.itens;
        a->tempo_total_preferencial += cliente_atendido.tempoAtendimento;
        a->contador_atendimento_comum = 0; // Reseta o contador de comuns
        atendeu = 1;
    } else if (!filaVazia(fComum)) {
        cliente_atendido = desenfileirar(fComum);
        a->total_atendidos_comum++;
        a->total_itens_comum += cliente_atendido.itens;
        a->tempo_total_comum += cliente_atendido.tempoAtendimento;
        a->contador_atendimento_comum++; // Incrementa o contador de comuns
        atendeu = 1;
    }

    if (atendeu) {
        printf("\n--- Cliente Atendido ---\n");
        imprimirCliente(&cliente_atendido);
        enfileirar(&a->historico_atendimentos, cliente_atendido);
    } else {
        printf("\nNenhum cliente nas filas para atender.\n");
    }
}

/**
 * Utiliza a função de exibir fila para mostrar o conteúdo do histórico.
 */
void exibirHistoricoAtendimentos(Atendimento* a) {
    printf("\n--- HISTORICO DE ATENDIMENTOS ---\n");
    exibirFila(&a->historico_atendimentos, "Histórico");
}

/**
 * Calcula e imprime a quantidade de atendimentos, total de itens e tempo médio
 * para cada tipo de fila (comum e preferencial).
 */
void exibirEstatisticasFinais(Atendimento* a) {
    printf("\n--- ESTATISTICAS FINAIS ---\n");

    // Estatísticas da Fila Comum
    int atendidos_comum = a->total_atendidos_comum;
    double tempo_medio_comum = (atendidos_comum > 0) ? (double)a->tempo_total_comum / atendidos_comum : 0;
    printf("Fila Comum:\n");
    printf("  - Total de Atendimentos: %d\n", atendidos_comum);
    printf("  - Total de Itens Processados: %d\n", a->total_itens_comum);
    printf("  - Tempo Medio de Atendimento: %.2f segundos\n", tempo_medio_comum);

    // Estatísticas da Fila Preferencial
    int atendidos_pref = a->total_atendidos_preferencial;
    double tempo_medio_pref = (atendidos_pref > 0) ? (double)a->tempo_total_preferencial / atendidos_pref : 0;
    printf("\nFila Preferencial:\n");
    printf("  - Total de Atendimentos: %d\n", atendidos_pref);
    printf("  - Total de Itens Processados: %d\n", a->total_itens_preferencial);
    printf("  - Tempo Medio de Atendimento: %.2f segundos\n", tempo_medio_pref);
    printf("--------------------------------\n");
}