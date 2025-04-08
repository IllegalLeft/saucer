#include <stdio.h>
#include <string.h>
#include <unistd.h>


struct sauce {
    char id[6];
    char version[3];
    char title[36];
    char author[21];
    char group[21];
    char date[9];
    unsigned long filesize;
    unsigned char datatype;
    unsigned char filetype;
    unsigned short tinfo1;
    unsigned short tinfo2;
    unsigned short tinfo3;
    unsigned short tinfo4;
    unsigned char comments;
    unsigned char tflags;
    char tinfos[23];

} ansi;

int main(int argc, char *argv[])
{
    FILE *fp;

    //char sauce[128];

    // open file
    if (argc != 2) {
        printf("Usage: saucer filename\n");
        return 1;
    }
    if ((fp = fopen(argv[1], "rb")) == NULL) {
        printf("%s cannot be opened.\n", argv[1]);
        return 1;
    }

    // move to start of what would be the SAUCE record
    fseek(fp, -128, SEEK_END);
    // get the SAUCE record
    fscanf(fp, "%5c", ansi.id);

    // is this SAUCE?
    if (strcmp(ansi.id, "SAUCE") != 0) {
        // this ain't no SAUCE
        printf("Not SAUCEd.\n");
        fclose(fp);
        return 2;
    }
    // read rest of the SAUCE
    fscanf(fp, "%2c", ansi.version);
    fscanf(fp, "%35c", ansi.title);
    fscanf(fp, "%20c", ansi.author);
    fscanf(fp, "%20c", ansi.group);
    fscanf(fp, "%8c", ansi.date);

    unsigned char buff[4];
    // read filesize
    fread(buff, 4, 1, fp);
    ansi.filesize = (buff[3] << (3*8)) + (buff[2] << (2*8)) + (buff[1]<<8) + buff[0];
    // read datatype
    fread(buff, 1, 1, fp);
    ansi.datatype = buff[0];
    // read filetype
    fread(buff, 1, 1, fp);
    ansi.filetype = buff[0];
    // read tinfo1
    fread(buff, 2, 1, fp);
    ansi.tinfo1 = (buff[1]<<8) + buff[0];
    // read tinfo2
    fread(buff, 2, 1, fp);
    ansi.tinfo2 = (buff[1]<<8) + buff[0];
    // read tinfo3
    fread(buff, 2, 1, fp);
    ansi.tinfo3 = (buff[1]<<8) + buff[0];
    // read tinfo4
    fread(buff, 2, 1, fp);
    ansi.tinfo4 = (buff[1]<<8) + buff[0];
    // read comments
    fread(buff, 1, 1, fp);
    ansi.comments = buff[0];
    // read tflags
    fread(buff, 1, 1, fp);
    ansi.tflags = buff[0];
    // read tinfos
    fscanf(fp, "%22c", ansi.tinfos);

    fclose(fp);


    // is this ANSi?
    if (ansi.datatype != 1) {
        printf("Not Character datatype.\n");
        return 2;
    }
    if (ansi.filetype != 1) {
        printf("Not ANSi.\n");
        return 2;
    }
    // is this DOS font?
    if (strstr(ansi.tinfos, "IBM") == NULL) {
        printf("Not an IBM font.\n");
        return 2;
    }
    // is this 8/9px?
    if (((ansi.tflags>>1) & 3) == 2) {
        printf("9\n");
    }
    else if (((ansi.tflags>>1) & 3) == 1) {
        printf("8\n");
    }

    return 0;
}
