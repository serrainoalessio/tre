#include <math.h>
#include <stdlib.h> 

/*
  DEFINE IF A CONDITION IS LIKELY OR UNLIKELY TO HAPPEN ( helps optimizing the code )
  example:
  if(likely(x == 0))....
*/

#define likely(x)	__builtin_expect(!!(x), 1)
#define unlikely(x)	__builtin_expect(!!(x), 0)



template<typename t> t randRange(t m,t M){
	return m + (M-m)*t(rand())/RAND_MAX;
}

template<typename t> t keepInRange(t v,t m,t M){
	if(unlikely(v < m))return m;
	if(unlikely(v > M))return M;
	return v;
}

