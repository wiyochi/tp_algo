OPT = -g -Wall -Wextra
LOG = @echo "\#MAKE"
TEST = test

all: $(TEST)

$(TEST): test.c pile.o
	gcc -o $(TEST) test.c pile.o $(OPT)
	$(LOG) "executable $(TEST) généré"

pile.o: pile.h pile.c
	gcc -o pile.o -c pile.c $(OPT)
	$(LOG) "lib pile généré"

clean:
	rm *.o
	rm $(TEST)