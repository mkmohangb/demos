#include <stdio.h>
#include <stdlib.h>

int globalVar = 45;

void f() {
	int y = 5;
	printf(" in f(), location of stack var. y: %p\n", &y);
}

int main(int argc, char* argv[]) {
	printf("location of code is %p\n", main);
	printf("location of global var is %p\n", &globalVar);
	printf("location of heap var: %p\n", malloc(1000));
	int x = 3;
	printf("location of stack var: %p\n",&x);
	f();
	char c;
	scanf("%c", &c);
	return 0;
}
