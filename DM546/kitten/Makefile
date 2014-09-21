#################################################################################################################
# VARIABLES #####################################################################################################
#################################################################################################################

CC = gcc

CFLAGS = -std=c99 -Wall -Wextra -pedantic -m32

OBJECTS = lex.yy.o y.tab.o tree.o pretty.o memory.o symbol.o dumpsymbol.o traversal.o codegen.o regalloc.o main.o

HEADERS = tree.h pretty.h memory.h symbol.h dumpsymbol.h traversal.h codegen.h regalloc.h

SOURCES = tree.c pretty.c memory.c symbol.c dumpsymbol.c traversal.c codegen.c regalloc.c main.c

MYFILES = $(HEADERS) $(SOURCES) kitten.y kitten.l

#################################################################################################################
# RULES #########################################################################################################
#################################################################################################################

main:             $(OBJECTS) $(HEADERS)
	          $(CC) $(OBJECTS) -o kitten -lfl

y.tab.c y.tab.h:  kitten.y
	          bison -y -d kitten.y

lex.yy.c:         kitten.l y.tab.h 
	          flex kitten.l

clean:            # delete executable file and all object files
	          @rm -f kitten $(OBJECTS)

runtests:         # test the compiler
	          @for f in test/*.miaow; \
	          do \
	            echo "$$f:"; \
	            b=`basename $$f .miaow`; \
	            ./kitten < $$f > test/$$b.s; \
	            [ ! -s test/$$b.s ] || gcc test/$$b.s -o test/$$b; \
	            [ ! -s test/$$b ] || ./test/$$b; \
	          done
	          @for f in test/bachelor/*.miaow; \
	          do \
	            echo "$$f:"; \
	            b=`basename $$f .miaow`; \
	            ./kitten < $$f > test/bachelor/$$b.s; \
	            [ ! -s test/bachelor/$$b.s ] || gcc test/bachelor/$$b.s -o test/bachelor/$$b; \
	            [ ! -s test/bachelor/$$b ] || ./test/bachelor/$$b; \
	          done

longlines:        # print line numbers of program lines longer than 79 characters
	          @for f in $(MYFILES); \
	          do \
	            awk 'length($0) > 79 { print "Linje", NR, "i", FILENAME }' $$f; \
	          done

countlines:       # count the number of program lines in each file
	          @for f in $(MYFILES); \
	          do \
	            awk 'END { print "Antallet af linjer i", FILENAME, "er", NR }' $$f; \
	          done

###################################################################################################################
