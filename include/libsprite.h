
/* --------------------------------------------------------------------------------------
 *	Program:		PBMToSpriteConverter
 *	Purpose:		Converting from image format to sprite.
 *	Author(s):		Shaun Karran
 *	Created:		November 2014
 * ----------------------------------------------------------------------------------- */

#ifndef _LIBSPRITE_H_
#define _LIBSPRITE_H_

/* Includes -------------------------------------------------------------------------- */
#include <stdio.h>
#include <string.h>

#include "libnetpbm.h"

/* Defines --------------------------------------------------------------------------- */

/* Function Declarations ------------------------------------------------------------- */
char write_sprite(char *file_name, struct Image *image);

char read_sprite(char *file_name, struct Image *image);

/* Helper Funtions ------------------------------------------------------------------- */
static void write_ppm_sprite(FILE *file, struct Image *image);

static void write_pgm_sprite(FILE *file, struct Image *image);

static void write_pbm_sprite(FILE *file, struct Image *image);

static unsigned int rgb888_to_rgb565(char r, char g, char b);

#endif /* _LIBSPRITE_H_ */
