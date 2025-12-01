#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Fantasias/fantasias.h"
#include "../Funcionarios/funcionarios.h"
#include "../Pedidos/pedidos.h"
#include "../Clientes/clientes.h" 
#include "../Utilidades/utilidades.h"

#ifdef _WIN32
    #include <windows.h>
    #define SLEEP(ms) Sleep(ms)
    #define CLEAR_SCREEN "cls"
#else
    #include <unistd.h>
    #define SLEEP(s) sleep(s)
    #define CLEAR_SCREEN "clear"
#endif


extern Fantasia* fantasias;
extern int num_fantasias;
extern void carregar_fantasias_binario(void);
extern void liberar_memoria_fantasias(void);


extern Funcionario* funcionarios;
extern int num_funcionarios;     
extern void carregar_funcionarios_binario(void);
extern void liberar_memoria_funcionarios(void);


extern Pedido* pedidos;
extern int num_pedidos;
extern void carregar_pedidos_binario(void);
extern void liberar_memoria_pedidos(void);


extern Cliente* clientes;
extern int num_clientes;
extern void carregar_clientes_binario(void);
extern void liberar_memoria_clientes(void);



char menu_relatorios(void) {
    char op;
    system(CLEAR_SCREEN);
    printf("╔═════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                              📁 Modulo Relatórios                               ║\n");
    printf("╠═════════════════════════════════════════════════════════════════════════════════╣\n");
    printf("║                              -> 1 • Fantasias Ativas                            ║\n");
    printf("║                              -> 2 • Funcionários Ativos                         ║\n");
    printf("║                              -> 3 • Pedidos Ativos                              ║\n");
    printf("║                              -> 4 • Clientes Ativos                             ║\n");
    printf("║                              -> 0 • Voltar                                      ║\n");
    printf("╚═════════════════════════════════════════════════════════════════════════════════╝\n");
    printf("Escolha uma opcao: ");
    scanf(" %c", &op);
    limpar_buffer();
    return op;
}


void relatorio_fantasias_ativas(void) {
    system(CLEAR_SCREEN);
    printf("╔═════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                          Relatório de Fantasias Ativas                          ║\n");
    printf("╚═════════════════════════════════════════════════════════════════════════════════╝\n");

    carregar_fantasias_binario(); 
    
    int ativos = 0;

    printf("\n%-45s %-10s %-20s\n", "NOME", "TAMANHO", "COR");
    printf("-------------------------------------------------------------------------------\n");

    for (int i = 0; i < num_fantasias; i++) {
        if (fantasias[i].ativo == 1) {
            printf("%-45s %-10s %-20s\n", 
                   fantasias[i].nome, 
                   fantasias[i].tamanho, 
                   fantasias[i].cor);
            ativos++;
        }
    }

    if (ativos == 0) {
        printf("\nNenhuma fantasia ativa encontrada.\n");
    } else {
        printf("\nTotal de fantasias ativas listadas: %d\n", ativos);
    }

    liberar_memoria_fantasias(); 

    printf("\nPressione Enter para continuar...");
    limpar_buffer();
}


void relatorio_funcionarios_ativos(void) {
    system(CLEAR_SCREEN);
    printf("╔═════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                         Relatório de Funcionários Ativos                        ║\n");
    printf("╚═════════════════════════════════════════════════════════════════════════════════╝\n");

    carregar_funcionarios_binario(); 
    
    int ativos = 0;

    printf("\n%-30s %-15s %-20s %-30s\n", "NOME", "CPF", "CELULAR", "EMAIL");
    printf("-----------------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < num_funcionarios; i++) {
        if (funcionarios[i].ativo == 1) {
            printf("%-30s %-15s %-20s %-30s\n", 
                   funcionarios[i].nome, 
                   funcionarios[i].cpf, 
                   funcionarios[i].celular, 
                   funcionarios[i].email);
            ativos++;
        }
    }

    if (ativos == 0) {
        printf("\nNenhum funcionário ativo encontrado.\n");
    } else {
        printf("\nTotal de funcionários ativos listados: %d\n", ativos);
    }
    
    liberar_memoria_funcionarios(); 

    printf("\nPressione Enter para continuar...");
    limpar_buffer();
}


void relatorio_pedidos_ativos(void) {
    system(CLEAR_SCREEN);
    printf("╔═════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                           Relatório de Pedidos Ativos                           ║\n");
    printf("╚═════════════════════════════════════════════════════════════════════════════════╝\n");

    carregar_pedidos_binario(); 
    
    int ativos = 0;

    printf("\n%-10s %-15s %-20s %-10s %-12s\n", "ID PEDIDO", "CPF CLIENTE", "FANTASIA", "PRECO", "DATA");
    printf("-------------------------------------------------------------------------------\n");

    for (int i = 0; i < num_pedidos; i++) {
        if (pedidos[i].ativo == 1) {
            printf("%-10lu %-15s %-20s R$%-8.2f %-12s\n", 
                   pedidos[i].id_pedido, 
                   pedidos[i].cpf_cliente,
                   pedidos[i].id_fantasia,
                   pedidos[i].preco,
                   pedidos[i].data_pedido);
            ativos++;
        }
    }

    if (ativos == 0) {
        printf("\nNenhum pedido ativo encontrado.\n");
    } else {
        printf("\nTotal de pedidos ativos listados: %d\n", ativos);
    }
    
    liberar_memoria_pedidos(); 

    printf("\nPressione Enter para continuar...");
    limpar_buffer();
}


void relatorio_clientes_ativos(void) {
    system(CLEAR_SCREEN);
    printf("╔═════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                           Relatório de Clientes Ativos                          ║\n");
    printf("╚═════════════════════════════════════════════════════════════════════════════════╝\n");

    carregar_clientes_binario(); 
    
    int ativos = 0;

    printf("\n%-30s %-15s %-20s %-30s\n", "NOME", "CPF", "CELULAR", "EMAIL");
    printf("-----------------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < num_clientes; i++) {
        if (clientes[i].ativo == 1) {
            printf("%-30s %-15s %-20s %-30s\n", 
                   clientes[i].nome, 
                   clientes[i].cpf, 
                   clientes[i].celular, 
                   clientes[i].email);
            ativos++;
        }
    }

    if (ativos == 0) {
        printf("\nNenhum cliente ativo encontrado.\n");
    } else {
        printf("\nTotal de clientes ativos listados: %d\n", ativos);
    }
    
    liberar_memoria_clientes(); 

    printf("\nPressione Enter para continuar...");
    limpar_buffer();
}



void modulo_relatorios() {
    char op;
    do {
        op = menu_relatorios();
        switch(op) {
            case '1':
                relatorio_fantasias_ativas();
                break;
            case '2':
                relatorio_funcionarios_ativos();
                break;
            case '3':
                relatorio_pedidos_ativos();
                break;
            case '4': 
                relatorio_clientes_ativos();
                break;
            case '0':
                printf("Voltando ao menu principal...\n");
                SLEEP(1);
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
                SLEEP(1);
        }
    } while(op != '0');
}