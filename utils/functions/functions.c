//
// Created by astri on 2025-04-11.
//

#include "functions.h"

static char* learners_quotes[] = {
   "\"L'education est le passeport pour l'avenir, car demain appartient a ceux qui s'y preparent aujourd'hui.\"",
   "\"L'apprentissage est un tresor qui suivra son proprietaire partout.\"",
   "\"Les enseignants peuvent ouvrir la porte, mais vous devez y entrer vous-meme.\"",
   "\"Ce qui est bien avec l'apprentissage, c'est que personne ne peut vous l'enlever.\"",
   "\"L'education est l'arme la plus puissante que vous puissiez utiliser pour changer le monde.\"",
};

static char* instructors_quotes[] = {
   "\"L'enseignement est l'art d'aider les autres a decouvrir leur potentiel.\"",
   "\"Un bon enseignant est comme une bougie, il se consume pour eclairer le chemin des autres.\"",
   "\"Je touche l'avenir. J'enseigne.\"",
   "\"L'enseignement est un acte d'amour et de devouement.\"",
   "\"Les enseignants peuvent avoir un impact si profond sur nos vies et devraient etre honores comme des heros.\"",
};

static char* admins_quotes[] = {
   "\"La gestion est l'art de faire les choses par les autres.\"",
   "\"Un bon leader inspire l'espoir, allume l'imagination et cree un sentiment de but.\"",
   "\"La gestion est la capacite de faire des choses a travers les autres.\"",
   "\"Un bon administrateur est celui qui sait ecouter et comprendre les besoins des autres.\"",
   "\"La gestion efficace est la cle du succes dans toute organisation.\"",
};

char* get_random_motivational_quote(UserRole user_role)
{
      char* quote = NULL;
      int random_index = rand() % 5;

      switch (user_role) {
         case LEARNER:
               quote = learners_quotes[random_index];
               break;
         case INSTRUCTOR:
               quote = instructors_quotes[random_index];
               break;
         case ADMIN:
               quote = admins_quotes[random_index];
               break;
         default:
               quote = "Aucune citation disponible.";
               break;
      }

      return quote;
}

char* get_user_role_description(UserRole user_role)
{
    switch (user_role) {
        case LEARNER:
            return "Apprenant";
        case INSTRUCTOR:
            return "Instructeur";
        case ADMIN:
            return "Administrateur";
        default:
            return "Inconnu";
    }
}

char* trim_whitespaces(char *str)
{
    char *end;

    // trim leading space
    while(isspace(*str))
        str++;

    if(*str == 0) // all spaces?
        return str;

    // trim trailing space
    end = str + strnlen(str, 128) - 1;

    while(end > str && isspace(*end))
        end--;

    // write new null terminator
    *(end+1) = '\0';

    return str;
}

// This function is used to hash a string using a simple hash function
char* hash_string(char *str)
{
    unsigned long hash = 5381;
    int c;

    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }

    // Convert the hash to a string
    char *hash_str = malloc(21); // Enough to hold a 64-bit integer as a string
    if (hash_str) {
        snprintf(hash_str, 21, "%lu", hash);
    }

    return hash_str;
}

// This function is used to free a linked list
void free_linked_list(void *list, size_t next_offset) {
    void *p = list;
    while (p) {
        void *next = *(void **)((char *)p + next_offset);
        free(p);
        p = next;
    }
}