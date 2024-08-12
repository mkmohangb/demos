#include <threads.h>
#include <stdio.h>
#include <stdatomic.h>

atomic_int cnt;

int mythread(void* thr_data) {
	for (int n=0; n<1000000000; ++n) {
		++cnt;
	}
	return 0;
}

int main(void) {
	thrd_t thr[10];
	for (int n=0; n<10; ++n)
		thrd_create(&thr[n], mythread, NULL);
	for (int n=0;n<10; ++n)
		thrd_join(thr[n], NULL);
	printf("count is %d\n", cnt);
}
