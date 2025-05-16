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

bool catString(FILE *fic, char **str1, char *str2, size_t n)
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
    if (fic)
    {
        if (fprintf(fic, "%s", *str1) < 0)
        {
            return false;
        }
    }

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

        if (!catString(NULL, &output, ptr1, (ptr2 - ptr1)))
        {
            return false;
        }
        if (!catString(NULL, &output, REPLACE_TAG, REPLACE_TAG_LEN))
        {
            return false;
        }
        ptr1 = ptr2 + TAG_LEN;
    }

    if (!catString(NULL, &output, ptr1, strlen(ptr1)))
    {
        return false;
    }

    return true;
}
bool tagValide(const char *tag)
{

    if (!tag || !tag[0])
    {
        return false;
    }

    for (int i = 0; i < tag[i]; i++)
    {
        if (!isalnum(tag[i]) && tag[i] != '_')
        {
            return false;
        }
    }

    return true;
}

bool formateTAGmySend(FILE *ficFormater, const char *line)
{
    char *ptr1 = NULL;
    char *ptr2 = NULL;
    char *ptr3 = NULL;
    char *output = NULL;
    char *tag = NULL;

    // ptr1 point sur le début de la ligne
    ptr1 = (char *)line;

    // tant que on trouve un START_TAG dans la ligne  ptr1 on point le Début du START_TAG dans ptr2
    while (ptr2 = strstr(ptr1, START_TAG))
    {
        // on concat dans output la chaîne de ptr1 jusqu’à START_TAG
        if (!catString(ficFormater, &output, ptr1, ptr2 - ptr1))
        {
            return false;
        }
        // on déplace ptr2 pour pointer a la fin du START_TAG
        ptr2 += START_TAG_LEN;

        // on cherche si il ya un END_TAG apres dans ptr2 et on point dessus le début du END_TAG avec ptr3
        if (ptr3 = strstr(ptr2, END_TAG))
        {
            // on copie l'identifiant du TAG dans tag
            if (!catString(NULL, &tag, ptr2, ptr3 - ptr2))
            {
                return false;
            }

            // on verify si le TAG est valide
            if (tagValide(tag))
            {
                // concat [toto] a la place du TAG
                if (!catString(ficFormater, &output, REPLACE_TAG, REPLACE_TAG_INVALID_LEN))
                {
                    return false;
                }
                ptr1 = ptr3 + END_TAG_LEN;
            }
            else // si tag est invalide on ecrit INVALID_TAG et on cherche un START TAG dans le TAG
            {
                if (!catString(ficFormater, &output, REPLACE_TAG_INVALID, REPLACE_TAG_INVALID_LEN))
                {
                    return false;
                }
                ptr1 = ptr2;
                continue;
            }
        }
        else
        {
            // si il n'y a pas de TAG_END apres le START_TAG on remplace START_TAG PAR [TAG_INVALID]
            if (!catString(ficFormater, &output, REPLACE_TAG_INVALID, REPLACE_TAG_INVALID_LEN))
            {
                return false;
            }
            // on fait pointer ptr1 sur le reste de la ligne
            ptr1 = ptr2;
            break;
        }
    }
    // si il ya un END_TAG dans ptr1 sans START_TAG  on pointe dessus avec ptr3
    while (ptr3 = strstr(ptr1, END_TAG))
    {
        // on concat INVALID_TAG a la place
        if (!catString(ficFormater, &output, REPLACE_TAG_INVALID, REPLACE_TAG_INVALID_LEN))
        {
            return false;
        }

        // on fait pointer ptr1 sur le reste de la ligne
        ptr1 = ptr3 + END_TAG_LEN;
        // on continue de chercher des END_TAG dans ptr1 jusqua que ptr3 = NULL
    }
    // on concat  la ligne pointer par ptr1 si pas de START_TAG trouvée ou  de END_START seul
    if (!catString(ficFormater, &output, ptr1, strlen(ptr1)))
    {
        return false;
    }

    free(output);
    return true;
}
