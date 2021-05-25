//
// Created by backs on 18/05/2021.
//

#ifndef LASD_P2_AUTHLIB_H
#define LASD_P2_AUTHLIB_H

int doLogin(char *username, char *password, char *filename);
int doRegistration(char *username, char *password, char *filename);
int checkIfUsernameAlreadyExists(char *username, char *filename);

#endif //LASD_P2_AUTHLIB_H
