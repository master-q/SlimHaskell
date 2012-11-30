#!/bin/sh
size FibHs > FibHs.size
size *.o *.a rts/* | sort -k 4 > size.log
