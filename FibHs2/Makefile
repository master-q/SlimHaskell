GHCDIR := /usr/local/ghc7.6.1/
GHC := ${GHCDIR}/bin/ghc
PROG := FibHs
HSLIB := Fib
CMAIN := CMain
UNSYM_NEED := -u base_GHCziConcziIO_ensureIOManagerIsRunning_closure
LINK_DIR := -L${GHCDIR}/lib/ghc-7.6.1/base-4.6.0.0 -L${GHCDIR}/lib/ghc-7.6.1/integer-gmp-0.5.0.0 -L${GHCDIR}/lib/ghc-7.6.1/ghc-prim-0.3.0.0 -L${GHCDIR}/lib/ghc-7.6.1
LINK_LIB_HS := -lHSbase-4.6.0.0 -lHSinteger-gmp-0.5.0.0 -lHSghc-prim-0.3.0.0
LINK_LIB_C := -lm -lrt -lgmp
LINK_OPT := -fno-stack-protector -Wl,--hash-size=31 -Wl,--reduce-memory-overheads
OBJ_RTS_HARD := rts/Apply.o rts/AutoApply.o rts/BlockAlloc.o rts/Capability.o rts/Compact.o rts/Evac.o rts/Exception.o rts/Hash.o rts/GC.o rts/GCAux.o rts/GCUtils.o rts/Globals.o rts/HeapStackCheck.o rts/MBlock.o rts/MarkWeak.o rts/Messages.o rts/OSMem.o rts/PrimOps.o rts/RaiseAsync.o rts/RtsAPI.o rts/RtsFlags.o rts/RtsUtils.o rts/STM.o rts/Scav.o rts/Schedule.o rts/RtsStartupSlim.o rts/Stable.o rts/StgCRun.o rts/StgMiscClosures.o rts/StgStartup.o rts/StgStdThunks.o rts/Storage.o rts/Sweep.o rts/Threads.o rts/Updates.o rts/WSDeque.o rts/Weak.o
OBJ_RTS := ${OBJ_RTS_HARD} rts/Adjustor.o rts/ClosureFlags.o rts/HsFFI.o rts/Inlines.o rts/Task.o rts/closures.o

all: ${PROG}
${PROG}: ${CMAIN}.o ${HSLIB}.o ${OBJ_RTS}
	gcc ${LINK_OPT} -o $@ $^ ${LINK_DIR} ${LINK_LIB_HS} ${LINK_LIB_C} ${UNSYM_NEED}

${CMAIN}.o: ${CMAIN}.c
	gcc -O2 -I/usr/local/ghc7.6.1/lib/ghc-7.6.1/include -c $<

${HSLIB}.o: ${HSLIB}.hs
	${GHC} -O2 -c $<

${OBJ_RTS}: ${GHCDIR}/lib/ghc-7.6.1/libHSrts.a
	mkdir -p rts
	cd rts/ && ar x $<

${HSLIB}.cmm: ${HSLIB}.hs
	${GHC} -O2 -ddump-cmm -c $< > $@

clean:
	rm -f ${PROG} *.o *.hi *_stub.h *~ *.cmm
	rm -rf rts

.PHONY: clean
