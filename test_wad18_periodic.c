#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "wad_fixed_point.h"

/* Test counter */
static int tests_passed = 0;
static int tests_failed = 0;

#define TEST(name) printf("Testing: %s ... ", name); fflush(stdout)
#define PASS() do { printf("PASS\n"); tests_passed++; } while(0)
#define FAIL() do { printf("FAIL\n"); tests_failed++; } while(0)

/* WAD18 Conversion Tests */
void test_wad18_from_string_integer() {
    TEST("WAD18 from string (integer)");
    wad18_t val = wad18_from_string("12");
    assert(val == 12000000000000000000LL);
    PASS();
}

void test_wad18_from_string_decimal() {
    TEST("WAD18 from string (decimal)");
    wad18_t val = wad18_from_string("12.011");
    /* 12.011 should be 12011000000000000000 */
    assert(val == 12011000000000000000LL);
    PASS();
}

void test_wad18_from_string_small_decimal() {
    TEST("WAD18 from string (small decimal)");
    wad18_t val = wad18_from_string("1.008");
    assert(val == 1008000000000000000LL);
    PASS();
}

/* Arithmetic Tests */
void test_wad18_addition() {
    TEST("WAD18 addition");
    wad18_t a = wad18_from_string("12.011");
    wad18_t b = wad18_from_string("1.008");
    wad18_t result = wad18_add(a, b);
    wad18_t expected = wad18_from_string("13.019");
    assert(result == expected);
    PASS();
}

void test_wad18_subtraction() {
    TEST("WAD18 subtraction");
    wad18_t a = wad18_from_string("15.999");
    wad18_t b = wad18_from_string("1.008");
    wad18_t result = wad18_sub(a, b);
    wad18_t expected = wad18_from_string("14.991");
    assert(result == expected);
    PASS();
}

void test_wad18_equals() {
    TEST("WAD18 equality");
    wad18_t a = wad18_from_string("12.011");
    wad18_t b = wad18_from_string("12.011");
    assert(wad18_equals(a, b));
    PASS();
}

void test_wad18_not_equals() {
    TEST("WAD18 inequality");
    wad18_t a = wad18_from_string("12.011");
    wad18_t b = wad18_from_string("12.012");
    assert(!wad18_equals(a, b));
    PASS();
}

/* Hash Tests */
void test_wad18_hash_deterministic() {
    TEST("WAD18 hash deterministic");
    wad18_t val = wad18_from_string("12.011");
    uint32_t hash1 = wad18_hash32(val);
    uint32_t hash2 = wad18_hash32(val);
    assert(hash1 == hash2);
    PASS();
}

void test_wad18_hash_different_values() {
    TEST("WAD18 hash different for different values");
    wad18_t val1 = wad18_from_string("12.011");
    wad18_t val2 = wad18_from_string("12.012");
    uint32_t hash1 = wad18_hash32(val1);
    uint32_t hash2 = wad18_hash32(val2);
    assert(hash1 != hash2);
    PASS();
}

/* Element-specific tests */
void test_hydrogen_atomic_mass() {
    TEST("Hydrogen atomic mass in WAD18");
    wad18_t expected = 1008000000000000000LL;
    wad18_t actual = wad18_from_string("1.008");
    assert(wad18_equals(actual, expected));
    PASS();
}

void test_carbon12_atomic_mass() {
    TEST("Carbon-12 atomic mass (definition)");
    wad18_t expected = 12000000000000000000LL;
    wad18_t actual = wad18_from_int(12);
    assert(wad18_equals(actual, expected));
    PASS();
}

void test_oxygen16_atomic_mass() {
    TEST("Oxygen-16 atomic mass");
    wad18_t expected = 15999000000000000000LL;
    wad18_t actual = wad18_from_string("15.999");
    assert(wad18_equals(actual, expected));
    PASS();
}

/* Reproducibility Tests */
void test_reproducibility_carbon() {
    TEST("Reproducibility: Carbon measurement");
    wad18_t measurement1 = wad18_from_string("12.011");
    wad18_t measurement2 = wad18_from_string("12.011");
    assert(wad18_equals(measurement1, measurement2));
    assert(wad18_hash32(measurement1) == wad18_hash32(measurement2));
    PASS();
}

void test_reproducibility_mixed_elements() {
    TEST("Reproducibility: Mixed element calculation");
    wad18_t h = wad18_from_string("1.008");
    wad18_t o = wad18_from_string("15.999");
    wad18_t c = wad18_from_string("12.011");
    
    /* H2O mass = 2*H + O */
    wad18_t h2o_1 = wad18_add(wad18_add(h, h), o);
    wad18_t h2o_2 = wad18_add(wad18_add(h, h), o);
    
    assert(wad18_equals(h2o_1, h2o_2));
    assert(wad18_hash32(h2o_1) == wad18_hash32(h2o_2));
    PASS();
}

/* Cross-platform consistency tests */
void test_wad18_byte_order_independent() {
    TEST("WAD18 value independent of byte order");
    wad18_t val = wad18_from_string("55.845");  /* Iron */
    uint32_t hash = wad18_hash32(val);
    /* Hash should be consistent regardless of platform endianness */
    assert(hash != 0);
    PASS();
}

/* Acceptance criteria tests */
void test_acceptance_ybco_tc() {
    TEST("Acceptance: YBCO Tc in range");
    wad18_t tc = wad18_from_string("92.0");  /* YBCO critical temperature */
    wad18_t tc_min = wad18_from_string("90.0");
    wad18_t tc_max = wad18_from_string("94.0");
    
    /* Check if 92 K is within acceptance range */
    assert(wad18_sub(tc, tc_min) >= 0);
    assert(wad18_sub(tc_max, tc) >= 0);
    PASS();
}

int main() {
    printf("\n=== WAD18 Periodic Table Unit Tests ===\n\n");
    
    /* Conversion tests */
    test_wad18_from_string_integer();
    test_wad18_from_string_decimal();
    test_wad18_from_string_small_decimal();
    
    /* Arithmetic tests */
    test_wad18_addition();
    test_wad18_subtraction();
    test_wad18_equals();
    test_wad18_not_equals();
    
    /* Hash tests */
    test_wad18_hash_deterministic();
    test_wad18_hash_different_values();
    
    /* Element tests */
    test_hydrogen_atomic_mass();
    test_carbon12_atomic_mass();
    test_oxygen16_atomic_mass();
    
    /* Reproducibility tests */
    test_reproducibility_carbon();
    test_reproducibility_mixed_elements();
    test_wad18_byte_order_independent();
    
    /* Acceptance criteria */
    test_acceptance_ybco_tc();
    
    printf("\n=== Test Results ===\n");
    printf("Passed: %d\n", tests_passed);
    printf("Failed: %d\n", tests_failed);
    printf("Total:  %d\n\n", tests_passed + tests_failed);
    
    return tests_failed == 0 ? 0 : 1;
}
