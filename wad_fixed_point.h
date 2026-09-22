#ifndef WAD_FIXED_POINT_H
#define WAD_FIXED_POINT_H

#include <stdint.h>
#include <stdbool.h>

/* WAD18: Wei Adjusted Denomination (10^-18 precision)
 * All values are 64-bit signed integers representing value * 10^18
 * Enables deterministic, cross-platform arithmetic with NO floating-point errors
 */

typedef int64_t wad18_t;

#define WAD18_SCALE 1000000000000000000LL  /* 10^18 */
#define WAD18_MAX   INT64_MAX
#define WAD18_MIN   INT64_MIN

/* Basic operations */
wad18_t wad18_from_int(int64_t value);
wad18_t wad18_from_string(const char *str);
wad18_t wad18_add(wad18_t a, wad18_t b);
wad18_t wad18_sub(wad18_t a, wad18_t b);
wad18_t wad18_mul(wad18_t a, wad18_t b);
wad18_t wad18_div(wad18_t a, wad18_t b);

/* Verification */
uint32_t wad18_hash32(wad18_t value);
bool wad18_equals(wad18_t a, wad18_t b);

/* String conversion */
char* wad18_to_string(wad18_t value, char *buffer, size_t len);
double wad18_to_double(wad18_t value);

#endif
