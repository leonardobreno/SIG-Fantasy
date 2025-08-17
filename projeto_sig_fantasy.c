#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <unistd.h>

char menuprincipal(void);


int main(void) {
    char opc;

    do {
        opc = menuprincipal();
        switch(opc) {
            case '1':
                break;
            case '2':
                break;
            case '3':
                break;
            case '4':
                break;
            case '5':
                break;
            case '6':
                printf("Fechando o programa...\n");
                sleep(1);
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
                sleep(1);
        }
    } while(opc != '6');

    return 0;
}

char menuprincipal(void) {
    char op;
    setlocale(LC_ALL, "Portuguese");

    system("clear||cls");

    printf("+------------------------------------------------+\n");
    printf("|                  SIG-Fantasy:                  |\n");
    printf("|                                                |\n");
    printf("|            Loja de fantasias e roupas          |\n");
    printf("+------------------------------------------------+\n");
    printf("|           -> 1 - Modulo Clientes               |\n");
    printf("|           -> 2 - Modulo Fantasias              |\n");
    printf("|           -> 3 - Modulo Pedidos                |\n");
    printf("|           -> 4 - Modulo Informações            |\n");
    printf("|           -> 5 - Modulo Relatórios             |\n");
    printf("|           -> 6 -     Sair                      |\n");
    printf("+------------------------------------------------+\n");
    printf("Escolha uma opção: ");
    scanf(" %c", &op);
    printf("Carregando...\n");
    sleep(2);
    return op;
}