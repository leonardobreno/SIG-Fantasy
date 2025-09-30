#include <stdio.h>   
    // Entrada e saída
#include <stdlib.h>  
    // Funções utilitárias
#include <unistd.h>  
    // Funções do Linux/Unix
#include <string.h>  
    // Manipulação de strings
#include "../Utilidades/utilidades.h"

char nome_fantasia[50] = "";
char tamanho[10] = "";
char cor[20] = "";

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

void cad_fantasia(char nome_fantasia[], char tamanho[], char cor[]){
    FILE *fantasias = fopen("Fantasias/fantasias.txt", "a");
    if(fantasias != NULL){
        fprintf(fantasias, "%s, %s, %s\n", nome_fantasia, tamanho, cor);
        fclose(fantasias);
    }else{
        printf("arquivo nao encontrado!\n");
    }
    
}


int menu_pesquisar_fantasia(char fantasia_pesquisar[]) {
    int comparacao = strcmp(fantasia_pesquisar, nome_fantasia);
    if (comparacao == 0)
    {
        system("clear||cls");
        printf("╔═════════════════════════════════════════════════════════════════════════════════╗\n");
        printf("║                                   Fantasia Pesquisada                           ║\n");
        printf("╚═════════════════════════════════════════════════════════════════════════════════╝\n");
        printf("Nome: %s\n", nome_fantasia);
        printf("Tamanho: %s\n", tamanho);
        printf("Cor: %s\n", cor);
        return 1;
    }
    else
    {
        system("clear||cls");
        printf("Nome_pesquisado: %s\n", fantasia_pesquisar);
        printf("\nNao tem nenhuma fantasia com esse nome.");
        return 0;
    }
    
}

void menu_cadastro_fantasia(char nome_fantasia[], char tamanho[], char cor[]) {
    system("clear||cls");
    printf("╔═════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                                   Cadastro Fantasia                             ║\n");
    printf("╚═════════════════════════════════════════════════════════════════════════════════╝\n");
    printf("Digite o nome da fantasia: ");
    scanf(" %[^\n]", nome_fantasia);
    limpar_buffer();

    printf("Digite o tamanho: ");
    scanf(" %[^\n]", tamanho);
    limpar_buffer();

    printf("Digite a cor: ");
    scanf(" %[^\n]", cor);
    limpar_buffer();

    cad_fantasia(nome_fantasia, tamanho, cor);

    printf("\nCadastro realizado!\n");
    sleep(1);
}

void menu_alterar_fantasia(char nome_fantasia[], char tamanho[], char cor[]) {
    system("clear||cls");
    printf("╔═════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                                    Alterar Fantasia                             ║\n");
    printf("╚═════════════════════════════════════════════════════════════════════════════════╝\n");
    printf("Digite o novo nome da fantasia: ");
    scanf(" %[^\n]", nome_fantasia);
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

void menu_deletar_fantasia(char nome_fantasia[], char tamanho[], char cor[]) {
    nome_fantasia[0] = '\0';
    tamanho[0] = '\0';
    cor[0] = '\0';
}

void modulo_fantasia(void) {
    char op;
    char nome_procurar[50] = "";
    char op_delete = '2';
    int cliente_achado;

    do {
        op = menu_fantasia();
        switch(op) {
            case '1':
                printf("\nDigite o nome da fantasia que deseja pesquisar: ");
                scanf("%[^\n]", nome_procurar);
                menu_pesquisar_fantasia(nome_procurar);
                getchar();
                printf("\nPressione Enter para voltar...\n");
                limpar_buffer();                
                break;
            case '2':
                menu_cadastro_fantasia(nome_fantasia, tamanho, cor);
                break;
            case '3':
                menu_alterar_fantasia(nome_fantasia, tamanho, cor);
                break;
            case '4':
                system("clear||cls");
                printf("\nDigite o nome da fantasia que deseja pesquisar: ");
                scanf("%[^\n]", nome_procurar);
                cliente_achado = menu_pesquisar_fantasia(nome_procurar);
                getchar();
                if (cliente_achado == 1)
                {
                    limpar_buffer();
                    printf("\nDeseja excluir essa fantasia?\n");
                    printf("1 - Sim\n");
                    printf("2 - Nao\n");
                    op_delete = getchar();
                    limpar_buffer();
                    switch (op_delete){
                    case '1':
                        menu_deletar_fantasia(nome_fantasia, tamanho, cor);
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