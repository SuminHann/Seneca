/* Citation and Sources...
Final Project Milestone 5 
Module: Item.cpp
Filename: Item.cpp
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
#include <iostream>
#include <cstring>
#include <iomanip>
#include <fstream>
#include <math.h>
#include "Item.h"
using namespace std;

namespace sdds{
    Item::Item() : m_ErrorState(){
        SKU[0] = '\0';
        m_name = nullptr;
        m_price = 0;
        m_taxed = false;
        m_quantity = 0;
        m_displayType = 0;
        m_ErrorState = ERROR_POS_EMPTY;
    }
    Item::Item(Item& a) : m_ErrorState(a.m_ErrorState) {
        strcpy(SKU, a.SKU);
        m_name = nullptr;
        if(a.m_name){
            m_name = new char[strlen(a.m_name)+1];
            strcpy(m_name, a.m_name);
        }
        m_price = a.m_price;
        m_taxed = a.m_taxed;
        m_quantity = a.m_quantity;
        m_displayType = a.m_displayType;
    }
    Item& Item::operator=(const Item& a){
        if (this != &a) {
            strcpy(SKU, a.SKU);
            delete [] m_name;
            m_name = nullptr;
            if(a.m_name){
                m_name = new char[strlen(a.m_name)+1];
                strcpy(m_name, a.m_name);
            }
            m_price = a.m_price;
            m_taxed = a.m_taxed;
            m_quantity = a.m_quantity;
            m_displayType = a.m_displayType;
            m_ErrorState = a.m_ErrorState;
        }
        return *this;
    }
    Item::~Item(){
        delete [] m_name;
        m_name = nullptr;
    }
    bool Item::operator==(const char* sku) const{
        return strcmp(SKU, sku) == 0;
    }
    bool Item::operator>(const Item& a) const{
        return strcmp(m_name, a.m_name) > 0;
    }
    int Item::operator+=(int rhs){
        int ans = m_quantity+rhs;
        if(ans > MAX_STOCK_NUMBER){
            m_quantity = MAX_STOCK_NUMBER;
            m_ErrorState.clear();
            m_ErrorState.set(ERROR_POS_QTY);
            cout<<m_ErrorState.getError()<<endl;
        }
        else{
            m_quantity = ans;
        }
        return m_quantity;
    }
    int Item::operator-=(int rhs){
        if(rhs>m_quantity){
            m_quantity = 0;
            m_ErrorState.clear();
            m_ErrorState.set(ERROR_POS_STOCK);
            cout<<m_ErrorState.getError()<<endl;
        }
        else{
            m_quantity-=rhs;
        }
        return m_quantity;
    }
    Item::operator bool() const{
        bool ans = false;
        if(strcmp(m_ErrorState.getError(), ERROR_POS_EMPTY) == 0){
            ans = true;
        }
        return ans;
    }
    Item& Item::displayType(int type){
        m_displayType = type;
        return *this;
    }
    char* Item::name() const{
        return m_name;
    }

    const char* Item::sku() const{
       return SKU;
    }
    double Item::cost() const{
        double a = m_price;
        if(m_taxed == true){
            a = m_price + m_price*TAX;
        }
        return a;
    }
    int Item::quantity() const{
        return m_quantity;
    }
    bool Item::taxed() const{
        return m_taxed;
    }
    double Item::price() const{
        return m_price;
    }
    Item& Item::clear(){
        m_ErrorState.clear();
        m_ErrorState.set(ERROR_POS_EMPTY);
        return *this;
    }
    std::ostream& Item::write(std::ostream& os) const{
        double value = m_price*m_quantity*(1+TAX);
        int roundValue = (int)((value+0.005000)*100);
        double taxedValue = (double)(roundValue)/100;
        if(m_displayType == POS_LIST){
            if(!*this && m_ErrorState.getError() != ERROR_POS_EMPTY){
                os << m_ErrorState.getError();
            }
            else{
            os << SKU << "   |";
                if(strlen(m_name)> 20 && m_name[20] != '\n'){
                    for(int i=0; i<20; i++){
                        os << m_name[i];
                    }
                    os << "|";
                }
                else{
                    os << std::left << std::setw(20) << m_name << "|";
                }
                os << std::right << std::setw(7) << std::fixed << std::setprecision(2) << m_price << "|";
                
                if(m_taxed == true){
                    os << std::setw(2)<< "X" << setw(2);
                    os << "|" << std::right << std::setw(4) << m_quantity << "|" << std::right << std::setw(9) << std::fixed << setprecision(2) << taxedValue;
                }
                else{
                    os << std::setw(3) << " " << "|";
                    os << std::right << std::setw(4) << m_quantity << "|" << std::right << std::setw(9) << std::fixed << setprecision(2) << m_price*m_quantity;
                }
                os << std::left << "| ";
                // os.unsetf(ios::fixed);
            }
        }
        else if(m_displayType == POS_FORM){
            if(!*this){
                os << m_ErrorState.getError();
            }
            else{
            os << "=============v" << std::endl;
            os << std::left << std::setw(13) << "Name:" << m_name << std::endl;
            os << std::left << std::setw(13) << "Sku:" << SKU << std::endl;
            os << std::left << std::setw(13) << "Price:" << m_price << std::endl;
            if(m_taxed == true){
                os << std::left << std::setw(13) << std::fixed << setprecision(2) << "Price + tax:" << m_price*(1+TAX) << std::endl;
            }
            else{
                os << std::left << std::setw(13) << "Price + tax:" << "N/A" << std::endl;
            }
            os << std::left << std::setw(13) << "Stock Qty:" << m_quantity << std::endl;
            }
        }
        return os;
    }
    std::istream& Item::read(std::istream& is) {
        char name[99];
        char tax = '\0';
        char sku[20];
        cout << "Sku" << endl;
        do{
            cout << "> ";
            is >> sku;
            // SKU[0] = '\0';
            // cout << strlen(sku) << endl;
            for(int i=0; i<20; i++){
                    SKU[i] = sku[i];
                }
                // cout << sku << endl;
                // cout << SKU << endl;
                // cout << strlen(SKU) << endl;
            if(strlen(SKU) > MAX_SKU_LEN){
                m_ErrorState.clear();
                m_ErrorState.set(ERROR_POS_SKU);
                cout << m_ErrorState.getError() << endl;
            }
        }while(strlen(SKU) > MAX_SKU_LEN);

        cout << "Name" << endl;
        is.ignore(60, '\n');
        do{
            m_name = nullptr;
            cout << "> ";
            is.getline(name, 60);
            // cout << name << endl;
            // cout << strlen(name) << endl;
            if(strlen(name) > MAX_NAME_LEN){
                m_ErrorState.clear();
                m_ErrorState.set(ERROR_POS_NAME);
                cout << m_ErrorState.getError() << endl;
            }
            else{
                delete [] m_name;
                m_name = new char[strlen(name)+1];
                strcpy(m_name, name);
                // cout << m_name << endl;
            }
        }while((m_name == nullptr) || strlen(name) > MAX_NAME_LEN);

        cout << "Price" << endl;
        do{
            cout << "> ";
            // is.ignore();
            is >> m_price;
            if(m_price < 0){
                m_ErrorState.clear();
                m_ErrorState.set(ERROR_POS_PRICE);
                cout << m_ErrorState.getError() << endl;
            }
            else if(is.fail()){
                m_ErrorState.clear();
                m_ErrorState.set(ERROR_POS_PRICE);
                cout << m_ErrorState.getError() << endl;
                is.clear();
                is.ignore(50, '\n');
                m_price = -1;
            }
            // cout << m_price << endl;
        }while(m_price < 0 || is.fail());

        cout << "Taxed?" << endl;
        cout << "(Y)es/(N)o: ";
        while(tax != 'y' && tax != 'n'){
            m_taxed = false;
            is >> tax;
            if(tax == 'y'){
                m_taxed = true;
            }
            else if(tax == 'n'){
                m_taxed = false;
            }
            else{
                cout << "Only 'y' and 'n' are acceptable: ";
                cin.clear();
                cin.ignore(50, '\n');
            }
        }
        cout << "Quantity" << endl;
        do{
            cout << "> ";
            is >> m_quantity;
            if(m_quantity <= 0 || m_quantity > MAX_STOCK_NUMBER){
                m_ErrorState.clear();
                m_ErrorState.set(ERROR_POS_QTY);
                cout << m_ErrorState.getError() << endl;
                is.clear();
                is.ignore(50, '\n');
            }
            else if(is.fail()){
                m_ErrorState.clear();
                m_ErrorState.set(ERROR_POS_QTY);
                cout << m_ErrorState.getError() << endl;
                is.clear();
                is.ignore(50, '\n');
            }
            clear();
        }while(m_quantity <= 0 || m_quantity > MAX_STOCK_NUMBER);
        return is;
    }
    std::ofstream& Item::save(std::ofstream& of) const{
        if(*this){
            of << "," << SKU << "," << m_name << "," <<fixed << setprecision(2) << m_price << "," << m_taxed << "," << m_quantity;
        }
        else{
            cerr << m_ErrorState.getError() << endl;
        }
        return of;
    }
    std::ifstream& Item::load(std::ifstream& inputfile){
        clear();
        
        char sku[99] = "";
        char name[99] = "";
        double price = 0.00;
        bool taxed = false;
        int quantity = 0;
        
        inputfile.getline(sku, 99, ',');
        // cout << sku << endl;
        if(!inputfile.fail()){
            inputfile.getline(name, 99, ',');
            // cout << name << endl;
            if(!inputfile.fail()){
                
                inputfile >> price;
                // cout << price << endl;
                if(!inputfile.fail()){
                    inputfile.ignore();
                    inputfile >> taxed;
                    // cout << taxed << endl;
                    if(!inputfile.fail()){
                        inputfile.ignore();
                        inputfile >> quantity;
                        // cout << quantity << endl;
                        if(inputfile.fail()){
                            m_ErrorState.set(ERROR_POS_QTY);
                        }
                    }
                    else{
                        m_ErrorState.clear();
                        m_ErrorState.set(ERROR_POS_TAX);
                    }
                }
                else{
                    m_ErrorState.clear();
                    m_ErrorState.set(ERROR_POS_PRICE);
                }
            }
            else{
                m_ErrorState.clear();
                m_ErrorState.set(ERROR_POS_NAME);
            }
        }
        else{
            m_ErrorState.clear();
            m_ErrorState.set(ERROR_POS_SKU);
        }
        if(quantity > 0 && quantity <= MAX_STOCK_NUMBER){
            m_quantity = quantity;
        }
        else{
            m_ErrorState.clear();
            m_ErrorState.set(ERROR_POS_QTY);
        }
        if(taxed == 1 || taxed == 0){
            m_taxed = taxed;
        }
        else{
            m_ErrorState.clear();
            m_ErrorState.set(ERROR_POS_TAX);
        }
        if(price > 0){
            m_price = price;
        }
        else{
            m_ErrorState.clear();
            m_ErrorState.set(ERROR_POS_PRICE);
        }
        if(name[0] != '\0' && strlen(name) < MAX_NAME_LEN+1){
            if(m_name){
                delete [] m_name;
                m_name = nullptr;
            }
            m_name = new char[strlen(name)+1];
            strcpy(m_name, name);
        }
        else{
            m_ErrorState.clear();
            m_ErrorState.set(ERROR_POS_NAME);
        }
        if(strlen(sku) < MAX_SKU_LEN+1){
            strcpy(SKU, sku);
        }
        else{
            m_ErrorState.clear();
            m_ErrorState.set(ERROR_POS_SKU);
        }
        // cout << SKU << endl;
        // cout << m_name << endl;
        // cout << m_price << endl;
        // cout << m_taxed << endl;
        // cout << m_quantity << endl;
        
        return inputfile;
    }
    std::ostream& Item::bprint(std::ostream& os) const{
        os << "| ";
        if(strlen(m_name)> 20 && m_name[20] != '\n'){
            for(int i=0; i<20; i++){
                os << m_name[i];
            }
            os << "|";
        }
        else{
            os << std::left << std::setw(20) << m_name << "|";
        }
        // os << right << setw(10) <<fixed << setprecision(2) << m_price << " | ";
        if(m_taxed == true){
            os << right << setw(10) <<fixed << setprecision(2) << m_price*(1+TAX) << " | ";
            os << setw(2) << "T" << setw(3) <<  "|"; 
        }
        else {
            os << right << setw(10) <<fixed << setprecision(2) << m_price << " | ";
            os << setw(4) << "" <<  "|"; 
        }
        os << endl;
        return os;
    }
    double operator+=(double value, const Item& rhs){
        return value += rhs.cost() * rhs.quantity();
    }
}
