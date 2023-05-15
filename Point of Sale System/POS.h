/* Citation and Sources...
Final Project Milestone 5 
Module: POS.h
Filename: POS.h
Version 1.0
Author	John Doe
Revision History
-----------------------------------------------------------
Date      Reason
2023/04/16  Preliminary release
2020/04/16  Debugged DMA
-----------------------------------------------------------
I have done all the coding by myself and only copied the code 
that my professor provided to complete my project milestones.
-----------------------------------------------------------
OR
-----------------------------------------------------------
Write exactly which part of the code is given to you as help and 
who gave it to you, or from what source you acquired it.
-----------------------------------------------------------*/
#ifndef SDDS_POS_H
#define SDDS_POS_H
#define TAX 0.13
#define MAX_SKU_LEN 7
#define MIN_YEAR 2000
#define MAX_YEAR 2030
#define MAX_STOCK_NUMBER 99
#define MAX_NO_ITEMS 200
#define MAX_NAME_LEN 40
#define POS_LIST 1
#define POS_FORM 2
#include <iostream>
using namespace std;

const char ERROR_POS_SKU[] = "SKU too long";
const char ERROR_POS_NAME[] = "Item name too long";
const char ERROR_POS_PRICE[] = "Invalid price value";
const char ERROR_POS_TAX[] = "Invalid tax status";
const char ERROR_POS_QTY[] = "Invalid quantity value";
const char ERROR_POS_STOCK[] = "Item out of stock";
const char ERROR_POS_EMPTY[] = "Invalid Empty Item";

#endif