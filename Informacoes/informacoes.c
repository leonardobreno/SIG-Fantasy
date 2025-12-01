#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <unistd.h>
#include <string.h>

#include "../Utilidades/utilidades.h"


char menu_informacoes(void) {
    char op;
    system("clear||cls");
    printf("╔═════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                                       SIG-Fantasy:                              ║\n");
    printf("║                                                                                 ║\n");
    printf("║                                    Modulo Informações                           ║\n");
    printf("╠═════════════════════════════════════════════════════════════════════════════════╣\n");
    printf("║                                 -> 1 • Sobre o projeto                          ║\n");
    printf("║                                 -> 2 • Equipe desenvolvedora                    ║\n");
    printf("║                                 -> 3 •     Voltar                               ║\n");
    printf("╚═════════════════════════════════════════════════════════════════════════════════╝\n");

    printf("Escolha uma opção: ");
    op = getchar();
    limpar_buffer();
    return op;
}

void menu_sobre_projeto(void) {
    system("clear||cls");
    printf("╔═════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                                    SIG-Fantasy:                                 ║\n");
    printf("║                                                                                 ║\n");
    printf("║                                  Sobre o projeto                                ║\n");
    printf("╠═════════════════════════════════════════════════════════════════════════════════╣\n");
    printf("║                   Programa desenvolvido com o fim de servir como                ║\n");
    printf("║                   projeto para disciplina de Programacao(DCT1106)               ║\n");
    printf("║                   Este programa serve como um sistema de gerencia               ║\n");
    printf("║                   para uma loja de fantasias/roupas. O sistema                  ║\n");
    printf("║                   permite que os clientes comprem ou aluguem                    ║\n");
    printf("║                   os produtos da loja, alem de guardar os pedidos               ║\n");
    printf("╚═════════════════════════════════════════════════════════════════════════════════╝\n");
    printf("\nPressione Enter para voltar...\n");
    limpar_buffer();
}

void menu_equipe(void) {
    system("clear||cls");
    printf("╔═════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                                      SIG-Fantasy:                               ║\n");
    printf("║                                                                                 ║\n");
    printf("║                                   Equipe do projeto                             ║\n");
    printf("╠═════════════════════════════════════════════════════════════════════════════════╣\n");
    printf("║                        Este projeto foi desenvolvido por:                       ║\n");
    printf("║                                 Leonardo Breno da Silva Santos,                 ║\n");
    printf("║                                 Pedro Lucas da Silva Araújo                     ║\n");
    printf("║                                 Thiago Gomes de Oliveira                        ║\n");
    printf("║                                 Maria Luíza Severo Lima                         ║\n");
    printf("║                                                                                 ║\n");
    printf("║                        E-mails: leonardodbreno@gmail.com,                       ║\n");
    printf("║                                 pedro.araujo.716@ufrn.edu.br                    ║\n");
    printf("║                                 thiago.oliveira.712@ufrn.edu.br                 ║\n");
    printf("║                                 maria.severo.063@ufrn.edu.br                    ║\n");
    printf("║                                                                                 ║\n");
    printf("║                        GitHub: https://github.com/leonardobreno                 ║\n");
    printf("║                                https://github.com/Pedro1349                     ║\n");
    printf("║                            https://github.com/thiagogomes1805                   ║\n");
    printf("║                               https://github.com/mluizasevero                   ║\n");
    printf("╚═════════════════════════════════════════════════════════════════════════════════╝\n");
    printf("\nPressione Enter para voltar...\n");
    limpar_buffer();
}

void modulo_informacoes(void) {
    char op;

    do{
        op = menu_informacoes();
        switch (op)
        {
        case '1':
            menu_sobre_projeto();
            break;
        case '2':
            menu_equipe();
            break;
        
        case '3':
            printf("Voltando ao menu principal...\n");
            sleep(1);
            break;
        default:
            printf("Opção inválida!\n");
            sleep(1);
        }

    } while (op != '3');
    
}