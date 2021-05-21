//
// Created by backs on 18/05/2021.
//

#ifndef LASD_P2_AUTHLIB_H
#define LASD_P2_AUTHLIB_H

#define MAX_SIZE_USERNAME 12
#define MAX_SIZE_PASSWORD 12

int doLogin(char *username, char *password, char *filename);
int doRegistration(char *username, char *password, char *peso, char *filename);
int checkIfUsernameAlreadyExists(char *username, char *filename);
void mainMenu();

#endif //LASD_P2_AUTHLIB_H
