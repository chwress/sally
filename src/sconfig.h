/*
 * Sally - A Tool for Embedding Strings in Vector Spaces
 * Copyright (C) 2010 Konrad Rieck (konrad@mlsec.org)
 * --
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 3 of the License, or (at your
 * option) any later version.  This program is distributed without any
 * warranty. See the GNU General Public License for more details. 
 */

#ifndef SCONFIG_H
#define SCONFIG_H

#ifdef HAVE_LIBCONFIG_H
#include <libconfig.h>
#endif


/** 
 * Default configuration. This structure is used to define a default
 * configuration. The type can be determined by first testing for a 
 * string and then for a float argument.
 */
typedef struct
{
    char *group;        /**< Configuration group */
    char *name;         /**< Configuration name */
    int type;           /**< Type of configuration */

    union
    {
        long num;       /**< Integer value */
        double flt;     /**< Float value  */
        char *str;      /**< String */
    } val;
} config_default_t;

/* Functions */
void config_print(config_t *cfg);
void config_check(config_t *cfg);
void config_fprint(FILE *, config_t *cfg);

#endif /* SCONFIG_H */
