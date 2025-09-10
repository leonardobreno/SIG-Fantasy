#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <unistd.h>
#include <string.h>

#include "../Utilidades/utilidades.h"

char menu_funcionario(void) {
    char op;
    system("clear||cls");
    printf("╔═════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                                Modulo Funcionario                               ║\n");
    printf("╠═════════════════════════════════════════════════════════════════════════════════╣\n");
    printf("║                             -> 1 • Listar funcionario                           ║\n");
    printf("║                             -> 2 • Cadastrar funcionario                        ║\n");
    printf("║                             -> 3 • Alterar funcionario                          ║\n");
    printf("║                             -> 4 • Deletar funcionario                          ║\n");
    printf("║                             -> 5    • Voltar                                    ║\n");
    printf("╚═════════════════════════════════════════════════════════════════════════════════╝\n");
    printf("Escolha uma opção: ");
    scanf(" %c", &op);
    limpar_buffer();

    return op;
}

void menu_lista_funcionario(char nome[], char cpf[], char celular[], char email[], float* salario) {
    system("clear||cls");
    printf("╔═════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                                   Lista de funcionarios                         ║\n");
    printf("╚═════════════════════════════════════════════════════════════════════════════════╝\n");
    printf("Nome do funcionario: %s\n", nome);
    printf("Cpf do funcionario: %s\n", cpf);
    printf("Telefone do funcionario: %s\n", celular);
    printf("Email do funcionario: %s\n", email);
    printf("Salario do funcionario: %f\n", *salario);
}

void menu_cadastro_funcionario(char nome[], char cpf[], char celular[], char email[], float* salario) {
    system("clear||cls");
    printf("╔═════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                                   Cadastro Funcionario                          ║\n");
    printf("╚═════════════════════════════════════════════════════════════════════════════════╝\n");
    printf("Digite o nome do funcionario: ");
    scanf(" %[^\n]", nome);
    limpar_buffer();

    printf("Digite o cpf do funcionario: ");
    scanf(" %[^\n]", cpf);
    limpar_buffer();

    printf("Digite o celular do funcionario: ");
    scanf(" %[^\n]", celular);
    limpar_buffer();

    printf("Digite o email do funcionario: ");
    scanf(" %[^\n]", email);
    limpar_buffer();

    printf("Digite o salario do funcionario: ");
    scanf(" %f", salario);
    limpar_buffer();

    printf("\nCadastro realizado!\n");
    sleep(1);
}

void menu_alterar_funcionario(char nome[], char cpf[], char celular[], char email[], float* salario) {
    system("clear||cls");
    printf("╔═════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                                   Alterar Funcionario                           ║\n");
    printf("╚═════════════════════════════════════════════════════════════════════════════════╝\n");
    printf("Digite o novo nome do funcionario: ");
    scanf(" %[^\n]", nome);
    limpar_buffer();

    printf("Digite o novo cpf do funcionario: ");
    scanf(" %[^\n]", cpf);
    limpar_buffer();

    printf("Digite o novo celular do funcionario: ");
    scanf(" %[^\n]", celular);
    limpar_buffer();

    printf("Digite o novo email do funcionario: ");
    scanf(" %[^\n]", email);
    limpar_buffer();

    printf("Digite o novo salario do funcionario: ");
    scanf(" %f", salario);
    limpar_buffer();

    printf("\nFuncionario alterado!\n");
    sleep(1);
}

void menu_deletar_funcionario(char nome[], char cpf[], char celular[], char email[], float* salario) {
    nome[0] = '\0';
    cpf[0] = '\0';
    celular[0] = '\0';
    email[0] = '\0';
    *salario = 0;
}

void modulo_funcionario(void) {
    char op;
    char nome[60] = "";
    char cpf[60] = "";
    char celular[60] = "";
    char email[60] = "";
    float salario = 0;
    char op_delete = '2';

    do {
        op = menu_funcionario();
        switch(op) {
            case '1':
                menu_lista_funcionario(nome, cpf, celular, email, &salario);
                printf("\nPressione Enter para voltar...\n");
                limpar_buffer();                  
                break;
            case '2':
                menu_cadastro_funcionario(nome, cpf, celular, email, &salario);
                break;
            case '3':
                menu_alterar_funcionario(nome, cpf, celular, email, &salario);
                break;
            case '4':
                system("clear||cls");
                menu_lista_funcionario(nome, cpf, celular, email, &salario);
                printf("\nDeseja excluir esse funcionario?\n");
                printf("1 - Sim\n");
                printf("2 - Nao\n");
                op_delete = getchar();
                limpar_buffer();
                switch (op_delete){
                case '1':
                    menu_deletar_funcionario(nome, cpf, celular, email, &salario);
                    system("clear||cls");
                    printf("Funcionario excluido com sucesso!\n");
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