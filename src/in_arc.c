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

/** 
 * @defgroup input Input functions
 * Implementation of various functions for reading data.
 *
 * @author Konrad Rieck (konrad@mlsec.org)
 * @{
 */

#include "config.h"
#include "common.h"
#include "util.h"

#ifdef ENABLE_LIBARCHIVE

#include <archive.h>
#include <archive_entry.h>
#include "in_arc.h"

/* Local variables */
static struct archive *a = NULL;

/**
 * Opens an archive for reading files. 
 * @param name Archive name
 * @return number of regular files
 */
int input_open_arc(char *name) 
{
    assert(name);    
    struct archive_entry *entry;

    a = archive_read_new();
    archive_read_support_compression_all(a);
    archive_read_support_format_all(a);
    int r = archive_read_open_filename(a, name, 4096);
    if (r != 0) {
        error("%s", archive_error_string(a));
        return 0;
    }

    /* Count regular files in archive */
    int num_files = 0;
    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        const struct stat *s = archive_entry_stat(entry);
        if (S_ISREG(s->st_mode))
            num_files++;
        archive_read_data_skip(a);
    }
    archive_read_finish(a);
    
    /* Open file again */
    a = archive_read_new();
    archive_read_support_compression_all(a);
    archive_read_support_format_all(a);
    archive_read_open_filename(a, name, 4096);
    return num_files;
}

/**
 * Reads a block of files into memory.
 * @param sa Sally configuration
 * @param data Array for file data
 * @param sizes Array of file sizes
 * @param names Array of file names
 * @param len Length of block
 * @return number of read files
 */
int input_read_arc(char **data, int *sizes, char **names, int len)
{
    assert(data && sizes && names);
    struct archive_entry *entry;
    int i, j = 0;
    
    /* Load block of files (no OpenMP here)*/
    for (i = 0; i < len; i++) {    
        /* Perform reading of archive */
        archive_read_next_header(a, &entry);
        const struct stat *s = archive_entry_stat(entry);
        if (!S_ISREG(s->st_mode)) {
            archive_read_data_skip(a);
            continue;
        }
        
        /* Add entry */
        data[j] = malloc(s->st_size * sizeof(char));
        archive_read_data(a, data[j], s->st_size);
        names[j] = strdup(archive_entry_pathname(entry));
        sizes[j] = s->st_size;
        j++;
    }
    
    return j;
}

/**
 * Closes an open directory.
 */
void input_close_arc()
{
    archive_read_finish(a);
}

#endif

/** @} */
