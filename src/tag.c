#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "headers/tag.h"
#include "headers/fct.h"

void Tag_Clear(tag_s *self)
{
    self->id[0] = '\0';
    self->value[0] = '\0';
}

bool Tag_SetId(tag_s *self, const char *id)
{
    if (!self || strlen(id) > TAG__ID_LEN_MAX)
    {
        printf("Erreur tag_s NULL or > TAG__ID_LEN_MAX(%d)\n", TAG__ID_LEN_MAX);
        return false;
    }

    if (!Tag_IsValidId(id))
    {
        printf("Tag_SetId id invalid '%s'\n", id);
        return false;
    }

    strcpy(self->id, id);
    return true;
}

bool Tag_SetValue(tag_s *self, const char *value)
{
    if (!self || strlen(value) > TAG__VALUE_LEN_MAX)
    {
        printf("Erreur tag_s NULL or > TAG__VALUE_LEN_MAX(%d)\n", TAG__VALUE_LEN_MAX);
        return false;
    }

    strcpy(self->value, value);
    return true;
}

bool Tag_IsValidId(const char *id)
{
    if (!id || !id[0])
    {
        return false;
    }

    for (int i = 0; id[i]; i++)
    {
        if (!isalnum(id[i]) && id[i] != '_')
        {
            return false;
        }
    }

    return true;
}