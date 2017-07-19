#compile it
gen: $(wildcard srcs/*.c) $(wildcard include/*.h)
	g++ $< -o $@ -Iinclude/ -pedantic
