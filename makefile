
# unix makefile for crashme program.

all: crashme pddet

# make CFLAGS=-Wall CC=gcc

crashme: crashme.o

crashme.o: crashme.c

pddet:	pddet.o

pddet.o: pddet.c

clean:
	-rm crashme pddet *.o core crashme.txt crashme.zip \
            crashme.tgz crashme_i386.zip *.plg *.ncb *.opt
	-rm -rf release debug

# create for dist for people without nroff

crashme.txt: crashme.man
	nroff -man crashme.man | col -bx > crashme.txt


DIST_FILES = crashme.man crashme.c crashme.html \
             crashme.vms-opt descrip.mms makefile \
             pddet.c crashme.txt crashme.dsw crashme.dsp pddet.dsp

crashme.zip: $(DIST_FILES)
	zip -D -j crashme.zip $(DIST_FILES)

crashme.tgz: $(DIST_FILES)
	tar cvf - $(DIST_FILES) | gzip -v > crashme.tgz

check:
	nsgmls -s crashme.html

dist: crashme.zip crashme.tgz crashme_i386.zip

CRASHME_I386=release/crashme.exe release/pddet.exe

crashme_i386.zip: $(DIST_FILES) $(CRASHME_I386)
	zip -D -j crashme_i386.zip $(DIST_FILES) $(CRASHME_I386)
