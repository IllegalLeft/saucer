#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "sauce.h"


int main(int argc, char *argv[])
{
    FILE *fp;
    struct saucerecord sauce;

    int c;
    int viewmode = 0;
    char *vfield;

    while ((c = getopt(argc, argv, "v:h")) != -1) {
        switch (c) {
            case 'h':
                fprintf(stderr, "Usage: saucer [-v field] filename\n");
                return 0;
            case 'v':
                viewmode = 1;
                vfield = optarg;
                break;
            case '?':
                fprintf(stderr, "Error, I think.\n");
                return 1;
            default:
                exit(1);
                break;
        }
    }

    // do we have a filename to work with?
    if (argv[optind] == NULL) {
        fprintf(stderr, "Usage: saucer [-v field] filename\n");
        return 1;
    }
    if ((fp = fopen(argv[optind], "rb")) == NULL) {
        fprintf(stderr, "Error: file %s cannot be opened.\n", argv[1]);
        return 1;
    }

    // move to start of what would be the SAUCE record
    fseek(fp, -128, SEEK_END);
    // get the SAUCE record
    fscanf(fp, "%5c", sauce.id);

    // is this SAUCE?
    if (strcmp(sauce.id, "SAUCE") != 0) {
        // this ain't no SAUCE
        printf("No SAUCE found.\n");
        fclose(fp);
        return 0;
    }
    // read rest of the SAUCE
    fscanf(fp, "%2c", sauce.version);
    fscanf(fp, "%35c", sauce.title);
    fscanf(fp, "%20c", sauce.author);
    fscanf(fp, "%20c", sauce.group);
    fscanf(fp, "%8c", sauce.date);

    unsigned char buff[4];
    // read filesize
    fread(buff, 4, 1, fp);
    sauce.filesize = (buff[3] << (3*8)) + (buff[2] << (2*8)) + (buff[1]<<8) + buff[0];
    // read datatype
    fread(buff, 1, 1, fp);
    sauce.datatype = buff[0];
    // read filetype
    fread(buff, 1, 1, fp);
    sauce.filetype = buff[0];
    // read tinfo1
    fread(buff, 2, 1, fp);
    sauce.tinfo1 = (buff[1]<<8) + buff[0];
    // read tinfo2
    fread(buff, 2, 1, fp);
    sauce.tinfo2 = (buff[1]<<8) + buff[0];
    // read tinfo3
    fread(buff, 2, 1, fp);
    sauce.tinfo3 = (buff[1]<<8) + buff[0];
    // read tinfo4
    fread(buff, 2, 1, fp);
    sauce.tinfo4 = (buff[1]<<8) + buff[0];
    // read comments
    fread(buff, 1, 1, fp);
    sauce.comments = buff[0];
    // read tflags
    fread(buff, 1, 1, fp);
    sauce.tflags = buff[0];
    // read tinfos
    fscanf(fp, "%22c", sauce.tinfos);

    fclose(fp);

    if (viewmode == 0) {
        // print some basic SAUCE info
        printf("Title: %s\n", sauce.title);
        printf("Author: %s\n", sauce.author);
        printf("Group: %s\n", sauce.group);
    }
    else {
        if (strstr("id", vfield) != NULL)
            printf("%s\n", sauce.id);
        else if (strstr("version", vfield) != NULL)
            printf("%s\n", sauce.version);
        else if (strstr("title", vfield) != NULL)
            printf("%s\n", sauce.title);
        else if (strstr("author", vfield) != NULL)
            printf("%s\n", sauce.author);
        else if (strstr("group", vfield) != NULL)
            printf("%s\n", sauce.group);
        else if (strstr("date", vfield) != NULL)
            printf("%s\n", sauce.date);
        else if (strstr("filesize", vfield) != NULL)
            printf("%ld\n", sauce.filesize);
        else if (strstr("datatype", vfield) != NULL)
            printf("%d\n", sauce.datatype);
        else if (strstr("filetype", vfield) != NULL)
            printf("%d\n", sauce.filetype);
        else if (strstr("tinfo1", vfield) != NULL)
            printf("%hd\n", sauce.tinfo1);
        else if (strstr("tinfo2", vfield) != NULL)
            printf("%hd\n", sauce.tinfo2);
        else if (strstr("tinfo3", vfield) != NULL)
            printf("%hd\n", sauce.tinfo3);
        else if (strstr("comments", vfield) != NULL)
            printf("%d\n", sauce.comments);
        else if (strstr("tflags", vfield) != NULL)
            printf("%d\n", sauce.tflags);
        else if (strstr("tinfos", vfield) != NULL)
            printf("%s\n", sauce.tinfos);
    }

    return 0;
}
