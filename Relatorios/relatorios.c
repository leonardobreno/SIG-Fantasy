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


void relatorio_clientes_por_letra(void) {
    char letra;
    system(CLEAR_SCREEN);
    printf("╔═════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                      Filtro: Clientes por Inicial do Nome                       ║\n");
    printf("╚═════════════════════════════════════════════════════════════════════════════════╝\n");
    
    printf("Digite a letra inicial para filtrar: ");
    scanf(" %c", &letra);
    limpar_buffer();

    letra = toupper(letra);

    carregar_clientes_binario();

    int encontrados = 0;
    printf("\n%-30s %-15s %-20s\n", "NOME", "CPF", "CELULAR");
    printf("-------------------------------------------------------------------\n");

    for (int i = 0; i < num_clientes; i++) {
        if (clientes[i].ativo == 1) {
            char inicial_cliente = toupper(clientes[i].nome[0]);

            if (inicial_cliente == letra) {
                printf("%-30s %-15s %-20s\n", 
                       clientes[i].nome, 
                       clientes[i].cpf, 
                       clientes[i].celular);
                encontrados++;
            }
        }
    }

    if (encontrados == 0) {
        printf("\nNenhum cliente encontrado com a inicial '%c'.\n", letra);
    } else {
        printf("\nTotal listado: %d\n", encontrados);
    }

    liberar_memoria_clientes();
    printf("\nPressione Enter para continuar...");
    limpar_buffer();
}


void relatorio_pedidos_por_preco(void) {
    float min_val, max_val;
    
    system(CLEAR_SCREEN);
    printf("╔═════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                      Filtro: Pedidos por Faixa de Preço                         ║\n");
    printf("╚═════════════════════════════════════════════════════════════════════════════════╝\n");
    
    printf("Digite o valor MINIMO (ex: 50.00): R$ ");
    scanf("%f", &min_val);
    limpar_buffer();

    printf("Digite o valor MAXIMO (ex: 200.00): R$ ");
    scanf("%f", &max_val);
    limpar_buffer();

    if (min_val > max_val) {
        printf("\nErro: O valor minimo nao pode ser maior que o maximo!\n");
        SLEEP(2);
        return;
    }

    carregar_pedidos_binario();

    int encontrados = 0;
    
    printf("\n=== PEDIDOS ENTRE R$ %.2f E R$ %.2f ===\n", min_val, max_val);
    printf("%-10s %-20s %-15s %-10s\n", "ID", "FANTASIA", "DATA", "VALOR");
    printf("-------------------------------------------------------------------\n");

    for (int i = 0; i < num_pedidos; i++) {
        if (pedidos[i].ativo == 1) {
            if (pedidos[i].preco >= min_val && pedidos[i].preco <= max_val) {
                printf("%-10lu %-20s %-15s R$ %.2f\n", 
                       pedidos[i].id_pedido, 
                       pedidos[i].id_fantasia, 
                       pedidos[i].data_pedido,
                       pedidos[i].preco);
                encontrados++;
            }
        }
    }

    if (encontrados == 0) {
        printf("\nNenhum pedido encontrado nessa faixa de preco.\n");
    } else {
        printf("\nTotal listado: %d\n", encontrados);
    }

    liberar_memoria_pedidos();
    printf("\nPressione Enter para continuar...");
    limpar_buffer();
}

void relatorio_pedidos_detalhado(void) {
    system(CLEAR_SCREEN);
    printf("╔═════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                   Relatório Detalhado de Pedidos (Cruzamento)                   ║\n");
    printf("╚═════════════════════════════════════════════════════════════════════════════════╝\n");

    carregar_pedidos_binario();
    carregar_clientes_binario();
    carregar_fantasias_binario();

    int encontrados = 0;

    printf("\n%-6s %-12s %-25s %-25s %-10s\n", "ID", "DATA", "CLIENTE", "FANTASIA", "VALOR");
    printf("------------------------------------------------------------------------------------\n");

    for (int i = 0; i < num_pedidos; i++) {
        if (pedidos[i].ativo == 1) {
            
            char nome_cliente_atual[50] = "-- Nao Encontrado --";
            char nome_fantasia_atual[50] = "-- Nao Encontrado --";

            for(int c = 0; c < num_clientes; c++) {
                if(strcmp(clientes[c].cpf, pedidos[i].cpf_cliente) == 0) {
                    strcpy(nome_cliente_atual, clientes[c].nome);
                    break;
                }
            }

            for(int f = 0; f < num_fantasias; f++) {
                if(strcmp(fantasias[f].nome, pedidos[i].id_fantasia) == 0) { 
                    strcpy(nome_fantasia_atual, fantasias[f].nome);
                    break;
                }
            }

            printf("%-6lu %-12s %-25s %-25s R$ %-8.2f\n", 
                   pedidos[i].id_pedido, 
                   pedidos[i].data_pedido,
                   nome_cliente_atual,
                   nome_fantasia_atual,
                   pedidos[i].preco);
            
            encontrados++;
        }
    }

    if (encontrados == 0) {
        printf("\nNenhum pedido ativo encontrado.\n");
    } else {
        printf("\nTotal de registros cruzados: %d\n", encontrados);
    }

    liberar_memoria_pedidos();
    liberar_memoria_clientes();
    liberar_memoria_fantasias();

    printf("\nPressione Enter para continuar...");
    limpar_buffer();
}


void relatorio_clientes_financeiro(void) {
    system(CLEAR_SCREEN);
    printf("╔═════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                 Relatório Financeiro por Cliente (Cruzamento)                   ║\n");
    printf("╚═════════════════════════════════════════════════════════════════════════════════╝\n");

    carregar_clientes_binario();
    carregar_pedidos_binario();

    int clientes_listados = 0;

    printf("\n%-30s %-15s %-15s %-15s\n", "CLIENTE", "CPF", "QTD PEDIDOS", "TOTAL GASTO");
    printf("--------------------------------------------------------------------------------\n");

    for (int i = 0; i < num_clientes; i++) {
        if (clientes[i].ativo == 1) {
            
            int qtd_pedidos = 0;
            float total_gasto = 0.0;

            for (int j = 0; j < num_pedidos; j++) {
                if (pedidos[j].ativo == 1 && strcmp(pedidos[j].cpf_cliente, clientes[i].cpf) == 0) {
                    qtd_pedidos++;
                    total_gasto += pedidos[j].preco;
                }
            }

            printf("%-30s %-15s %-15d R$ %-10.2f\n", 
                   clientes[i].nome, 
                   clientes[i].cpf, 
                   qtd_pedidos, 
                   total_gasto);
            
            clientes_listados++;
        }
    }

    if (clientes_listados == 0) {
        printf("\nNenhum cliente ativo encontrado.\n");
    }

    liberar_memoria_clientes();
    liberar_memoria_pedidos();

    printf("\nPressione Enter para continuar...");
    limpar_buffer();
}

char menu_relatorios(void) {
    char op;
    system(CLEAR_SCREEN);
    printf("╔═════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                              📁 Modulo Relatórios                               ║\n");
    printf("╠═════════════════════════════════════════════════════════════════════════════════╣\n");
    printf("║                              --- CLIENTES ---                                   ║\n");
    printf("║                              -> 1 • Listar Ativos                               ║\n");
    printf("║                              -> 2 • Filtrar por Letra                           ║\n");
    printf("║                              -> 3 • Histórico Financeiro                        ║\n");
    printf("║                                                                                 ║\n");
    printf("║                              --- FANTASIAS ---                                  ║\n");
    printf("║                              -> 4 • Listar Ativas                               ║\n");
    printf("║                                                                                 ║\n");
    printf("║                              --- FUNCIONÁRIOS ---                               ║\n");
    printf("║                              -> 5 • Listar Ativos                               ║\n");
    printf("║                                                                                 ║\n");
    printf("║                              --- PEDIDOS ---                                    ║\n");
    printf("║                              -> 6 • Listar Ativos                               ║\n");
    printf("║                              -> 7 • Filtrar por Faixa de Preço                  ║\n");
    printf("║                              -> 8 • Relatório Detalhado (Combinado)             ║\n");
    printf("║                                                                                 ║\n");
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
                relatorio_clientes_ativos();
                break;
            case '2':
                relatorio_clientes_por_letra();
                break;
            case '3':
                relatorio_clientes_financeiro();
                break;
            case '4':
                relatorio_fantasias_ativas();
                break;
            case '5':
                relatorio_funcionarios_ativos();
                break;
            case '6':
                relatorio_pedidos_ativos();
                break;
            case '7':
                relatorio_pedidos_por_preco();
                break;
            case '8':
                relatorio_pedidos_detalhado();
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