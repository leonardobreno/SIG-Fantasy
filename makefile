ifeq ($(OS),Windows_NT)
	REMOVE = del /Q
	EXE = projeto.exe
else
	REMOVE = rm -f
	EXE = projeto
endif

all:
	gcc -c -Wall Validacoes/validacoes.c
	gcc -c -Wall Utilidades/utilidades.c
	gcc -c -Wall Clientes/clientes.c
	gcc -c -Wall Fantasias/fantasias.c
	gcc -c -Wall Funcionarios/funcionarios.c
	gcc -c -Wall Pedidos/pedidos.c
	gcc -c -Wall Informacoes/informacoes.c
	gcc -c -Wall Relatorios/relatorios.c
	gcc -c -Wall projeto.c
	gcc -o $(EXE) *.o

run: all
	./$(EXE)

clean:
	-$(REMOVE) *.o