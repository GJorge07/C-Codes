# makefile The Boys
# Carlos Maziero - DINF/UFPR, 2024/2

CC      = gcc
CFLAGS  = -Wall -Wextra -Werror -g -std=c99
LDLIBS  = -lm
MAIN    = theboys
ENTREGA = $(MAIN)

# lista de arquivos de cabeçalho (a completar)
HDR = fila.h fprio.h conjunto.h lista.h entidades.h eventos.h inicia_mundo.h destroi_mundo.h chama_eventos.h outras_funcoes.h

# lista de arquivos-objeto (a completar)
# não inclua conjunto.o, senão ele será removido com "make clean"
OBJ = theboys.o fila.o fprio.o lista.o inicia_mundo.o eventos.o chama_eventos.o destroi_mundo.o outras_funcoes.o


# construir o executável
$(MAIN): $(MAIN).o $(OBJ) conjunto.o

# construir os arquivos-objeto (a completar)
theboys.o: theboys.c $(HDR)

# construir os TADs
fila.o: fila.c fila.h
fprio.o: fprio.c fprio.h
lista.o: lista.c lista.h

# executar
run: $(MAIN)
	./$(MAIN)

# testar no Valgrind
valgrind: $(MAIN)
	valgrind --leak-check=full --track-origins=yes ./$(MAIN)

# gerar arquivo TGZ para entregar
tgz: clean
	-mkdir -p /tmp/$(USER)/$(ENTREGA)
	chmod 0700 /tmp/$(USER)/$(ENTREGA)
	cp *.c *.h conjunto.o makefile /tmp/$(USER)/$(ENTREGA)
	tar czvf $(ENTREGA).tgz -C /tmp/$(USER) $(ENTREGA)
	rm -rf /tmp/$(USER)
	@echo "Arquivo $(ENTREGA).tgz criado para entrega"

# limpar arquivos temporários
clean:
	rm -f *~ $(OBJ) $(MAIN) /tmp/$(USER)/$(ENTREGA) $(ENTREGA).tgz

