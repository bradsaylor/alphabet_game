#taken from tutorial @ http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/

IDIR =../include
CC=gcc
CFLAGS=-g -I$(IDIR)

ODIR=../obj
LDIR=../lib

LIBS= 


_DEPS = log.h pick_letter.h evaluate.h graphics.h getch.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = game.o log.o pick_letter.o evaluate.o graphics.o getch.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) #-DENABLE_MEDIA

alphabet_game: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)
	rm -f TAGS
	find . -name "*.[ch]" -print | xargs etags -a

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
