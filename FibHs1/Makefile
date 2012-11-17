GHC := /usr/local/ghc7.6.1/bin/ghc
PROG := FibHs
HSLIB := Fib
CMAIN := CMain

all: ${PROG}
${PROG}: ${CMAIN}.o ${HSLIB}.o
	${GHC} -O2 -no-hs-main $^ -o ${PROG}

${CMAIN}.o: ${CMAIN}.c
	gcc -O2 -I/usr/lib/ghc/include -c $<

${HSLIB}.o: ${HSLIB}.hs
	${GHC} -O2 -c $<

${HSLIB}.cmm: ${HSLIB}.hs
	${GHC} -O2 -ddump-cmm -c $< > $@

clean:
	rm -f ${PROG} *.o *.hi *_stub.h *~ *.cmm

.PHONY: clean
