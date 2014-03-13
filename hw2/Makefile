CC=gcc
FLAGS=-I./src/
TARGETS=hw2ex
LIBS=-lm

main: $(TARGETS)


lib/%.o: src/%.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(TARGETS) lib/*.o

%:lib/hw2.o lib/%.o
	$(CC) -o $@ $^ $(LIBS)
