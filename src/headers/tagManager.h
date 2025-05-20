#ifndef TAG_MANAGER_15052025_232234_my_send_H
#define TAG_MANAGER_15052025_232234_my_send_H

#include <stdbool.h>
#include <stdio.h>
#include "tag.h"

#define  TAG_MANAGER__TAG_MAX  30
typedef struct tagManager
{
    tag_s list[TAG_MANAGER__TAG_MAX];
    size_t nbTag;
} tagManager_s;

//Met en position correcte la liste de TAG et nbTag a 0
void TagManager_Clear(tagManager_s *self);
//Ajoute un TAG id a la list des TAG (les id sont unique dans la list)
bool TagManager_AddTag(tagManager_s *self, const char *id);
//Supprime un TAG de la list et le remplace par le dernier, enlève 1 a nbTag
bool TagManager_RemoveTag(tagManager_s *self, const char *id);
//Met a jour une Valeur dans un TAG dont id est passer en paramètre
bool TagManager_UpdateValue(tagManager_s *self, const char *id, const char *value);
//Retourne la valeur d'un TAG dont l'id est pass"e en paramètre
char * TagMAnager_GetValue(tagManager_s *self, const char *id);
//Retourne un  pointeur vers un Tag_s dont l'id est passer en paramètre  ATTENTION : le retour n'est garantie que jusqu'a la prochaine utilisation de TagManager
tag_s * TagManager_SearchTag(tagManager_s *self, const char *id);
#endif