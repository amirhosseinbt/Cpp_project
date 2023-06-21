#include <iostream>
#include <string>
#include <vector>
#include <ctime>

#include "Tweet.hpp"
Tweet::Tweet()
{}
void Tweet::set_content(std::string c)
{
    content = c;
}
std::string Tweet::get_content()
{
    return content;
}
int Tweet::get_id()
{
    return id;
}
void Tweet::set_id(int i)
{
    id = i;
}
void Tweet::like_fun()
{
    like++;
}
void Tweet::dislike()
{
    like--;
}
int Tweet::get_like()
{
    return like;
}
void Tweet::set_who_like(std::string* user)
{
    who_like.push_back(user);
}
std::vector<std::string*> Tweet::get_who_like()
{
    return who_like;
}
void Tweet::set_who_retweet(std::string* user)
{
    who_retweet.push_back(user);
}
std::vector<std::string*> Tweet::get_who_retweet()
{
    return who_retweet;
}
void Tweet::earase_who_like(std::string * uname)
{
    for (int i = 0; i < who_like.size(); i++)
    {
        if (who_like[i] == uname)
        {
            who_like.erase(who_like.begin()+i);
        }
        
    }
}
char* Tweet::get_time_()
{
    return std::ctime(&time_now);
}
void Tweet::set_time(std::time_t now)
{
    time_now = now;

}
