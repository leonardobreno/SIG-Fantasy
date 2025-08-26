#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <unistd.h>
#include <string.h>

// Assinaturas das funções
char menu_principal(void);
char saida_programa(void);
void limpar_buffer(void);

char menu_informacoes(void);
void menu_sobre_projeto(void);
void menu_equipe(void);
void modulo_informacoes(void);

char menu_cliente(void);
void modulo_cliente(void);
void menu_cadastro_cliente(char[], char[], char[], char[]);
void menu_alterar_cliente(char[], char[], char[], char[]);
void menu_lista_cliente(char[], char[], char[], char[]);
void menu_deletar_cliente(char[], char[], char[], char[]);

char menu_fantasia(void);
void modulo_fantasia(void);
void menu_cadastro_fantasia(char[], char[], char[]);
void menu_alterar_fantasia(char[], char[], char[]);
void menu_lista_fantasia(char[], char[], char[]);
void menu_deletar_fantasia(char[], char[], char[]);

char menu_pedido(void);
void modulo_pedido(void);
void menu_lista_pedido(int*, int*, float*, char[]);
void menu_cadastro_pedido(int*, int*, float*, char[]);
void menu_alterar_pedido(int*, int*, float*, char[]);
void menu_deletar_pedido(int*, int*, float*, char[]);

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
                modulo_pedido();
                break;                
            case '4':
                modulo_informacoes();
                break;
            case '6':
                opc = saida_programa();
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
                sleep(1);
        }
    } while(opc != '6');

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
    printf("║                              -> 3 • Modulo Pedidos                              ║\n");
    printf("║                              -> 4 • Modulo Informações                          ║\n");
    printf("║                              -> 5 • Modulo Relatórios                           ║\n");
    printf("║                              -> 6 •      Sair                                   ║\n");
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
            opcao = '6';
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

void limpar_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

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
    getchar();
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
    printf("║                                                                                 ║\n");
    printf("║                        E-mails: leonardodbreno@gmail.com,                       ║\n");
    printf("║                                 pedro.araujo.716@ufrn.edu.br                    ║\n");
    printf("║                                                                                 ║\n");
    printf("║                        GitHub: https://github.com/leonardobreno                 ║\n");
    printf("║                                https://github.com/Pedro1349                     ║\n");
    printf("╚═════════════════════════════════════════════════════════════════════════════════╝\n");
    printf("\nPressione Enter para voltar...\n");
    getchar();
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

void menu_cadastro_cliente(char nome[], char cpf[], char celular[], char email[]) {
    system("clear||cls");
    printf("╔═════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                                     Cadastro                                    ║\n");
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
    printf("║                                      Alteração                                  ║\n");
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

    printf("\nCadastro alterado!\n");
    sleep(1);
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
                getchar();
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
    printf("║                               -> 5 • Voltar                                     ║\n");
    printf("╚═════════════════════════════════════════════════════════════════════════════════╝\n");
    printf("Escolha uma opção: ");
    scanf(" %c", &op);
    limpar_buffer();
    return op;
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

    printf("\nCadastro alterado!\n");
    sleep(1);
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
                getchar();
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

char menu_pedido(void) {
    char op;
    system("clear||cls");
    printf("╔═════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                                    Modulo Pedidos                               ║\n");
    printf("╠═════════════════════════════════════════════════════════════════════════════════╣\n");
    printf("║                               -> 1 • Listar pedido                              ║\n");    
    printf("║                               -> 2 • Cadastrar pedido                           ║\n");
    printf("║                               -> 3 • Alterar pedido                             ║\n");
    printf("║                               -> 4 • Excluir pedido                             ║\n");
    printf("║                               -> 5 • Voltar                                     ║\n");
    printf("╚═════════════════════════════════════════════════════════════════════════════════╝\n");
    printf("Escolha uma opção: ");
    scanf(" %c", &op);
    limpar_buffer();
    return op;
}

void menu_lista_pedido(int* id_fantasia, int* id_cliente, float* preco, char data_pedido[]) {
    system("clear||cls");
    printf("╔═════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                                   Lista de Fantasias                            ║\n");
    printf("╚═════════════════════════════════════════════════════════════════════════════════╝\n");
    printf("Id da fantasia: %d\n", *id_fantasia);
    printf("Id do cliente: %d\n", *id_cliente);
    printf("Preco do pedido: %f\n", *preco);
    printf("Data do pedido: %s\n", data_pedido);
}

void menu_cadastro_pedido(int* id_fantasia, int* id_cliente, float* preco, char data_pedido[]) {
    system("clear||cls");
    printf("╔═════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                                   Cadastro pedido                               ║\n");
    printf("╚═════════════════════════════════════════════════════════════════════════════════╝\n");
    printf("Digite o id da fantasia: ");
    scanf(" %d", id_fantasia);
    limpar_buffer();

    printf("Digite o id do cliente: ");
    scanf(" %d", id_cliente);
    limpar_buffer();

    printf("Digite o preco do pedido: ");
    scanf(" %f", preco);
    limpar_buffer();

    printf("Digite a data do pedido: ");
    scanf(" %[^\n]", data_pedido);
    limpar_buffer();

    printf("\nCadastro realizado!\n");
    sleep(1);
}

void menu_alterar_pedido(int* id_fantasia, int* id_cliente, float* preco, char data_pedido[]) {
    system("clear||cls");
    printf("╔═════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                                   Alterar pedido                                ║\n");
    printf("╚═════════════════════════════════════════════════════════════════════════════════╝\n");
    printf("Digite o id da fantasia: ");
    scanf(" %d", id_fantasia);
    limpar_buffer();

    printf("Digite o id do cliente: ");
    scanf(" %d", id_cliente);
    limpar_buffer();

    printf("Digite o preco do pedido: ");
    scanf(" %f", preco);
    limpar_buffer();

    printf("Digite a data do pedido: ");
    scanf(" %[^\n]", data_pedido);
    limpar_buffer();

    printf("\nCadastro realizado!\n");
    sleep(1);
}

void menu_deletar_pedido(int* id_fantasia, int* id_cliente, float* preco, char data_pedido[]) {
    *id_fantasia = 0;
    *id_cliente = 0;
    *preco = 0;
    data_pedido[0] = '\0';
}

void modulo_pedido(void) {
    char op;
    int id_fantasia = 0;
    int id_cliente = 0;
    float preco = 0;
    char data_pedido[60] = "";
    char op_delete = '2';

    do {
        op = menu_pedido();
        switch(op) {
            case '1':
                menu_lista_pedido(&id_fantasia, &id_cliente, &preco, data_pedido);
                printf("\nPressione Enter para voltar...\n");
                getchar();
                limpar_buffer();                  
                break;
            case '2':
                menu_cadastro_pedido(&id_fantasia, &id_cliente, &preco, data_pedido);
                break;
            case '3':
                menu_alterar_pedido(&id_fantasia, &id_cliente, &preco, data_pedido);
                break;
            case '4':
                system("clear||cls");
                menu_lista_pedido(&id_fantasia, &id_cliente, &preco, data_pedido);
                printf("\nDeseja excluir esse pedido?\n");
                printf("1 - Sim\n");
                printf("2 - Nao\n");
                op_delete = getchar();
                limpar_buffer();
                switch (op_delete){
                case '1':
                    menu_deletar_pedido(&id_fantasia, &id_cliente, &preco, data_pedido);
                    system("clear||cls");
                    printf("Pedido excluido com sucesso!\n");
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