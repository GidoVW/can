INCL_PATH=inc/

all: src/cansv.c src/cancl.c 
	gcc -I$(INCL_PATH) src/cansv.c -o cansv -l:liblogit.a
	gcc -I$(INCL_PATH) src/cancl.c -o cancl -l:liblogit.a


