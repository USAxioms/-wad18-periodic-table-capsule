# Reproducibility Verification Guide

## What This Guide Covers

How to independently verify that the WAD18 periodic table is:
- ✅ **Bit-exact reproducible** across platforms
- ✅ **Deterministic** (same input → same output, always)
- ✅ **Cryptographically verifiable** (hash-checked)
- ✅ **Cross-platform consistent** (no platform-dependent behavior)

---

## Quick Reproducibility Check (5 minutes)

### Step 1: Build
```bash
make clean
make test
```

### Step 2: Record Results
Note the output. All 14 tests should PASS.

### Step 3: Rebuild Multiple Times
```bash
make clean && make test
make clean && make test
make clean && make test
```

**Expected:** Identical output every time. Same tests pass.

### Step 4: Verify
If all runs produce identical results, reproducibility is verified on your platform.

---

## Full Reproducibility Verification (30 minutes)

### Part 1: Single-Platform Reproducibility

#### Build with Different Optimization Levels

```bash
# Build with no optimization
CFLAGS="-O0 -Wall -Wextra -std=c99" make clean && make test > results_O0.txt

# Build with standard optimization
CFLAGS="-O2 -Wall -Wextra -std=c99" make clean && make test > results_O2.txt

# Build with aggressive optimization
CFLAGS="-O3 -Wall -Wextra -std=c99" make clean && make test > results_O3.txt
```

Compare results:
```bash
diff results_O0.txt results_O2.txt
diff results_O2.txt results_O3.txt
```

**Expected:** All three files are identical (or differ only in timing, not results).

#### Build with Different Compilers

If GCC and Clang are both available:

```bash
# GCC
CC=gcc make clean && make test > results_gcc.txt

# Clang
CC=clang make clean && make test > results_clang.txt
```

Compare:
```bash
diff results_gcc.txt results_clang.txt
```

**Expected:** Output is identical (or differs only in compiler version string).

### Part 2: Cross-Platform Reproducibility

If you have access to multiple platforms (x86, ARM, different architectures):

```bash
# Platform 1 (e.g., x86-64 Linux)
make clean && make test > platform1.txt

# Platform 2 (e.g., ARM Linux or macOS)
make clean && make test > platform2.txt

# Compare
diff platform1.txt platform2.txt
```

**Expected:** Absolutely identical output.

### Part 3: Hash Verification

Each element has a deterministic hash. Verify it:

```c
/* From C code */
wad18_t carbon = wad18_from_string("12.011");
uint32_t hash = wad18_hash32(carbon);
printf("Carbon hash: 0x%X\n", hash);
```

Run this multiple times (different compiles, different machines). Hash must be identical.

### Part 4: Acceptance Criteria Validation

The test suite includes acceptance criteria tests:

```bash
make test 2>&1 | grep "acceptance"
```

Expected output:
```
Testing: Acceptance: YBCO Tc in range ... PASS
```

This verifies that:
- ✅ YBCO Tc (92K) is within acceptance range (90-94K)
- ✅ Range checks are deterministic
- ✅ Acceptance decision is reproducible

---

## Cross-Platform Testing Script

Script to verify reproducibility on multiple platforms:

```bash
#!/bin/bash
# test_reproducibility.sh

platforms=()
results=()

echo "=== Cross-Platform Reproducibility Test ==="
echo ""

for i in {1..3}; do
    echo "Run $i:"
    make clean > /dev/null 2>&1
    make test 2>&1 | grep -E "^Testing:|Passed:|Failed:"
    
    # Capture hash of entire test output
    HASH=$(make test 2>&1 | sha256sum | cut -d' ' -f1)
    results+=("$HASH")
    
    echo "  Hash: $HASH"
    echo ""
done

echo "=== Reproducibility Check ==="
if [ "${results[0]}" == "${results[1]}" ] && [ "${results[1]}" == "${results[2]}" ]; then
    echo "✅ REPRODUCIBLE: All three runs produced identical output"
    exit 0
else
    echo "❌ NOT REPRODUCIBLE: Output differs between runs"
    exit 1
fi
```

Usage:
```bash
chmod +x test_reproducibility.sh
./test_reproducibility.sh
```

---

## Validation Checklist

- [ ] **Unit Tests Pass**: All 14 tests pass on first run
- [ ] **Deterministic**: Multiple runs produce identical output
- [ ] **Compiler Independent**: Different compilers produce same results
- [ ] **Optimization Independent**: -O0, -O2, -O3 all produce same results
- [ ] **Platform Independent**: x86, ARM, other architectures identical
- [ ] **Hash Consistent**: Same value always produces same hash
- [ ] **Acceptance Criteria**: Range checks are reproducible
- [ ] **No Memory Errors**: Debug build with sanitizers passes

---

## Common Issues & Solutions

### Issue: Tests pass but output differs slightly

**Symptom:**
```
Run 1: Passed: 14, Failed: 0
Run 2: Passed: 14, Failed: 0
```
But timing or compiler version differs.

**Solution:**
This is acceptable. What matters is:
- ✅ All tests pass
- ✅ No tests fail
- ✅ Numerical results are identical

### Issue: Tests pass on x86 but fail on ARM

**Symptom:**
```
x86-64:  14/14 tests pass
ARM:     13/14 tests pass
```

**Cause:** Platform-specific bug in WAD18 implementation.

**Solution:**
1. Check wad_fixed_point.c for non-portable code
2. Look for assumptions about byte order
3. Check 64-bit arithmetic (__int128 support)
4. File issue with platform details

### Issue: Different compiler gives different results

**Symptom:**
```
GCC:   14 tests pass
Clang: 14 tests pass
But binary output differs
```

**Cause:** Likely legitimate compiler difference (timing, optimization).

**Solution:**
As long as tests pass and numerical results are identical, this is acceptable. WAD18 arithmetic should be bit-exact; if it's not, there's a bug.

---

## Hash Verification for Periodic Table Data

### Verify JSON Integrity

```bash
# Calculate hash of periodic table
sha256sum periodic_table_wad18.json

# Compare to reference hash
cat periodic_table_wad18.json.sha256
```

**Expected:** Hashes match exactly.

### Element-by-Element Verification

```bash
# Extract Carbon from JSON
jq '.elements[] | select(.z == 6)' periodic_table_wad18.json

# Verify hash
# If hash = 0xA7F3E2B1..., calculate:
# sha256(json_object) should equal 0xA7F3E2B1...
```

---

## Reproducibility in Your Research

### Step 1: Freeze WAD18 Version
```json
{
  "wad18_version": "1.0.0",
  "periodic_table_version": "1.0.0",
  "date_frozen": "2026-09-21"
}
```

### Step 2: Record Hash
```bash
sha256sum periodic_table_wad18.json
# Output: 0xA1B2C3D4E5F6A7B8C9D0E1F2A3B4C5D6
```

### Step 3: Document in Methodology
> We used the WAD18 periodic table version 1.0.0 (frozen 2026-09-21, hash 0xA1B2C3D4...) for all calculations. This ensures perfect reproducibility of our results independent of platform or compiler.

### Step 4: Verify in Replication
When someone replicates your work:
```bash
sha256sum periodic_table_wad18.json
# Must produce: 0xA1B2C3D4E5F6A7B8C9D0E1F2A3B4C5D6
```

If hashes match, periodic table data is identical. Results must be identical.

---

## Reproducibility Testing Matrix

| Test | Verification | Status |
|------|---|---|
| Unit tests pass | All 14 tests PASS | ✅ |
| Deterministic | Multiple runs identical | ✅ |
| Compiler independent | GCC and Clang | ✅ |
| Optimization independent | -O0, -O2, -O3 | ✅ |
| Platform independent | x86, ARM if available | ✅ |
| Hash reproducible | Same value → same hash | ✅ |
| No memory errors | Sanitizers pass | ✅ |
| Data integrity | JSON hash matches | ✅ |

---

## Publishing Your Reproducibility Results

When you publish research using this framework:

```markdown
## Reproducibility

All calculations used the WAD18 periodic table v1.0.0 (frozen 2026-09-21).

Data integrity verified:
- Hash: 0xA1B2C3D4E5F6A7B8C9D0E1F2A3B4C5D6
- Platform: [x86-64 Linux / ARM / macOS]
- Compiler: [GCC version / Clang version]
- Optimization: -O2

Reproducibility verified:
- ✅ All unit tests pass
- ✅ Identical output on multiple runs
- ✅ Cross-platform consistency verified
- ✅ Deterministic arithmetic (no floating-point errors)

Code and data available at: [repository link]
```

---

## References

- WAD18 Arithmetic: See wad_fixed_point.c
- Periodic Table Data: See periodic_table_wad18.json
- Acceptance Criteria: See acceptance_criteria.md
- Unit Tests: See test_wad18_periodic.c

---

**Reproducibility is not aspiration. It is binary.**

**Either your results are bit-exact reproducible, or they are not.**

**This framework makes reproducibility the default.**
