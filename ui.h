//
// Created by gianl on 21/05/2021.
//

#ifndef LASD_P2_UI_H
#define LASD_P2_UI_H
#include "orderManagement.h"
#include "productCatalogue.h"
#include "driver.h"

PtrOrder addToCart(PtrOrder cart, PtrCatalogue catalogue);
void registrationMenu();
void showCartInfo(Driver driver, PtrOrder cart);
void driverShopMenu(Driver* driver);
void driverDeliveryMenu(Driver driver);
void driverMenu(Driver driver);
void authenticationMenu();
void mainMenu();

#endif //LASD_P2_UI_H

