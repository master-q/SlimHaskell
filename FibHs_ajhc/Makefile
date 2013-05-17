JHC := ajhc
PROG := FibHs
CSRCS := CMain.c tmp/rts/profile.c tmp/rts/rts_support.c tmp/rts/gc_none.c tmp/rts/jhc_rts.c tmp/lib/lib_cbits.c tmp/rts/gc_jgc.c tmp/rts/stableptr.c
CFLAGS := '-std=gnu99' -D_GNU_SOURCE '-falign-functions=4' -ffast-math -Wextra -Wall -Wno-unused-parameter -fno-strict-aliasing -DNDEBUG -O3 '-D_JHC_GC=_JHC_GC_JGC' -D_JHC_STANDALONE=0

all: ${PROG}
${PROG}: hs_main.c
	gcc -Itmp/cbits -Itmp ${CFLAGS} -o $@ ${CSRCS} $<

hs_main.c: Main.hs Fib.hs
	${JHC} -fffi -fno-standalone --tdir=tmp -C -o $@ $<

clean:
	rm -f ${PROG} *~ hs_main.c
	rm -rf tmp

.PHONY: clean
