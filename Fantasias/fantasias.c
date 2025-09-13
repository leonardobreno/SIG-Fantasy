#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <unistd.h>
#include <string.h>

#include "../Utilidades/utilidades.h"

char menu_fantasia(void) {
    char op;
    system("clear||cls");
    printf("╔═════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                                    Modulo Fantasias                             ║\n");
    printf("╠═════════════════════════════════════════════════════════════════════════════════╣\n");
    printf("║                               -> 1 • Listar fantasia                            ║\n");    
    printf("║                               -> 2 • Cadastrar fantasia                         ║\n");
    printf("║                               -> 3 • Alterar fantasia                           ║\n");
    printf("║                               -> 4 • Excluir fantasia                           ║\n");
    printf("║                               -> 5    • Voltar                                  ║\n");
    printf("╚═════════════════════════════════════════════════════════════════════════════════╝\n");
    printf("Escolha uma opção: ");
    scanf(" %c", &op);
    limpar_buffer();
    return op;
}

void menu_lista_fantasia(char nome[], char tamanho[], char cor[]) {
    system("clear||cls");
    printf("╔═════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                                   Lista de Fantasias                            ║\n");
    printf("╚═════════════════════════════════════════════════════════════════════════════════╝\n");
    printf("Nome: %s\n", nome);
    printf("Tamanho: %s\n", tamanho);
    printf("Cor: %s\n", cor);
}

void menu_cadastro_fantasia(char nome[], char tamanho[], char cor[]) {
    system("clear||cls");
    printf("╔═════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                                   Cadastro Fantasia                             ║\n");
    printf("╚═════════════════════════════════════════════════════════════════════════════════╝\n");
    printf("Digite o nome da fantasia: ");
    scanf(" %[^\n]", nome);
    limpar_buffer();

    printf("Digite o tamanho: ");
    scanf(" %[^\n]", tamanho);
    limpar_buffer();

    printf("Digite a cor: ");
    scanf(" %[^\n]", cor);
    limpar_buffer();

    printf("\nCadastro realizado!\n");
    sleep(1);
}

void menu_alterar_fantasia(char nome[], char tamanho[], char cor[]) {
    system("clear||cls");
    printf("╔═════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                                    Alterar Fantasia                             ║\n");
    printf("╚═════════════════════════════════════════════════════════════════════════════════╝\n");
    printf("Digite o novo nome da fantasia: ");
    scanf(" %[^\n]", nome);
    limpar_buffer();

    printf("Digite o novo tamanho: ");
    scanf(" %[^\n]", tamanho);
    limpar_buffer();

    printf("Digite a nova cor: ");
    scanf(" %[^\n]", cor);
    limpar_buffer();

    printf("\nFantasia alterada!\n");
    sleep(1);
}

void menu_deletar_fantasia(char nome[], char tamanho[], char cor[]) {
    nome[0] = '\0';
    tamanho[0] = '\0';
    cor[0] = '\0';
}

void modulo_fantasia(void) {
    char op;
    char nome[50] = "";
    char tamanho[10] = "";
    char cor[20] = "";
    char op_delete = '2';

    do {
        op = menu_fantasia();
        switch(op) {
            case '1':
                menu_lista_fantasia(nome, tamanho, cor);
                printf("\nPressione Enter para voltar...\n");
                limpar_buffer();                
                break;
            case '2':
                menu_cadastro_fantasia(nome, tamanho, cor);
                break;
            case '3':
                menu_alterar_fantasia(nome, tamanho, cor);
                break;
            case '4':
                system("clear||cls");
                menu_lista_fantasia(nome, tamanho, cor);
                printf("\nDeseja excluir essa fantasia?\n");
                printf("1 - Sim\n");
                printf("2 - Nao\n");
                op_delete = getchar();
                limpar_buffer();
                switch (op_delete){
                case '1':
                    menu_deletar_fantasia(nome, tamanho, cor);
                    system("clear||cls");
                    printf("Fantasia excluida com sucesso!\n");
                    sleep(1);
                    break;
                
                case '2':
                    printf("Abortando exclusao...\n");
                    sleep(1);
                    break;
                
                default:
                    printf("Opção inválida!\n");
                    sleep(1);
                    break;
                }
                sleep(1);
                break;
            case '5':
                printf("Voltando ao menu principal...\n");
                sleep(1);
                break;
            default:
                printf("Opção inválida!\n");
                sleep(1);
        }
    } while(op != '5');
}