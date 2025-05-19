#ifndef TAG_MANAGER_15052025_232234_my_send_H
#define TAG_MANAGER_15052025_232234_my_send_H

#include <stdbool.h>
#include <stdio.h>
#include "tag.h"

#define TAG_MANAGER__TAG_MAX 30
typedef struct tagManager
{
    tag_s list[TAG_MANAGER__TAG_MAX];
    size_t nbTag;
} tagManager_s;

void TagManager_Clear(tagManager_s *self);
bool TagManager_AddTag(tagManager_s *self, const char *id);
bool TagManager_RemoveTag(tagManager_s *self, const char *id);
bool TagManager_UpdateValue(tagManager_s *self, const char *id, const char *value);
char * TagMAnager_GetValue(tagManager_s *self, const char *id);
// ATTENTION : le retour n'est garantie que jusqu'a la prochaine utilisation de TagManager
tag_s * TagManager_SearchTag(tagManager_s *self, const char *id);
void TagManager_PrintListTag(tagManager_s *self);


#endif