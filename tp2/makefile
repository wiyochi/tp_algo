OPT = -g -Wall -Wextra
LOG = @echo "\#MAKE"
PF = pile-file
TRUC = truc

all: $(PF) $(TRUC)

$(TRUC): truc.c pile.o
	gcc -o $(TRUC) truc.c pile.o $(OPT)
	$(LOG) "executable truc généré"

$(PF): test.c pile.o file.o
	gcc -o $(PF) test.c pile.o file.o $(OPT)
	$(LOG) "excutable pile-file généré"

pile.o: pile.h pile.c
	gcc -o pile.o -c pile.c $(OPT)
	$(LOG) "lib pile généré"
	
file.o: file.h file.c
	gcc -o file.o -c file.c $(OPT)
	$(LOG) "lib file généré"

clean:
	rm *.o
	rm $(PF)
	rm $(TRUC)