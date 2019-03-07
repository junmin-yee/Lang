##**************************************
## Makefile
##
## Build routine for lang compiler
##
## Author: Junmin Yee 
##
## Date: January 31, 2019
##

COPTS=-Wall -g -c  -O0 -std=c++11
OBJS=main.o \
	 langlex.o \
	 langparse.o \
	 cVisitor.o \
	 cSymbolTable.o \
	 symbolTable_t.o \
	 emit.o 

all: lang

clean:
	rm -f $(OBJS)
	rm -f langlex.c
	rm -f langparse.c
	rm -f langparse.h
	rm -f lang
	rm -f out
	rm -f langout.lst
	rm -f langout.sl
	rm -f langout.slb

.cpp.o:
	g++ $(COPTS) $? -o $@

.c.o:
	g++ $(COPTS) $? -o $@

main.o: main.cpp langparse.c langlex.c 
	g++ $(COPTS) main.cpp -o $@

langlex.o: langlex.c
	g++ $(COPTS) -Wno-sign-compare $? -o $@

langlex.c: lang.l langparse.c
	flex -o langlex.c lang.l

langparse.c: lang.y
	bison --defines=langparse.h lang.y -o langparse.c

lang: $(OBJS)
	g++ $(OBJS) -o lang

