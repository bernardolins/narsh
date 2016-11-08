CC=gcc

INC=inc
SRC=src
OBJ=obj
BIN=bin

TAILNAME=tail
TAILOBJS=$(OBJ)/tail.o

clean:
	rm -rf $(OBJ) $(BIN)/*
	mkdir $(OBJ)

deps:
	mkdir -p $(OBJ)
	mkdir -p $(BIN)

tail: clean deps $(TAILOBJS)
	$(CC) -o $(BIN)/$(TAILNAME) $(TAILOBJS) -I$(INC)


# build tail object
$(OBJ)/tail.o: $(SRC)/tail.c
	$(CC) -o $(OBJ)/tail.o -c $(SRC)/tail.c -I$(INC)

