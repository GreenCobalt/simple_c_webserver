CC=gcc
CFLAGS=-I. -O3
LDFLAGS=-lconfuse -lmagic

IDIR = include
ODIR = obj

_DEPS = server.h str.h def.h file.h http_error.h date.h
_OBJS = httpd.o server.o str.o def.o file.o http_error.o date.o

DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))
OBJS = $(patsubst %,$(ODIR)/%,$(_OBJS))

obj/%.o: src/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

server: $(OBJS)
	$(CC) -o server $(OBJS) -I. $(LDFLAGS)

.PHONY: clean
clean:
	rm -rf $(ODIR)/*.o server a.out