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
        #define GTE(x, y) ((x) >= (y) - APPROX_THRESHOLD)
        #define LTE(x, y) ((x) <= (y) + APPROX_THRESHOLD)
    #else // PERCENT_THRESHOLD false or not defined
        #define APPROX_THRESHOLD 1E-10 // 0.0000...001 %
        #define GTE(x, y) ((x) >= (y) - (y)*APPROX_THRESHOLD)
        #define LTE(x, y) ((x) <= (y) + (y)*APPROX_THRESHOLD)
    #endif // PERCENT_THRESHOLD

    #define EQ(x, y)  (GTE((x), (y)) && LTE((x), (y))) // (x >= y && x <= y)
    #define NEQ(x, y) (!EQ((x), (y)))  // !(x == y)
    #define GT(x, y)  (GTE((x), (y)) && NEQ((x), (y))) // (x >= y && x != y)
    #define LT(x, y)  (LTE((x), (y)) && NEQ((x), (y))) // (x <= y && x != y)

#else // ENABLE_APROX false or not defined
    #define GTE(x, y) ((x) >= (y))
    #define LTE(x, y) ((x) <= (y))
    #define EQ(x, y)  ((x) == (y))
    #define NEQ(x, y) ((x) != (y))
    #define GT(x, y)  ((x) >  (y))
    #define LT(x, y)  ((x) <  (y))
#endif

// optional: small case (for camel case compatibility)

#define eq(x, y)  EQ(x, y)
#define neq(x, y) NEQ(x, y)
#define gte(x, y) GTE(x, y)
#define lte(x, y) LTE(x, y)
#define gt(x, y)  GT(x, y)
#define lt(x, y)  LT(x, y)
