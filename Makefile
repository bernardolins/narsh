CC=gcc
AR=ar

INC=inc
SRC=src
OBJ=obj
BIN=bin

LIB=lib

LIBINC=$(LIB)
LIBSRC=$(LIB)
LIBOBJ=$(LIB)

TAILNAME=tail
TAILOBJS=$(OBJ)/tail.o

HEADNAME=head
HEADOBJS=$(OBJ)/head.o

RMNAME=rm
RMOBJS=$(OBJ)/rm.o

LSNAME=ls
LSOBJS=$(OBJ)/ls.o

MANNAME=man
MANOBJS=$(OBJ)/man.o

LIBNAME=libnarsh.a
LIBOBJS=$(OBJ)/lib/libnarsh.o

LIBFILES=$(LIBSRC)/narsh.c

LIBARGS=-static -L$(LIB) -lnarsh -I$(LIBINC)

all: lib tail head rm ls

clean:
	rm -rf $(OBJ) $(BIN)/*
	mkdir $(OBJ)

deps:
	mkdir -p $(OBJ)
	mkdir -p $(BIN)

libdeps:
	rm -f $(LIB)/$(LIBNAME)
	mkdir -p $(LIBOBJ)

lib: libdeps
	$(CC) -c $(LIBFILES) -o $(LIBOBJS) -I$(LIBINC)
	$(AR) rcs $(LIB)/$(LIBNAME) $(LIBOBJS)

tail: clean deps $(TAILOBJS)
	$(CC) -o $(BIN)/$(TAILNAME) $(TAILOBJS) -L$(LIB) -lnarsh -I$(INC)

head: clean deps $(HEADOBJS)
	$(CC) -o $(BIN)/$(HEADNAME) $(HEADOBJS) -I$(INC)

rm: clean deps $(RMOBJS)
	$(CC) -o $(BIN)/$(RMNAME) $(RMOBJS) -I$(INC)

ls: clean deps $(LSOBJS)
	$(CC) -o $(BIN)/$(LSNAME) $(LSOBJS) -I$(INC)

man: clean deps $(MANOBJS)
	$(CC) -o $(BIN)/$(MANNAME) $(MANOBJS) -I$(INC)

# build tail object
$(OBJ)/tail.o: $(SRC)/tail.c
	$(CC) -o $(OBJ)/tail.o -c $(SRC)/tail.c -I$(INC)

# build head object
$(OBJ)/head.o: $(SRC)/head.c
	$(CC) -o $(OBJ)/head.o -c $(SRC)/head.c -I$(INC)

# build rm object
$(OBJ)/rm.o: $(SRC)/rm.c
	$(CC) -o $(OBJ)/rm.o -c $(SRC)/rm.c -I$(INC)

# build ls object
$(OBJ)/ls.o: $(SRC)/ls.c
	$(CC) -o $(OBJ)/ls.o -c $(SRC)/ls.c -I$(INC)

# build man object
$(OBJ)/man.o: $(SRC)/man.c
	$(CC) -o $(OBJ)/man.o -c $(SRC)/man.c -I$(INC)
