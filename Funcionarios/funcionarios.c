#include <stdio.h>   
    // Entrada e saída
#include <stdlib.h>  
    // Funções utilitárias
#include <unistd.h>  
    // Funções do Linux/Unix
#include <string.h>  
    // Manipulação de strings
#include "../Utilidades/utilidades.h"

char nome_func[60] = "";
char cpf_func[60] = "";
char celular_func[60] = "";
char email_func[60] = "";
char salario_func[60] = "";

void cad_funcinario(char nome_func[], char cpf_func[], char cel_func[], char email_func[], char salario_func[]){
    FILE *funcionarios = fopen("Funcionarios/funcionarios.txt", "a");
    if(funcionarios != NULL){
        fprintf(funcionarios, "%s, %s, %s, %s, %s\n", nome_func, cpf_func, cel_func, email_func, salario_func);
        fclose(funcionarios);
    }
    else{
        printf("arquivo nao encontrado!\n");
    }
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

int menu_pesquisar_funcionario(char cpf_pesquisar[]) {
    FILE *busca = fopen("Funcionarios/funcionarios.txt", "r");
    char nome_temp[60], cpf_temp[60], cel_temp[60], email_temp[60], salario_temp[60];
    int encontrado = 0;

    if (busca == NULL) {
        printf("Erro ao abrir arquivo funcionarios\n");
        return 0;
    }

    // Percorre o arquivo linha por linha
    while (fscanf(busca, " %59[^,], %59[^,], %59[^,], %59[^,], %59[^\n]\n",
                  nome_temp, cpf_temp, cel_temp, email_temp, salario_temp) == 5) {
        if (strcmp(cpf_pesquisar, cpf_temp) == 0) {
            // Copia para as variáveis globais
            strcpy(nome_func, nome_temp);
            strcpy(cpf_func, cpf_temp);
            strcpy(celular_func, cel_temp);
            strcpy(email_func, email_temp);
            strcpy(salario_func, salario_temp);
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
        printf("Nome do funcionario: %s\n", nome_func);
        printf("Cpf do funcionario: %s\n", cpf_func);
        printf("Telefone do funcionario: %s\n", celular_func);
        printf("Email do funcionario: %s\n", email_func);
        printf("Salario do funcionario: %s\n", salario_func);
        return 1;
    } else {
        printf("Cpf pesquisado: %s\n", cpf_pesquisar);
        printf("\nNao tem nenhum funcionario com esse cpf.\n");
        return 0;
    }
}


void menu_cadastro_funcionario(char nome_func[], char cpf_func[], char celular_func[], char email_func[], char salario_func[]){
    system("clear||cls");
    printf("╔═════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                                   Cadastro Funcionario                          ║\n");
    printf("╚═════════════════════════════════════════════════════════════════════════════════╝\n");
    printf("Digite o nome do funcionario: ");
    scanf(" %[^\n]", nome_func);
    limpar_buffer();

    printf("Digite o cpf do funcionario: ");
    scanf(" %[^\n]", cpf_func);
    limpar_buffer();

    printf("Digite o celular do funcionario: ");
    scanf(" %[^\n]", celular_func);
    limpar_buffer();

    printf("Digite o email do funcionario: ");
    scanf(" %[^\n]", email_func);
    limpar_buffer();

    printf("Digite o salario do funcionario: ");
    scanf(" %[^\n]", salario_func);
    limpar_buffer();

    cad_funcinario(nome_func, cpf_func, celular_func, email_func, salario_func);

    printf("\nCadastro realizado!\n");
    sleep(1);
}

void menu_alterar_funcionario(char cpf_procurar[]) {
    if (menu_pesquisar_funcionario(cpf_procurar)) {
        system("clear||cls");
        printf("╔═════════════════════════════════════════════════════════════════════════════════╗\n");
        printf("║                                   Alterar Funcionario                           ║\n");
        printf("╚═════════════════════════════════════════════════════════════════════════════════╝\n");

        printf("Nome atual: %s\n", nome_func);
        printf("CPF atual: %s\n", cpf_func);
        printf("Celular atual: %s\n", celular_func);
        printf("Email atual: %s\n", email_func);
        printf("Salario atual: %s\n\n", salario_func);

        printf("Digite o novo nome do funcionario: ");
        scanf(" %[^\n]", nome_func);
        limpar_buffer();

        printf("Digite o novo cpf do funcionario: ");
        scanf(" %[^\n]", cpf_func);
        limpar_buffer();

        printf("Digite o novo celular do funcionario: ");
        scanf(" %[^\n]", celular_func);
        limpar_buffer();

        printf("Digite o novo email do funcionario: ");
        scanf(" %[^\n]", email_func);
        limpar_buffer();

        printf("Digite o novo salario do funcionario: ");
        scanf(" %[^\n]", salario_func);
        limpar_buffer();

        FILE *arquivo = fopen("Funcionarios/funcionarios.txt", "r");
        FILE *alterar = fopen("Funcionarios/alterar.txt", "w");

        char nome[60], cpf[60], cel[60], email[60], salario[60];
        while (fscanf(arquivo, " %59[^,], %59[^,], %59[^,], %59[^,], %59[^\n]\n",
                      nome, cpf, cel, email, salario) == 5) {
            if (strcmp(cpf, cpf_procurar) == 0) {
                fprintf(alterar, "%s, %s, %s, %s, %s\n", nome_func, cpf_func, celular_func, email_func, salario_func);
            } else {
                fprintf(alterar, "%s, %s, %s, %s, %s\n", nome, cpf, cel, email, salario);
            }
        }

        fclose(arquivo);
        fclose(alterar);

        remove("Funcionarios/funcionarios.txt");
        rename("Funcionarios/alterar.txt", "Funcionarios/funcionarios.txt");

        system("clear||cls");
        printf("╔═════════════════════════════════════════════════════════════════════════════════╗\n");
        printf("║                       Funcionario alterado com sucesso!                         ║\n");
        printf("╚═════════════════════════════════════════════════════════════════════════════════╝\n");
        sleep(1);
    } else {
        printf("Nenhum funcionario encontrado com esse CPF!\n");
        sleep(1);
    }
}

void menu_deletar_funcionario(char cpf_pesquisar[]) {
    FILE *busca = fopen("Funcionarios/funcionarios.txt", "r");
    FILE *excluir = fopen("Funcionarios/temp.txt", "w");
    int encontrado = 0;

    if(busca == NULL || excluir == NULL){
        printf("Erro ao abrir arquivo de funcionarios!\n");
        return;
    }

    while (fscanf(busca, " %59[^,], %59[^,], %59[^,], %59[^,], %59[^\n]\n",
                  nome_func, cpf_func, celular_func, email_func, salario_func) == 5) {
        if(strcmp(cpf_pesquisar, cpf_func) != 0) {
            fprintf(excluir, "%s, %s, %s, %s, %s\n", nome_func, cpf_func, celular_func, email_func, salario_func);
        } else {
            encontrado = 1;
        }
    }

    fclose(busca);
    fclose(excluir);

    remove("Funcionarios/funcionarios.txt");
    rename("Funcionarios/temp.txt", "Funcionarios/funcionarios.txt");

    system("clear||cls");

    if(encontrado) {
        printf("╔═════════════════════════════════════════════════════════════════════════════════╗\n");
        printf("║                       Funcionario excluído com sucesso!                         ║\n");
        printf("╚═════════════════════════════════════════════════════════════════════════════════╝\n");
    } else {
        printf("╔═════════════════════════════════════════════════════════════════════════════════╗\n");
        printf("║                        Nenhum funcionario encontrado!                           ║\n");
        printf("╚═════════════════════════════════════════════════════════════════════════════════╝\n");
    }

    sleep(1);
}


void modulo_funcionario(void) {
    char op;
    char cpf_procurar[50] = "";
    char op_delete = '2';
    int funcionario_achado;

    do {
        op = menu_funcionario();
        switch(op) {
            case '1':
                printf("\nDigite o cpf do cliente que deseja pesquisar: ");
                scanf("%[^\n]", cpf_procurar);
                menu_pesquisar_funcionario(cpf_procurar);
                getchar();
                printf("\nPressione Enter para voltar...\n");
                limpar_buffer();                  
                break;
            case '2':
                menu_cadastro_funcionario(nome_func, cpf_func, celular_func, email_func, salario_func);
                break;
            case '3':
                menu_alterar_funcionario(cpf_func);
                break;
            case '4':
                system("clear||cls");
                printf("\nDigite o cpf do cliente que deseja pesquisar: ");
                scanf("%[^\n]", cpf_procurar);
                funcionario_achado = menu_pesquisar_funcionario(cpf_procurar);
                getchar();
                if (funcionario_achado == 1)
                {
                    printf("\nDeseja excluir esse funcionario?\n");
                    printf("1 - Sim\n");
                    printf("2 - Nao\n");
                    op_delete = getchar();
                    limpar_buffer();
                    switch (op_delete){
                    case '1':
                        menu_deletar_funcionario(cpf_func);
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
                }     
                else
                {
                    sleep(1);
                }
                     
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