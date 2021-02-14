CC = gcc
CFLAGS = -Wall -pedantic
OBJECTS = main.o inputsettings.o optionhandler.o processdata.o processstatus.o processstat.o processstatm.o buffer.o processcmdline.o prochandler.o outputprinter.o

537ps: $(OBJECTS)
	$(CC) $(CFLAGS) -o 537ps $(OBJECTS)

537ps.o: main.c inputsettings.h processoptions.h processdata.h prochandler.h outputprinter.h
	$(CC) $(CFLAGS) -c main.c

inputsettings.o: inputsettings.c inputsettings.h
	$(CC) $(CFLAGS) -c inputsettings.c

optionhandler.o: optionhandler.c optionhandler.h inputsettings.h
	$(CC) $(CFLAGS) -c optionhandler.c

processdata.o: processdata.c processdata.h
	$(CC) $(CFLAGS) -c processdata.c

processstatus.o: processstatus.c processstatus.h
	$(CC) $(CFLAGS) -c processstatus.c

processstat.o: processstat.c processstat.h
	$(CC) $(CFLAGS) -c processstat.c

processstatm.o: processstatm.c processstatm.h
	$(CC) $(CFLAGS) -c processstatm.c

buffer.o: buffer.c buffer.h
	$(CC) $(CFLAGS) -c buffer.c

processcmdline.o: processcmdline.c processcmdline.h buffer.h
	$(CC) $(CFLAGS) -c processcmdline.c

prochandler.o: prochandler.c prochandler.h processcmdline.h buffer.h processstatm.h processstat.h processstatus.h processdata.h
	$(CC) $(CFLAGS) -c prochandler.c

outputprinter.o: outputprinter.c outputprinter.h processdata.h inputsettings.h
	$(CC) $(CFLAGS) -c outputprinter.c

clean: 
	rm -f $(OBJECTS) 537ps
