#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "headers/getLine.h"



///  Lecture sécurisée d'une ligne avec gestion dynamique et contrôle UTF-8
ssize_t my_getline(char **lineptr, size_t *n, FILE *stream) {
    if (!lineptr || !n || !stream) return -1;

    // Allocation initiale si nécessaire
    if (*lineptr == NULL) {
        *n = 128;
        *lineptr = malloc(*n);
        if (!*lineptr) return -1;
    }

    size_t pos = 0;

    while (1) {
        // Lecture dans le tampon à partir de pos
        if (fgets(*lineptr + pos, *n - pos, stream) == NULL) {
            return (pos == 0) ? -1 : (ssize_t)pos;
        }

        // Mesurer manuellement la longueur ajoutée
        size_t lus = 0;
        while ((*lineptr)[pos + lus] != '\0') lus++;

        pos += lus;

        // Si un \n a été lu, on termine
        if (pos > 0 && (*lineptr)[pos - 1] == '\n') {
            break;
        }

        // Sinon, réallocation
        size_t new_size = (*n) * 2;
        char *new_ptr = realloc(*lineptr, new_size);
        if (!new_ptr) {
            free(*lineptr);
            *lineptr = NULL;
            return -1;
        }

        *lineptr = new_ptr;
        *n = new_size;
    }
   
    return (ssize_t)pos;
}
