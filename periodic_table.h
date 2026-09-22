#ifndef PERIODIC_TABLE_H
#define PERIODIC_TABLE_H

#include "wad_fixed_point.h"

/* Element properties encoded in WAD18 format */
typedef struct {
    int z;                          /* Atomic number */
    char symbol[3];                 /* Element symbol */
    char name[32];                  /* Element name */
    
    wad18_t atomic_mass;            /* Atomic mass (u) */
    wad18_t ionization_energy;      /* First ionization energy (eV) */
    wad18_t electron_affinity;      /* Electron affinity (eV) */
    wad18_t electronegativity;      /* Electronegativity (Pauling scale) */
    
    wad18_t atomic_radius;          /* Atomic radius (pm) */
    wad18_t density;                /* Density at 300K (g/cm^3) */
    wad18_t melting_point;          /* Melting point (K) */
    wad18_t boiling_point;          /* Boiling point (K) */
    
    uint32_t hash;                  /* Element hash for verification */
    char reference[128];            /* Reference source */
} element_t;

/* Periodic table: all 118 elements */
typedef struct {
    element_t elements[118];
    uint32_t table_hash;            /* Hash of entire table */
    char version[32];               /* Version identifier */
    char timestamp[32];             /* Creation timestamp */
} periodic_table_t;

/* Load/verify periodic table */
periodic_table_t* periodic_table_load(const char *json_file);
bool periodic_table_verify_hash(periodic_table_t *table);
bool element_verify_hash(element_t *elem);

/* Specimen passport */
void element_generate_passport(element_t *elem, char *buffer, size_t len);

#endif
