#include <stdio.h>
#include <stdlib.h>
#ifndef TEACHER_H
#define TEACHER_H

void createInstructor(char email, int mdp1, int mdp2){
    printf("Enter your email :");
    scanf("%c\n" ,&email);
    printf("Create a keyword :");
    scanf("%c\n" ,&mdp1);
    printf("Confirm your keyword :");
    scanf("%c\n" ,&mdp2);
    if ( mdp1 == mdp2){
        printf("Your account has been well created");
        else{
            printf("Your confirmation's keyword is different")
            exit()
        }
    }
    printf("Your account has been well created");
}

void connectInstructor(char email, char action, int mdp){
    printf("Enter your email :");
    scanf("%c\n" ,&email);
    printf("Choose an action : ");
    scanf("%c\n" ,&action);
}
