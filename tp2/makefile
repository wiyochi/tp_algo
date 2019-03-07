OPT = -g -Wall -Wextra
LOG = @echo "\#MAKE"
EXE = pile-file

all: $(EXE)

$(EXE): test.c pile.o file.o
	gcc -o $(EXE) test.c pile.o file.o $(OPT)
	$(LOG) "Executable généré"

pile.o: pile.h pile.c
	gcc -o pile.o -c pile.c $(OPT)
	$(LOG) "lib pile généré"
	
file.o: file.h file.c
	gcc -o file.o -c file.c $(OPT)
	$(LOG) "lib file généré"

clean:
	rm *.o
	rm $(EXE)