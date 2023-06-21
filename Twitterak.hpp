#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <tuple>

#include "User.hpp"
#include "Tweet.hpp"
class Twitterak
{
private:
    std::map<std::string, User*> Users;
    User* login_user = nullptr;
    User* instance;
public:
    Twitterak();
    void run();
    void help();
    void throw_method(std::string message);
    std::string foraml_username(const std::string command,const int iterator);
    bool search_in_map(std::string key);
    bool signup(std::string user_name);
    bool login();
    bool login(std::string user_name);
    bool login(std::string user_name , std::string pass);
    void logout();
    void delete_account();
    void profile_2();
    void profile(std::string uname);
    bool edit_profile(std::string param ,std::string val);
    void tweet_fun(std::string con);
    void print_tweet(std::string uname);
    void delete_tweet(int id);
    void edit_tweet(int id);
    void like(std::string username,int id);
    void print_who(std::string username,int id);
    void dislike_tweet(std::string username,int id);
    void retweet(std::string username,int id);
    void quote_tweet(std::string username,int id);
};

