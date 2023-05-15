/* Citation and Sources...
Final Project Milestone 5 
Module: PosApp.cpp
Filename: PosApp.cpp
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
#include <iomanip>
#include <fstream>
#include <cstring>
#include "PosApp.h"

using namespace std;
namespace sdds{
    PosApp::PosApp(){
        m_fileName[0] = '\0';
    }
    PosApp::PosApp(const char* filename){
        if(filename && filename[0] != '\0'){
            strcpy(m_fileName, filename);
        }
    }
    int PosApp::menu(){
        int selection;
        cout<<"The Sene-Store"<<endl;
        cout<<"1- List items"<<endl;
        cout<<"2- Add item"<<endl;
        cout<<"3- Remove item"<<endl;
        cout<<"4- Stock item"<<endl;
        cout<<"5- POS"<<endl;
        cout<<"0- exit program"<<endl;
        cout<<"> ";
        cin>>selection;
        while(cin.fail() || selection<0 || selection>5){
            if(cin.fail()){
                cout<<"Invalid Integer, try again: ";
                cin.clear();
                cin.ignore(10000, '\n'); 
            }
            else if(selection<0 || selection>5){
                cout<<"[0<=value<=5], retry: > ";
                cin.clear();
                cin.ignore(10000, '\n');
            }
            cin>>selection;
        }
        return selection;
    }

    void PosApp::actionTitle(const char* title){
        cout<<">>>> "<<left<<setw(72)<<setfill('.')<<title<<endl;
        cout<<setfill(' ');
    }
    bool PosApp::addItems(){
        char type = '\0';
        actionTitle("Adding Item to the store");
        if(nptr >= MAX_NO_ITEMS){
            cout<<"Inventory Full!"<<endl;
        }
        else{
            Item* A;
            cout<<"Is the Item perishable? (Y)es/(N)o: ";
            while(type != 'y' && type != 'n'){
                cin >> type;
                if(type == 'y'){
                    A = new Perishable();
                }
                else if(type == 'n'){
                    A = new NonPerishable();
                }
                else{
                    cout << "Only 'y' and 'n' are acceptable: ";
                    cin.clear();
                    cin.ignore(50, '\n');
                }
            }
            do{
            A->read(cin);
            if(!A){
                cout<<A->displayType(POS_LIST)<<", try again...\n";
            }
            else{
                Iptr[nptr] = A;
                nptr++;
            }
            } while(!A);
            actionTitle("DONE!");
        }
        return true;
    }
    bool PosApp::removeItem(){
        actionTitle("Remove Item");
        int rowNum = selectItem();
        cout<<"Removing...."<<endl;
        if(Iptr[rowNum-1]){
            cout<<Iptr[rowNum-1]->displayType(POS_FORM);
            delete Iptr[rowNum-1];
            for(int i=rowNum; i<nptr; i++){
                Iptr[i-1] = Iptr[i];
            }
            nptr--;;
            actionTitle("DONE!");
        }
        return true;
    }
    int PosApp::selectItem(){
        int i, j;
        signed int rowNum;
        actionTitle("Item Selection by row number");
        cout << "Press <ENTER> to start....";
        cin.get();
        cin.ignore();
        actionTitle("Listing Items");
        
        for(i=nptr-1; i>0; i--){
            for(j=0; j<i; j++){
                if(Iptr[j] && Iptr[j+1] && strcmp(Iptr[j]->name(), Iptr[j+1]->name())>0){
                    Item* temp = Iptr[j];
                    Iptr[j] = Iptr[j+1];
                    Iptr[j+1] = temp;
                }
            }
        }
        cout<<" Row | SKU    | Item Name          | Price |TX |Qty |   Total | Expiry Date |"<<endl;
        cout<<"-----|--------|--------------------|-------|---|----|---------|-------------|"<<endl;
        for(int i=0; i<nptr; i++){
            cout<<right<<setw(4)<<i+1<<" | ";
            cout<<Iptr[i]->displayType(POS_LIST)<<endl;
        }
        cout<<"-----^--------^--------------------^-------^---^----^---------^-------------^"<<endl;
        cout<<"Enter the row number: ";
        do{
        cin>>rowNum;
        if(cin.fail()){
            cout<<"Invalid Integer, try again: ";
            cin.clear();
            cin.ignore(100, '\n');
        }
        else if(!(rowNum>=1 && rowNum<=nptr)){
            cout<<"[1<=value<="<<nptr<<"], retry: Enter the row number: ";
            cin.clear();
            cin.ignore(100, '\n');
        }
        } while(!(rowNum>=1 && rowNum<=nptr) || cin.fail());
        return rowNum;
    }
    void PosApp::stockItem(){
        int stock;
        actionTitle("Select an item to stock");
        int rowNum = selectItem();
        cout<<"Selected Item:\n";
        if(Iptr[rowNum-1]){
            cout<<Iptr[rowNum-1]->displayType(POS_FORM);
            cout<<"Enter quantity to add: ";
            do{
                cin>>stock;
                if(cin.fail()){
                    cout<<"Invalid Integer, try again: ";
                    cin.clear();
                    cin.ignore(100, '\n');
                }
                else if(!(stock>=1 && stock<=(MAX_STOCK_NUMBER-Iptr[rowNum-1]->quantity()))){
                    cout<<"[1<=value<="<<MAX_STOCK_NUMBER-Iptr[rowNum-1]->quantity()<<"], retry: Enter quantity to add: ";
                    cin.clear();
                    cin.ignore(100, '\n');
                }
            } while(!(stock>=1 && stock<=(MAX_STOCK_NUMBER-Iptr[rowNum-1]->quantity())) || cin.fail());
            Iptr[rowNum-1]->operator+=(stock);
        }
        actionTitle("DONE!");
    }
    void PosApp::listItems(){
        actionTitle("Listing Items");
        int i, j;
        double totalAsset = 0;
        for(i=nptr-1; i>0; i--){
            for(j=0; j<i; j++){
                if(Iptr[j] && Iptr[j+1] && strcmp(Iptr[j]->name(), Iptr[j+1]->name())>0){
                    Item* temp = Iptr[j];
                    Iptr[j] = Iptr[j+1];
                    Iptr[j+1] = temp;
                }
            }
        }
        cout<<" Row | SKU    | Item Name          | Price |TX |Qty |   Total | Expiry Date |"<<endl;
        cout<<"-----|--------|--------------------|-------|---|----|---------|-------------|"<<endl;
        for(int i=0; i<nptr; i++){
            cout<<right<<setw(4)<<i+1<<" | ";
            cout<<Iptr[i]->displayType(POS_LIST)<<endl;
            totalAsset +=Iptr[i]->cost() * Iptr[i]->quantity();
        }
        cout<<"-----^--------^--------------------^-------^---^----^---------^-------------^"<<endl;
        cout<<"                               Total Asset: $  |       "<<totalAsset<<"|"<<endl;
        cout<<"-----------------------------------------------^--------------^"<<endl<<endl;
    }
    Item* PosApp::search(const char sku[MAX_SKU_LEN]){
        Item* A = nullptr;
        for(int i=0; i<nptr; i++){
            if(strcmp(Iptr[i]->sku(), sku)==0){
                A = Iptr[i];
            }
        }
        return A;
    }
    void PosApp::POS(){
        char sku[MAX_SKU_LEN];
        Bill bill;
        actionTitle("Starting Point of Sale");
        cin.ignore(100, '\n');
        do
        {
            cout<<"Enter SKU or <ENTER> only to end sale..."<<endl;
            cout<<"> ";
            cin.getline(sku, MAX_SKU_LEN);
            if(sku[0] != '\0' && !cin.fail()){
                if(search(sku)){
                    int quantityOg = search(sku)->quantity();
                    search(sku)->operator-=(1);
                    if(search(sku)->quantity() == quantityOg-1){
                        cout<<search(sku)->displayType(POS_FORM)<<endl;
                        bill.add(search(sku));
                        cout<<">>>>> Added to bill"<<endl;
                        cout<<">>>>> Total: "<<bill.total()<<endl;
                    }
                    else{
                        search(sku)->clear();
                    }
                }
                else{
                    cout<<"!!!!! Item Not Found !!!!!"<<endl;
                }
            }
            else if(cin.fail()){
                cout<<ERROR_POS_SKU<<endl;
                cin.clear();
                cin.ignore(100, '\n');
            }
        } while (strlen(sku) != 0);
        bill.print(cout);
    }
    void PosApp::saveRecs(){
        actionTitle("Saving Data");
        ofstream output(m_fileName);
        if(!output){
            cout<<"Unable to open file!"<<endl;
        }
        else{
            for(int i=0; i<nptr; i++){
                output << Iptr[i]->itemType();
                Iptr[i]->save(output)<<endl;
                delete Iptr[i];
            }
        }
    }
    bool PosApp::loadRecs(char* fileName){
        char ch;
        actionTitle("Loading Items");
        ifstream input(fileName);
        if(!input){
            ofstream output(fileName);
            output.close();
        }
        else{
            for(int i=0; i<MAX_NO_ITEMS; i++){
                Iptr[i] = nullptr;
            }
            nptr = 0;

            while(input && nptr < MAX_NO_ITEMS){
                if(input.get(ch)){
                    // cout<<ch<<endl;
                    input.ignore();
                    if(ch == 'P'){
                        Iptr[nptr] = new Perishable();
                    }
                    else if(ch == 'N'){
                        Iptr[nptr] = new NonPerishable();
                    }
                    if(Iptr[nptr]){
                        Iptr[nptr]->load(input);
                        input.ignore();
                        nptr++;
                    }
                }
            }
        }
        return true;
    }
    void PosApp::run(){
        loadRecs(m_fileName);
        int selection;
        do
        {
            selection = menu();
            if(selection == 1){
                listItems();
            }
            else if(selection == 2){
                addItems();
            }
            else if(selection == 3){
                removeItem();
            }
            else if(selection == 4){
                stockItem();
            }
            else if(selection == 5){
                POS();
            }
            else if(selection == 0){
                saveRecs();
            }
        } while (selection != 0);
        cout<<"Goodbye!"<<endl;
    }
}