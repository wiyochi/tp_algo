OPT = -g -Wall -Wextra
LOG = @echo "\#MAKE"
TEST = test

all: $(TEST)

$(TEST): test.c dictionnaire.o
	gcc -o $(TEST) test.c dictionnaire.o $(OPT)
	$(LOG) "executable $(TEST) généré"

dictionnaire.o: dictionnaire.h dictionnaire.c
	gcc -o dictionnaire.o -c dictionnaire.c $(OPT)
	$(LOG) "lib dictionnaire généré"

clean:
	rm *.o
	rm $(TEST)