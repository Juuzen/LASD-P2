#ifndef LASD_P2_UI_H
#define LASD_P2_UI_H
#include "orderManagement.h"
#include "productCatalogue.h"
#include "driver.h"

/* Funzioni di interfaccia grafica */
void projectRun();
void authenticationMenu();
void registrationMenu();

void driverMenu(Driver driver);

void driverShopMenu(Driver* driver);
PtrOrder addCartItemMenu(PtrOrder cart, PtrCatalogue catalogue);
PtrOrder removeCartItemMenu(PtrOrder cart);
void showCartInfoMenu(Driver driver, PtrOrder cart);
void showDriverInfoMenu(Driver driver);

void driverDeliveryMenu(Driver driver);

/* Funzioni di appoggio */
PtrOrder addItemToCart(PtrOrder cart, PtrCatalogue catalogue);
PtrOrder removeItemFromCart(PtrOrder cart);

#endif //LASD_P2_UI_H

