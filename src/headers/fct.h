#ifndef FCT_15052025_232234_my_send_H
#define FCT_15052025_232234_my_send_H

#include <stdbool.h>

#define BUFFER_TEXTE_MAX 256
#define BUFFER_CHEMIN_MAX 512

#define FIC_INPUT "exemple.txt"
#define FIC_OUT "exemple.txt.result"

#define TAG "PHIL"
#define TAG_LEN 4

#define START_TAG "[MYSEDBEGIN_"
#define START_TAG_LEN strlen(START_TAG)

#define END_TAG "_MYSEDEND]"
#define END_TAG_LEN strlen(END_TAG)

#define REPLACE_TAG "[toto]"
#define REPLACE_TAG_LEN strlen(REPLACE_TAG)

#define REPLACE_TAG_INVALID "[TAG_INVALID]"
#define REPLACE_TAG_INVALID_LEN strlen(REPLACE_TAG_INVALID)

void videBuffer(void);
void activeAffichageUTF8DansLaConsole(bool activerUTF8pourLaSaisie);
bool catString(FILE *fic, char **str1, char *str2, size_t n);
bool formateTAG(const char *line);
bool tagValide(const char *tag);
bool formateTAGmySend(FILE * ficFormater, const char *line);

#endif /*FCT_15052025_232234_my_send_H*/