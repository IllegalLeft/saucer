struct saucerecord {
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

};

int readsauce(FILE *fp, struct saucerecord *sauce);

int printsaucefield(struct saucerecord *sauce, char *field);
