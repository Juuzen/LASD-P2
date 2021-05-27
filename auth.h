#ifndef LASD_P2_AUTH_H
#define LASD_P2_AUTH_H

int auth_login (char *username, char *password, char *filename);
int auth_register (char *username, char *password, char *filename);
int auth_checkExistingUsername (char *username, char *filename);

#endif //LASD_P2_AUTHLIB_H
