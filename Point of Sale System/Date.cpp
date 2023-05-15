/* Citation and Sources...
Final Project Milestone 5 
Module: Date.cpp
Filename: Date.cpp
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
#include "Error.h"
#include "Date.h"
#include "POS.h"
using namespace std;
namespace sdds{
    Date::Date(){
        m_dateOnly = false;
        getSystemDate(m_year, m_month, m_day, m_hour, m_minute, m_dateOnly);
    }
    Date::Date(int year, int month, int day){
        dateOnly(true);
        m_year = year;
        m_month = month;
        m_day = day;
        validation();
    }
    Date::Date(int year, int month, int day, int hour, int minute){
        dateOnly(false);
        m_year = year;
        m_month = month;
        m_day = day;
        m_hour = hour;
        m_minute = minute;
        validation();
    }
    Date& Date::operator=(const Date& rhs){
        m_year = rhs.m_year;
        m_month = rhs.m_month;
        m_day = rhs.m_day;
        m_hour = rhs.m_hour;
        m_minute = rhs.m_minute;
        validation();
        return *this;
    }
    void Date::validation(){
        if(m_year<MIN_YEAR || m_year>MAX_YEAR){
            m_error.set("Invalid Year");
        }
        else if(m_month<1 || m_month>12){
            m_error.set("Invalid Month");
        }
        else if(m_day<1 || m_day>daysOfMonth(m_year, m_month)){
            m_error.set("Invalid Day");
        }
        else if(m_hour<0 || m_hour>23){
            m_error.set("Invalid Hour");
        }
        else if(m_minute<0 || m_minute>59){
            m_error.set("Invlid Minute");
        }
    }
    void Date::clear(){
        m_year = 0;
        m_month = 0;
        m_day = 0;
        m_hour = 0;
        m_minute = 0;
        m_error.clear();
    }
    bool Date::operator==(const Date& rhs) const{
        return (m_year == rhs.m_year || m_month == rhs.m_month || m_day == rhs.m_day || m_hour == rhs.m_hour || m_minute == rhs.m_minute);
    }
    bool Date::operator!=(const Date& rhs) const{
        return (m_year != rhs.m_year || m_month != rhs.m_month || m_day != rhs.m_day || m_hour != rhs.m_hour || m_minute != rhs.m_minute);
    }
    bool Date::operator<(const Date& rhs) const{
        return (m_year < rhs.m_year || m_month < rhs.m_month || m_day < rhs.m_day || m_hour < rhs.m_hour || m_minute < rhs.m_minute);
    }
    bool Date::operator>(const Date& rhs) const{
        return (m_year > rhs.m_year || m_month > rhs.m_month || m_day > rhs.m_day || m_hour > rhs.m_hour || m_minute > rhs.m_minute);
    }
    bool Date::operator<=(const Date& rhs) const{
        return (m_year <= rhs.m_year || m_month <= rhs.m_month || m_day <= rhs.m_day || m_hour <= rhs.m_hour || m_minute <= rhs.m_minute);
    }
    bool Date::operator>=(const Date& rhs) const{
        return (m_year >= rhs.m_year || m_month >= rhs.m_month || m_day >= rhs.m_day || m_hour >= rhs.m_hour || m_minute >= rhs.m_minute);
    }
    Date& Date::dateOnly(bool dateOnly){
        m_dateOnly = dateOnly;
        if(m_dateOnly == true){
            m_hour = 0;
            m_minute = 0;
        }
        return *this;
    }
    Date::operator bool() const{
        return m_error.getError() == nullptr;
    }
    const Error& Date::error() const{
        return m_error;
    }
    const int Date::year() const{
        return m_year;
    }
    const int Date::month() const{
        return m_month;
    }
    const int Date::day() const{
        return m_day;
    }
    const int Date::hour() const{
        return m_hour;
    }
    const int Date::minute() const{
        return m_minute;
    }
    const bool Date::dateOnly() const{
        return m_dateOnly;
    }
    std::ostream& operator<<(std::ostream& os, const Date& a){
        if(a.dateOnly() == true){
            if(a){
                os<<a.year();
                if(a.month()<10){
                    os<<"/0"<<a.month();
                }
                else{
                    os<<"/"<<a.month();
                }
                if(a.day()<10){
                    os<<"/0"<<a.day();
                }
                else{
                    os<<"/"<<a.day();
                }
            }
            else{
                os<<a.error()<<"("<<a.year();
                if(a.month()<10){
                    os<<"/0"<<a.month();
                }
                else{
                    os<<"/"<<a.month();
                }
                if(a.day()<10){
                    os<<"/0"<<a.day()<<")";
                }
                else{
                    os<<"/"<<a.day()<<")";
                }
            }
        }
        else{
            if(a){
                os<<a.year();
                if(a.month()<10){
                    os<<"/0"<<a.month();
                }
                else{
                    os<<"/"<<a.month();
                }
                if(a.day()<10){
                    os<<"/0"<<a.day();
                }
                else{
                    os<<"/"<<a.day();
                }
                if(a.hour()<10){
                    os<<", 0"<<a.hour();
                }
                else{
                    os<<", "<<a.hour();
                }
                if(a.minute()<10){
                    os<<":0"<<a.minute();
                }
                else{
                    os<<":"<<a.minute();
                }
            }
            else{
                os<<a.error()<<"("<<a.year();
                if(a.month()<10){
                    os<<"/0"<<a.month();
                }
                else{
                    os<<"/"<<a.month();
                }
                if(a.day()<10){
                    os<<"/0"<<a.day();
                }
                else{
                    os<<"/"<<a.day();
                }
                if(a.hour()<10){
                    os<<", 0"<<a.hour();
                }
                else{
                    os<<", "<<a.hour();
                }
                if(a.minute()<10){
                    os<<":0"<<a.minute()<<")";
                }
                else{
                    os<<":"<<a.minute()<<")";
                }
            }
        }
        return os;
    }
    std::istream& operator>>(std::istream& is, Date& a){
        bool error = false;
        a.clear();
        is>>a.m_year;
        if(is.fail()){
            a.m_error.set("Cannot read year entry");
            error = true;
        }
        else{
            is.ignore();
            is>>a.m_month;
            if(is.fail()){
                a.m_error.set("Cannot read month entry");
                error = true;
            }
            else{
                is.ignore();
                is>>a.m_day;
                if(is.fail()){
                    a.m_error.set("Cannot read day entry");
                    error = true;
                }
                else if(!a.m_dateOnly){
                    is.ignore();
                    is>>a.m_hour;
                    if(is.fail()){
                        a.m_error.set("Cannot read hour entry");
                        error = true;
                    }
                    else{
                        is.ignore();
                        is>>a.m_minute;
                        if(is.fail()){
                            a.m_error.set("Cannot read minute entry");
                            error = true;
                        }
                    }
                }
            }
        }
        if(!error){
            a.validation();
        }
        return is;
    }
}