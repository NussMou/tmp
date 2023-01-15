# use on windows with msys2

CC       := gcc
CFLAGS   := -std=c99 -Wall -Wextra -pedantic

INCFLAGS := -Iallegro/include
LIB      := allegro/lib/liballegro_monolith-debug.dll.a
SRC      := $(wildcard src/*.c)

main: main.exe

main.exe: $(SRC)
	$(CC) $(CFLAGS) $(INCFLAGS) $^ $(LIB) -o main.exe

.PHONY: run
run:
	main.exe

.PHONY: clean
clean:
	if exist main.exe del main.exe
