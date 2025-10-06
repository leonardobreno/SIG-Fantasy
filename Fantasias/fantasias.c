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
    FILE *busca = fopen("Fantasias/fantasias.txt", "r");
    int encontrado = 0;
    char nome_temp[50], tamanho_temp[20], cor_temp[20];

    if (busca == NULL) {
        printf("Erro ao abrir arquivo fantasias\n");
        return 0;
    }

    while (fscanf(busca, " %49[^,], %19[^,], %19[^\n]\n", nome_temp, tamanho_temp, cor_temp) == 3) {
        if (strcmp(fantasia_pesquisar, nome_temp) == 0) {
            encontrado = 1;
            strcpy(nome_fantasia, nome_temp);
            strcpy(tamanho, tamanho_temp);
            strcpy(cor, cor_temp);
            break;
        }
    }

    fclose(busca);
    system("clear||cls");

    if (encontrado) {
        printf("╔═════════════════════════════════════════════════════════════════════════════════╗\n");
        printf("║                                   Fantasia Pesquisada                           ║\n");
        printf("╚═════════════════════════════════════════════════════════════════════════════════╝\n");
        printf("Nome: %s\n", nome_fantasia);
        printf("Tamanho: %s\n", tamanho);
        printf("Cor: %s\n", cor);
        return 1;
    } else {
        printf("Nome pesquisado: %s\n", fantasia_pesquisar);
        printf("\nNão há nenhuma fantasia com esse nome.\n");
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
    char fantasia_pesquisar[50];
    FILE *busca = fopen("Fantasias/fantasias.txt", "r");
    FILE *alterar = fopen("Fantasias/alterar.txt", "w");
    int encontrado = 0;

    if (busca == NULL || alterar == NULL) {
        printf("Erro ao abrir o arquivo de fantasias!\n");
        return;
    }

    system("clear||cls");
    printf("Digite o nome da fantasia que deseja alterar: ");
    scanf(" %[^\n]", fantasia_pesquisar);
    limpar_buffer();

    while (fscanf(busca, " %49[^,], %19[^,], %19[^\n]\n", nome_fantasia, tamanho, cor) == 3) {
        if (strcmp(fantasia_pesquisar, nome_fantasia) == 0) {
            system("clear||cls");
            printf("╔═════════════════════════════════════════════════════════════════════════════════╗\n");
            printf("║                                 Alterar Fantasia                                ║\n");
            printf("╚═════════════════════════════════════════════════════════════════════════════════╝\n");

            printf("Fantasia encontrada!\n\n");
            printf("Nome atual: %s\n", nome_fantasia);
            printf("Tamanho atual: %s\n", tamanho);
            printf("Cor atual: %s\n\n", cor);

            printf("Digite o novo nome da fantasia: ");
            scanf(" %[^\n]", nome_fantasia);
            limpar_buffer();

            printf("Digite o novo tamanho: ");
            scanf(" %[^\n]", tamanho);
            limpar_buffer();

            printf("Digite a nova cor: ");
            scanf(" %[^\n]", cor);
            limpar_buffer();

            fprintf(alterar, "%s, %s, %s\n", nome_fantasia, tamanho, cor);
            encontrado = 1;
        } else {
            fprintf(alterar, "%s, %s, %s\n", nome_fantasia, tamanho, cor);
        }
    }

    fclose(busca);
    fclose(alterar);

    remove("Fantasias/fantasias.txt");
    rename("Fantasias/alterar.txt", "Fantasias/fantasias.txt");

    system("clear||cls");

    if (encontrado) {
        printf("╔═════════════════════════════════════════════════════════════════════════════════╗\n");
        printf("║                         Fantasia alterada com sucesso!                          ║\n");
        printf("╚═════════════════════════════════════════════════════════════════════════════════╝\n");
    } else {
        printf("╔═════════════════════════════════════════════════════════════════════════════════╗\n");
        printf("║                        Nenhuma fantasia encontrada!                             ║\n");
        printf("╚═════════════════════════════════════════════════════════════════════════════════╝\n");
    }

    sleep(1);
}

void menu_deletar_fantasia(char fantasia_pesquisar[]) {
    FILE *busca = fopen("Fantasias/fantasias.txt", "r");
    FILE *excluir = fopen("Fantasias/alterar.txt", "w");
    int encontrado = 0;

    if (busca == NULL || excluir == NULL) {
        printf("Erro ao abrir arquivo de fantasias!\n");
        return;
    }

    while (fscanf(busca, " %49[^,], %9[^,], %19[^\n]\n", nome_fantasia, tamanho, cor) == 3) {
        if (strcmp(fantasia_pesquisar, nome_fantasia) != 0) {
            fprintf(excluir, "%s, %s, %s\n", nome_fantasia, tamanho, cor);
        } else {
            encontrado = 1;
        }
    }

    fclose(busca);
    fclose(excluir);

    remove("Fantasias/fantasias.txt");
    rename("Fantasias/alterar.txt", "Fantasias/fantasias.txt");

    system("clear||cls");

    if (encontrado) {
        printf("╔═════════════════════════════════════════════════════════════════════════════════╗\n");
        printf("║                           Fantasia excluída com sucesso!                        ║\n");
        printf("╚═════════════════════════════════════════════════════════════════════════════════╝\n");
    } else {
        printf("╔═════════════════════════════════════════════════════════════════════════════════╗\n");
        printf("║                         Nenhuma fantasia encontrada!                            ║\n");
        printf("╚═════════════════════════════════════════════════════════════════════════════════╝\n");
    }

    nome_fantasia[0] = '\0';
    tamanho[0] = '\0';
    cor[0] = '\0';

    sleep(1);
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
                        menu_deletar_fantasia(nome_procurar);
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