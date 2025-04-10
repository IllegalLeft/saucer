#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "sauce.h"


int main(int argc, char *argv[]) {
    FILE *fp;
    struct saucerecord sauce;

    int c;
    int viewmode = 0;
    int humanreadable = 0;
    char *field;    // specific field to view

    while ((c = getopt(argc, argv, "f:Hh")) != -1) {
        switch (c) {
            case 'H':
                humanreadable = 1;
                break;
            case 'h':
                fprintf(stderr, "Usage: saucer [-v field] filename\n");
                return 0;
            case 'f':
                viewmode = 1;
                field = optarg;
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

    if (readsauce(fp, &sauce) > 0){
        // no SAUCE found
        fclose(fp);
        return 0;
    }
    fclose(fp);

    if (viewmode == 0) {
        // print some basic SAUCE info
        printf("Title: %s\n", sauce.title);
        printf("Author: %s\n", sauce.author);
        printf("Group: %s\n", sauce.group);
    }
    else {
        printsaucefield(&sauce, field, humanreadable);
    }

    return 0;
}
