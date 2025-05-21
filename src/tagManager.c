#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "headers/tag.h"
#include "headers/tagManager.h"

/*Met les tag dans list de tagManager a zero et dans une situation correcte*/
void TagManager_Clear(tagManager_s *self)
{
    for (int i = 0; i < TAG_MANAGER__TAG_MAX; i++)
    {
        Tag_Clear(&self->list[i]);
    }

    self->nbTag = 0;
}

/* Ajoute un Tag a la list de tagManager si id du tag n'existe pas déjà dans list*/
bool TagManager_AddTag(tagManager_s *self, const char *id)
{
    tag_s newTag;

    Tag_Clear(&newTag);
    if (!self)
    {
        fprintf(stderr, "TagManager_AddTag tagManager_s = NULL");
        return false;
    }

    if (self->nbTag + 1 > TAG_MANAGER__TAG_MAX)
    {
        fprintf(stderr, "TagManager_AddTag nbTag > %d\n", TAG_MANAGER__TAG_MAX);
        return false;
    }

    if (!Tag_SetId(&newTag, id))
    {
        return false;
    }

    if (TagManager_SearchTag(self, id) != NULL)
    {
        fprintf(stderr, "TagManager_AddTag id '%s' exist\n", id);
        return false;
    }

    self->list[self->nbTag++] = newTag;
    return true;
}

/*Supprime un tag dans la list de tagManager dont l'id est passer en paramètre*/
bool TagManager_RemoveTag(tagManager_s *self, const char *id)
{
    tag_s *tag = NULL;
    tag_s TagTmp;

    if (!self)
    {
        return false;
    }

    if (!(tag = TagManager_SearchTag(self, id)))
    {
        fprintf(stderr, "TagManager_RemoveTag tag id '%s' is not here\n", id);
        return false;
    }
    // Si le tag est dans list on le met dans une situation correcte et on l'alterne avec le dernier tag avant de diminuer le nombre de tag de 1
    Tag_Clear(tag);
    TagTmp = *tag;
    *tag = self->list[self->nbTag - 1];
    self->list[self->nbTag - 1] = TagTmp;
    self->nbTag--;
    return true;
}

/*Met a jour la valeur d'un tag correspondant a l'id donnée en paramètre*/
bool TagManager_UpdateValue(tagManager_s *self, const char *id, const char *value)
{
    tag_s *tag = NULL;

    if (!self)
    {
        fprintf(stderr, "TagManager_UpdateValue tagManager_s = NULL");
        return false;
    }

    if (!(tag = TagManager_SearchTag(self, id)))
    {
       fprintf(stderr, "TagManager_UpdateValue id: '%s' not here", id);
        return false;
    }

    if (!Tag_SetValue(tag, value))
    {
        return false;
    }
    return true;
}

/*Retourne la valeur d'un tag dont l'id est passée en paramètre*/
char *TagMAnager_GetValue(tagManager_s *self, const char *id)
{
    if (!self)
    {
        return NULL;
    }

    int i = 0;
    while (i < self->nbTag)
    {
        if (strcmp(self->list[i].id, id) == 0)
        {
            return self->list[i].value;
        }
        i++;
    }
    return NULL;
}

// ATTENTION : le retour n'est garantie que jusqu'a la prochaine utilisation de TagManager
tag_s *TagManager_SearchTag(tagManager_s *self, const char *id)
{
    int i = 0;

    if (!self)
    {
        return NULL;
    }

    while (i < self->nbTag)
    {
        if (strcmp(self->list[i].id, id) == 0)
        {
            return &self->list[i];
        }
        i++;
    }

    return NULL;
}