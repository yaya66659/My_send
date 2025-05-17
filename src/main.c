
// -*- coding: utf-8 -*-
#include <stdio.h>
#include <stdlib.h>

#include "headers/fct.h"
#include "headers/getLine.h"
int main(int argc, char *argv[])
{
        FILE *ficAformatter = NULL;
        FILE *ficOut = NULL;
        char *line = NULL;
        size_t n = BUFFER_TEXTE_MAX;
        activeAffichageUTF8DansLaConsole(false);
        system("cls");
        printf("My_send Project\n\n");

        if (!(ficAformatter = fopen(FIC_INPUT, "r")))
        {
                printf("Erreur ouverture de %s en mode \"r\"\n", FIC_INPUT);
                return -1;
        }

        if (!(ficOut = fopen(FIC_OUT, "w")))
        {
                printf("Erreur ouverture %s en mode w \n");
                fclose(ficAformatter);
                return -1;
        }

        while (my_getline(&line, &n, ficAformatter) != -1)
        {

                if (!formateTAGmySend(ficOut, line))
                {
                        printf("Erreur formatTAGmySend()\n");
                        fclose(ficOut);
                        fclose(ficAformatter);
                        return -1;
                }
        }
        printf("\n!!SUCCESS FULL!!\n");

        fclose(ficOut);
        fclose(ficAformatter);

        getchar();

        return 0;
}