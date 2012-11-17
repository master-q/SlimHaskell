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
void awaitEvent(int wait) {}
int getDelayTarget (int us) {usleep(us); return 0;}
void heapCensus(double t) {}
void ffi_call(void *cif, void (*fn)(), void *rvalue, void **avalue) {}
void stat_startGC(void *cap, void *gct) {}
void stat_endGC(void *cap, void *gct, size_t alloc, size_t live,
    size_t copied, size_t slop, int gen, int par_n_threads,
    size_t par_max_copied, size_t par_tot_copied) {}
void stat_exit(int alloc) {}
int lockFile(int fd, long long int dev, long long int ino, int for_writing) {}
int unlockFile(int fd) {return 0;}
