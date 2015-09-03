// defaultargs.h -- Handles default arguments
// Up to five parameters, no real reason to extend
// beyond this amount.
#ifndef DEFAULTARGS_H
#define DEFAULTARGS_H

#define GETNARG(_5,_4,_3,_2,_1,N,...) N
#define ARGSEQ() 5,4,3,2,1
#define ARGN(...) NUMARGS(__VA_ARGS__, ARGSEQ())

#endif
