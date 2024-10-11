all: prob.c
	as -o gadgets.o gadgets.asm
	gcc -no-pie -fno-stack-protector -z norelro -o output_binary prob.c gadgets.o -o prob
	rm -rf gadgets.o
clean:
	rm -rf prob 
