
// -*- coding: utf-8 -*-
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "headers/fct.h"
#include "headers/getLine.h"
#include "headers/tag.h"
#include "headers/tagManager.h"

int main(void)
{       
        int resultMainFonction = 1;
        FILE *ficAformatter = NULL;
        FILE *ficOut = NULL;
        char *line = NULL;
        size_t n = BUFFER_TEXTE_MAX;
        int nLine = 0;
        tagManager_s tags;

        TagManager_Clear(&tags);
        if (!TagManager_AddTag(&tags, "TAG1"))
        {
                goto END_MAIN_FONCTION;
        }

        if (!TagManager_UpdateValue(&tags, "TAG1", "[toto]"))
        {
                goto END_MAIN_FONCTION;
        }

        if (!TagManager_AddTag(&tags, "TAG2"))
        {
                goto END_MAIN_FONCTION;
        }

        if (!TagManager_UpdateValue(&tags, "TAG2", "[titi]"))
        {
                goto END_MAIN_FONCTION;
        }

        if (!TagManager_AddTag(&tags, "TAG3"))
        {
                goto END_MAIN_FONCTION;
        }

        if (!TagManager_UpdateValue(&tags, "TAG3", "[yaya]"))
        {
                goto END_MAIN_FONCTION;
        }

        activeAffichageUTF8DansLaConsole(false);
        printf("My_send Project\n\n");
        if (!(ficAformatter = fopen(FIC_INPUT, "r")))
        {
                printf("Erreur ouverture de %s en mode \"r\"\n", FIC_INPUT);
                goto END_MAIN_FONCTION;
        }

        if (!(ficOut = fopen(FIC_OUT, "w")))
        {
                printf("Erreur ouverture %s en mode w \n", FIC_OUT);
                goto END_MAIN_FONCTION;
        }

        while (my_getline(&line, &n, ficAformatter) != -1)
        {
                nLine++;
                if (!formateTAGmySend(ficOut, line, nLine, &tags))
                {
                        goto END_MAIN_FONCTION;
                }
        }

        resultMainFonction = 0;
        printf("\n!!SUCCESS FULL!!\n");

END_MAIN_FONCTION:

        if (ficAformatter)
        {
                fclose(ficAformatter);
        }

        if (ficOut)
        {
                fclose(ficOut);
        }
        free(line);
        getchar();

        if (resultMainFonction == 1)
        {
        }
        return resultMainFonction;
}