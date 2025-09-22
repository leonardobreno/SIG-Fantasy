#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <unistd.h>
#include <string.h>

#include "../Utilidades/utilidades.h"

char nome[50] = "";
char cpf[20] = "";
char celular[20] = "";
char email[50] = "";

char menu_cliente(void) {
    char op;
    system("clear||cls");
    printf("╔═════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                                  Modulo Clientes                                ║\n");
    printf("╠═════════════════════════════════════════════════════════════════════════════════╣\n");
    printf("║                             -> 1 • Pesquisar cliente                            ║\n");
    printf("║                             -> 2 • Cadastrar cliente                            ║\n");
    printf("║                             -> 3 • Alterar cliente                              ║\n");
    printf("║                             -> 4 • Deletar cliente                              ║\n");
    printf("║                             -> 5    • Voltar                                    ║\n");
    printf("╚═════════════════════════════════════════════════════════════════════════════════╝\n");
    printf("Escolha uma opção: ");
    scanf(" %c", &op);
    limpar_buffer();

    return op;
}

void menu_pesquisar_cliente(char cpf_procurar[]) {
    int comparacao = strcmp(cpf_procurar, cpf);
    if (comparacao == 0){
        system("clear||cls");
        printf("╔═════════════════════════════════════════════════════════════════════════════════╗\n");
        printf("║                                   Cliente Pesquisado                            ║\n");
        printf("╚═════════════════════════════════════════════════════════════════════════════════╝\n");
        printf("Nome: %s\n", nome);
        printf("CPF: %s\n", cpf);
        printf("CPF_pesquisado: %s\n", cpf_procurar);
        printf("Celular: %s\n", celular);
        printf("Email: %s\n", email);
    }
    else
    {
        system("clear||cls");
        printf("CPF_pesquisado: %s\n", cpf_procurar);
        printf("\nNao tem nenhum usuario com esse cpf.");
    }
    
}

void menu_cadastro_cliente(char nome[], char cpf[], char celular[], char email[]) {
    system("clear||cls");
    printf("╔═════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                                  Cadastro Cliente                               ║\n");
    printf("╚═════════════════════════════════════════════════════════════════════════════════╝\n");
    printf("Digite seu nome: ");
    scanf(" %[^\n]", nome);
    limpar_buffer();

    printf("Digite seu CPF: ");
    scanf(" %[^\n]", cpf);
    limpar_buffer();

    printf("Digite seu numero de celular: ");
    scanf(" %[^\n]", celular);
    limpar_buffer();

    printf("Digite seu Email: ");
    scanf(" %[^\n]", email);
    limpar_buffer();

    printf("\nCadastro realizado!\n");
    sleep(1);
}

void menu_alterar_cliente(char nome[], char cpf[], char celular[], char email[]) {
    system("clear||cls");
    printf("╔═════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                                     Alterar Cliente                             ║\n");
    printf("╚═════════════════════════════════════════════════════════════════════════════════╝\n");
    printf("Digite seu novo nome: ");
    scanf(" %[^\n]", nome);
    limpar_buffer();

    printf("Digite seu novo CPF: ");
    scanf(" %[^\n]", cpf);
    limpar_buffer();

    printf("Digite seu novo celular: ");
    scanf(" %[^\n]", celular);
    limpar_buffer();

    printf("Digite seu novo email: ");
    scanf(" %[^\n]", email);
    limpar_buffer();

    printf("\nCliente alterado!\n");
    sleep(1);
}

void menu_deletar_cliente(char nome[], char cpf[], char celular[], char email[]) {
    nome[0] = '\0';
    cpf[0] = '\0';
    celular[0] = '\0';
    email[0] = '\0';
}

void modulo_cliente(void) {
    char op;
    char op_delete = '2';
    char cpf_procurar[50];

    do {
        op = menu_cliente();
        switch(op) {
            case '1':
                printf("\nDigite o valor do cpf do cliente que deseja procurar: ");
                scanf("%[^\n]", cpf_procurar);
                menu_pesquisar_cliente(cpf_procurar);
                getchar();
                printf("\nPressione Enter para voltar...\n");
                limpar_buffer();
                break;
            case '2':
                menu_cadastro_cliente(nome, cpf, celular, email);
                break;
            case '3':
                menu_alterar_cliente(nome, cpf, celular, email);
                break;
            case '4':
                system("clear||cls");
                limpar_buffer();
                printf("\nDigite o valor do cpf do cliente que deseja procurar: ");
                scanf("%[^\n]", cpf_procurar);
                menu_pesquisar_cliente(cpf_procurar);
                printf("\nDeseja excluir esse cliente?\n");
                printf("1 - Sim\n");
                printf("2 - Nao\n");
                op_delete = getchar();
                limpar_buffer();
                switch (op_delete){
                case '1':
                    menu_deletar_cliente(nome, cpf, celular, email);
                    system("clear||cls");
                    printf("Cliente excluido com sucesso!\n");
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