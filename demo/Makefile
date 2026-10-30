CC= gcc
CFLAGS= -Wall -Wextra -pedantic -std=c99
LDFLAGS= -L../ -Wl,-rpath=../ -ltext -lSDL3 -lSDL3_ttf

EXEC= demo_text
DEMO_SRC= demo.c
LIBSO= ../libtext.so

run: $(EXEC)
	@./$(EXEC)

all: $(EXEC)

$(EXEC): $(LIBSO) $(DEMO_SRC)
	$(CC) $(CFLAGS) -o $@ $(DEMO_SRC) $(LDFLAGS)

clean:
	@rm -f $(EXEC)
