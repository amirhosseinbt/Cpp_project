#pragma once
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <utility>
#include <ctime>
#include "Date.hpp"
#include "Tweet.hpp"
class User
{
private:
    std::string Name , Username , Biography , Country , Link , PhoneNumber , Password , Header;
    Date Birthday;
    int tweet_id=0 , header_num;
    std::vector<Tweet*> tweets;
    Tweet* temp;
    
   
public:
    User();
    void throw_method(std::string message);
    void set_name(std::string name);
    std::string get_name();

    bool set_username(std::string username);
    std::string get_usernname();
    std::string* get_usernname_addr();

    bool set_biography(std::string biography);
    std::string get_biography();

    void set_country(std::string country);
    std::string get_country();

    void set_link(std::string link);
    std::string get_link();

    void set_birthday(Date birthday);
    Date get_birthday();

    bool set_phonenumber(std::string phonenumber);
    std::string get_phonenumber();

    void set_password(std::string password);
    std::string get_password();

    bool set_header(std::string header);
    int get_header_id();
    std::string get_header();

    void tweet(std::string content);

    std::vector<Tweet*> get_tweets();

    void earase_tweet(int id);

    void edit_tweet(int id,std::string con);

    void like(int id,std::string* wh);
    std::vector<std::string*> who(int id);

    void dlike(int id,std::string* wh);

    void retweet(int id,User *& user);
    std::vector<std::string*> who_re(int id);
};
