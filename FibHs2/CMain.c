#include <stdio.h>
#include "HsFFI.h"
#ifdef __GLASGOW_HASKELL__
#include "Fib_stub.h"
#endif

int main(int argc, char *argv[])
{
	int i;

	hs_init_slim(&argc, &argv);
	for (i = 0; i < 30; i++) {
		printf("%d\n", fib(i));
	}
/*	hs_exit(); */
	return 0;
}

/* dummy */
void stg_exit(int n) {}
void hs_exit(void) {}
void shutdownHaskell(void) {}
void shutdownHaskellAndExit(int n) {}
void shutdownHaskellAndSignal(int sig) {}
void initTimer(void) {}
void startTimer(void) {}
void stopTimer(void) {}
int performHeapProfile;
void stopHeapProfTimer(void) {}
void startHeapProfTimer(void) {}
