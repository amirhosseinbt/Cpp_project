#include <iostream>
#include <string>
#include <exception>
#include <map>
#include <windows.h>
#include <utility>
#include <vector>
#include <string>
#include <ctime>
#include <chrono>
#include "Date.hpp"
#include "User.hpp"
#include "Tweet.hpp"
#define sleep Sleep(3000)
User::User()
{
};
void User::throw_method(std::string message)
{
    try
    {
        throw std::invalid_argument(message);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        sleep;
        system("CLS");
    }
}
void User::set_name(std::string name)
{
    Name = name;
}
std::string User::get_name()
{
    return Name;
}
bool User::set_username(std::string username)
{
       
        bool flag = true;
        try
        {
            if (username.size() < 5)
            {
                throw std::invalid_argument("! Username must contain at least 5 character.");
            } // if
            std::string cpy_username;
            for (int i = 0; i < username.size(); i++)
            {
                if ((username[0] >= 48 && username[0] <= 57))
                {
                    throw std::invalid_argument("! Username can not start with number.");
                } // if
                if ((username[i] >= 48 && username[i] <= 57) || (username[i] >= 65 && username[i] <= 90) || (username[i] >= 97 && username[i] <= 122))
                {
                    cpy_username = cpy_username + username[i];
                } // if
                else if(username[i] == '@' && i == 0)//for username that have @ at first
                {
                    if ((username[1] >= 48 && username[1] <= 57))
                    {
                        throw std::invalid_argument("! Username can not start with number.");
                    }
                }// else
                else
                {
                    throw std::invalid_argument("! Username just contains numbers and English letters.");
                }
            }// for
            username = cpy_username;
            std::string commands = "help,signup,login,delete account,profile,me,edit,tweet,delete,like,logout,exit,quit,q,likes,dislike,retweet,quote tweet"; // all commands most be lowercase
            std::string single_command ;
            for (int i = 0; i < commands.size(); i++)//check username is reserved key or not
            {
                std::string nulstring;
                if(commands[i] == ',')
                {
                    if(username == single_command)
                    {
                        throw std::invalid_argument("! This is a reserved keyword. You can not choose it as your username.");
                    }
                    single_command = nulstring;
                }
                else
                {
                    single_command = single_command + commands[i];

                }
            }
           
            Username = username;
        }
        catch (const std::exception &e)
        {
            flag = false;
            std::cerr << e.what() << '\n';
        }

    return flag;

} // set_username
std::string User::get_usernname()
{
    return Username;
}
std::string* User::get_usernname_addr()
{
    return &Username;
}
bool User::set_biography(std::string biography)
{

    bool flag = true;
    try
    {

        if (biography.size() > 160)
        {
            throw std::invalid_argument("! Biography must has less than 160 characters.");
        }
        Biography = biography;
    }
    catch (const std::exception &e)
    {
        flag = false;
        std::cerr << e.what() << '\n';
    }

    return flag;

}
std::string User::get_biography()
{
    return Biography;
}
void User::set_country(std::string country)
{
    Country = country;
}
std::string User::get_country()
{
    return Country;
}
void User::set_link(std::string link)
{
    std::string https = "https://";
    if (link.find(https) == std::string::npos)
    {
        Link = https + link;
    }
    else
    {
        Link = link;
    }
}
std::string User::get_link()
{
    return Link;
}
void User::set_birthday(Date birthday) // validation will execute in getting day month year
{
    int y = birthday.get_year();
    int m = birthday.get_month();
    int d = birthday.get_day();
    Birthday.set_year(std::to_string(y));
    Birthday.set_month(std::to_string(m));
    Birthday.set_day(std::to_string(d));
}
Date User::get_birthday()
{
    return Birthday;
}
bool User::set_phonenumber(std::string phonenumber)
{
    bool flag = true;
    try
    {
        for (int i = 0; i < phonenumber.size(); i++)
        {
            if (phonenumber[i] >= 48 && phonenumber[i] <= 57)
            {
            }
            else
            {
                throw std::invalid_argument("! Phonenumber just contains numbers.");
            }
        }
        PhoneNumber = phonenumber;
    }
    catch (const std::exception &e)
    {
        flag = false;
        std::cerr << e.what() << '\n';
    }
    return flag;
}
std::string User::get_phonenumber()
{
    return PhoneNumber;
}
void User::set_password(std::string password)
{
    Password = password;
}
std::string User::get_password()
{
    return Password;
}
bool User::set_header(std::string header)
{
    for(auto& ch : header)//lowercase input
    {
        ch = tolower(ch);
    }
    if (header == "white")
    {
        header_num = 15;
    }
    else if (header == "red")
    {
        header_num = 12;
    }
    else if (header == "orange")
    {
        header_num = 4;
    }
    else if (header == "yellow")
    {
        header_num = 14;
    }
    else if (header == "green")
    {
        header_num = 10;
    }
    else if (header == "blue")
    {
        header_num = 9;
    }
    else if (header == "purple")
    {
        header_num = 13;
    }
    else if (header == "black")
    {
        header_num = 8;
    }
    else
    {
        try
        {
            throw std::invalid_argument("! Color is invalid.");
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            return 0;

        }
        
    }
    
    Header = header;
    return 1;
}
int User::get_header_id()
{
    return header_num;
}
std::string User::get_header()
{
    return Header;
}
void User::tweet(std::string content)
{
    temp = new Tweet;
    temp->set_content(content);
    tweet_id++;
    temp->set_id(tweet_id);
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    std::time_t t_c = std::chrono::system_clock::to_time_t(now);
    temp->set_time(t_c);
    tweets.push_back(temp);
    
}
std::vector<Tweet*> User::get_tweets()
{
    return tweets;
}
void User::earase_tweet(int id)
{
    for (int i = 0; i < tweets.size(); i++)
    {
        if (tweets[i]->get_id()== id)
        {
            tweets.erase(tweets.begin()+i);
        }
        
    }
    
}
void User::edit_tweet(int id,std::string con)
{
    for(auto &t:tweets)
    {
        if (t->get_id()==id)
        {
            t->set_content(con);
        }
        
    }
}
void User::like(int id,std::string* wh)
{
    for(auto &t:tweets)
    {
        if (t->get_id()==id)
        {
            t->like_fun();
            t->set_who_like(wh);
        }
        
    }
}
void User::dlike(int id,std::string* wh)
{
    for(auto &t:tweets)
    {
        if (t->get_id()==id)
        {
            t->dislike();
            t->earase_who_like(wh);
        }
        
    }
}
std::vector<std::string*> User::who(int id)//who like tweet
{
    for(auto &t:tweets)
    {
        if (t->get_id()==id)
        {
            return t->get_who_like();
        }
        
    }
}
void User::retweet(int id,User *& user)
{
    for(auto &t:user->get_tweets())
    {
        if (t->get_id()==id)
        {
            tweets.push_back(t);
            t->set_who_retweet(&Username);
        }
        
    }
}
std::vector<std::string*> User::who_re(int id)//who retweet
{
    for(auto &t:tweets)
    {
        if (t->get_id()==id)
        {
            return t->get_who_retweet();
        }
        
    }
}