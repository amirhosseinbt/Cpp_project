#pragma once
#include <iostream>
#include <string>
#include <ctime>
class Date
{
private:
    int Year, Month, Day;
    std::time_t t = std::time(0);
    std::tm* now = std::localtime(&t);
public:
    Date(std::string year , std::string month , std::string day);
    Date();
    bool check_input(std::string input);
    int get_year();
    int get_month();
    int get_day();    
    bool set_year(std::string y);
    bool set_month(std::string m);
    bool set_day(std::string d);
    void print_date();
    int calculate_age();
    char * get_time();
    
};

