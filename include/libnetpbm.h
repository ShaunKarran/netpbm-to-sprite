
/* --------------------------------------------------------------------------------------
 *	Program:		PBMToSpriteConverter
 *	Purpose:		File input/output functions.
 *	Author(s):		Shaun Karran
 *	Created:		November 2014
 * ----------------------------------------------------------------------------------- */

#ifndef _LIBNETPBM_H_
#define _LIBNETPBM_H_

/* Includes -------------------------------------------------------------------------- */
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Type Definitions ------------------------------------------------------------------ */
struct Image
{
	char     	 name[64];
	char 	 	 format; /* File format (4 = pbm, 5 = pgm, 6 = ppm). */
	unsigned int width;
	unsigned int height;
	unsigned int depth;
	unsigned int size;  /* In bytes. */
	char  		 *data;
};

/* Defines --------------------------------------------------------------------------- */
#define PBM '4'
#define PGM '5'
#define PPM '6'

/* Function Declarations ------------------------------------------------------------- */
char read_netpbm(char *file_name, struct Image *image);

char write_netpbm(char *file_name, struct Image *image);

/* Helper Funtions ------------------------------------------------------------------- */
static void skip_comments(FILE *file);

static void move_to_next_line(FILE *file);

static void remove_extension(char *file_name);

#endif /* _LIBNETPBM_H_ */
