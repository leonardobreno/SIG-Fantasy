#include <stdio.h>   
    // Entrada e saída
#include <stdlib.h>  
    // Funções utilitárias
#include <unistd.h>  
    // Funções do Linux/Unix
#include <string.h>  
    // Manipulação de strings
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

void cad_cliente(char nome[], char cpf[], char celular[], char email[]){
    FILE *clientes = fopen("Clientes/clientes.txt", "a");
    if(clientes != NULL){
        fprintf(clientes, "%s, %s, %s, %s\n", nome, cpf, celular, email);
        fclose(clientes);
    }
    else{
        printf("arquivo nao encontrado!\n");
    }
}


int menu_pesquisar_cliente(char cpf_procurar[]) {
    FILE *busca = fopen("Clientes/clientes.txt", "r");
    char nome_tempo[60], cpf_tempo[60], cel_tempo[60], email_tempo[60];
    int encontrado = 0;

    if (busca == NULL) {
        printf("Erro ao abrir arquivo clientes\n");
        return 0;
    }

    while (fscanf(busca, " %59[^,], %59[^,], %59[^,], %59[^,]\n",
                  nome_tempo, cpf_tempo, cel_tempo, email_tempo) == 4) {
        if (strcmp(cpf_procurar, cpf_tempo) == 0) {
            strcpy(nome, nome_tempo);
            strcpy(cpf, cpf_tempo);
            strcpy(celular, cel_tempo);
            strcpy(email, email_tempo);
            encontrado = 1;
            break;
        }
    }

    fclose(busca);

    system("clear||cls");

    if (encontrado) {
        printf("╔═════════════════════════════════════════════════════════════════════════════════╗\n");
        printf("║                                  Funcionario Pesquisado                          ║\n");
        printf("╚═════════════════════════════════════════════════════════════════════════════════╝\n");
        printf("Nome do funcionario: %s\n", nome);
        printf("Cpf do funcionario: %s\n", cpf);
        printf("Telefone do funcionario: %s\n", celular);
        printf("Email do funcionario: %s\n", email);
        return 1;
    } else {
        printf("Cpf pesquisado: %s\n", cpf_procurar);
        printf("\nNao tem nenhum cliente com esse cpf.\n");
        return 0;
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
    
    cad_cliente(nome, cpf, celular, email);

    printf("\nCadastro realizado!\n");
    sleep(1);
}

void menu_alterar_cliente(char nome[], char cpf[], char celular[], char email[]) {
    char nome[60], celular[60], email[60], salario[60];
    char cpf_procurar[60], cpf_cliente[60];
    FILE *busca = fopen("Clientes/clientes.txt", "r");
    FILE *alterar = fopen("Clientes/alteracao.txt", "w");
    int encontrado = 0;

    if (busca == NULL || alterar == NULL) {
        printf("Erro ao abrir o arquivo de clientes!\n");
        return;
    }

    system("clear||cls");
    printf("Digite o CPF do cliente que deseja alterar: ");
    scanf(" %[^\n]", cpf_procurar);
    limpar_buffer();

    while (fscanf(busca, " %59[^,], %59[^,], %59[^,], %59[^,], %59[^\n]\n",
                  nome, cpf_cliente, celular, email) == 4) {

        if (strcmp(cpf_procurar, cpf_cliente) == 0) {
            system("clear||cls");
            printf("╔═════════════════════════════════════════════════════════════════════════════════╗\n");
            printf("║                                Alterar Funcionario                              ║\n");
            printf("╚═════════════════════════════════════════════════════════════════════════════════╝\n");

            printf("Funcionario encontrado!\n\n");
            printf("Nome: %s\n", nome);
            printf("CPF: %s\n", cpf_cliente);
            printf("Celular atual: %s\n", celular);
            printf("Email atual: %s\n", email);

            printf("Digite o novo celular: ");
            scanf(" %[^\n]", celular);
            limpar_buffer();

            printf("Digite o novo email: ");
            scanf(" %[^\n]", email);
            limpar_buffer();

            fprintf(alterar, "%s, %s, %s, %s, %s\n", nome, cpf_cliente, celular, email);
            encontrado = 1;
        } else {
            // mantém os dados do funcionário não alterado
            fprintf(alterar, "%s, %s, %s, %s, %s\n", nome, cpf_cliente, celular, email);
        }
    }

    fclose(busca);
    fclose(alterar);

    remove("Clientes/clientes.txt");
    rename("Clientes/alteracao.txt", "Clientes/clientes.txt");

    system("clear||cls");

    if (encontrado) {
        printf("╔═════════════════════════════════════════════════════════════════════════════════╗\n");
        printf("║                         Cliente alterado com sucesso!                           ║\n");
        printf("╚═════════════════════════════════════════════════════════════════════════════════╝\n");
    } else {
        printf("╔═════════════════════════════════════════════════════════════════════════════════╗\n");
        printf("║                          Nenhum cliente encontrado!                             ║\n");
        printf("╚═════════════════════════════════════════════════════════════════════════════════╝\n");
    }

    sleep(1);
}

void menu_deletar_cliente(char cpf_procurar[]) {
    char nome[60], cpf[60], celular[60], email[60];
    FILE *busca = fopen("Clientes/clientes.txt", "r");
    FILE *alterar = fopen("Clientes/alterar.txt", "w");
    int encontrado = 0;

    if (!busca || !alterar) {
        printf("Erro ao abrir o arquivo de clientes!\n");
        return;
    }

    while (fscanf(busca, " %59[^,], %59[^,], %59[^,], %59[^,]\n",
                  nome, cpf, celular, email) == 4) {
        if (strcmp(cpf_procurar, cpf) == 0) {
            encontrado = 1;
        } else {
            fprintf(alterar, "%s, %s, %s, %s\n", nome, cpf, celular, email);
        }
    }

    fclose(busca);
    fclose(alterar);

    remove("Clientes/clientes.txt");
    rename("Clientes/alterar.txt", "Clientes/clientes.txt");

    system("clear||cls");

    if (encontrado) {
        printf("Cliente excluído com sucesso!\n");
    } else {
        printf("Nenhum cliente encontrado com esse CPF!\n");
    }

    sleep(1);
}
