//
// Created by gianl on 21/05/2021.
//

#ifndef LASD_P2_UI_H
#define LASD_P2_UI_H
#include "orderManagement.h"
#include "productCatalogue.h"
#include "driver.h"

void mainMenu();
void authenticationMenu();
void registrationMenu();
void driverMenu(Driver driver);
void driverShopMenu(Driver* driver);
PtrOrder addItemToCart(PtrOrder cart, PtrCatalogue catalogue);
PtrOrder removeItemFromCart(PtrOrder cart, int *wasItemRemoved);
void showCartInfo(Driver driver, PtrOrder cart);
void showDriverInfoMenu(Driver driver);
void driverDeliveryMenu(Driver driver);

#endif //LASD_P2_UI_H

