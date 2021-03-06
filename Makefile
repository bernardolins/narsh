CC=gcc
AR=ar

INC=inc
SRC=src
OBJ=obj
BIN=bin

LIB=lib

LIBINC=$(LIB)
LIBSRC=$(LIB)
LIBOBJ=$(LIB)/obj

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
LIBOBJS=$(LIBOBJ)/libnarsh.o

LIBFILES=$(LIBSRC)/narsh.c

all: lib tail head rm ls

clean:
	rm -rf $(OBJ) $(BIN)/*

deps:
	mkdir -p $(OBJ)
	mkdir -p $(BIN)

libdeps:
	rm -f $(LIB)/$(LIBNAME)
	mkdir -p $(LIBOBJ)

lib: libdeps
	$(CC) -c $(LIBFILES) -o $(LIBOBJS) -I$(LIBINC)
	$(AR) rcs $(LIB)/$(LIBNAME) $(LIBOBJS)

tail: clean deps lib $(TAILOBJS)
	$(CC) -o $(BIN)/$(TAILNAME) $(TAILOBJS) -L$(LIB) -lnarsh -I$(INC)

head: clean deps $(HEADOBJS)
	$(CC) -o $(BIN)/$(HEADNAME) $(HEADOBJS) -L$(LIB) -lnarsh -I$(INC)

rm: clean deps $(RMOBJS)
	$(CC) -o $(BIN)/$(RMNAME) $(RMOBJS) -L$(LIB) -lnarsh -I$(INC)

ls: clean deps $(LSOBJS)
	$(CC) -o $(BIN)/$(LSNAME) $(LSOBJS) -L$(LIB) -lnarsh -I$(INC)

man: clean deps $(MANOBJS)
	$(CC) -o $(BIN)/$(MANNAME) $(MANOBJS) -L$(LIB) -lnarsh -I$(INC)

# build tail object
$(OBJ)/tail.o: $(SRC)/tail.c
	$(CC) -o $(OBJ)/tail.o -c $(SRC)/tail.c -I$(INC) -I$(LIBINC)

# build head object
$(OBJ)/head.o: $(SRC)/head.c
	$(CC) -o $(OBJ)/head.o -c $(SRC)/head.c -I$(INC) -I$(LIBINC)
# build rm object
$(OBJ)/rm.o: $(SRC)/rm.c
	$(CC) -o $(OBJ)/rm.o -c $(SRC)/rm.c -I$(INC) -I$(LIBINC)

# build ls object
$(OBJ)/ls.o: $(SRC)/ls.c
	$(CC) -o $(OBJ)/ls.o -c $(SRC)/ls.c -I$(INC) -I$(LIBINC)

# build man object
$(OBJ)/man.o: $(SRC)/man.c
	$(CC) -o $(OBJ)/man.o -c $(SRC)/man.c -I$(INC) -I$(LIBINC)
