#include "wad_fixed_point.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

wad18_t wad18_from_int(int64_t value) {
    return value * WAD18_SCALE;
}

wad18_t wad18_from_string(const char *str) {
    /* Parse decimal string like "12.011" to WAD18 */
    char *dot = strchr(str, '.');
    if (!dot) {
        return atoll(str) * WAD18_SCALE;
    }
    
    int64_t integer_part = atoll(str);
    const char *decimal_part = dot + 1;
    int decimal_len = strlen(decimal_part);
    
    int64_t decimal_value = atoll(decimal_part);
    for (int i = decimal_len; i < 18; i++) {
        decimal_value *= 10;
    }
    
    return integer_part * WAD18_SCALE + decimal_value;
}

wad18_t wad18_add(wad18_t a, wad18_t b) {
    return a + b;
}

wad18_t wad18_sub(wad18_t a, wad18_t b) {
    return a - b;
}

wad18_t wad18_mul(wad18_t a, wad18_t b) {
    /* Multiply two WAD18 values, scale result */
    return ((__int128)a * b) / WAD18_SCALE;
}

wad18_t wad18_div(wad18_t a, wad18_t b) {
    /* Divide two WAD18 values, scale result */
    return ((__int128)a * WAD18_SCALE) / b;
}

uint32_t wad18_hash32(wad18_t value) {
    /* Simple 32-bit hash: FNV-1a style */
    uint32_t hash = 2166136261u;
    uint64_t v = (uint64_t)value;
    
    for (int i = 0; i < 8; i++) {
        hash ^= (v >> (i * 8)) & 0xFF;
        hash = (hash * 16777619u);
    }
    
    return hash;
}

bool wad18_equals(wad18_t a, wad18_t b) {
    return a == b;
}

char* wad18_to_string(wad18_t value, char *buffer, size_t len) {
    int64_t integer = value / WAD18_SCALE;
    int64_t decimal = value % WAD18_SCALE;
    
    if (decimal < 0) decimal = -decimal;
    
    snprintf(buffer, len, "%lld.%018lld", (long long)integer, (long long)decimal);
    return buffer;
}

double wad18_to_double(wad18_t value) {
    return (double)value / WAD18_SCALE;
}
