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

    char *comment;

};


#define DTYPE_BUFF_LEN  10


int datatypestr(int datatype, char **str);

int readsauce(FILE *fp, struct saucerecord *sauce);

int readcomnt(FILE *fp, char **comnt, int lines);

int printsaucefield(struct saucerecord *sauce, char *field, int humanreadable);

