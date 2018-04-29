IDIR=../include
ODIR=obj
LDIR=lib
OLDIR=$(ODIR)/lib

CC=gcc
CFLAGS =-Wall -O3 -Wextra -pedantic -std=c11 -g `pkg-config --cflags libxml-2.0` `pkg-config --cflags glib-2.0` -I$(IDIR) -lm

DEPS=$(IDIR)/$(wildcard *.h)
SOURCES=$(wildcard *.c)
MY_LIBS=$(wildcard $(LDIR)/*.c)
SOURCES_OBJ=$(patsubst %.c,$(ODIR)/%.o,$(SOURCES))
MY_LIBS_OBJ=$(foreach o, $(patsubst %.c,%.o,$(MY_LIBS)), $(ODIR)/$o)
LIBS = `pkg-config --libs libxml-2.0` `pkg-config --libs glib-2.0`

print-% : ; @echo $* = $($*)

$(ODIR)/%.o : %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

program: $(SOURCES_OBJ) $(MY_LIBS_OBJ)
	$(CC) $(wildcard $(ODIR)/*.o)  $(wildcard $(OLDIR)/*.o) -o program $(LIBS) $(CFLAGS)

clean:
	rm obj/*.o
	rm obj/lib/*.o
	rm program

clean_doc:
	rm -rf ../doc/html ../doc/latex

clean_relatorio:
	rm ../Relatorio/relatorio.aux ../Relatorio/relatorio.log ../Relatorio/relatorio.toc ../Relatorio/relatorio.pdf 

doc:
	doxygen Doxyfile.bak

relatorio:
	pdflatex ../Relatorio/relatorio.tex -output-directory ../Relatorio/relatorio.tex
