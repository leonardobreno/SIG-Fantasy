#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Fantasias/fantasias.h"
#include "../Funcionarios/funcionarios.h"
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

// acess as variáveis e funções declaradas como extern em fantasias.h
extern Fantasia* fantasias;
extern int num_fantasias;
extern void carregar_fantasias_binario(void);
extern void liberar_memoria_fantasias(void);

extern Funcionario* funcionarios;
extern int num_funcionarios;     
extern void carregar_funcionarios_binario(void);
extern void liberar_memoria_funcionarios(void);


// ---------- MENU DE RELATÓRIOS ----------

char menu_relatorios(void) {
    char op;
    system(CLEAR_SCREEN);
    printf("╔═════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                              📁 Modulo Relatórios                               ║\n");
    printf("╠═════════════════════════════════════════════════════════════════════════════════╣\n");
    printf("║                              -> 1 • Fantasias Ativas                            ║\n");
    printf("║                              -> 2 • Funcionários Ativos                         ║\n");
    printf("║                              -> 0 • Voltar                                      ║\n");
    printf("╚═════════════════════════════════════════════════════════════════════════════════╝\n");
    printf("Escolha uma opcao: ");
    scanf(" %c", &op);
    limpar_buffer();
    return op;
}

// ---------- RELATÓRIO DE FANTASIAS ATIVAS (Listagem) ----------

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

// ---------- MÓDULO PRINCIPAL DE RELATÓRIOS ----------

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

// ---------- RELATÓRIO DE FUNCIONÁRIOS ATIVOS (Listagem) ----------

void relatorio_funcionarios_ativos(void) {
    system(CLEAR_SCREEN);
    printf("╔═════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                         Relatório de Funcionários Ativos                        ║\n");
    printf("╚═════════════════════════════════════════════════════════════════════════════════╝\n");

    // Garante que os dados estejam carregados na memória
    carregar_funcionarios_binario(); 
    
    int ativos = 0;

    // Cabeçalho da tabela
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
    
    // Libera a memória para evitar vazamentos
    liberar_memoria_funcionarios(); 

    printf("\nPressione Enter para continuar...");
    limpar_buffer();
}
