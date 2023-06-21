#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
class Tweet
{
private:
    std::string content;
    int id,like = 0;
    std::vector<std::string*> who_like;
    std::vector<std::string*> who_retweet;
    std::time_t time_now; 
public:
    Tweet();
    void set_content(std::string c);
    void set_id(int i);
    std::string get_content();
    int get_id();
    void like_fun();
    void dislike();
    int get_like();
    void set_who_like(std::string* user);
    std::vector<std::string*> get_who_like();
    void set_who_retweet(std::string* user);
    std::vector<std::string*> get_who_retweet();
    void earase_who_like(std::string * uname);
    char*get_time_();
    void set_time(std::time_t n);
    

};
