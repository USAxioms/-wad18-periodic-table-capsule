# Pre-Declared Acceptance Criteria for WAD18 Periodic Table

**Status:** IMMUTABLE (frozen at release)  
**Date:** 2026-09-21  
**Hash:** [SHA-256 of this document]

---

## Purpose

These criteria establish what measurements are accepted for inclusion in the WAD18 periodic table. **These criteria are pre-declared and CANNOT change retroactively.** They are evaluated BEFORE any measurement is taken.

**This prevents p-hacking.** No goalpost moving after data collection.

---

## Atomic Mass

### Acceptance Criteria
- **Value Source**: IUPAC Commission on Isotopic Abundances and Atomic Weights
- **Uncertainty**: ±0.01 u (atomic mass units) maximum
- **Latest Update**: IUPAC 2021
- **Verification**: Atomic mass value multiplied by 10¹⁸ = WAD18 representation

### Examples (PASS)
```
Element Z=6 (Carbon-12): 12.0000 u ✅
  WAD18: 12000000000000000000
  Source: IUPAC definition
  Status: PASS

Element Z=8 (Oxygen-16): 15.999 u ✅
  WAD18: 15999000000000000000
  Source: IUPAC 2021
  Uncertainty: ±0.001 u
  Status: PASS

Element Z=26 (Iron): 55.845 u ✅
  WAD18: 55845000000000000000
  Source: IUPAC 2021
  Uncertainty: ±0.002 u
  Status: PASS
```

### Examples (FAIL)
```
Measurement with uncertainty ±0.015 u ❌
  Reason: Uncertainty exceeds ±0.01 u limit
  Status: FAIL

Value from non-IUPAC source ❌
  Reason: Must be IUPAC certified
  Status: FAIL

Old IUPAC value (pre-2020) ❌
  Reason: Must use latest certified value
  Status: FAIL
```

---

## Ionization Energy (First)

### Acceptance Criteria
- **Value Source**: NIST Atomic Spectra Database (SRD 144)
- **Units**: Electron volts (eV)
- **Uncertainty**: ±0.1 eV maximum
- **Documentation**: Peer-reviewed measurement
- **Verification**: Value × 10¹⁸ = WAD18 representation

### Examples (PASS)
```
Hydrogen (Z=1): 13.5984 eV ✅
  WAD18: 13598400000000000000
  Source: NIST SRD 144
  Measurement: Spectroscopic (Rydberg constant)
  Status: PASS

Oxygen (Z=8): 13.6181 eV ✅
  WAD18: 13618100000000000000
  Source: NIST SRD 144
  Status: PASS

Iron (Z=26): 7.8749 eV ✅
  WAD18: 7874900000000000000
  Source: NIST SRD 144
  Status: PASS
```

### Examples (FAIL)
```
Value with uncertainty ±0.2 eV ❌
  Reason: Exceeds ±0.1 eV limit
  Status: FAIL

Measurement from non-reviewed source ❌
  Reason: Must be NIST-verified or peer-reviewed
  Status: FAIL

Different reference data ❌
  Reason: Must use NIST SRD 144
  Status: FAIL
```

---

## Electronegativity (Pauling Scale)

### Acceptance Criteria
- **Value Source**: Pauling (original definition)
- **Range**: 0.0 to 4.0 (inclusive)
- **Reference**: Hydrogen = 2.1 (fixed)
- **Consistency**: Relative to hydrogen electronegativity
- **Verification**: Value × 10¹⁸ = WAD18 representation

### Examples (PASS)
```
Hydrogen (Z=1): 2.10 ✅
  WAD18: 2100000000000000000
  Source: Pauling definition (reference)
  Status: PASS

Fluorine (Z=9): 3.98 ✅
  WAD18: 3980000000000000000
  Source: Most electronegative element
  Status: PASS

Boron (Z=5): 2.04 ✅
  WAD18: 2040000000000000000
  Source: Pauling scale
  Status: PASS

Francium (Z=87): 0.7 ✅
  WAD18: 700000000000000000
  Source: Least electronegative element
  Status: PASS
```

### Examples (FAIL)
```
Value > 4.0 ❌
  Status: FAIL (exceeds physical limit)

Electronegativity for noble gas ≠ 0 ❌
  Status: FAIL (inconsistent with definition)

Value < 0.0 ❌
  Status: FAIL (negative values undefined)
```

---

## Density (at 300K, 1 atm)

### Acceptance Criteria
- **Condition**: Standard conditions (300K = 27°C, 1 atm)
- **Phase**: Solid or liquid at standard conditions
- **Source**: Peer-reviewed measurement
- **State Specification**: Must declare phase (solid/liquid)
- **Verification**: Density (g/cm³) × 10¹⁸ = WAD18 representation

### Examples (PASS)
```
Iron (Z=26), solid: 7.874 g/cm³ ✅
  WAD18: 7874000000000000000
  Phase: Solid at 300K, 1 atm
  Source: CRC Handbook
  Status: PASS

Water (H₂O compound), liquid: 0.9971 g/cm³ ✅
  WAD18: 997100000000000000
  Phase: Liquid at 300K, 1 atm
  Status: PASS

Aluminum (Z=13), solid: 2.708 g/cm³ ✅
  WAD18: 2708000000000000000
  Source: Peer-reviewed measurement
  Status: PASS
```

### Examples (FAIL)
```
Density without temperature specification ❌
  Reason: Must specify "at 300K, 1 atm"
  Status: FAIL

Hydrogen (Z=1) density at 1 atm, 300K ❌
  Reason: Hydrogen is gas at standard conditions
  Status: FAIL (use gas density if specified)

Measurement at different temperature ❌
  Reason: Must be at 300K
  Status: FAIL
```

---

## Melting Point & Boiling Point

### Acceptance Criteria
- **Units**: Kelvin (K)
- **Source**: Peer-reviewed measurement or CRC Handbook
- **Condition**: At 1 atm pressure (unless otherwise specified)
- **State**: Solid → Liquid (melting) or Liquid → Gas (boiling)
- **Verification**: Temperature (K) × 10¹⁸ = WAD18 representation

### Examples (PASS)
```
Iron (Z=26) melting point: 1811 K ✅
  WAD18: 1811000000000000000
  Source: CRC Handbook
  Pressure: 1 atm
  Status: PASS

Water (compound) boiling point: 373.15 K ✅
  WAD18: 373150000000000000
  Source: Definition (at 1 atm)
  Status: PASS

Nitrogen (Z=7) melting point: 63.15 K ✅
  WAD18: 63150000000000000
  Source: CRC Handbook
  Status: PASS
```

### Examples (FAIL)
```
Temperature at non-standard pressure ❌
  Reason: Must be at 1 atm (or explicitly noted)
  Status: FAIL

Sublimation point instead of melting point ❌
  Reason: Wrong phase transition
  Status: FAIL

Noble gas with melting point ❌
  Reason: Most noble gases don't melt at standard pressure
  Status: FAIL
```

---

## Hash Verification (Applies to All Properties)

### Acceptance Criteria
- **Algorithm**: SHA-256
- **Input**: All element properties as JSON string
- **Output**: 64-character hex string
- **Verification**: Hash must match reference hash exactly
- **Re-calculation**: On any property update

### Examples (PASS)
```
Element JSON: {"z":6,"symbol":"C","name":"Carbon",...}
SHA256: 0xA7F3E2B1C9D8F4E6A2B1C9D8F4E6A2B1...
Reference: 0xA7F3E2B1C9D8F4E6A2B1C9D8F4E6A2B1...
Match: ✅ PASS
```

### Examples (FAIL)
```
Element JSON: {"z":6,"symbol":"C","name":"Carbon",...}
SHA256: 0xDEADBEEF...
Reference: 0xA7F3E2B1...
Match: ❌ FAIL (data corrupted or changed)
```

---

## Transformation Rules (How Properties Evolve)

These rules govern how properties can change **while maintaining acceptance criteria**.

### Atomic Mass Update Rule
```
IF (new_measurement from IUPAC)
AND (uncertainty < ±0.01 u)
AND (independently verified)
AND (previous value archived with timestamp)
THEN accept new value
AND recalculate hash
AND increment version
```

### Ionization Energy Update Rule
```
IF (published in peer-reviewed journal)
AND (in NIST SRD 144)
AND (multiple measurements agree)
AND (uncertainty < ±0.1 eV)
THEN accept new value
AND recalculate hash
AND increment version
```

### General Update Rule
```
FOR ANY property update:
  1. Verify source meets acceptance criteria
  2. Archive old value with timestamp
  3. Calculate new hash
  4. Increment version number
  5. Document reason for change
  6. Verify new hash matches calculation
```

---

## Examples of Acceptance Decisions

### Scenario 1: New Atomic Mass Measurement
```
Claim: Carbon-12.0001 u (not 12.0000 u)
Reason: New high-precision measurement
Source: Non-IUPAC laboratory

Decision: ❌ FAIL
Reason: Only IUPAC certified values accepted
Action: Refer to IUPAC Commission
```

### Scenario 2: Updated Ionization Energy
```
Claim: Hydrogen 13.6056 eV (not 13.5984 eV)
Reason: Refined spectroscopic measurement
Source: Published in Nature Physics, 2025
Verification: Matches NIST SRD 144 update

Decision: ✅ PASS
Action: Update in periodic table v1.1
Hash: Recalculate and verify
Timestamp: 2026-09-21
Changelog: "NIST update to Rydberg constant"
```

### Scenario 3: Contaminated Sample
```
Claim: Iron density 7.80 g/cm³ (not 7.874 g/cm³)
Reason: Lab measurement with dust
Source: Unknown laboratory
Verification: Fails independent check

Decision: ❌ FAIL
Reason: Fails consistency check with established value
Action: Reject measurement
Note: Iron density is well-established; reject outliers
```

---

## Summary

| Property | Source | Uncertainty | Verification |
|----------|--------|-------------|--------------|
| Atomic Mass | IUPAC | ±0.01 u | WAD18 hash |
| Ionization Energy | NIST | ±0.1 eV | WAD18 hash |
| Electronegativity | Pauling | 0.0–4.0 range | Consistency |
| Density | Peer-review | Standard conditions | WAD18 hash |
| Melting Point | Peer-review | 1 atm | WAD18 hash |
| Boiling Point | Peer-review | 1 atm | WAD18 hash |

---

## Immutability Statement

**These criteria are frozen as of 2026-09-21.**

Changes require:
1. Publication of new scientific evidence
2. International consensus (IUPAC)
3. New version release with hash recalculation
4. Archived changelog

**No retroactive modification of acceptance criteria.**

---

## References

- IUPAC Commission on Isotopic Abundances and Atomic Weights (2021)
- NIST Atomic Spectra Database (SRD 144)
- Pauling Scale (Electronegativity definition)
- CRC Handbook of Chemistry and Physics
- Peer-reviewed sources as cited

---

**These criteria ensure reproducibility through pre-declaration.** No goalpost moving. No p-hacking. No ambiguity.
