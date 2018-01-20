CFLAGS = `sdl2-config --cflags` -O2 -Wall -Wextra -pedantic -ansi -Wfloat-equal
INCS = neillsdl2.h telet.h sixel.h testing.h

TARGET = teletext
SOURCES =  $(TARGET).c neillsdl2.c sixel.c testing.c telet.c
MAIN = teletext.c
LIBS =  `sdl2-config --libs` -lm
CC = gcc

EXTINCS = extension/extension.h
EXTSOURCES = extension/extension.c
ETARGET = ext

all: $(TARGET)

$(TARGET): $(SOURCES) $(INCS)
	$(CC) $(SOURCES) -o $(TARGET) $(CFLAGS) $(LIBS)

ext: $(EXTSOURCES) $(SOURCES) $(EXTINCS) $(INCS)
		$(CC) -D EXTON $(EXTSOURCES) $(SOURCES) -o $(ETARGET) $(CFLAGS) $(LIBS)

clean:
	rm -f $(TARGET)

run: all
	./$(TARGET)
