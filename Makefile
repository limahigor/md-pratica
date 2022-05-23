all:
	mkdir src
	mkdir bin
	mkdir build
	gcc -o build/painel.o src/painel.c -c
	gcc -o build/comb_linear.o src/comb_linear.c -c
	gcc -o build/fatora_module.o src/fatora_module.c -c
	gcc -o build/md_module.o src/md_module.c -c
	mv *.o build/
	gcc -O2 -s -o bin/md-pratica build/painel.o build/comb_linear.o build/fatora_module.o build/md_module.o  -lm

windows:
	mkdir src
	mkdir bin
	mkdir build
	gcc -o build/painel.o src/painel.c -c
	gcc -o build/comb_linear.o src/comb_linear.c -c
	gcc -o build/fatora_module.o src/fatora_module.c -c
	gcc -o build/md_module.o src/md_module.c -c
	mv *.o build/
	gcc -O2 -s -o bin/md-pratica.exe build/painel.o build/comb_linear.o build/fatora_module.o build/md_module.o  -lm

clean:
	rm bin/md-pratica
