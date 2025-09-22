#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <unistd.h>
#include <string.h>

#include "../Utilidades/utilidades.h"

char nome_func[60] = "";
char cpf_func[60] = "";
char celular_func[60] = "";
char email_func[60] = "";
float salario_func = 0;

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
    int comparacao = strcmp(cpf_pesquisar, cpf_func);
    if (comparacao == 0)
    {
        system("clear||cls");
        printf("╔═════════════════════════════════════════════════════════════════════════════════╗\n");
        printf("║                                    Funcionario Pesquisado                       ║\n");
        printf("╚═════════════════════════════════════════════════════════════════════════════════╝\n");
        printf("Nome do funcionario: %s\n", nome_func);
        printf("Cpf do funcionario: %s\n", cpf_func);
        printf("Telefone do funcionario: %s\n", celular_func);
        printf("Email do funcionario: %s\n", email_func);
        printf("Salario do funcionario: %f\n", salario_func);
        return 1;
    }
    else
    {
        system("clear||cls");
        printf("Cpf_pesquisado: %s\n", cpf_pesquisar);
        printf("\nNao tem nenhum funcionario com esse cpf.");
        return 0;
    }
    
}

void menu_cadastro_funcionario(char nome_func[], char cpf_func[], char celular_func[], char email_func[], float* salario_func) {
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
    scanf(" %f", salario_func);
    limpar_buffer();

    printf("\nCadastro realizado!\n");
    sleep(1);
}

void menu_alterar_funcionario(char nome_func[], char cpf_func[], char celular_func[], char email_func[], float* salario_func) {
    system("clear||cls");
    printf("╔═════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                                   Alterar Funcionario                           ║\n");
    printf("╚═════════════════════════════════════════════════════════════════════════════════╝\n");
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
    scanf(" %f", salario_func);
    limpar_buffer();

    printf("\nFuncionario alterado!\n");
    sleep(1);
}

void menu_deletar_funcionario(char nome_func[], char cpf_func[], char celular_func[], char email_func[], float* salario_func) {
    nome_func[0] = '\0';
    cpf_func[0] = '\0';
    celular_func[0] = '\0';
    email_func[0] = '\0';
    *salario_func = 0;
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
                menu_cadastro_funcionario(nome_func, cpf_func, celular_func, email_func, &salario_func);
                break;
            case '3':
                menu_alterar_funcionario(nome_func, cpf_func, celular_func, email_func, &salario_func);
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
                        menu_deletar_funcionario(nome_func, cpf_func, celular_func, email_func, &salario_func);
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