#include "yuv.h"

void write_yuv(BmpFile *bmp)
{
    FILE *yuvfl = fopen("test.yuv", "wb");
    if ((FILE*)NULL != yuvfl)
    {
        fwrite(bmp->yuv, sizeof(unsigned char),
            bmp->info.width * bmp->info.height * 3 / 2, yuvfl);
        fclose(yuvfl);
    }
}