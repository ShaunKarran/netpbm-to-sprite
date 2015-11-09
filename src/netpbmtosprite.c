
/* --------------------------------------------------------------------------------------
 *  Program:        PBMToSpriteConverter
 *  Purpose:        Convert a pbm image into the text version of the data in
 *                  the format for the teensy graphics lib.
 *  Author(s):      Shaun Karran
 *  Created:        November 2014
 * ----------------------------------------------------------------------------------- */

/* Includes -------------------------------------------------------------------------- */
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>

#include "libnetpbm.h"
#include "libsprite.h"

/* Function Definitions -------------------------------------------------------------- */

int main(int argc, char *argv[])
{
    struct Image image;

    if (argc != 3) {
        printf("\nInvalid arguments. Usage: netpbm_to_sprite <inputfile> <outputfile>\n\n");
        exit(EXIT_FAILURE);
    }

    printf("\nReading image %s\n", basename(argv[1]));
    
    if (read_netpbm(argv[1], &image) == 0) {
        exit(EXIT_FAILURE);
    }

    printf("\nWriting sprite %s\n", basename(argv[2]));

    if (write_sprite(argv[2], &image) == 0) {
     exit(EXIT_FAILURE);
    }

    printf("\nConversion of %s completed successfully.\n\n", basename(argv[1]));

    exit(EXIT_SUCCESS);
}
