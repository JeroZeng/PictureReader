#include<string.h>
#include "bitmap.h"
#include "yuv.h"

int main(int argc, char *argv[])
{
    const char *bmpName = "big.bmp";
    BmpFile bmp;
    memset(&bmp, 0, sizeof(BmpFile));
    FILE *bmpfl = fopen(bmpName, "rb");
    if ((FILE*)NULL == bmpfl)
    {
        printf("Err: Can't open file %s\n", bmpName);
        return -1;
    }
    read_bitmap(bmpfl, &bmp);

    write_yuv(&bmp);

    clear_bitmap(&bmp);
    fclose(bmpfl);
    return 0;
}