
/* --------------------------------------------------------------------------------------
 *  Program:        PBMToSpriteConverter
 *  Purpose:        Converting from image format to sprite.
 *  Author(s):      Shaun Karran
 *  Created:        November 2014
 * ----------------------------------------------------------------------------------- */

/* Includes -------------------------------------------------------------------------- */
#include "libsprite.h"

/* Function Definitions -------------------------------------------------------------- */
char write_sprite(char *file_name, struct Image *image)
{
    FILE *file;

    file = fopen(file_name, "w");
    if (file == NULL) {
        perror("fopen");
        return 0;
    }

    switch (image->format) {
        case PBM:
            write_pbm_sprite(file, image);
            break;

        case PGM:
            write_pgm_sprite(file, image);
            break;

        case PPM:
            write_ppm_sprite(file, image);
            break;

        default:
            printf("write_sprite: Invalid image format.\n");
            return 0;
    }

    fclose(file);
    return 1;
}

char read_sprite(char *file_name, struct Image *image)
{
    return 0;
}

/* Helper Funtions ------------------------------------------------------------------- */
static void write_ppm_sprite(FILE *file, struct Image *image)
{
    char           r, g, b;
    unsigned short colour;

    fprintf(file, "static const uint16_t sprite_%s[] = \n{\n\t", image->name);
    fprintf(file, "0x%04X, 0x%04X,\n", image->width, image->height);

    for (int i = 0; i < image->height; i++) {
        fprintf(file, "\t");

        for (int j = 0; j < image->width * 3; j += 3) { /* 3 bytes per pixel */
            r = image->data[i * (image->width * 3) + j];
            g = image->data[i * (image->width * 3) + j + 1];
            b = image->data[i * (image->width * 3) + j + 2];
            colour = rgb888_to_rgb565(r, g, b);

            fprintf(file, "0x%04hX, ", colour);
        }
        fprintf(file, "\n");
    }
    fprintf(file, "};\n");
}

static void write_pgm_sprite(FILE *file, struct Image *image)
{
    fprintf(file, "static const uint8_t sprite_%s[] = \n{\n\t", image->name);
    fprintf(file, "0x%02X, 0x%02X,\n", image->width, image->height);

    for (int i = 0; i < image->height; i++) {
        fprintf(file, "\t");

        for (int j = 0; j < image->width; j++) {
            fprintf(file, "0x%02hhX, ", image->data[i * image->width + j]);
        }
        fprintf(file, "\n");
    }
    fprintf(file, "};\n");
}

static void write_pbm_sprite(FILE *file, struct Image *image)
{
    char width = (image->width - 1) / 8 + 1;

    fprintf(file, "static const uint8_t sprite_%s[] = \n{\n\t", image->name);
    fprintf(file, "0x%02X, 0x%02X,\n", width, image->height);

    for (int i = 0; i < image->height; i++) {
        fprintf(file, "\t");

        for (int j = 0; j < width; j++) {
            fprintf(file, "0x%02hhX, ", image->data[i * width + j]);
        }
        fprintf(file, "\n");
    }
    fprintf(file, "};\n");
}

static unsigned int rgb888_to_rgb565(char r, char g, char b)
{
    unsigned int colour = 0x0000;

    colour  = ((r >> 3) << 11) & 0xF800;
    colour |= ((g >> 2) << 5)  & 0x07E0;
    colour |= ((b >> 3) << 0)  & 0x001F;

    return colour;
}
