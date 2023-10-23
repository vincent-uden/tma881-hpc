CFLAGS = -O3 -lm -std=c11 -Wall -Wextra -Wshadow

.PHONY : clean
clean :
	rm -rf ./build

naive : ./src/ppm.c ./src/cli.c ./src/naive.c
	mkdir -p build
	gcc -o ./build/$@ $^ $(CFLAGS)
