BINS = O0 O2 O2nat

.PHONY : all
all: $(BINS)

.PHONY : clean
clean :
	rm -f $(BINS)

O0 : locality.c
	gcc -o $@ $< -O0 -march=x86-64

O2 : locality.c
	gcc -o $@ $< -O2 -march=x86-64

O2nat : locality.c
	gcc -o $@ $< -O2 -march=native

bench : all
	@echo
	@echo -n "O0:    "
	@./O0
	@echo -n "O2:    "
	@./O2
	@echo -n "O2nat: "
	@./O2nat
