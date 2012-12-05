GHCDIR := /usr/local/ghc7.6.1/
GHC := ${GHCDIR}/bin/ghc
PROG := FibHs
HSLIB := Fib
CMAIN := CMain
LINK_OPT := -fno-stack-protector -Wl,--hash-size=31 -Wl,--reduce-memory-overheads
OBJ_RTS_HARD := rts/Apply.o rts/AutoApply.o rts/BlockAlloc.o rts/Capability.o rts/Compact.o rts/Evac.o rts/Exception.o rts/Hash.o rts/GC.o rts/GCAux.o rts/GCUtils.o rts/Globals.o rts/HeapStackCheck.o rts/MBlock.o rts/MarkWeak.o rts/Messages.o rts/OSMem.o rts/PrimOps.o rts/RaiseAsync.o rts/RtsAPI.o rts/RtsFlags.o rts/RtsUtils.o rts/STM.o rts/Scav.o rts/Schedule.o rts/RtsStartupSlim.o rts/Stable.o rts/StgCRun.o rts/StgMiscClosures.o rts/StgStartup.o rts/StgStdThunks.o rts/Storage.o rts/Sweep.o rts/Threads.o rts/Updates.o rts/WSDeque.o rts/Weak.o
OBJ_RTS := ${OBJ_RTS_HARD} rts/Adjustor.o rts/ClosureFlags.o rts/HsFFI.o rts/Inlines.o rts/Task.o
# Should copy by hand.
OBJ_BASE := libHSbase-4.6.0.0.a libHSghc-prim-0.3.0.0.a

all: ${PROG}
${PROG}: ${CMAIN}.o ${HSLIB}.o ${OBJ_RTS} ${OBJ_BASE}
	gcc ${LINK_OPT} -o $@ $^

${CMAIN}.o: ${CMAIN}.c
	gcc -O2 -I${GHCDIR}/lib/ghc-7.6.1/include -c $<

${HSLIB}.o: ${HSLIB}.hs
	${GHC} -O2 -c $<

${OBJ_RTS}: ${GHCDIR}/lib/ghc-7.6.1/libHSrts.a
	mkdir -p rts
	cd rts/ && ar x $< $@

${HSLIB}.cmm: ${HSLIB}.hs
	${GHC} -O2 -ddump-cmm -c $< > $@

test: all
	./${PROG}

clean:
	rm -f ${PROG} *.o *.hi *_stub.h *~ *.cmm
	rm -rf rts

.PHONY: test clean
