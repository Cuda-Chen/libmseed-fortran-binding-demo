# libmseed-fortran-binding-demo
Fortran binding to libmseed demo.

## Fortran linking
 gfortran -std=legacy -g -ffixed-line-length-128 f2ms.f pack_mseed.o -L/usr/lobal/ -lmseed -o f2ms

./f2ms ABCD BHZ 20 tests/testwaveform.txt 2021-02-21T00:00:34.22
