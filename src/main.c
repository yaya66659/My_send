
// -*- coding: utf-8 -*-
#include <stdio.h>
#include <stdlib.h>

#include "headers/fct.h"
int main(int argc, char *argv[])
{
        activeAffichageUTF8DansLaConsole(false);
        system("cls");
        printf("Modèle main.c\n");
        const char *strTAG = "PHILyoyo PHILPHILtututuyTAGoyuyPHIL   TAGPHILPHILPHIL   aaaTAGaaaaaaaaTAGPHIL";
        printf("la chaîne de caractère : '%s'\n", strTAG);
        printf("va être réécrite en remplacent tout les %s avec des %s sur la sortie standard stdout\n", TAG, REPLACE_TAG);
        printf("Saisir ENTER pour formater la chaîne\n\n\n");
        getchar();
        if (formateTAG(strTAG))
        {
                printf("\nLa chaîne a étés formatée avec Succès  Saisir ENTER pour quitter\n");
        }
        else
        {
                printf("\nÉCHEC du formatage\n");
        }
        getchar();

        return 0;
}