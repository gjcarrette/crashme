
# unix makefile for crashme program.

CFLAGS=-DPRNG_MT

all: crashme pddet

# make CFLAGS=-Wall CC=gcc

crashme: crashme.o vnsq.o mt19937ar.o

crashme.o: crashme.c

pddet:	pddet.o

pddet.o: pddet.c

vnsq.o: vnsq.c

mt19937ar.o: mt19937ar.c

showdefs:
	$(CC) -dM -E - < /dev/null

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


# here are some tests taken from the BAT files done for windows.

LOG_DIR=logs

test1: test1a test1b test1c

test1a:
	mkdir -p $(LOG_DIR)
	./pddet -examine 16
	./pddet -examine 16 > $(LOG_DIR)/pddet.log

test1b:
	sh -c "CRASHPRNG=MT;export CRASHPRNG;./crashme -64 666 5 -15 3" > $(LOG_DIR)/crashme-prng_mt.log
	sh -c "CRASHPRNG=RAND;export CRASHPRNG;./crashme -64 666 5 -15 3" > $(LOG_DIR)/crashme-prng_rand.log
	sh -c "CRASHPRNG=VNSQ;export CRASHPRNG;./crashme -64 666 5 -15 3" > $(LOG_DIR)/crashme-prng_vnsq.log

#test1c: test1ca test1cb test1cc

test1c:
	@echo the run until elapsed time mechanism is broken

test1ca:
	sh -c "CRASHPRNG=MT;export CRASHPRNG;CRASHLOG=$(LOG_DIR)/crashme-test1-mt.log;export CRASHLOG;./crashme 8192 666 100 00:00:30 3"

test1cb:
	sh -c "CRASHPRNG=RAND;export CRASHPRNG;CRASHLOG=$(LOG_DIR)/crashme-test1-rand.log;export CRASHLOG;./crashme 8192 666 100 00:00:30 3"


test1cc:
	sh -c "CRASHPRNG=VNSQ;export CRASHPRNG;CRASHLOG=$(LOG_DIR)/crashme-test1-vnsq.log;export CRASHLOG;./crashme 8192 666 100 00:00:30 3"

