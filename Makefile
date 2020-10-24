SRC = main.c hashtable.c node.c
OBJ = main.o hashtable.o node.o
PROG = wordfreak

$(PROG): $(OBJ)
	gcc $(OBJ) -o $(PROG)

$(OBJ): $(SRC)