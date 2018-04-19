LD_LIB_PATH=/home/gwijkvan/private/can/lib/
LFLAGS=-L$(LD_LIB_PATH)

all: src/cansv.c src/cancl.c loglib
	gcc -Iinc $(LFLAGS) src/cansv.c -o cansv -llog
	gcc -Iinc $(LFLAGS) src/cancl.c -o cancl -llog

loglib: lib/src/log_it.c
	gcc -c -Wall -Werror -fPIC lib/src/log_it.c -o lib/src/log_it.o
	gcc -shared -o lib/liblog.so lib/src/log_it.o
