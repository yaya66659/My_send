#ifndef FCT_15052025_232234_my_send_H
#define FCT_15052025_232234_my_send_H

#include <stdbool.h>

#define BUFFER_TEXTE_MAX 256
#define BUFFER_CHEMIN_MAX 512

#define TAG "PHIL"
#define TAG_LEN 4
#define REPLACE_TAG "[REPLACE_TAG]"
#define REPLACE_TAG_LEN 13

void videBuffer(void);
void activeAffichageUTF8DansLaConsole(bool activerUTF8pourLaSaisie);
bool catString(char **str1, char *str2, size_t n);
bool formateTAG(const char *line);


#endif /*FCT_15052025_232234_my_send_H*/