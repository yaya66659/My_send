#ifndef TAG_15052025_232234_my_send_H
#define TAG_15052025_232234_my_send_H

#include <stdbool.h>

#define TAG__ID_LEN_MAX 30
#define TAG__VALUE_LEN_MAX 256

typedef struct tag
{
    char id[TAG__ID_LEN_MAX];
    char value[TAG__VALUE_LEN_MAX];
} tag_s;

void Tag_Clear(tag_s *self);
bool Tag_SetId(tag_s *self, const char *id);
bool Tag_SetValue(tag_s *self, const char *value);
bool Tag_IsValidId(const char *tag);

#endif