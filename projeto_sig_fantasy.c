#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <unistd.h>
#include <string.h>

#include "Utilidades/utilidades.h"
#include "Informacoes/informacoes.h"
#include "Pedidos/pedidos.h"


// Assinaturas das funções
char menu_principal(void);
char saida_programa(void);

char menu_cliente(void);
void menu_lista_cliente(char[], char[], char[], char[]);
void menu_cadastro_cliente(char[], char[], char[], char[]);
void menu_alterar_cliente(char[], char[], char[], char[]);
void menu_deletar_cliente(char[], char[], char[], char[]);
void modulo_cliente(void);

char menu_fantasia(void);
void menu_lista_fantasia(char[], char[], char[]);
void menu_cadastro_fantasia(char[], char[], char[]);
void menu_alterar_fantasia(char[], char[], char[]);
void menu_deletar_fantasia(char[], char[], char[]);
void modulo_fantasia(void);

char menu_funcionario(void);
void menu_lista_funcionario(char[], char[], char[], char[], float*);
void menu_cadastro_funcionario(char[], char[], char[], char[], float*);
void menu_alterar_funcionario(char[], char[], char[], char[], float*);
void menu_deletar_funcionario(char[], char[], char[], char[], float*);
void modulo_funcionario(void);

int main(void) {
    char opc;
    do {
        opc = menu_principal();
        switch(opc) {
            case '1':
                modulo_cliente();
                break;
            case '2':
                modulo_fantasia();
                break;
            case '3':
                modulo_funcionario();
                break;
            case '4':
                modulo_pedido();
                break;                
            case '5':
                modulo_informacoes();
                break;
            case '6':
                printf("\nModulo em processo de criacao.");
                printf("\nVoltando ao menu...");
                sleep(2);
                break;
            case '0':
                opc = saida_programa();
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
                sleep(1);
        }
    } while(opc != '0');

    return 0;
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
    setlocale(LC_ALL, "Portuguese");

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


char menu_cliente(void) {
    char op;
    system("clear||cls");
    printf("╔═════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                                  Modulo Clientes                                ║\n");
    printf("╠═════════════════════════════════════════════════════════════════════════════════╣\n");
    printf("║                             -> 1 • Listar cliente                               ║\n");
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

void menu_lista_cliente(char nome[], char cpf[], char celular[], char email[]) {
    system("clear||cls");
    printf("╔═════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                                  Lista de clientes                              ║\n");
    printf("╚═════════════════════════════════════════════════════════════════════════════════╝\n");
    printf("Nome: %s\n", nome);
    printf("CPF: %s\n", cpf);
    printf("Celular: %s\n", celular);
    printf("Email: %s\n", email);
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
    char nome[50] = "";
    char cpf[20] = "";
    char celular[20] = "";
    char email[50] = "";
    char op_delete = '2';

    do {
        op = menu_cliente();
        switch(op) {
            case '1':
                menu_lista_cliente(nome, cpf, celular, email);
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
                menu_lista_cliente(nome, cpf, celular, email);
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