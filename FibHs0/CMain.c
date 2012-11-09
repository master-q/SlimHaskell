#include <stdio.h>
#include "HsFFI.h"

#ifdef __GLASGOW_HASKELL__
#include "Fib_stub.h"
#endif

int main(int argc, char *argv[])
{
	int i;

	hs_init(&argc, &argv);

	for (i = 0; i < 30; i++) {
		printf("%d\n", fib(i));
	}

	hs_exit();
	return 0;
}
