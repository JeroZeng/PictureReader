#ifndef _BITMAP_H_
#define _BITMAP_H_

#include <stdio.h>
#include <stdlib.h>

#define MAX(a, b) ((a) > (b)) ? (a) : (b)
#define MIN(a, b) ((a) < (b)) ? (a) : (b)

typedef struct BmpHeader
{
    char signature[2];
    unsigned int fileSize;
    unsigned int reserved;
    unsigned int offset;
}BmpHeader;

typedef struct BmpImageInfo
{
    unsigned int headerSize;
    unsigned int width;
    unsigned int height;
    unsigned short planeCount;
    unsigned short bitDepth;
    unsigned int compression;
    unsigned int compressedImageSize;
    unsigned int horizontalResolution;
    unsigned int verticalResolution;
    unsigned int numColors;
    unsigned int importantColors;

}BmpImageInfo;

typedef struct Rgb
{
    unsigned char blue;
    unsigned char green;
    unsigned char red;

}Rgb;

typedef struct BmpFile
{
    BmpHeader header;
    BmpImageInfo info;
    Rgb *palette;
    Rgb *pixels;
    unsigned char *yuv;
}BmpFile;

void read_bitmap(FILE *bitmapfl, BmpFile *bmp);
void clear_bitmap(BmpFile *bmp);

#endif//_BITMAP_H_