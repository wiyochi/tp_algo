OPT = -g -Wall -Wextra
LOG = @echo "\#MAKE"
TEST = test

all: $(TEST)

$(TEST): test.c pile.o arbre.o
	gcc -o $(TEST) test.c pile.o arbre.o $(OPT)
	$(LOG) "executable $(TEST) généré"

pile.o: pile.h pile.c
	gcc -o pile.o -c pile.c $(OPT)
	$(LOG) "lib pile généré"

arbre.o: arbre.h arbre.c
	gcc -o arbre.o -c arbre.c $(OPT)
	$(LOG) "lib arbre généré"

clean:
	rm *.o
	rm $(TEST)