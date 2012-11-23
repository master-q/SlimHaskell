GHC := /usr/local/ghc7.6.1/bin/ghc
PROG := FibHs
HSLIB := Fib
CMAIN := CMain
#UNSYM_ALL := -u ghczmprim_GHCziTypes_Izh_static_info -u ghczmprim_GHCziTypes_Czh_static_info -u ghczmprim_GHCziTypes_Fzh_static_info -u ghczmprim_GHCziTypes_Dzh_static_info -u base_GHCziPtr_Ptr_static_info -u ghczmprim_GHCziTypes_Wzh_static_info -u base_GHCziInt_I8zh_static_info -u base_GHCziInt_I16zh_static_info -u base_GHCziInt_I32zh_static_info -u base_GHCziInt_I64zh_static_info -u base_GHCziWord_W8zh_static_info -u base_GHCziWord_W16zh_static_info -u base_GHCziWord_W32zh_static_info -u base_GHCziWord_W64zh_static_info -u base_GHCziStable_StablePtr_static_info -u ghczmprim_GHCziTypes_Izh_con_info -u ghczmprim_GHCziTypes_Czh_con_info -u ghczmprim_GHCziTypes_Fzh_con_info -u ghczmprim_GHCziTypes_Dzh_con_info -u base_GHCziPtr_Ptr_con_info -u base_GHCziPtr_FunPtr_con_info -u base_GHCziStable_StablePtr_con_info -u ghczmprim_GHCziTypes_False_closure -u ghczmprim_GHCziTypes_True_closure -u base_GHCziPack_unpackCString_closure -u base_GHCziIOziException_stackOverflow_closure -u base_GHCziIOziException_heapOverflow_closure -u base_ControlziExceptionziBase_nonTermination_closure -u base_GHCziIOziException_blockedIndefinitelyOnMVar_closure -u base_GHCziIOziException_blockedIndefinitelyOnSTM_closure -u base_ControlziExceptionziBase_nestedAtomically_closure -u base_GHCziWeak_runFinalizzerBatch_closure -u base_GHCziTopHandler_flushStdHandles_closure -u base_GHCziTopHandler_runIO_closure -u base_GHCziTopHandler_runNonIO_closure -u base_GHCziConcziIO_ensureIOManagerIsRunning_closure -u base_GHCziConcziSync_runSparks_closure -u base_GHCziConcziSignal_runHandlers_closure
# /usr/local/ghc7.6.1/lib/ghc-7.6.1/libHSrts.a(RtsStartup.o): 関数 `hs_init_ghc' 内:
# RtsStartup.c:(.text+0x265): `base_GHCziConcziIO_ensureIOManagerIsRunning_closure' に対する定義されていない参照です
UNSYM_NEED := -u base_GHCziConcziIO_ensureIOManagerIsRunning_closure
LINK_DIR := -L/usr/local/ghc7.6.1/lib/ghc-7.6.1/base-4.6.0.0 -L/usr/local/ghc7.6.1/lib/ghc-7.6.1/integer-gmp-0.5.0.0 -L/usr/local/ghc7.6.1/lib/ghc-7.6.1/ghc-prim-0.3.0.0 -L/usr/local/ghc7.6.1/lib/ghc-7.6.1
LINK_LIB_HS := -lHSbase-4.6.0.0 -lHSinteger-gmp-0.5.0.0 -lHSghc-prim-0.3.0.0 -lHSrts
LINK_LIB_C := -lm -lrt -ldl -lgmp
LINK_OPT := -fno-stack-protector -Wl,--hash-size=31 -Wl,--reduce-memory-overheads

all: ${PROG}
${PROG}: ${CMAIN}.o ${HSLIB}.o
	gcc ${LINK_OPT} -o $@ $^ ${LINK_DIR} ${LINK_LIB_HS} ${LINK_LIB_C} ${UNSYM_NEED}

${CMAIN}.o: ${CMAIN}.c
	gcc -O2 -I/usr/local/ghc7.6.1/lib/ghc-7.6.1/include -c $<

${HSLIB}.o: ${HSLIB}.hs
	${GHC} -O2 -c $<

${HSLIB}.cmm: ${HSLIB}.hs
	${GHC} -O2 -ddump-cmm -c $< > $@

clean:
	rm -f ${PROG} *.o *.hi *_stub.h *~ *.cmm

.PHONY: clean
