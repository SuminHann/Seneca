/* Citation and Sources...
Final Project Milestone 5 
Module: Error.cpp
Filename: Error.cpp
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
#include "Error.h"
using namespace std;

namespace sdds{
    Error::Error(){
        m_error = nullptr;
    }
    Error::Error(const char* error){
        set(error);
    }
    
    void Error::set(const char* error){
        // m_error = nullptr;
        
        // clear();
        m_error = new char[strlen(error)+1];
        strcpy(m_error, error);
    }
    Error& Error::operator=(const Error& rhs){
        if(this != &rhs){
            delete[] m_error;
            if(rhs.m_error != nullptr){
                m_error = new char[strlen(rhs.m_error)+1];
                strcpy(m_error, rhs.m_error);
            }
            else{
                m_error = nullptr;
            }
        }
        return *this;
    }
    Error::operator bool() const{
        return m_error != nullptr;
    }
    Error& Error::clear(){
        delete [] m_error;
        m_error = nullptr;
        return *this;
    }
    Error::~Error(){
        delete[] m_error;
        m_error = nullptr;
    }
    const char* Error::getError() const{
        return m_error;
    }
    ostream& operator<<(ostream& os, const Error& a){
        if(a.getError() != nullptr){
            os << a.getError();
        }
        return os;
    }
}