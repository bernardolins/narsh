CC=gcc

INC=inc
SRC=src
OBJ=obj
BIN=bin

TAILNAME=tail
TAILOBJS=$(OBJ)/tail.o

RMNAME=rm
RMOBJS=$(OBJ)/rm.o

clean:
	rm -rf $(OBJ) $(BIN)/*
	mkdir $(OBJ)

deps:
	mkdir -p $(OBJ)
	mkdir -p $(BIN)

tail: clean deps $(TAILOBJS)
	$(CC) -o $(BIN)/$(TAILNAME) $(TAILOBJS) -I$(INC)

rm: clean deps $(RMOBJS)
	$(CC) -o $(BIN)/$(RMNAME) $(RMOBJS) -I$(INC)

# build tail object
$(OBJ)/tail.o: $(SRC)/tail.c
	$(CC) -o $(OBJ)/tail.o -c $(SRC)/tail.c -I$(INC)

# build rm object
$(OBJ)/rm.o: $(SRC)/rm.c
	$(CC) -o $(OBJ)/rm.o -c $(SRC)/rm.c -I$(INC)
