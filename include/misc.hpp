#ifndef MISC_H
#define MISC_H

#include <math.h>
#include <stdlib.h> 

/*
  DEFINE IF A CONDITION IS LIKELY OR UNLIKELY TO HAPPEN ( helps optimizing the code )
  example:
  if(likely(x == 0))....
*/

#define likely(x)	__builtin_expect(!!(x), 1)
#define unlikely(x)	__builtin_expect(!!(x), 0)


/*
	MATH FUNCTIONS
*/

template<typename t> t randRange(t m,t M){
	return m + (M-m)*t(rand())/RAND_MAX;
}

template<typename t> t keepInRange(t v,t m,t M){
	if(unlikely(v < m))return m;
	if(unlikely(v > M))return M;
	return v;
}

/*
	CONSOLE COLORS
*/

#define CONSOLE_RED "\033[38;5;196m"
#define CONSOLE_YELLOW "\033[38;5;220m"
#define CONSOLE_BLUE "\033[38;5;19m"
#define CONSOLE_GREEN "\033[38;5;46m"
#define CONSOLE_GRAY "\033[38;5;246m"

#define CONSOLE_BACKGROUND_RED "\033[48;5;196m"
#define CONSOLE_BACKGROUND_YELLOW "\033[48;5;220m"
#define CONSOLE_BACKGROUND_BLUE "\033[48;5;19m"
#define CONSOLE_BACKGROUND_GREEN "\033[48;5;46m"
#define CONSOLE_BACKGROUND_GRAY "\033[48;5;246m"

#define CONSOLE_RESET "\033[39;49m"

#endif