//
// Created by gianl on 21/05/2021.
//

#ifndef LASD_P2_UI_H
#define LASD_P2_UI_H
#include "orderManagement.h"
#include "productCatalogue.h"
#include "driver.h"

PtrOrder addToCart(PtrCatalogue catalogue);
void registrationMenu();
void showCartInfo(Driver driver, PtrOrder cart);
void driverShopMenu(Driver driver);
void driverDeliveryMenu();
void driverMenu(Driver driver);
void authenticationMenu();
void mainMenu();
int recoverTruckWeight(char *username);

#endif //LASD_P2_UI_H

