OPT = -g -Wall -Wextra
LOG = @echo "\#MAKE"
EXE = pile-file

all: $(EXE)

$(EXE): test.c pile.o
	gcc -o $(EXE) test.c pile.o $(OPT)
	$(LOG) "Executable généré"

pile.o: pile.h pile.c
	gcc -o pile.o -c pile.c $(OPT)
	$(LOG) "lib liste chainee généré"

clean:
	rm *.o
	rm $(EXE)