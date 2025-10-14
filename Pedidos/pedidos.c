#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct {
    char nome[51];
    char cpf[15];
    char celular[20];
    char email[51];
    char salario[20];
    int ativo;
} Funcionario;

Funcionario* funcionarios = NULL;
int num_funcionarios = 0;

void salvar_funcionarios_binario();
void carregar_funcionarios_binario();
void liberar_memoria_funcionarios();
void menu_cadastro_funcionario();
void menu_pesquisar_funcionario();
void menu_alterar_funcionario();
void menu_deletar_funcionario();
char menu_funcionario(void);
void limpar_buffer();
void gerenciar_funcionarios();

void gerenciar_funcionarios() {
    carregar_funcionarios_binario();
    char op;
    do {
        op = menu_funcionario();
        switch (op) {
            case '1':
                menu_pesquisar_funcionario();
                break;
            case '2':
                menu_cadastro_funcionario();
                break;
            case '3':
                menu_alterar_funcionario();
                break;
            case '4':
                menu_deletar_funcionario();
                break;
            case '5':
                printf("Voltando ao menu principal...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
                sleep(1);
        }
    } while (op != '5');
    liberar_memoria_funcionarios();
}

void salvar_funcionarios_binario() {
    FILE* arquivo = fopen("funcionarios.dat", "wb");
    if (arquivo == NULL) {
        printf("Erro fatal: Nao foi possivel abrir o arquivo para escrita!\n");
        return;
    }
    fwrite(funcionarios, sizeof(Funcionario), num_funcionarios, arquivo);
    fclose(arquivo);
}

void carregar_funcionarios_binario() {
    FILE* arquivo = fopen("funcionarios.dat", "rb");
    if (arquivo == NULL) {
        printf("Arquivo de dados nao encontrado. Iniciando com base de dados vazia.\n");
        return;
    }

    fseek(arquivo, 0, SEEK_END);
    long tamanho_arquivo = ftell(arquivo);
    rewind(arquivo);

    num_funcionarios = tamanho_arquivo / sizeof(Funcionario);

    funcionarios = (Funcionario*) malloc(num_funcionarios * sizeof(Funcionario));
    if (funcionarios == NULL) {
        printf("Erro fatal: Falha ao alocar memoria!\n");
        fclose(arquivo);
        return;
    }
    fread(funcionarios, sizeof(Funcionario), num_funcionarios, arquivo);
    fclose(arquivo);
}

void liberar_memoria_funcionarios() {
    if (funcionarios != NULL) {
        free(funcionarios);
        funcionarios = NULL;
        num_funcionarios = 0;
    }
}

void menu_cadastro_funcionario() {
    system("clear||cls");
    printf("╔═════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                                 Cadastro Funcionário                              ║\n");
    printf("╚═════════════════════════════════════════════════════════════════════════════════╝\n");

    Funcionario novo_funcionario;

    printf("Digite o nome: ");
    scanf(" %50[^\n]", novo_funcionario.nome);
    limpar_buffer();

    printf("Digite o CPF: ");
    scanf(" %14[^\n]", novo_funcionario.cpf);
    limpar_buffer();

    printf("Digite o numero de celular: ");
    scanf(" %19[^\n]", novo_funcionario.celular);
    limpar_buffer();

    printf("Digite o Email: ");
    scanf(" %50[^\n]", novo_funcionario.email);
    limpar_buffer();
    
    printf("Digite o Salário: ");
    scanf(" %19[^\n]", novo_funcionario.salario);
    limpar_buffer();

    novo_funcionario.ativo = 1;

    Funcionario* temp = realloc(funcionarios, (num_funcionarios + 1) * sizeof(Funcionario));
    if (temp == NULL) {
        printf("Erro: Nao foi possivel alocar memoria!\n");
        return;
    }
    funcionarios = temp;

    funcionarios[num_funcionarios] = novo_funcionario;
    num_funcionarios++;

    salvar_funcionarios_binario();

    printf("\nCadastro realizado com sucesso!\n");
    sleep(1);
}

void menu_pesquisar_funcionario() {
    char cpf_procurar[15];
    int encontrado = 0;

    system("clear||cls");
    printf("Digite o CPF do funcionário que deseja pesquisar: ");
    scanf(" %14[^\n]", cpf_procurar);
    limpar_buffer();

    for (int i = 0; i < num_funcionarios; i++) {
        if (strcmp(cpf_procurar, funcionarios[i].cpf) == 0 && funcionarios[i].ativo == 1) {
            system("clear||cls");
            printf("╔═════════════════════════════════════════════════════════════════════════════════╗\n");
            printf("║                               Funcionário Encontrado                            ║\n");
            printf("╚═════════════════════════════════════════════════════════════════════════════════╝\n");
            printf("Nome: %s\n", funcionarios[i].nome);
            printf("CPF: %s\n", funcionarios[i].cpf);
            printf("Celular: %s\n", funcionarios[i].celular);
            printf("Email: %s\n", funcionarios[i].email);
            printf("Salário: %s\n", funcionarios[i].salario);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("\nNenhum funcionário ativo encontrado com o CPF: %s\n", cpf_procurar);
    }
    printf("\nPressione Enter para continuar...");
    limpar_buffer();
}

void menu_alterar_funcionario() {
    char cpf_procurar[15];
    int encontrado_idx = -1;

    system("clear||cls");
    printf("Digite o CPF do funcionário que deseja alterar: ");
    scanf(" %14[^\n]", cpf_procurar);
    limpar_buffer();

    for (int i = 0; i < num_funcionarios; i++) {
        if (strcmp(cpf_procurar, funcionarios[i].cpf) == 0 && funcionarios[i].ativo == 1) {
            encontrado_idx = i;
            break;
        }
    }

    if (encontrado_idx != -1) {
        system("clear||cls");
        printf("╔═════════════════════════════════════════════════════════════════════════════════╗\n");
        printf("║                                 Alterar Funcionário                               ║\n");
        printf("╚═════════════════════════════════════════════════════════════════════════════════╝\n");
        printf("Funcionário encontrado! (Deixe em branco e pressione Enter para nao alterar)\n\n");
        
        printf("Nome: %s\n", funcionarios[encontrado_idx].nome);
        printf("CPF: %s\n", funcionarios[encontrado_idx].cpf);

        char novo_celular[20], novo_email[51], novo_salario[20];

        printf("Celular atual: %s\n", funcionarios[encontrado_idx].celular);
        printf("Digite o novo celular: ");
        scanf(" %19[^\n]", novo_celular);
        limpar_buffer();

        printf("Email atual: %s\n", funcionarios[encontrado_idx].email);
        printf("Digite o novo email: ");
        scanf(" %50[^\n]", novo_email);
        limpar_buffer();

        printf("Salário atual: %s\n", funcionarios[encontrado_idx].salario);
        printf("Digite o novo salário: ");
        scanf(" %19[^\n]", novo_salario);
        limpar_buffer();

        if (strlen(novo_celular) > 0) {
            strcpy(funcionarios[encontrado_idx].celular, novo_celular);
        }
        if (strlen(novo_email) > 0) {
            strcpy(funcionarios[encontrado_idx].email, novo_email);
        }
        if (strlen(novo_salario) > 0) {
            strcpy(funcionarios[encontrado_idx].salario, novo_salario);
        }
        
        salvar_funcionarios_binario();
        printf("\nFuncionário alterado com sucesso!\n");
    } else {
        printf("\nNenhum funcionário ativo encontrado com o CPF: %s\n", cpf_procurar);
    }
    sleep(1);
}

void menu_deletar_funcionario() {
    char cpf_procurar[15];
    int encontrado_idx = -1;

    system("clear||cls");
    printf("Digite o CPF do funcionário que deseja deletar: ");
    scanf(" %14[^\n]", cpf_procurar);
    limpar_buffer();

    for (int i = 0; i < num_funcionarios; i++) {
        if (strcmp(cpf_procurar, funcionarios[i].cpf) == 0 && funcionarios[i].ativo == 1) {
            encontrado_idx = i;
            break;
        }
    }

    if (encontrado_idx != -1) {
        funcionarios[encontrado_idx].ativo = 0;
        salvar_funcionarios_binario();
        printf("Funcionário excluído com sucesso!\n");
    } else {
        printf("Nenhum funcionário ativo encontrado com esse CPF!\n");
    }
    sleep(1);
}

char menu_funcionario(void) {
    char op;
    system("clear||cls");
    printf("╔═════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                                 Modulo Funcionários                               ║\n");
    printf("╠═════════════════════════════════════════════════════════════════════════════════╣\n");
    printf("║                               -> 1 • Pesquisar funcionário                        ║\n");
    printf("║                               -> 2 • Cadastrar funcionário                        ║\n");
    printf("║                               -> 3 • Alterar funcionário                          ║\n");
    printf("║                               -> 4 • Deletar funcionário                          ║\n");
    printf("║                               -> 5 • Voltar                                       ║\n");
    printf("╚═════════════════════════════════════════════════════════════════════════════════╝\n");
    printf("Escolha uma opção: ");
    scanf(" %c", &op);
    limpar_buffer();
    return op;
}

void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    gerenciar_funcionarios();
    return 0;
}