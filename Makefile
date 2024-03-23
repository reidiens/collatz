BIN = collatz
SRC = $(BIN).c
FLAGS = -Wall -O2

$(BIN) : $(SRC)
	gcc $(FLAGS) $(SRC) -o $(BIN)
