/*                          *
 *  APPROXIMATION SETTINGS  *
 *                          */
#define ENABLE_APROX      1
#define PERCENT_THRESHOLD 0
/* === END OF APPROXIMATION SETTINGS === */

// GTE = Greather Than or Equal
// LTE = Less Than or equals
// only this two macros are defined

#if defined(ENABLE_APROX) && ENABLE_APROX == 1
    #if defined(PERCENT_THRESHOLD) && PERCENT_THRESHOLD
        #define APPROX_THRESHOLD 1E-15 // approximation due to calculation errors
        // Leave the next two as they are
        #define _GTE(x, y) ((x) >= (y) - APPROX_THRESHOLD)
        #define _LTE(x, y) ((x) <= (y) + APPROX_THRESHOLD)
    #else // PERCENT_THRESHOLD false or not defined
        #define APPROX_THRESHOLD 1E-10 // 0.0000...001 %
        #define _GTE(x, y) ((x) >= (y) - (y)*APPROX_THRESHOLD)
        #define _LTE(x, y) ((x) <= (y) + (y)*APPROX_THRESHOLD)
    #endif // PERCENT_THRESHOLD

    #define _EQ(x, y)  (_GTE((x), (y)) && _LTE((x), (y))) // (x >= y && x <= y)
    #define _NEQ(x, y) (!_EQ((x), (y)))  // !(x == y)
    #define _GT(x, y)  (_GTE((x), (y)) && _NEQ((x), (y))) // (x >= y && x != y)
    #define _LT(x, y)  (_LTE((x), (y)) && _NEQ((x), (y))) // (x <= y && x != y)

#else // ENABLE_APROX false or not defined
    #define _GTE(x, y) ((x) >= (y))
    #define _LTE(x, y) ((x) <= (y))
    #define _EQ(x, y)  ((x) == (y))
    #define _NEQ(x, y) ((x) != (y))
    #define _GT(x, y)  ((x) >  (y))
    #define _LT(x, y)  ((x) <  (y))
#endif

// optional: small case (for camel case compatibility)

#define eq(x, y)  _EQ(x, y)
#define neq(x, y) _NEQ(x, y)
#define gte(x, y) _GTE(x, y)
#define lte(x, y) _LTE(x, y)
#define gt(x, y)  _GT(x, y)
#define lt(x, y)  _LT(x, y)
