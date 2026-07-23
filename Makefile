FLAGS = -Wall -g
SRC = $(wildcard src/*.c)

./bin/test: $(SRC) inc/kv.h
	gcc -o $@ -I./inc $^ $(FLAGS)


clean:
	rm ./bin/test