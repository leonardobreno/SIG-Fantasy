#include <stdio.h>   
    // Entrada e saída
#include <stdlib.h>  
    // Funções utilitárias
#include <unistd.h>  
    // Funções do Linux/Unix
#include <string.h>  
    // Manipulação de strings

void limpar_buffer(void) {
    int c;
    c = getchar();
    while ((c != '\n' && c != EOF)) {
        c = getchar();
    };
}

char menu_principal(void) {
    char op;
    system("clear||cls");
    printf("╔═════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                                                                                 ║\n");
    printf("║   ╔═══╗  ╔╗  ╔═══╗         ╔═══╗ ╔═══╗   ╠╗    ║ ╔══════╗ ╔═══╗  ╔═══╗ ║   ║    ║\n");
    printf("║   ║      ║║  ║             ║     ║ ╔╗ ║  ║╚╗   ║ ╚══╗╔══╝ ║ ╔╗ ║ ║     ╚╗ ╔╝    ║\n");
    printf("║   ╚═══╗  ║║  ║ ╔═╗ ╔═════╗ ╠══╗  ║ ╚╝ ║  ║ ╚═╗ ║    ║║    ║ ╚╝ ║ ╚═══╗  ╚╦╝     ║\n");
    printf("║       ║  ║║  ║   ║ ╚═════╝ ║     ║ ╔╗ ║  ║   ╚╗║    ║║    ║ ╔╗ ║     ║   ║      ║\n");
    printf("║   ╚═══╝  ╚╝  ╚═══╝         ║     ╠═╝╚═╣  ║    ╚╣    ║║    ╠═╝╚═╣ ╚═══╝   ║      ║\n");
    printf("╚═════════════════════════════════════════════════════════════════════════════════╝\n");


    printf("╔═════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                                     SIG-Fantasy:                                ║\n");
    printf("║                                                                                 ║\n");
    printf("║                             Loja de fantasias e roupas                          ║\n");
    printf("╠═════════════════════════════════════════════════════════════════════════════════╣\n");
    printf("║                              -> 1 • Modulo Clientes                             ║\n");
    printf("║                              -> 2 • Modulo Fantasias                            ║\n");
    printf("║                              -> 3 • Modulo Funcionarios                         ║\n");
    printf("║                              -> 4 • Modulo Pedidos                              ║\n");
    printf("║                              -> 5 • Modulo Informações                          ║\n");
    printf("║                              -> 6 • Modulo Relatórios                           ║\n");
    printf("║                              -> 0 •      Sair                                   ║\n");
    printf("╚═════════════════════════════════════════════════════════════════════════════════╝\n");
    printf("Escolha uma opção: ");
    scanf(" %c", &op);
    limpar_buffer();
    printf("Carregando...\n");
    sleep(1);
    return op;
}

char saida_programa(void) {
    int confirmacao = 0;
    char opcao;
    while (confirmacao == 0){
        printf("Tem certeza que deseja sair do programa? (s/n)\n");
        scanf(" %c", &opcao);
        limpar_buffer();
        if (opcao == 's' || opcao == 'S')
        {
            printf("Fechando o programa...\n");
            opcao = '0';
            confirmacao = 1;
            sleep(1);

        } else if (opcao == 'n' || opcao == 'N')
        {
            printf("Cancelando a saida...");
            confirmacao = 1;
            sleep(1);
        } else
        {
            printf("opcao invalida\n");
            opcao = 'n';
            sleep(1);
        }
    
    }
    return opcao;
}
