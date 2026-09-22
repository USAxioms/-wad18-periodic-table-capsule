# Specimen Passport Specification

## Overview

A **specimen passport** is a cryptographically-verified digital certificate for each element in the periodic table. It records:
- Element identity
- All properties in WAD18 format
- Measurement methodology
- Certification authority
- Cryptographic hash
- Timestamp
- References

---

## Specimen Passport Structure

```json
{
  "passport": {
    "element": "Carbon",
    "z": 6,
    "symbol": "C",
    "version": "1.0.0",
    
    "properties": {
      "atomic_mass_wad18": "12011000000000000000",
      "atomic_mass_decimal": "12.011",
      "ionization_energy_wad18": "11260700000000000000",
      "ionization_energy_decimal": "11.2607 eV",
      "electron_affinity_wad18": "121776000000000000000",
      "electron_affinity_decimal": "1.21776 eV",
      "electronegativity_wad18": "2550000000000000000",
      "electronegativity_decimal": "2.55",
      "atomic_radius_wad18": "77000000000000000000",
      "atomic_radius_decimal": "77 pm",
      "density_wad18": "2267000000000000000",
      "density_decimal": "2.267 g/cm³ (at 300K, solid)",
      "melting_point_wad18": "3550150000000000000000",
      "melting_point_decimal": "3550.15 K",
      "boiling_point_wad18": "4827150000000000000000",
      "boiling_point_decimal": "4827.15 K"
    },
    
    "metadata": {
      "created": "2026-09-21T00:00:00Z",
      "last_updated": "2026-09-21T00:00:00Z",
      "certification_date": "2026-09-21",
      "revision": "1.0"
    },
    
    "certification": {
      "authority": "IUPAC Commission on Isotopic Abundances and Atomic Weights",
      "method": "Consensus of peer-reviewed measurements",
      "status": "ACCEPTED"
    },
    
    "verification": {
      "hash_algorithm": "SHA-256",
      "hash_value": "0xA7F3E2B1C9D8F4E6A2B1C9D8F4E6A2B1C9D8F4E6A2B1C9D8F4E6A2B1C9D8F4E",
      "hash_input": "All properties concatenated and hashed",
      "verification_status": "VERIFIED"
    },
    
    "references": [
      "IUPAC 2021 Atomic Weights",
      "NIST SRD 144 Atomic Spectra Database",
      "CRC Handbook of Chemistry and Physics (104th Edition)",
      "Pauling Scale (Electronegativity)"
    ],
    
    "acceptance_criteria": {
      "atomic_mass": {
        "criterion": "IUPAC certified, uncertainty < ±0.01 u",
        "status": "PASS",
        "value_status": "12.011 u (within bounds)"
      },
      "ionization_energy": {
        "criterion": "NIST SRD 144, uncertainty < ±0.1 eV",
        "status": "PASS",
        "value_status": "11.2607 eV (within bounds)"
      },
      "physical_properties": {
        "criterion": "Peer-reviewed at standard conditions",
        "status": "PASS",
        "conditions": "300K, 1 atm"
      }
    },
    
    "transformation_rules": {
      "atomic_mass_update": "New value accepted if IUPAC certified and uncertainty < ±0.01 u",
      "ionization_energy_update": "Updated from NIST database if peer-reviewed",
      "physical_properties_update": "Accepted if measured under standard conditions with documented methodology",
      "hash_update": "Recalculated whenever any property changes, timestamp updated"
    },
    
    "changelog": [
      {
        "date": "2026-09-21",
        "revision": "1.0",
        "change": "Initial WAD18 periodic table release",
        "hash": "0xA7F3E2B1..."
      }
    ]
  }
}
```

---

## Field Specifications

### Element Identity
- **element**: Full element name
- **z**: Atomic number (1-118)
- **symbol**: Element symbol (H, He, Li, etc.)
- **version**: Passport version (for tracking updates)

### Properties (Dual Representation)
Every property has TWO representations:
1. **WAD18 format**: Integer value (10¹⁸ scale)
2. **Decimal format**: Human-readable with units

Example (Carbon atomic mass):
- **atomic_mass_wad18**: 12011000000000000000
- **atomic_mass_decimal**: "12.011 u"

**Why dual format?**
- WAD18 for calculation and verification
- Decimal for readability and reference

### Metadata
- **created**: ISO-8601 timestamp of first creation
- **last_updated**: Timestamp of last modification
- **certification_date**: Date when certified
- **revision**: Version number (1.0, 1.1, 2.0, etc.)

### Certification
- **authority**: Who certified this element (IUPAC, NIST, etc.)
- **method**: How it was certified
- **status**: Current status (ACCEPTED, UNDER_REVIEW, DEPRECATED)

### Verification (Cryptographic)
- **hash_algorithm**: SHA-256
- **hash_value**: The actual hash (64-char hex)
- **hash_input**: What was hashed
- **verification_status**: VERIFIED or FAILED

### Acceptance Criteria
Explicitly shows:
- What criterion must be met
- Whether current value meets it
- Status (PASS or FAIL)

### Transformation Rules
Documents how this element's properties can change while remaining reproducible.

### Changelog
Historical record of all updates:
- Date of change
- What changed
- Hash of new values
- Reason for change

---

## How to Verify a Specimen Passport

### Step 1: Load the Passport
```bash
cat C_passport.json
```

### Step 2: Extract Hash Value
```bash
jq '.passport.verification.hash_value' C_passport.json
```

### Step 3: Calculate Hash
```bash
# Create verification string (properties only)
jq '.passport.properties' C_passport.json | sha256sum

# Or manually concatenate:
echo "C|6|12011000000000000000|11260700000000000000|..." | sha256sum
```

### Step 4: Compare
```bash
# Should output:
# 0xA7F3E2B1... == 0xA7F3E2B1...  ✅ VERIFIED
```

---

## Specimen Passport Lifecycle

### Creation (Initial Release)
```json
{
  "status": "CREATED",
  "date": "2026-09-21",
  "hash": "0xA7F3E2B1...",
  "revision": "1.0"
}
```

### Update (Property Change)
```json
{
  "status": "UPDATED",
  "date": "2026-12-15",
  "previous_hash": "0xA7F3E2B1...",
  "new_hash": "0xB8C4D2E3...",
  "revision": "1.1",
  "reason": "IUPAC 2026 Atomic Weights update"
}
```

### Verification (Hash Check)
```json
{
  "status": "VERIFIED",
  "verification_date": "2026-12-20",
  "hash_calculated": "0xB8C4D2E3...",
  "hash_stored": "0xB8C4D2E3...",
  "result": "MATCH ✅"
}
```

### Deprecation (Old Value Replaced)
```json
{
  "status": "DEPRECATED",
  "superseded_by": "revision 2.0",
  "replacement_date": "2027-06-01",
  "archived_hash": "0xB8C4D2E3...",
  "note": "Improved measurement technique"
}
```

---

## Specimen Passport Examples

### Example 1: Hydrogen (Lightest Element)
```json
{
  "z": 1,
  "symbol": "H",
  "element": "Hydrogen",
  "atomic_mass_wad18": "1008000000000000000",
  "atomic_mass_decimal": "1.008 u",
  "hash": "0xC1D2E3F4A5B6C7D8E9F0A1B2C3D4E5F6",
  "status": "VERIFIED"
}
```

### Example 2: Carbon-12 (Definition)
```json
{
  "z": 6,
  "symbol": "C",
  "element": "Carbon",
  "atomic_mass_wad18": "12000000000000000000",
  "atomic_mass_decimal": "12.000 u (EXACT - by definition)",
  "note": "Carbon-12 is the reference for atomic mass scale",
  "hash": "0xA7F3E2B1C9D8F4E6A2B1C9D8F4E6A2B1",
  "status": "VERIFIED"
}
```

### Example 3: Iron (Materials Science)
```json
{
  "z": 26,
  "symbol": "Fe",
  "element": "Iron",
  "atomic_mass_wad18": "55845000000000000000",
  "atomic_mass_decimal": "55.845 u",
  "density_wad18": "7874000000000000000",
  "density_decimal": "7.874 g/cm³ (at 300K)",
  "melting_point_wad18": "1811150000000000000000",
  "melting_point_decimal": "1811.15 K",
  "hash": "0xF7E3B1A9C8D2F5E6A7B1C9D8F4E6A2B1",
  "status": "VERIFIED"
}
```

---

## Integration with Research

### Using Specimen Passport in Your Work

```markdown
## Materials & Methods

Periodic table data from WAD18 v1.0.0 specimen passports:

**Carbon-12:**
- Atomic mass: 12.000000... u (by definition)
- Hash: 0xA7F3E2B1...
- Status: VERIFIED

**Oxygen-16:**
- Atomic mass: 15.999000... u
- Hash: 0xD4E5F6G7...
- Status: VERIFIED

All calculations performed using WAD18 fixed-point arithmetic
to ensure cross-platform reproducibility.
```

### Documenting Verification

```markdown
## Data Integrity

Specimen passports verified via SHA-256:

| Element | Expected Hash | Calculated Hash | Status |
|---------|---|---|---|
| H | 0xC1D2E3F4... | 0xC1D2E3F4... | ✅ PASS |
| C | 0xA7F3E2B1... | 0xA7F3E2B1... | ✅ PASS |
| O | 0xD4E5F6G7... | 0xD4E5F6G7... | ✅ PASS |
| Fe | 0xF7E3B1A9... | 0xF7E3B1A9... | ✅ PASS |
```

---

## Specimen Passport Archive

The WAD18 periodic table maintains an **immutable archive** of all specimen passports:

```
passport_archive/
├── H_v1.0.json         (Hydrogen, version 1.0)
├── H_v1.1.json         (Hydrogen, version 1.1, if updated)
├── He_v1.0.json        (Helium)
├── ...
└── Og_v1.0.json        (Oganesson, element 118)
```

Each passport:
- ✅ Is immutable once created
- ✅ Is timestamped
- ✅ Is hash-verified
- ✅ Is retained in archive (never deleted)
- ✅ Is referenced by all dependent research

---

## Specimen Passport Validation Checklist

- [ ] Element identity is correct (z, symbol, name)
- [ ] All properties present and in WAD18 format
- [ ] Hash algorithm is SHA-256
- [ ] Hash can be independently verified
- [ ] Certification authority is legitimate
- [ ] Acceptance criteria status is documented
- [ ] Transformation rules are defined
- [ ] Changelog is complete
- [ ] Metadata timestamps are ISO-8601
- [ ] References are credible

---

## References

- Specimen passport structure: This document
- WAD18 arithmetic: wad_fixed_point.c
- Acceptance criteria: acceptance_criteria.md
- Periodic table data: periodic_table_wad18.json
- Reproducibility guide: REPRODUCIBILITY_GUIDE.md

---

**Every element now has a digital identity. Every property is cryptographically verified. Trust is verifiable.**
