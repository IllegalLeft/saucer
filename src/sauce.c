#include <stdio.h>
#include <string.h>

#include "sauce.h"


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
        fclose(fp);
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


int printsaucefield(struct saucerecord *sauce, char *field) {
    if (strstr("id", field) != NULL)
        printf("%s\n", sauce->id);
    else if (strstr("version", field) != NULL)
        printf("%s\n", sauce->version);
    else if (strstr("title", field) != NULL)
        printf("%s\n", sauce->title);
    else if (strstr("author", field) != NULL)
        printf("%s\n", sauce->author);
    else if (strstr("group", field) != NULL)
        printf("%s\n", sauce->group);
    else if (strstr("date", field) != NULL)
        printf("%s\n", sauce->date);
    else if (strstr("filesize", field) != NULL)
        printf("%ld\n", sauce->filesize);
    else if (strstr("datatype", field) != NULL)
        printf("%d\n", sauce->datatype);
    else if (strstr("filetype", field) != NULL)
        printf("%d\n", sauce->filetype);
    else if (strstr("tinfo1", field) != NULL)
        printf("%hd\n", sauce->tinfo1);
    else if (strstr("tinfo2", field) != NULL)
        printf("%hd\n", sauce->tinfo2);
    else if (strstr("tinfo3", field) != NULL)
        printf("%hd\n", sauce->tinfo3);
    else if (strstr("comments", field) != NULL)
        printf("%d\n", sauce->comments);
    else if (strstr("tflags", field) != NULL)
        printf("%d\n", sauce->tflags);
    else if (strstr("tinfos", field) != NULL)
        printf("%s\n", sauce->tinfos);

    return 0;
}
