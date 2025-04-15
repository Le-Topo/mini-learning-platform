//
// Created by astrid on 2025-04-07.
//

#ifndef USER_H
#define USER_H
#include <stdio.h>
#include <string.h>

#include "utils/enums/user-role.h"

struct User {
  long id;
  char *email;
  char *password1;
  char *password2;
  char *firstname;
  char *lastname;
  char *distinction; // Disctions of the user, if applicable (e.g: Ing., Dr., etc.)
  UserRole role;

  char *created_at; // ISO 8601 format
  char *updated_at; // ISO 8601 format
};
typedef struct User User;

#endif //USER_H


void displayMenu(){
    
      int action;
      printf("\n=== MENU PRINCIPAL ===\n");
        printf("1. Create an account\n");
        printf("2. Connect to an account\n");
        printf("3. Quit\n");
        printf("Your action : ");
  
        scanf("%d", &action);
      

     switch (action) {
        case 1:
         createAccount();  
         break;

        case 2:
            connectAccount();
            break;

        case 3:
            printf("Goodbye\n");

        default:
       printf("Invalid choice, please try again\n");
      }
    


    }



void createAccount() {
    FILE *fp = fopen("users.txt", "a");
    User u;

    printf("\n=== Creation of an account ===\n");
    printf("Enter your id : ");
    scanf("%d", u.id);
    printf("Enter your firstname: ");
    scanf("%s", u.firstname);
    printf("Enter your lastname : ");
    scanf("%d", u.lastname);
    printf("Enter your distinction : ");
    scanf("%s", u.distinction);
    printf("Enter your email: ");
    scanf("%s", u.email);
    printf("Create a password : ");
    scanf("%d", u.password1);
    printf("Confirm your  password : ");
    scanf("%d", u.password2);
    if (u.password1 == u.password2){
      printf("Your password is valide");

    }else {
      printf("your confirmaton's passwordis invalid");
      break;
    }
    
}

void connectAccount ();{
int login() {
    FILE *fp = fopen("users.txt", "r");
    if (fp == NULL) {
        printf("Erreur : fichier users.txt introuvable.\n");
        return 0;
    }

    printf("\n=== Connexion ===\n");
    printf("id : ");
    scanf("%s", u.id);
    printf("Mot de passe : ");
    scanf("%s", u.password1);

    while (fscanf(fp, "%s %s", fileUser, filePass) != EOF) {
        if (strcmp(username, fileUser) == 0 && strcmp(password, filePass) == 0) {
            fclose(fp);
            printf("✅ Connexion réussie ! Bienvenue, %s\n", username);
            return 1; // Connexion réussie
        }
    }

    fclose(fp);
    printf("❌ Échec de connexion. Nom d'utilisateur ou mot de passe incorrect.\n");
    return 0; // Échec
}
}

void deconnect(){
  int option;
            
  printf("\n--- Menu ---\n");
 printf("1. Create a course\n") 
 printf("2. Read a course\n");
 printf("3. To Deconnect\n")
 printf("Choose an option : ");
 scanf("%d", &option);

  switch (choix) {
    case 1:
     create(id);
     break;
    case 2:
      displayCourse(id);
      break;
    case 3:
     printf("Deconnexion...\n");
     break;
     default:
      printf("invalid choice.\n");
      }
           
    

    fclose(fp);
    printf("incorrect identifiant.\n");
    return 0;
}

