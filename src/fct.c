// -*- coding: utf-8 -*-

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <ctype.h>

#include "headers/fct.h"
#include "headers/tagManager.h"

void flushStdinBuffer(void)
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

bool concatString(char **dest, char *src, size_t n)
{
    char *destTmp = NULL;
    if (!*dest)
    {
        *dest = malloc(n + 1);
        if (!*dest)
        {
            printf("catString Erreur malloc\n");
            return false;
        }
        *dest[0] = '\0';
    }
    else
    {
        destTmp = realloc(*dest, strlen(*dest) + n + 1);
        if (destTmp == NULL)
        {
            printf("ERREUR realloc\n");
            return false;
        }
        *dest = destTmp;
    }

    if (!strncat(*dest, src, n))
    {
        printf("Erreur strncat de concatString sur str1 = %s, str2 = %s, n = %d\n", dest, src, n);
        return false;
    }

    return true;
}

bool isgValide(const char *tag)
{
    if (!tag || !tag[0])
    {
        return false;
    }

    for (int i = 0; tag[i]; i++)
    {
        if (!isalnum(tag[i]) && tag[i] != '_')
        {
            return false;
        }
    }

    return true;
}

bool formateTAGmySend(FILE *ficOut, const char *line, const int nLine, tagManager_s *self)
{
    bool resultFonction = false;
    tagManager_s tags;
    tag_s *tagValid = NULL;

    char *ptr1 = NULL;
    char *ptr2 = NULL;
    char *ptr3 = NULL;
    char *output = NULL;
    char *tagId = NULL;

    // ptr1 point sur le début de la ligne
    ptr1 = (char *)line;

    do// tant que il y a un END_TAG dans ptr1 on boucle pour verifier si il ya un START_TAG devant 
    {
        // si il ya un END_TAG dans ptr1 sans START_TAG  on stop
        ptr3 = strstr(ptr1, END_TAG);
        ptr2 = strstr(ptr1, START_TAG);

        if (ptr3 && (!ptr2 || ptr3 < ptr2))
        {
            // on  stop
            printf("Erreur END_TAG seul détecté line %d\n", nLine);
            goto END_FONCTION;
        }

        // tant que on trouve un START_TAG dans la ligne ptr1 et que il n'y a pas de END_TAG seul avant  on point le Début du START_TAG dans ptr2
        while ((ptr2 = strstr(ptr1, START_TAG)) && !((ptr3 = strstr(ptr1, END_TAG)) < ptr2))
        {
           // on concat dans output la chaîne de ptr1 jusqu’à START_TAG
            if (!concatString(&output, ptr1, ptr2 - ptr1))
            {
                goto END_FONCTION;
            }
            // on déplace ptr2 pour pointer a la fin du START_TAG
            ptr2 += START_TAG_LEN;

            // on cherche si il ya un END_TAG apres dans ptr2 et on point dessus le début du END_TAG avec ptr3
            if (ptr3 = strstr(ptr2, END_TAG))
            {
                // on copie l'identifiant du TAG dans tagId
                if (!concatString(&tagId, ptr2, ptr3 - ptr2))
                {
                    goto END_FONCTION;
                }

                //  on cherche le tag dans la list
                tagValid = TagManager_SearchTag(self, tagId);
                if (!tagValid)
                {
                    printf("Erreur TAG:%s is invalid line %d\n", tagId, nLine);
                    goto END_FONCTION;
                }
                free(tagId);
                tagId = NULL;

                // Si le tag est dans la list on le remplace par sa valeur
                if (!concatString(&output, tagValid->value, strlen(tagValid->value)))
                {
                    goto END_FONCTION;
                }
                // on fait pointer ptr1 sur le rest de la ligne
                ptr1 = ptr3 + END_TAG_LEN;
            }
            else
            {
                // si il n'y a pas de TAG_END apres le START_TAG on stop
                printf("Erreur TAG non fermer line %d\n", nLine);
                goto END_FONCTION;
            }
        }
    } while (ptr3 = strstr(ptr1, END_TAG));// tant que il y a un END_TAG dans ptr1 on boucle pour verifier si il ya un START_TAG devant 

    // on concat  la ligne pointer par ptr1 si pas de START_TAG trouvée ou  de END_START seul
    if (!concatString(&output, ptr1, strlen(ptr1)))
    {
        goto END_FONCTION;
    }

    // on écrit output dans le fichier de sortie
    if (fprintf(ficOut, "%s", output) < 0)
    {
        fprintf(ficOut, "Erreur écriture de %s dans %s\n", output, FIC_OUT);
        goto END_FONCTION;
    }

    resultFonction = true;
END_FONCTION:
    free(tagId);
    free(output);
    return resultFonction;
}
