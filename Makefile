
BISON = bison

FLEX = flex

CC = gcc

OBJS = cmc.tab.o lex.yy.o main.o util.o analyze.o symtab.o cgen.o

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
  
analyze.o: symtab.o symtab.h globals.h analyze.h 
	@echo "6"
	$(CC) -c analyze.c

symbtab.o: symtab.h
	@echo "5"
	$(CC) -c symtab.c
	
cgen.o :
	@echo "7"
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