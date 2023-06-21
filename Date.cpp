#include <iostream>
#include <exception>
#include <iomanip>
#include <windows.h>
#include <string>
#include <ctime>


#include "Date.hpp"

#define sleep Sleep(3000)
    Date::Date(const std::string year, const std::string month, const std::string day) : Year{std::stoi(year)}, Month{std::stoi(month)}, Day{std::stoi(day)}
    {
       
        std::cout << (now->tm_year + 1900) << '-' 
            << (now->tm_mon + 1) << '-'
            <<  now->tm_mday
            << "\n";
    }
    Date::Date()
    {
        
    }

    bool Date::set_year(std::string y)
    {
        bool flag = true;
        for (int i = 0; i < y.size(); i++)
        {
            if (y[i] >= 48 && y[i] <= 57)
            {
                ;
            }
            else
            {
                flag = false;
                break;
            }
            
        }
        if(flag)
        {
            try
            {
                if(std::stoi(y) > (now->tm_year + 1900)  || std::stoi(y) < 1900)
                {
                    std::string current_year = std::to_string((now->tm_year + 1900));
                    throw std::invalid_argument("! Year can be between 1900 and "+current_year+".");
                }
                Year = std::stoi(y);
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
                sleep;
                return 0;
            }
        }
        else
        {
            try
            {
             
                    throw std::invalid_argument("! Year just contain numbers.");
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
                sleep;
                return 0;
            }
        }
        
        return 1;

    }
    bool Date::set_month(std::string m)
    {
        bool flag = true;
        for (int i = 0; i < m.size(); i++)
        {
            if (m[i] >= 48 && m[i] <= 57)
            {
                ;
            }
            else
            {
                flag = false;
                break;
            }
            
        }
        if(flag)
        {
            try
            {
                if(std::stoi(m) > 12 || std::stoi(m) < 1)
                {
                    throw std::invalid_argument("! Month can be between 1 and 12.");
                }
                if(Year == (now->tm_year + 1900) && std::stoi(m) > (now->tm_mon + 1))
                {
                    throw std::invalid_argument("! Month is invalid.");
                }
                Month = std::stoi(m);
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
                sleep;
                return 0;
            }
        }
        else
        {
            try
            {
             
                throw std::invalid_argument("! Month just contain numbers.");
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
                sleep;
                return 0;
            }
        }
        
        return 1;
    }
    bool Date::set_day(std::string d)
    {
        bool flag = true;
        for (int i = 0; i < d.size(); i++)
        {
            if (d[i] >= 48 && d[i] <= 57)
            {
                ;
            }
            else
            {
                flag = false;
                break;
            }
            
        }
        if(flag)
        {
            int month_31[7]{1,3,5,7,8,10,12};
            int month_30[4]{4,6,9,11};
            int month_29[1]{2};
            try
            {
                for (int i = 0; i <7 ; i++)
                {
                    if(Month == month_31[i] && std::stoi(d) > 31)
                    {
                        throw std::invalid_argument("! Day can be between 1 and 31.");
                    }
                }
                for (int i = 0; i <4 ; i++)
                {
                    if(Month == month_30[i] && std::stoi(d) > 30)
                    {
                        throw std::invalid_argument("! Day can be between 1 and 30.");
                    }
                }
                for (int i = 0; i <1 ; i++)
                {
                    if(Month == month_29[i] && std::stoi(d) > 29)
                    {
                        throw std::invalid_argument("! Day can be between 1 and 29.");
                    }
                }
                
                if(Year == (now->tm_year + 1900) && Month == (now->tm_mon + 1) && std::stoi(d) > now->tm_mday)
                {
                    throw std::invalid_argument("! Day is invalid.");
                }
                Day = std::stoi(d);
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
                sleep;
                return 0;
            }
        }
        else
        {
            try
            {
             
                throw std::invalid_argument("! Day just contain numbers.");
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
                sleep;
                return 0;
            }
        }
        
        return 1;

    }
    int Date::get_year()
    {
        return Year;
    }
    int Date::get_month()
    {
        return Month;
    }
    int Date::get_day()
    {
        return Day;
    }
    void Date::print_date()
    {
        std::cout << Year << "/"<< std::setfill('0') << std::setw(2) << Month << "/" << std::setw(2) << Day << '\n';
    }
    int Date::calculate_age()
    {
        int y;
        y = (now->tm_year + 1900) - Year;
        return y;
    }
    char * Date::get_time()
    {
        return std::asctime(now);
    }