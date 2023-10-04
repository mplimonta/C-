
BISON = bison

FLEX = flex

CC = gcc

OBJS = cmc.tab.o lex.yy.o util.o symtab.o analyze.o  cgen.o main.o

cminus_files := $(wildcard *.cminus)
CminusComp = "./CminusComp"

all: Compilador clean Exec

Exec: $(cminus_files)
	@echo "10"
	for file in $(cminus_files); do \
		$(CminusComp) $$file; \
	done
Compilador: $(OBJS)
	@echo "8"
	$(CC) $(OBJS) -lfl -o CminusComp

main.o: main.c globals.h util.h scan.h cgen.o
	@echo "7"
	$(CC) -c main.c

util.o:
	@echo "3"
	$(CC) -c util.c

cmc.tab.o: cmc.y globals.h
	@echo "1"
	bison -d cmc.y
	$(CC) -c cmc.tab.c

lex.yy.o: cmc.l scan.h util.h globals.h
	@echo "2"
	flex cmc.l
	$(CC) -c lex.yy.c
  
analyze.o: symtab.o symtab.h globals.h analyze.h
	@echo "5"
	$(CC) -c analyze.c

symbtab.o: util.o symtab.h 
	@echo "4"
	$(CC) -c symtab.c
	
cgen.o : analyze.o
	@echo "6"
	$(CC) -c cgen.c

clean:
	@echo "9"
	-rm -f $(OBJS)
	-rm -f cmc.tab.c
	-rm -f cmc.tab.h
	-rm -f lex.yy.c
	-rm -f $(OBJS)
	find . -name "*.quad" -type f -delete
	find . -name "*.smbtbl" -type f -delete