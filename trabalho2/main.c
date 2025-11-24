#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "cliente.h"
#include "fila.h"
#include "atendimento.h"

int main() {
    int opcao;
    char nome[50];
    int itens;

    // Inicializa as filas de clientes
    Fila filaComum, filaPreferencial;
    
    inicializarFila(&filaComum);
    inicializarFila(&filaPreferencial);

    // Inicializa o módulo de estatísticas e atendimento
    Atendimento* a = inicializarAtendimento();

    do {
        printf("\n=================================\n");
        printf("    SISTEMA SUPERMERCADO   \n");
        printf("=================================\n");
        printf("1 - Adicionar cliente na fila Comum\n");
        printf("2 - Adicionar cliente na fila Preferencial\n");
        printf("3 - Atender proximo cliente\n");
        printf("4 - Exibir filas de espera\n");
        printf("5 - Exibir clientes ja atendidos\n");
        printf("6 - Exibir estatisticas finais\n");
        printf("7 - Testar funcionalidades do cliente\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch(opcao) {

            case 1: {
                printf("\n--- Novo Cliente Comum ---\n");
                printf("Nome do cliente: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';

                printf("Quantidade de itens: ");
                scanf("%d", &itens);

                Cliente novoCliente = criarCliente(nome, 0, itens); // tipo 0 = comum
                enfileirar(&filaComum, novoCliente); // CORRETO: passa por valor
                printf("Cliente comum enfileirado com sucesso!\n");
                break;
            }

            case 2: {
                printf("\n--- Novo Cliente Preferencial ---\n");
                printf("Nome do cliente: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';

                printf("Quantidade de itens: ");
                scanf("%d", &itens);

                Cliente novoCliente = criarCliente(nome, 1, itens); // tipo 1 = preferencial
                enfileirar(&filaPreferencial, novoCliente); // CORRETO: passa por valor
                printf("Cliente preferencial enfileirado com sucesso!\n");
                break;
            }

            case 3:
                atenderProximoCliente(&filaComum, &filaPreferencial, a);
                break;

            case 4:
                printf("\n--- FILAS DE ESPERA ---\n");
                exibirFila(&filaComum, "COMUM");
                exibirFila(&filaPreferencial, "PREFERENCIAL");
                break;

            case 5:
                exibirHistoricoAtendimentos(a);
                break;

            case 6:
                exibirEstatisticasFinais(a);
                break;

            case 7: {
                printf("\n--- FUNCIONALIDADES CLIENTE ---\n");
                Cliente teste = criarCliente("Cliente Teste", 1, 15); 
                printf("Cliente criado: ");
                imprimirCliente(&teste); 
                printf("É preferencial? %s\n", isPreferencial(teste.tipo) ? "Sim" : "Não");
                printf("Tempo de atendimento: %d segundos\n", calcularTempoAtendimento(teste.itens));
                break;
            }

            case 0:
                printf("\nSaindo...\n");
                liberarFila(&filaComum);
                liberarFila(&filaPreferencial);
                liberarAtendimento(a);
                break;

            default:
                printf("\nOpcao invalida!\n");
        }

    } while (opcao != 0);

    return 0;
}