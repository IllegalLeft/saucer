#include <stdio.h>
#include <string.h>

#include "sauce.h"


int datatypestr(int datatype, char **str) {
    switch (datatype) {
        case 0:
            *str = "None";
            break;
        case 1:
            *str = "Character";
            break;
        case 2:
            *str = "Bitmap";
            break;
        case 3:
            *str = "Vector";
            break;
        case 4:
            *str = "Audio";
            break;
        case 5:
            *str = "BinaryText";
            break;
        case 6:
            *str = "XBin";
            break;
        case 7:
            *str = "Archive";
            break;
        case 8:
            *str = "Executable";
            break;
        default:
            break;
    }

    return 0;
}

int readsauce(FILE *fp, struct saucerecord *sauce) {
    unsigned char buff[4];

    // move to start of what would be the SAUCE record
    fseek(fp, -128, SEEK_END);
    // get the SAUCE record
    fscanf(fp, "%5c", sauce->id);

    // is this SAUCE?
    if (strcmp(sauce->id, "SAUCE") != 0) {
        // this ain't no SAUCE
        printf("No SAUCE found.\n");
        return 1;
    }
    // read rest of the SAUCE
    fscanf(fp, "%2c", sauce->version);
    fscanf(fp, "%35c", sauce->title);
    fscanf(fp, "%20c", sauce->author);
    fscanf(fp, "%20c", sauce->group);
    fscanf(fp, "%8c", sauce->date);

    // read filesize
    fread(buff, 4, 1, fp);
    sauce->filesize = (buff[3] << (3*8)) + (buff[2] << (2*8)) + (buff[1]<<8) + buff[0];
    // read datatype
    fread(buff, 1, 1, fp);
    sauce->datatype = buff[0];
    // read filetype
    fread(buff, 1, 1, fp);
    sauce->filetype = buff[0];
    // read tinfo1
    fread(buff, 2, 1, fp);
    sauce->tinfo1 = (buff[1]<<8) + buff[0];
    // read tinfo2
    fread(buff, 2, 1, fp);
    sauce->tinfo2 = (buff[1]<<8) + buff[0];
    // read tinfo3
    fread(buff, 2, 1, fp);
    sauce->tinfo3 = (buff[1]<<8) + buff[0];
    // read tinfo4
    fread(buff, 2, 1, fp);
    sauce->tinfo4 = (buff[1]<<8) + buff[0];
    // read comments
    fread(buff, 1, 1, fp);
    sauce->comments = buff[0];
    // read tflags
    fread(buff, 1, 1, fp);
    sauce->tflags = buff[0];
    // read tinfos
    fscanf(fp, "%22c", sauce->tinfos);

    return 0;
}

int readcomnt(FILE *fp, char **comnt, int lines) {
    char id[6];
    char linebuff[65];
    linebuff[64] = '\0'; // null-terminate the buffer

    fseek(fp, -5 - (64 * lines) - 128, SEEK_END);

    // read ID
    fscanf(fp, "%5c", id);
    // is this a COMNT block?
    if (strncmp(id, "COMNT", 5) != 0) {
        // this isn't a COMNT block
        fprintf(stderr, "COMNT block not found.\n");
        //return 1;
    }
    for (int i = 0; i < lines; i++) {
        // read line
        fscanf(fp, "%64c", linebuff);
        strcat(*comnt, linebuff);
    }

    return 0;
}

int printsaucefield(struct saucerecord *sauce, char *field, int humanreadable) {
    if (strcmp("id", field) == 0)
        printf("%s\n", sauce->id);
    else if (strcmp("version", field) == 0)
        printf("%s\n", sauce->version);
    else if (strcmp("title", field) == 0)
        printf("%s\n", sauce->title);
    else if (strcmp("author", field) == 0)
        printf("%s\n", sauce->author);
    else if (strcmp("group", field) == 0)
        printf("%s\n", sauce->group);
    else if (strcmp("date", field) == 0)
        printf("%s\n", sauce->date);
    else if (strcmp("filesize", field) == 0)
        printf("%ld\n", sauce->filesize);
    else if (strcmp("datatype", field) == 0)
        if (humanreadable) {
            char *hbuff;
            datatypestr(sauce->datatype, &hbuff);
            printf("%s\n", hbuff);
        }
        else
            printf("%d\n", sauce->datatype);
    else if (strcmp("filetype", field) == 0)
        printf("%d\n", sauce->filetype);
    else if (strcmp("tinfo1", field) == 0)
        printf("%hd\n", sauce->tinfo1);
    else if (strcmp("tinfo2", field) == 0)
        printf("%hd\n", sauce->tinfo2);
    else if (strcmp("tinfo3", field) == 0)
        printf("%hd\n", sauce->tinfo3);
    else if (strcmp("comments", field) == 0)
        printf("%d\n", sauce->comments);
    else if (strcmp("comment", field) == 0)
        printf("%s\n", sauce->comment);
    else if (strcmp("tflags", field) == 0)
        printf("%d\n", sauce->tflags);
    else if (strcmp("tinfos", field) == 0)
        printf("%s\n", sauce->tinfos);

    return 0;
}
