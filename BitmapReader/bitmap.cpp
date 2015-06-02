#include "bitmap.h"

void read_bitmap(FILE *bitmapfl, BmpFile *bmp)
{

    //fread(&bmp->header, 14, 1, bitmapfl);
    fseek(bitmapfl, 14, SEEK_CUR);
        
    if (fread(&bmp->info, sizeof(BmpImageInfo), 1, bitmapfl) != 1)
    {
        return;
    }

    if (bmp->info.numColors > 0)
    {
        bmp->palette = (Rgb*)malloc(sizeof(Rgb) * bmp->info.numColors);
        if (fread(bmp->palette, sizeof(Rgb), bmp->info.numColors, bitmapfl) != bmp->info.numColors)
        {
            return;
        }
    }

    bmp->pixels = (Rgb*)malloc(sizeof(Rgb) * bmp->info.width * bmp->info.height);
    bmp->yuv = (unsigned char*)malloc(sizeof(unsigned char) * bmp->info.width * bmp->info.height * 3 / 2);

    if (fread(bmp->pixels, sizeof(Rgb), bmp->info.width * bmp->info.height, bitmapfl) !=
        bmp->info.width * bmp->info.height)
    {
        return;
    }

    unsigned char *bufY = bmp->yuv;
    unsigned char *bufU = bufY + bmp->info.width * bmp->info.height;
    unsigned char *bufV = bufU + bmp->info.width * bmp->info.height / 4;
    unsigned char y, u, v;

    for (unsigned int j = 0; j < bmp->info.height; j++)
    {
        Rgb *tmpRGB = bmp->pixels + bmp->info.width * (bmp->info.height - 1 - j);
        for (unsigned int i = 0; i < bmp->info.width; i++)
        {
            y = (unsigned char)((66 * tmpRGB->red + 129 * tmpRGB->green + 25 * tmpRGB->blue + 128) >> 8) + 16;
            u = (unsigned char)((-38 * tmpRGB->red - 74 * tmpRGB->green + 112 * tmpRGB->blue + 128) >> 8) + 128;
            v = (unsigned char)((112 * tmpRGB->red - 94 * tmpRGB->green - 18 * tmpRGB->blue + 128) >> 8) + 128;
            tmpRGB++;
            *(bufY++) = MAX(0, MIN(y, 255));
            if ((j % 2 == 0) && (i % 2 == 0))
            {
                *(bufU++) = MAX(0, MIN(u, 255));
            }
            else
            {
                if (i % 2 == 0)
                {
                    *(bufV++) = MAX(0, MIN(v, 255));
                }
            }
        }
    }
}

void clear_bitmap(BmpFile *bmp)
{
    if (bmp->palette)
    {
        free(bmp->palette);
        bmp->palette = NULL;
    }
    if (bmp->pixels)
    {
        free(bmp->pixels);
        bmp->pixels = NULL;
    }
    if (bmp->yuv)
    {
        free(bmp->yuv);
        bmp->yuv = NULL;
    }
}