ifeq ($(OS),Windows_NT)
    REMOVE = del /Q
    EXE = projeto.exe
else
    REMOVE = rm -f
    EXE = projeto
endif


CFLAGS = -Wall -finput-charset=UTF-8 -fexec-charset=UTF-8

all:
    gcc -c $(CFLAGS) Validacoes/validacoes.c
    gcc -c $(CFLAGS) Utilidades/utilidades.c
    gcc -c $(CFLAGS) Clientes/clientes.c
    gcc -c $(CFLAGS) Fantasias/fantasias.c
    gcc -c $(CFLAGS) Funcionarios/funcionarios.c
    gcc -c $(CFLAGS) Pedidos/pedidos.c
    gcc -c $(CFLAGS) Informacoes/informacoes.c
    gcc -c $(CFLAGS) projeto.c
    gcc -o $(EXE) *.o $(CFLAGS)

run: all
    ./$(EXE)

clean:
    -$(REMOVE) *.o