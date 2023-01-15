
BISON = bison

FLEX = flex

CC = gcc

OBJS = cmc.tab.o lex.yy.o main.o util.o

Compilador:$(OBJS)
	$(CC) $(OBJS) -ly -lfl -o CminusComp

main.o: main.c globals.h util.h scan.h
	$(CC) -c main.c

util.o: util.c util.h globals.h
	$(CC) -c util.c

cmc.tab.o: cmc.y globals.h
	bison -d cmc.y
	$(CC) -c cmc.tab.c

lex.yy.o: cmc.l scan.h util.h globals.h
	flex cmc.l
	$(CC) -c lex.yy.c
  
analyze.o: symtab.h globals.h analyze.h
	$(CC) -c analyze.c

symbtab.o: symtab.h
	$(CC) -c symtab.c


clean:
	-rm -f CminusComp
	-rm -f $(OBJS)
	-rm -f cmc.tab.c
	-rm -f cmc.tab.h
	-rm -f lex.yy.c
	-rm -f $(OBJS)

