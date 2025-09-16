#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <unistd.h>
#include <string.h>

#include "Utilidades/utilidades.h"
#include "Informacoes/informacoes.h"
#include "Pedidos/pedidos.h"
#include "Funcionarios/funcionarios.h"
#include "Fantasias/fantasias.h"
#include "Clientes/clientes.h"

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