
BISON = bison

FLEX = flex

CC = gcc

OBJS = cmc.tab.o lex.yy.o main.o util.o analyze.o symtab.o cgen.o code.o

all: Compilador clean

Compilador:$(OBJS)
	@echo "9"
	$(CC) $(OBJS) -lfl -o CminusComp

main.o: main.c globals.h util.h scan.h
	@echo "3"
	$(CC) -c main.c

util.o: util.c util.h globals.h
	@echo "4"
	$(CC) -c util.c

cmc.tab.o: cmc.y globals.h
	@echo "1"
	bison -d cmc.y
	$(CC) -c cmc.tab.c

lex.yy.o: cmc.l scan.h util.h globals.h
	@echo "2"
	flex cmc.l
	$(CC) -c lex.yy.c
  
analyze.o: symtab.h globals.h analyze.h symtab.o
	@echo "6"
	$(CC) -c analyze.c

symbtab.o: symtab.h
	@echo "5"
	$(CC) -c symtab.c
code.o : analyze.o 
	@echo "7"
	$(CC) -c code.c
	
cgen.o : code.o 
	@echo "8"
	$(CC) -c cgen.c

clean:
	-rm -f $(OBJS)
	-rm -f cmc.tab.c
	-rm -f cmc.tab.h
	-rm -f lex.yy.c
	-rm -f $(OBJS)