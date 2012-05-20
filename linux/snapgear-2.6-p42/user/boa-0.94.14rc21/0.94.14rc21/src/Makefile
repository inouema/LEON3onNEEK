# $Id: Makefile.in,v 1.59.2.15 2005/02/22 03:02:40 jnelson Exp $

.SUFFIXES:
.SUFFIXES: .o .c
.PHONY: clean mrclean distclean all dist depend

# The following gcc warning switches are too noisy to be useful checking
# Boa for lint:
#  -Wtraditional -Wconversion -Wredundant-decls -Wunreachable-code
# The following gcc warning switches should generate no warnings:
GCC_FLAGS = -Wstrict-prototypes -Wpointer-arith -Wcast-align -Wcast-qual \
  -Wshadow -Waggregate-return -Wmissing-prototypes -Wnested-externs \
  -Wall -W -Wno-unused -Winline -Wwrite-strings -Wundef -pedantic

srcdir = .
VPATH = ./../extras
LDFLAGS = -Wl,-Bdynamic -mcpu=v8 -g
LIBS = 
CFLAGS = -mcpu=v8 -idirafter /home/daniel/reps/SNAPGEAR_REP/snapgear/linux-2.6.18.1/include -idirafter /home/daniel/reps/SNAPGEAR_REP/snapgear   -pipe -Wall
CPPFLAGS =  -I. -I.
DEPEND = .depend

CC = sparc-linux-gcc 
CPP = sparc-linux-gcc -E

SOURCES = alias.c boa.c buffer.c cgi.c cgi_header.c config.c escape.c \
	get.c hash.c ip.c log.c mmap_cache.c pipe.c queue.c range.c \
	read.c request.c response.c signals.c util.c sublog.c \
	select.c 

OBJS = $(SOURCES:.c=.o) timestamp.o 

all:	boa boa_indexer

boa:	$(OBJS) 
	$(CC) -o $@ $^ $(LDFLAGS) $(LIBS)
	
boa_indexer:	index_dir.o escape.o   
	$(CC) -o $@ $^ $(LDFLAGS) $(LIBS)

clean:
	rm -f $(OBJS) boa core *~ boa_indexer index_dir.o
	rm -f    poll.o select.o access.o
	
distclean:	mrclean

mrclean:	clean
	rm -f config.status config.cache config.h Makefile config.log

# timestamp

timestamp.o:	$(SOURCES)

# depend stuff
depend: $(SOURCES)
	$(CPP) $(CPPFLAGS) -MM $^ select.c poll.c access.c > $(DEPEND)
        
-include $(DEPEND)


# tags
tags:	$(SOURCES)
	ctags -o tags $^ *.h

# object dump
boa.objdump:    boa
	objdump --disassemble-all --source boa > $@

