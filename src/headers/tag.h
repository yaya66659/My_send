#ifndef TAG_15052025_232234_my_send_H
#define TAG_15052025_232234_my_send_H

#include <stdbool.h>

#define  TAG__ID_LEN_MAX  30
#define  TAG__VALUE_LEN_MAX  256

typedef struct tag
{
    char id[TAG__ID_LEN_MAX];
    char value[TAG__VALUE_LEN_MAX];
} tag_s;

//met le tag_s id et value en position correcte
void Tag_Clear(tag_s *self);
//modifie un id d'un tag_s
bool Tag_SetId(tag_s *self, const char *id);
//modifie un la value d'un tag_s
bool Tag_SetValue(tag_s *self, const char *value);
//verify si  un id est valide
bool Tag_IsValidId(const char *id);
#endif