
// -*- coding: utf-8 -*-
#include <stdio.h>
#include <stdlib.h>

#include "headers/fct.h"
#include "headers/getLine.h"
int main(int argc, char *argv[])
{
        FILE *ficAformatter = NULL;
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

        while (my_getline(&line, &n, ficAformatter) != -1)
        {
                printf("%s", line);
                if (!formateTAGmySend(line))
                {
                        printf("Erreur formatTAGmySend()\n");
                        return -1;
                }
        }
        printf("!!SUCCESS FULL!!");
        fclose(ficAformatter);

        getchar();

        return 0;
}