#ifndef GET_LINE_11052025_003752_mySend_H
#define GET_LINE_11052025_003752_mySend_H

#include <stdio.h> // FILE, size_t

// Lecture sécurisée d’une ligne depuis un flux,
// - lineptr : pointeur vers le tampon à allouer ou réallouer
// - n       : pointeur vers la taille du tampon
// - stream  : fichier d’entrée
// Retourne : le nombre d’octets lus (ssize_t), ou -1 en cas d’erreur.
ssize_t my_getline(char **lineptr, size_t *n, FILE *stream);
#endif /*GET_LINE_11052025_003752_mySend_H*/