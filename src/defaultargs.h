// defaultargs.h -- Handles default arguments
// Up to five parameters, no real reason to extend
// beyond this amount.
#ifndef DEFAULTARGS_H
#define DEFAULTARGS_H

#define PASTER(x,y) x ## y
#define EVALUATE(x,y) PASTER(x,y)
#define ARGSEQ 5,4,3,2,1
#define GETNARG(_5,_4,_3,_2,_1,N,...) N
#define GETNARG_(...) GETNARG(__VA_ARGS__)
#define ARGN(...) GETNARG_(__VA_ARGS__, ARGSEQ)

#endif
