
/* --------------------------------------------------------------------------------------
 *	Program:		PBMToSpriteConverter
 *	Purpose:		File input/output functions.
 *	Author(s):		Shaun Karran
 *	Created:		November 2014
 * ----------------------------------------------------------------------------------- */

/* Includes -------------------------------------------------------------------------- */
#include "libnetpbm.h"

/* Function Definitions -------------------------------------------------------------- */
char read_netpbm(char *file_name, struct Image *image)
{
	FILE 	*file;
	size_t  read_result;

	file = fopen(file_name, "rb");
	if (file == NULL) {
		perror("fopen");
		return 0;
	}

	fscanf(file, "P%c ", &image->format); /* Read the format number and skip the new line. */

	/* This is needed becasue GIMP puts a comment between the magic number and dimensions. */
	skip_comments(file);

	switch (image->format) {
		case PBM: /* Black & white */
			fscanf(file, "%u %u", &(image->width), &(image->height));
			image->size = ((image->width - 1) / 8 + 1) * image->height; /* 1 bit per pixel. */
			break;

		case PGM: /* Greyscale */
			fscanf(file, "%u %u %u", &(image->width), &(image->height), &(image->depth));
			image->size = image->width * image->height;
			break;

		case PPM: /* Colour */
			fscanf(file, "%u %u %u", &(image->width), &(image->height), &(image->depth));
			image->size = image->width * image->height * 3; /* 3 bytes per pixel. */
			break;

		default:
			printf("read_netpbm: Invalid image format.\n");
			return 0;
	}

	fgetc(file); /* Move past new line at end of header. */

	/* Allocate enough memory for the image data to be read into. */
	image->data = malloc(sizeof(char) * image->size);
	if (image->data == NULL) {
		perror("malloc");
		return 0;
	}

	/* Read the data into image->data. */
	read_result = fread(image->data, sizeof(char), image->size, file);
	if (read_result != image->size) {
		printf("fread: Failed to read image data.\n");
		return 0;
	}

	strcpy(image->name, basename(file_name));
	remove_extension(image->name);

	fclose(file);
	return 1;
}

char write_netpbm(char *file_name, struct Image *image)
{
	FILE* file;

	file = fopen(file_name, "wb");
	if (file == NULL) {
		perror("fopen");
		return 0;
	}

	/* Header format is different for PBM. */
	if (image->format == PBM) {
		fprintf(file, "P%c %d %d\n", image->format, image->width, image->height);
	} else {
		fprintf(file, "P%c %d %d %d\n", image->format, image->width,
									   image->height, image->depth);
	}

	/* Write image data to file. */
	fwrite(image->data, sizeof(char), image->size, file);

	fclose(file);
	return 1;
}

/* Helper Funtions ------------------------------------------------------------------- */
static void skip_comments(FILE *file)
{
	while (fgetc(file) == '#') /* Check for all comment lines. */
	{
		move_to_next_line(file);
	}
	fseek(file, -1, SEEK_CUR); /* fgetc call moves file pointer, so move back by 1. */
}

static void move_to_next_line(FILE *file)
{
	while (fgetc(file) != '\n') { ; } /* Move past the next \n character. */
}

static void remove_extension(char *file_name)
{
	int period_index;
	int str_lenth = strlen(file_name);

	for (int i = 0; i < str_lenth; i++) {
		if (file_name[i] == '.') {
			period_index = i;
		}
	}

	file_name[period_index] = '\0';
}
