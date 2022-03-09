
# unix makefile for crashme program.

CCFLAGS=-DPRNG_MT $(CFLAGS) $(LDFLAGS) $(CPPFLAGS)
DIST_VERSION=2.8.5

all: crashme pddet

# make "CFLAGS=-Wall -DPRNG_MT -g"xo CC=gcc

crashme: crashme.o vnsq.o mt19937ar.o
	$(CC) $(CCFLAGS) -o crashme crashme.o vnsq.o mt19937ar.o

crashme.o: crashme.c
	$(CC) $(CCFLAGS) -c crashme.c

pddet:	pddet.o
	$(CC) $(CCFLAGS) -o pddet pddet.o

pddet.o: pddet.c
	$(CC) $(CCFLAGS) -c pddet.c

vnsq.o: vnsq.c
	$(CC) $(CCFLAGS) -c vnsq.c

mt19937ar.o: mt19937ar.c
	$(CC) $(CCFLAGS) -c mt19937ar.c

showdefs:
	$(CC) -dM -E - < /dev/null

clean:
	-rm crashme pddet *.o core crashme.zip \
            crashme.tgz crashme_i386.zip *.plg *.ncb *.opt
	-rm -rf release debug test-dist-tgz crashme-$(DIST_VERSION)

# create for dist for people without nroff

crashme.txt: crashme.man
	nroff -man crashme.man | col -bx > crashme.txt

pddet.txt: pddet.man
	nroff -man pddet.man | col -bx > pddet.txt


DIST_FILES = crashme.man crashme.c crashme.html \
             crashme.vms-opt descrip.mms makefile \
             pddet.c crashme.txt mt19937ar.h vnsq.h \
             vnsq.c mt19937ar.c pddet.man pddet.txt

# These files were in the distribution. 
# but they got lost and it isn't clear

# crashme.dsw crashme.dsp pddet.dsp

crashme.zip: $(DIST_FILES)
	zip -D -j crashme.zip $(DIST_FILES)

crashme.tgz: $(DIST_FILES)
	tar cvf - $(DIST_FILES) | gzip -v > crashme.tgz

check:
	#nsgmls -s crashme.html
	xmllint --noout crashme.html
	xmllint --noout downloads.html

TAGS_SRC=$(DIST_FILES) downloads.html

TAGS:	$(TAGS_SRC)
	etags $(TAGS_SRC)

dist: crashme.zip crashme.tgz 

dist-version: crashme-$(DIST_VERSION).tgz

crashme-$(DIST_VERSION).tgz: $(DIST_FILES)
	rm -rf crashme-$(DIST_VERSION)
	mkdir crashme-$(DIST_VERSION)
	cp -a $(DIST_FILES) crashme-$(DIST_VERSION)
	tar cvfz crashme-$(DIST_VERSION).tgz crashme-$(DIST_VERSION)

#crashme_i386.zip

CRASHME_I386=release/crashme.exe release/pddet.exe

crashme_i386.zip: $(DIST_FILES) $(CRASHME_I386)
	zip -D -j crashme_i386.zip $(DIST_FILES) $(CRASHME_I386)

test-dist: crashme.tgz
	(rm -rf test-dist-tgz;\
         mkdir test-dist-tgz;\
         cd test-dist-tgz;\
         tar xvfz ../crashme.tgz;\
         make all dist ptest1 ptest7)

test-dist-version: dist-version
	(cd crashme-$(DIST_VERSION);\
         make all dist ptest1 ptest7)

####

LOG_DIR=logs
# This directory is in Apple Mac Darwin.
# It will fill up with junk and probably really
# slow down things unless you turn off crash reporting
# for crashme.
LOG_DIR2=$$HOME/Library/Logs/DiagnosticReports

showcrashlogs:
	ls $(LOG_DIR)
	if [ -d $(LOG_DIR2) ]; then ls $(LOG_DIR2); fi




ptest1:
	./pddet

ptest2:
	./crashme 100 666 100

ptest3:
	./crashme 100 667 100

ptest4:
	mkdir -p $(LOG_DIR)
	sh -c "CRASHPRNG=RAND;export CRASHPRNG;CRASHLOG=$(LOG_DIR)/crashme-ptest4.log;export CRASHLOG;./crashme 100 666 100"


ptest5:
	./crashme -100 666 100

ptest6:
	@echo This tests alarm clock
	@echo you can also use control-C
	./crashme 0 666 3

ptest7:
	./crashme +256 666 10 3

ptest8:
	./crashme +256 666 10 3 4

ptest9:
	./crashme +256 666 100 3 4

ptest10:
	./crashme +4096 666 100 00:00:05 4

ptest11:
	./crashme +4096 666 250 00:03:00 4


# here are some tests taken from the BAT files done for windows.

test1: test1a test1b test1c

test1a:
	mkdir -p $(LOG_DIR)
	./pddet -examine 16
	./pddet -examine 16 > $(LOG_DIR)/pddet.log

test1b:
	mkdir -p $(LOG_DIR)
	sh -c "CRASHPRNG=MT;export CRASHPRNG;./crashme -64 666 5 -15 3" > $(LOG_DIR)/crashme-prng_mt.log
	sh -c "CRASHPRNG=RAND;export CRASHPRNG;./crashme -64 666 5 -15 3" > $(LOG_DIR)/crashme-prng_rand.log
	sh -c "CRASHPRNG=VNSQ;export CRASHPRNG;./crashme -64 666 5 -15 3" > $(LOG_DIR)/crashme-prng_vnsq.log

test1c: test1ca test1cb test1cc

test1ca:
	mkdir -p $(LOG_DIR)
	sh -c "CRASHPRNG=MT;export CRASHPRNG;CRASHLOG=$(LOG_DIR)/crashme-test1-mt.log;export CRASHLOG;./crashme 8192 666 100 00:00:30 3"

test1cb:
	mkdir -p $(LOG_DIR)
	sh -c "CRASHPRNG=RAND;export CRASHPRNG;CRASHLOG=$(LOG_DIR)/crashme-test1-rand.log;export CRASHLOG;./crashme 8192 666 100 00:00:30 3"


test1cc:
	mkdir -p $(LOG_DIR)
	sh -c "CRASHPRNG=VNSQ;export CRASHPRNG;CRASHLOG=$(LOG_DIR)/crashme-test1-vnsq.log;export CRASHLOG;./crashme 8192 666 100 00:00:30 3"

test-mt19937ar: mt19937ar_main
	./mt19937ar_main

mt19937ar_main: mt19937ar.c
	$(CC) $(CCFLAGS) -DMT19937AR_MAIN -o mt19937ar_main mt19937ar.c


### Use these targets to disable all crash report generation,
### otherwise large amounts of system resources could be consumed.

### These targets are for Apple Mac.

report-crash-stop:
	-launchctl unload -w /System/Library/LaunchAgents/com.apple.ReportCrash.plist
	-sudo launchctl unload -w /System/Library/LaunchDaemons/com.apple.ReportCrash.Root.plist

report-crash-start:
	-launchctl load -w /System/Library/LaunchAgents/com.apple.ReportCrash.plist
	-sudo launchctl load -w /System/Library/LaunchDaemons/com.apple.ReportCrash.Root.plist

### These commands work in some linux environments.
### An alternative would configuration of ~/.apport-ignore.xml or /etc/apport
### to tell apport to ignore crashme. But that still that leaves 
### /proc/sys/kernel/core_pattern
### sending a large number of crash dumps to apport.

APPORT_INIT=/etc/init.d/apport
CORE_PATTERN_API=/proc/sys/kernel/core_pattern
CORE_PATTERN=core-%p-%u-%g-%s-%t-%h-%e

apport-crash-stop:
	sudo $(APPORT_INIT) stop
	cat $(CORE_PATTERN_API)

apport-crash-start:
	sudo $(APPORT_INIT) start
	cat $(CORE_PATTERN_API)

set-core-pattern:
	sudo sh -c 'echo $(CORE_PATTERN) > $(CORE_PATTERN_API)'
	cat $(CORE_PATTERN_API)

show-core-limit:
	bash -c "ulimit -a"

#
ps:
	-ps -C crashme -f -H

pgrep:
	-pgrep -l crashme

pkill:
	-pkill crashme

