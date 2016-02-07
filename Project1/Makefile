CC = gcc
CFLAGS = -Wall -Werror -std=c99 -pedantic -g
OUTPUT = ./p1
EXEOBJ = ./main.o
LIBOBJ = ./alerts.o
LIBTOKEN = ./libtoken.a
default: $(OUTPUT)
all: default clean

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBTOKEN): $(LIBOBJ)
	ar rc $(LIBTOKEN) $(LIBOBJ)

$(OUTPUT): $(EXEOBJ) $(LIBTOKEN)
	$(CC) $(CFLAGS) $(EXEOBJ) $(LIBTOKEN) alerts.h -o $@

clean:
	$(RM) *.o core
	$(RM) $(LIBTOKEN)

rebuild: clean $(OUTPUT)
