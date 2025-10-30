run: all
	./projeto.exe

all:
	gcc -c Wall Validacoes/validacoes.c; gcc -c -Wall Utilidades/utilidades.c; gcc -c -Wall Clientes/clientes.c; gcc -c -Wall Fantasias/fantasias.c; gcc -c -Wall Funcionarios/funcionarios.c; gcc -c -Wall Pedidos/pedidos.c; gcc -c -Wall Informacoes/informacoes.c; gcc -c -Wall projeto.c;
	gcc -o projeto.exe *o

clean:
	rm *.o
