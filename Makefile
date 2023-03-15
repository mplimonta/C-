
BISON = bison

FLEX = flex

CC = gcc

OBJS = cmc.tab.o lex.yy.o main.o util.o

all: Compilador clean

Compilador:$(OBJS)
	@echo "5"
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
  
analyze.o: symtab.h globals.h analyze.h
	@echo "6"
	$(CC) -c analyze.c

symbtab.o: symtab.h
	@echo "7"
	$(CC) -c symtab.c

clean:
	-rm -f $(OBJS)
	-rm -f cmc.tab.c
	-rm -f cmc.tab.h
	-rm -f lex.yy.c
	-rm -f $(OBJS)