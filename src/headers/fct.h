#ifndef  FCT_15052025_232234_my_send_H
#define  FCT_15052025_232234_my_send_H

#include  <stdbool.h>
#include  "tagManager.h"

#define  BUFFER_TEXTE_MAX  256
#define  BUFFER_CHEMIN_MAX  512

#define  FIC_INPUT  "exemple.txt"
#define  FIC_OUT  "exemple.txt.result"

#define  START_TAG  "[MYSEDBEGIN_"
#define  START_TAG_LEN  strlen(START_TAG)

#define  END_TAG  "_MYSEDEND]"
#define  END_TAG_LEN strlen(END_TAG)

#define  TAG1  "TAG1"
#define  TAG2  "TAG2"
#define  TAG3  "TAG3"

#define  REPLACE_TAG1  "[toto]"
#define  REPLACE_TAG2  "[titi]"
#define  REPLACE_TAG3  "[yaya]"

#define  REPLACE_TAG_INVALID  "[TAG_INVALID]"
#define  REPLACE_TAG_INVALID_LEN  strlen(REPLACE_TAG_INVALID)

void flushStdinBuffer(void);
void activeAffichageUTF8DansLaConsole(bool activerUTF8pourLaSaisie);
bool concatString(char **dest, char *src, size_t n);
bool formateTAGmySend(FILE *ficOut, const char *line, const int nLine, tagManager_s *self);

#endif /*FCT_15052025_232234_my_send_H*/