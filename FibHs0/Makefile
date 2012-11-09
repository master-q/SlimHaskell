PROG := FibHs
HSLIB := Fib
CMAIN := CMain

all: ${PROG}
${PROG}: ${CMAIN}.o ${HSLIB}.o
	ghc -no-hs-main $^ -o ${PROG}

${CMAIN}.o: ${CMAIN}.c
	gcc -I/usr/lib/ghc/include -c $<

${HSLIB}.o: ${HSLIB}.hs
	ghc -c $<

clean:
	rm -f ${PROG} *.o *.hi *_stub.h *~

.PHONY: clean
