GHC := /usr/local/ghc7.6.1/bin/ghc
PROG := FibHs
HSLIB := Fib
CMAIN := CMain

all: ${PROG}
${PROG}: ${CMAIN}.o ${HSLIB}.o
	${GHC} -O2 -no-hs-main $^ -o ${PROG}

${CMAIN}.o: ${CMAIN}.c
	gcc -I/usr/lib/ghc/include -c $<

${HSLIB}.o: ${HSLIB}.hs
	${GHC} -O2 -c $<

clean:
	rm -f ${PROG} *.o *.hi *_stub.h *~

.PHONY: clean
