// -*- coding: utf-8 -*-

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#include "headers/fct.h"

void videBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

void activeAffichageUTF8DansLaConsole(bool activerUTF8pourLaSaisie)
{

    SetConsoleOutputCP(CP_UTF8); // Force l'affichage correct des caractères UTF-8

    if (activerUTF8pourLaSaisie)
    {
        SetConsoleCP(CP_UTF8); // UTF8 Pour la saisie
    }
}

bool catString(char **str1, char *str2, size_t n)
{

    *str1 = (char *)realloc(*str1, n + 1);
    if (*str1 == NULL)
    {
        printf("ERREUR realloc\n");
        return false;
    }

    *str1[0] = '\0';
    if (!strncat(*str1, str2, n))
    {
        printf("Erreur strncat de catString sur str1 = %s, str2 = %s, n = %d\n", *str1, str2, n);
        return false;
    }

    printf("%s", *str1);
    return true;
}

bool formateTAG(const char *line)
{
    char *ptr1 = NULL;
    char *ptr2 = NULL;
    char *output = NULL;

    if (!line)
    {
        return false;
    }

    ptr1 = (char *)line;

    while (ptr2 = strstr(ptr1, TAG))
    {

        if (!catString(&output, ptr1, (ptr2 - ptr1)))
        {
            return false;
        }
        if (!catString(&output, REPLACE_TAG, REPLACE_TAG_LEN))
        {
            return false;
        }
        ptr1 = ptr2 + TAG_LEN;
    }

    if (!catString(&output, ptr1, strlen(ptr1)))
    {
        return false;
    }

    return true;
}
