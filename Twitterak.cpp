#include <iostream>
#include <string>
#include <windows.h>
#include <exception>
#include <tuple>
#include <map>
#include <utility>
#include <conio.h>
#include <stdlib.h>
#include <vector>
#include <stdlib.h>

#include "User.hpp"
#include "Twitterak.hpp"
#include "Date.hpp"
#include "Tweet.hpp"
#include "Design.hpp"
#define sleep Sleep(3000)
//sleep before cls i use system(CLS) because console will be ugly without it
Twitterak::Twitterak()
{
    auto col = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(col, 10);
    // std::cout << "Welcome to teltweet" << '\n';
    print_welecome();
    SetConsoleTextAttribute(col, 15);
}
void Twitterak::run()
{
    while (1)
    {
        try
        {
            std::cout << "> ";
            if (login_user != nullptr)
            {
                std::cout << login_user->get_usernname() << " >";
            }
            std::string Command, Copy_Command;
            getline(std::cin >> std::ws, Command);
            Copy_Command = Command;
            for (auto &ch : Copy_Command)//for lowercase command
            {
                ch = tolower(ch);
            }
            if (Copy_Command == "help")
            {
                help();
            }
            else if (Copy_Command.find("signup") != std::string::npos)
            {
                if (login_user == nullptr)
                {

                    if (Copy_Command.size() > 7)//signup with parameter after command
                    {
                        std::string user_name;
                        user_name = foraml_username(Command, 7);
                        signup(user_name);
                    }
                    else
                    {
                        signup("");//signup without parameter
                    }
                } // second if
                else
                {
                    throw_method("! For signup you must logout first.");
                }
            } // if
            else if (Copy_Command.find("login") != std::string::npos)
            {
                if (login_user == nullptr)
                {
                    if (Copy_Command.size() > 5)
                    {

                        std::string us_name, pas;
                        bool flag = true;//for separating username and password
                        for (int i = 6; i < Command.size(); i++)
                        {
                            if (Command[i] != '@')
                            {
                                if (Command[i] != ' ' && flag)
                                {
                                    us_name = us_name + Command[i];
                                }
                                else
                                {
                                    flag = false;
                                    if (Command[i] != ' ')
                                    {
                                        pas = pas + Command[i];
                                    }
                                }
                            } // if
                        }
                        if (flag)
                        {
                            try
                            {
                                if (login(us_name))
                                {
                                }
                                else
                                {
                                    throw std::invalid_argument("! Username or Password is incorrect");
                                }
                            }
                            catch (const std::exception &e)
                            {
                                std::cerr << e.what() << '\n';
                                sleep;
                                system("CLS");
                            }
                        }
                        else
                        {
                            try
                            {
                                if (login(us_name, pas))
                                {
                                }
                                else
                                {
                                    throw std::invalid_argument("! Username or Password is incorrect");
                                }
                            }
                            catch (const std::exception &e)
                            {
                                std::cerr << e.what() << '\n';
                                sleep;
                                system("CLS");
                            }
                        }

                    } // if
                    else
                    {
                        login();
                    }
                } // second if
                else
                {
                    throw_method("! For new login you must logout first.");
                }

            } // if
            else if (Copy_Command == "delete account")
            {
                delete_account();
            }
            else if (Copy_Command.find("edit profile") != std::string::npos)
            {
                if (login_user == nullptr)
                {
                    throw_method("! You must login first.");
                }
                else
                {
                    std::string parametr, value;
                    bool flag = true;//for separating parameter and value
                    for (int i = 13; i < Copy_Command.size(); i++)
                    {
                        if (Command[i] != ' ' && flag)
                        {
                            parametr = parametr + Copy_Command[i];
                        }
                        else
                        {
                            flag = false;
                        }
                        if (!flag && Command[i] != '\"' && Command[i] != ' ')
                        {
                            value = value + Command[i];
                        }
                    }
                    if (edit_profile(parametr, value))
                    {
                        std::cout << "* Your " << parametr << " has been successfully changed." << '\n';
                        sleep;
                        system("CLS");
                    }
                    else
                    {
                        std::cout << "! Changing was not successful." << '\n';
                        sleep;
                        system("CLS");
                    }
                }
            }
            else if (Copy_Command.find("profile") != std::string::npos || Copy_Command == "profile" || Copy_Command == "me")
            {
                if (Copy_Command.size() > 7)//for checking which print profile need
                {
                    std::string u_name;
                    u_name = foraml_username(Command, 8);
                    if (search_in_map(u_name))
                    {
                        profile(u_name);
                    }
                    else
                    {
                        throw_method("! This username does not exist.");
                    }

                } // if
                else
                {
                    if (login_user == nullptr)
                    {
                        throw_method("! You must login first.");
                    }
                    else
                    {
                        profile_2();
                    }
                }
            }
            else if (Copy_Command.find("delete tweet") != std::string::npos)
            {
                if (login_user == nullptr)
                {
                    throw_method("! You must login first.");
                }
                else
                {
                    std::string id;
                    for (int i = 13; i < Command.size(); i++)
                    {
                        if (Command[i] != ' ')
                        {
                            id = id + Command[i];
                        }
                    }
                    delete_tweet(std::stoi(id));
                }
            }
            else if (Copy_Command.find("edit tweet") != std::string::npos)
            {
                if (login_user->get_birthday().calculate_age() >= 18)
                {
                    if (login_user == nullptr)
                    {
                        throw_method("! You must login first.");
                    }
                    else
                    {
                        std::string id;
                        for (int i = 11; i < Command.size(); i++)
                        {
                            if (Command[i] != ' ')
                            {
                                id = id + Command[i];
                            }
                        }
                        edit_tweet(std::stoi(id));
                    }
                }
                else
                {
                    throw_method("! You must be at least 18 years old.");
                }
            }
            else if (Copy_Command.find("quote tweet") != std::string::npos)
            {
                std::string uname, id;
                bool flag = false;
                for (int i = 12; i < Command.size(); i++)
                {
                    if (Command[i] != ':' && !flag)
                    {
                        if (Command[i] != '@')
                        {
                            uname = uname + Command[i];
                        }
                    }
                    else
                    {
                        flag = true;
                    }
                    if (flag && Command[i] != ':')
                    {
                        id = id + Command[i];
                    }
                }
                quote_tweet(uname, std::stoi(id));
            }
            else if (Copy_Command.find("retweet") != std::string::npos)
            {
                std::string uname, id;
                bool flag = false;
                for (int i = 8; i < Command.size(); i++)
                {
                    if (Command[i] != ':' && !flag)
                    {
                        if (Command[i] != '@')
                        {
                            uname = uname + Command[i];
                        }
                    }
                    else
                    {
                        flag = true;
                    }
                    if (flag && Command[i] != ':')
                    {
                        id = id + Command[i];
                    }
                }
                retweet(uname, std::stoi(id));
            }
            else if (Copy_Command.find("tweet") != std::string::npos)
            {
                if (login_user == nullptr)
                {
                    throw_method("! You must login first.");
                }
                else
                {
                    std::string value;
                    for (int i = 6; i < Copy_Command.size(); i++)
                    {

                        if (Command[i] != '\"')
                        {
                            value = value + Command[i];
                        }
                    }
                    tweet_fun(value);
                }
            }
            else if (Copy_Command.find("likes") != std::string::npos)
            {
                std::string uname, id;
                bool flag = false;
                for (int i = 0; i < Command.size(); i++)
                {
                    if (Command[i] != ':' && !flag)
                    {
                        if (Command[i] != '@')
                        {
                            uname = uname + Command[i];
                        }
                    }
                    else
                    {
                        flag = true;
                    }
                    if (flag && Command[i] != ':' && (Command[i] >= 48 && Command[i] <= 57))
                    {
                        id = id + Command[i];
                    }
                }
                print_who(uname, std::stoi(id));
            }
            else if (Command[0] == '@')
            {
                std::string uname;
                uname = foraml_username(Command, 0);
                if (login_user == nullptr)
                {
                    throw_method("! You must login first.");
                }
                else
                {
                    if (uname == "me")//for check whose tweets will print
                    {

                        print_tweet((*login_user).get_usernname());
                    }
                    else
                    {
                        print_tweet(uname);
                    }
                }
            }
            else if (Copy_Command.find("dislike") != std::string::npos)
            {
                std::string uname, id;
                bool flag = false;
                for (int i = 8; i < Command.size(); i++)
                {
                    if (Command[i] != ':' && !flag)
                    {
                        if (Command[i] != '@')
                        {
                            uname = uname + Command[i];
                        }
                    }
                    else
                    {
                        flag = true;
                    }
                    if (flag && Command[i] != ':')
                    {
                        id = id + Command[i];
                    }
                }
                dislike_tweet(uname, std::stoi(id));
            }
            else if (Copy_Command.find("like") != std::string::npos)
            {
                std::string uname, id;
                bool flag = false;
                for (int i = 5; i < Command.size(); i++)
                {
                    if (Command[i] != ':' && !flag)
                    {
                        if (Command[i] != '@')
                        {
                            uname = uname + Command[i];
                        }
                    }
                    else
                    {
                        flag = true;
                    }
                    if (flag && Command[i] != ':')
                    {
                        id = id + Command[i];
                    }
                }
                like(uname, std::stoi(id));
            }
            // else if (Copy_Command[0] == '#')
            // {

            // }
            else if (Copy_Command.find("logout") != std::string::npos)
            {
                logout();
            }
            else if (Copy_Command =="exit" || Copy_Command =="quit" || Copy_Command == "q")
            {
                delete login_user;
                delete instance;
                exit(0);
            }
            else
            {
                throw_method("! Undefined command.");
            }
        } // try
        catch (const std::exception &e)
        {
            std::cerr << "! Undefined command." << '\n';
            sleep;
            system("CLS");
        }

    } // while

} // run
void Twitterak::throw_method(std::string message)
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
std::string Twitterak::foraml_username(const std::string command, const int iterator)
{
    std::string user_name;
    for (int i = iterator; i < command.size(); i++)
    {
        if (command[i] != '@')
        {
            user_name = user_name + command[i];
        }
    }
    return user_name;
}
bool Twitterak::search_in_map(const std::string u_name)
{
    auto found = Users.find(u_name);
    if (found != Users.end())
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
void Twitterak::help()
{
    auto col = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(col, 1);
    std::cout << "signup [Username] : Create an acount " << '\n';
    std::cout << "Parameters : " << '\n';
    std::cout << '\t' << "Name  Username  Biography  Country  Link  Birthday  PhoneNumber  Password  Header" << '\n';
    std::cout << "-------------------------------------------------------------------------------" << '\n';

    SetConsoleTextAttribute(col, 2);
    std::cout << "login [Username] [Password]: Login to your acount " << '\n';
    std::cout << "Parameters : " << '\n';
    std::cout << '\t' << "Username  Password" << '\n';
    std::cout << "-------------------------------------------------------------------------------" << '\n';

    SetConsoleTextAttribute(col, 3);
    std::cout << "delete account : You can delete your acount " << '\n';
    std::cout << "-------------------------------------------------------------------------------" << '\n';

    SetConsoleTextAttribute(col, 4);
    std::cout << "profile / me : You can see your profile " << '\n';
    std::cout << "-------------------------------------------------------------------------------" << '\n';

    SetConsoleTextAttribute(col, 5);
    std::cout << "profile Username : You can see profile of this User " << '\n';
    std::cout << "-------------------------------------------------------------------------------" << '\n';

    SetConsoleTextAttribute(col, 6);
    std::cout << "edit profile : You can edit each part of your profile " << '\n';
    std::cout << "Parameters : " << '\n';
    std::cout << '\t' << "After command and in one line write the name of the part that you want to edit then write your new value" << '\n';
    std::cout << "-------------------------------------------------------------------------------" << '\n';

    SetConsoleTextAttribute(col, 7);
    std::cout << "tweet : You can write a tweet" << '\n';
    std::cout << "Parameters : " << '\n';
    std::cout << '\t' << "After command and write your tweet" << '\n';
    std::cout << "-------------------------------------------------------------------------------" << '\n';

    SetConsoleTextAttribute(col, 8);
    std::cout << "@Username (@me): You can see all of the Username's (your) tweets" << '\n';
    std::cout << "-------------------------------------------------------------------------------" << '\n';

    SetConsoleTextAttribute(col, 9);
    std::cout << "delete tweet : You can delete your tweet " << '\n';
    std::cout << "Parameters : " << '\n';
    std::cout << '\t' << "Number of tweet" << '\n';
    std::cout << "-------------------------------------------------------------------------------" << '\n';

    SetConsoleTextAttribute(col, 10);
    std::cout << "edit tweet : You can edit your tweet " << '\n';
    std::cout << "Parameters : " << '\n';
    std::cout << '\t' << "Number of tweet and New tweet" << '\n';
    std::cout << "-------------------------------------------------------------------------------" << '\n';

    SetConsoleTextAttribute(col, 7);
    std::cout << "retweet : You can retweet a tweet " << '\n';
    std::cout << "Parameters : " << '\n';
    std::cout << '\t' << "Username:Number of tweet" << '\n';
    std::cout << "-------------------------------------------------------------------------------" << '\n';

    SetConsoleTextAttribute(col, 2);
    std::cout << "quote tweet : You can quote tweet a tweet " << '\n';
    std::cout << "Parameters : " << '\n';
    std::cout << '\t' << "Username:Number of tweet , comment" << '\n';
    std::cout << "-------------------------------------------------------------------------------" << '\n';

    SetConsoleTextAttribute(col, 3);
    std::cout << "like : You can like a tweet " << '\n';
    std::cout << "Parameters : " << '\n';
    std::cout << '\t' << "Username:Number of tweet" << '\n';
    std::cout << "-------------------------------------------------------------------------------" << '\n';

    SetConsoleTextAttribute(col, 4);
    std::cout << "likes : You can see users that like a tweet. " << '\n';
    std::cout << "Parameters : " << '\n';
    std::cout << '\t' << "Username:Number of tweet" << '\n';
    std::cout << "-------------------------------------------------------------------------------" << '\n';

    SetConsoleTextAttribute(col, 12);
    std::cout << "dislike : You can dislike a tweet " << '\n';
    std::cout << "Parameters : " << '\n';
    std::cout << '\t' << "Username:Number of tweet" << '\n';
    std::cout << "-------------------------------------------------------------------------------" << '\n';

    // SetConsoleTextAttribute(col,12);
    // std::cout << "#text: You can see all of tweets that have this #text" << '\n';
    // std::cout << "-------------------------------------------------------------------------------" << '\n';

    SetConsoleTextAttribute(col, 13);
    std::cout << "logout: You can leave your acount" << '\n';
    std::cout << "-------------------------------------------------------------------------------" << '\n';

    SetConsoleTextAttribute(col, 14);
    std::cout << "exit / quit / q : You can exit the app" << '\n';
    SetConsoleTextAttribute(col, 15);
} // help
bool Twitterak::signup(std::string user_name)
{
    std::string input, birth_input;
    instance = new User;
    if (user_name == "")
    {
        system("CLS");
    }
    if (user_name != "")//for checking that user enter with parameter username or not
    {
        if (!instance->set_username(user_name))
        {
            sleep;
            system("CLS");
            return 0;
        }
        else
        {

            if (search_in_map(user_name))
            {
                std::cout << "! This username exicts." << '\n';
                sleep;
                system("CLS");
                User temp;
                return 0;
            }
            else
            {
                system("CLS");
            }
        }
    }
    else
    {
        while (1)
        {

            std::cout << "$ Username: ";
            getline(std::cin >> std::ws, input);
            std::string u_name;
            u_name = foraml_username(input, 0);
            if (search_in_map(u_name))
            {
                std::cout << "! This username exicts." << '\n';
                sleep;
                system("CLS");
                User temp;
                return 0;
            }
            else
            {
                if (instance->set_username(input))
                {
                    system("CLS");
                    break;
                }
                sleep;
                system("CLS");
            }
        }
    }
    std::cout << "$ Name: ";
    getline(std::cin >> std::ws, input);
    instance->set_name(input);
    system("CLS");

    while (1)
    {
        std::cout << "$ Biography: ";
        getline(std::cin >> std::ws, input);
        if (instance->set_biography(input))
        {
            system("CLS");
            break;
        }
        sleep;
        system("CLS");
    }

    std::cout << "$ Country: ";
    getline(std::cin >> std::ws, input);
    instance->set_country(input);
    system("CLS");

    std::cout << "$ Link: ";
    getline(std::cin >> std::ws, input);
    instance->set_link(input);
    system("CLS");

    Date birth{};
    while (1)
    {
        std::cout << "$ Year of Birthday: ";
        getline(std::cin >> std::ws, birth_input);
        if (birth.set_year(birth_input))
        {
            system("CLS");
            break;
        }
        system("CLS");
    }

    while (1)
    {
        std::cout << "$ Month of Birthday: ";
        getline(std::cin >> std::ws, birth_input);
        if (birth.set_month(birth_input))
        {
            system("CLS");
            break;
        }
        system("CLS");
    }
    while (1)
    {
        std::cout << "$ Day of Birthday: ";
        getline(std::cin >> std::ws, birth_input);
        if (birth.set_day(birth_input))
        {
            system("CLS");
            break;
        }
        system("CLS");
    }
    instance->set_birthday(birth);

    while (1)
    {
        std::cout << "$ PhoneNumber: ";
        getline(std::cin >> std::ws, input);
        if (instance->set_phonenumber(input))
        {
            system("CLS");
            break;
        }
        sleep;
        system("CLS");
    }
    std::cout << "$ Password: ";
    getline(std::cin >> std::ws, input);
    instance->set_password(input);
    system("CLS");

    while (1)
    {
        std::cout << "$ Header (white/red/orange/yellow/green/blue/purple/black): ";
        getline(std::cin >> std::ws, input);
        if (instance->set_header(input))
        {
            system("CLS");
            break;
        }
        sleep;
        system("CLS");
    }
    Users[instance->get_usernname()] = instance;
    login_user = instance;
    std::cout << "* Registration was successful." << '\n';
    sleep;
    system("CLS");

    return 1;

} // signup
bool Twitterak::login()//without parameter after command
{
    while (1)
    {
        try
        {
            std::string use_name, pas;
            std::cout << "$ Username: ";
            getline(std::cin >> std::ws, use_name);

            std::cout << "$ Password: ";
            getline(std::cin >> std::ws, pas);
            bool flag = false;
            auto found = Users.find(use_name);
            if (found != Users.end() && pas == (*found).second->get_password())
            {
                std::cout << "* Login was successful." << '\n';
                flag = true;
                login_user = found->second;
                sleep;
                system("CLS");
                return 1;
            }
            if (!flag)
            {
                throw std::invalid_argument("! Username or Password is incorrect");
            }
        } // try
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        } // catch
        std::cout << "? Do you want to login again ? (y/n)" << '\n';
        std::string check;
        getline(std::cin >> std::ws, check);
        if (check == "y")
        {
            system("CLS");
        }
        else if (check == "n")
        {
            system("CLS");
            return 0;
        }
        else
        {
            std::cout << "Input is invalid so I consider n" << '\n';
            sleep;
            system("CLS");
            return 0;
        }
    } // while
}//login
bool Twitterak::login(std::string user_name)//with parameter username after command
{

    std::string pas;
    std::cout << "$ Password: ";
    getline(std::cin >> std::ws, pas);
    bool flag = false;
    auto found = Users.find(user_name);
    if (found != Users.end() && pas == (*found).second->get_password())
    {
        std::cout << "* Login was successful." << '\n';
        flag = true;
        login_user = found->second;
        sleep;
        system("CLS");
        return 1;
    }
    if (!flag)
    {
        system("CLS");
        User temp;
        return 0;
    }
}//login
bool Twitterak::login(std::string user_name, std::string pass)//with two parameter
{

    bool flag = false;
    auto found = Users.find(user_name);
    if (found != Users.end() && pass == (*found).second->get_password())
    {
        std::cout << "* Login was successful." << '\n';
        flag = true;
        login_user = found->second;
        sleep;
        system("CLS");
        return 1;
    }
    if (!flag)
    {
        User temp;
        return 0;
    }

} // login
void Twitterak::logout()
{
    if (login_user == nullptr)
    {
        try
        {
            throw std::invalid_argument("! You didn't login.");
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
            sleep;
            system("CLS");
        }
    } // if
    else
    {
        login_user = nullptr;
        std::cout << "* Logout was successful." << '\n';
        sleep;
        system("CLS");
    }
} // logout
void Twitterak::delete_account()
{
    if (login_user == nullptr)
    {
        throw_method("! You must login first.");
    } // if
    else
    {
        std::cout << "? This operation cannot be reversed in any way. Are you sure? (y/n) :" << '\n';
        std::string check;
        getline(std::cin >> std::ws, check);
        if (check == "y")
        {
            std::string user_name = login_user->get_usernname();
            Users.erase(user_name);
            login_user = nullptr;
            std::cout << "* Delete account was successful.";
            sleep;
            system("CLS");
        }
        else if (check == "n")
        {
            system("CLS");
        }
        else
        {
            std::cout << "Input is invalid so we consider n" << '\n';
            sleep;
            system("CLS");
        }
    } // else

} // delete account
void Twitterak::profile_2()//shows for login user
{

    auto col = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(col, login_user->get_header_id());
    print_logo2();
    //addition code for header
    // for (int i = 0; i <= 11+(*(login_user->get_usernname())).size(); i++)
    // {
    //     if(i == 0)
    //     {
    //         std::cout <<char(201);
    //     }
    //     else if(i == 11+(*(login_user->get_usernname())).size())
    //     {
    //         std::cout <<char(187)<<'\n';
    //     }
    //     else
    //     {
    //         std::cout <<char(205);
    //     }
    // }
    // for (int i = 0; i <= 11+(*(login_user->get_usernname())).size(); i++)
    // {
    //     if (i == 0)
    //     {
    //         std::cout <<char(186);
    //     }
    //     else if (i == 11+(*(login_user->get_usernname())).size())
    //     {
    //         std::cout <<char(186)<<'\n';
    //     }
    //     else
    //     {
    //         std::cout <<char(176);

    //     }

    // }
    // for (int i = 0; i <= 11+(*(login_user->get_usernname())).size(); i++)
    // {
    //     if(i == 0)
    //     {
    //         std::cout <<char(200);
    //     }
    //     else if(i == 11+(*(login_user->get_usernname())).size())
    //     {
    //         std::cout <<char(188)<<'\n';
    //     }
    //     else
    //     {
    //         std::cout <<char(205);
    //     }
    // }
    SetConsoleTextAttribute(col, 12);
    std::cout << " Username: " << login_user->get_usernname() << '\n';

    SetConsoleTextAttribute(col, 10);
    std::cout << " Name: " << login_user->get_name() << '\n';

    SetConsoleTextAttribute(col, 13);
    std::cout << " Biography: " << login_user->get_biography() << '\n';

    SetConsoleTextAttribute(col, 14);
    std::cout << " Country: " << login_user->get_country() << '\n';

    SetConsoleTextAttribute(col, 11);
    std::cout << " Link: " << login_user->get_link() << '\n';

    SetConsoleTextAttribute(col, 4);
    std::cout << " Birthday: ";
    login_user->get_birthday().print_date();

    SetConsoleTextAttribute(col, 15);
    std::cout << " PhoneNumber: " << login_user->get_phonenumber() << '\n';

    SetConsoleTextAttribute(col, 3);
    std::cout << " Password: " << login_user->get_password() << '\n';

    SetConsoleTextAttribute(col, login_user->get_header_id());
    std::cout << " Header: " << login_user->get_header() << '\n';

    SetConsoleTextAttribute(col, 15);

} // profile_2
void Twitterak::profile(std::string uname)//shows user's profile
{
    auto found = Users.find(uname);
    auto temp = found->second;
    auto col = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(col, temp->get_header_id());
    print_logo1();
    //addition code for header
    // for (int i = 0; i <= 11+(*(temp->get_usernname())).size(); i++)
    // {
    //     if(i == 0)
    //     {
    //         std::cout <<char(201);
    //     }
    //     else if(i == 11+(*(temp->get_usernname())).size())
    //     {
    //         std::cout <<char(187)<<'\n';
    //     }
    //     else
    //     {
    //         std::cout <<char(205);
    //     }
    // }
    // for (int i = 0; i <= 11+(*(temp->get_usernname())).size(); i++)
    // {
    //     if (i == 0)
    //     {
    //         std::cout <<char(186);
    //     }
    //     else if (i == 11+(*(temp->get_usernname())).size())
    //     {
    //         std::cout <<char(186)<<'\n';
    //     }
    //     else
    //     {
    //         std::cout <<char(176);
    //     }

    // }
    // for (int i = 0; i <= 11+(*(temp->get_usernname())).size(); i++)
    // {
    //     if(i == 0)
    //     {
    //         std::cout <<char(200);
    //     }
    //     else if(i == 11+(*(temp->get_usernname())).size())
    //     {
    //         std::cout <<char(188)<<'\n';
    //     }
    //     else
    //     {
    //         std::cout <<char(205);
    //     }
    // }
    SetConsoleTextAttribute(col, 12);
    std::cout << " Username: " << temp->get_usernname() << '\n';

    SetConsoleTextAttribute(col, 10);
    std::cout << " Name: " << temp->get_name() << '\n';

    SetConsoleTextAttribute(col, 13);
    std::cout << " Biography: " << temp->get_biography() << '\n';

    SetConsoleTextAttribute(col, 14);
    std::cout << " Country: " << temp->get_country() << '\n';

    SetConsoleTextAttribute(col, 11);
    std::cout << " Link: " << temp->get_link() << '\n';

    SetConsoleTextAttribute(col, 4);
    std::cout << " Birthday: ";
    temp->get_birthday().print_date();

    SetConsoleTextAttribute(col, temp->get_header_id());
    std::cout << " Header: " << temp->get_header() << '\n';

    SetConsoleTextAttribute(col, 15);
} // profile
bool Twitterak::edit_profile(std::string param, std::string val)
{
    std::string copy_key = login_user->get_usernname();//for earasing in map
    if (param == "name")
    {
        login_user->set_name(val);
    }
    else if (param == "username")
    {
        if (search_in_map(foraml_username(val, 0)))
        {
            throw_method("! This username exists.");
            return 0;
        }
        else
        {
            if (!login_user->set_username(val))
            {
                return 0;
            }
        }
    }
    else if (param == "biography")
    {
        if (!login_user->set_biography(val))
        {
            return 0;
        }
    }
    else if (param == "country")
    {
        login_user->set_country(val);
    }
    else if (param == "link")
    {
        login_user->set_link(val);
    }
    else if (param == "birthday") // format yyyy/mm/dd
    {
        std::string y, m, d;
        for (int i = 0; i < val.size(); i++)//for separating year,month and day
        {
            if (i >= 0 && i < 4)
            {
                y = y + val[i];
            }
            if (i >= 5 && i < 7)
            {
                m = m + val[i];
            }
            if (i >= 8 && i < 10)
            {
                d = d + val[i];
            }
        }
        Date birth;
        sleep;
        if (birth.set_year(y) && birth.set_month(m) && birth.set_day(d))
        {
            login_user->set_birthday(birth);
        }
        else
        {
            return 0;
        }
    }
    else if (param == "phonenumber")
    {
        if (!login_user->set_phonenumber(val))
        {
            return 0;
        }
    }
    else if (param == "password")
    {
        login_user->set_password(val);
    }
    else if (param == "header")
    {
        if (!login_user->set_header(val))
        {
            sleep;
            system("CLS");
            return 0;
        }
    }
    else
    {
        throw_method("! Adjective is incorrect.");
        return 0;
    }
    Users.erase(copy_key);
    Users[login_user->get_usernname()] = login_user;
    return 1;
} // edit
void Twitterak::tweet_fun(std::string con)
{

    login_user->tweet(con);
    int count = 0;
    for (int i = 0; i < con.size(); i++)
    {
        if(con[i] == ' ')
        {
            count++;
        }
    }
    if (count == con.size())
    {
        throw_method("! Tweet can not be null.");
    }
    else
    {
        std::cout << "* Tweet was successful." << '\n';
        sleep;
        system("CLS");
    }
    
    


} // tweet_fun
void Twitterak::print_tweet(std::string un)
{
    auto found_user = Users.find(un);
    if (found_user != Users.end())//check user exict
    {
        auto tw = found_user->second->get_tweets();
        if (tw.empty())//check tweet exict
        {
            throw_method("! No tweet exists.");
        }
        else
        {
            for (auto &data : tw)
            {
                std::cout << data->get_id() << ": " << data->get_content() << " Like: " << data->get_like() << " " << data->get_time_();
            }
        }
    }
    else
    {
        throw_method("! This username does not exist.");
    }
}
void Twitterak::delete_tweet(int id)
{
    auto tw = login_user->get_tweets();
    if (tw.empty())//check tweet exict
    {
        throw_method("! No tweet exists.");
    }
    else
    {
        bool flag = false;//for checking tweet id
        for (int j = 0; j < tw.size(); ++j)
        {
            if (tw[j]->get_id() == id)
            {
                flag = true;
                login_user->earase_tweet(id);
                std::cout << "* Tweet delete was successful." << '\n';
                sleep;
                system("CLS");
            }
        }
        if (!flag)
        {
            throw_method("! Tweet with this number does not exist.");
        }
    }

} // delete tweet
void Twitterak::edit_tweet(int id)
{

    auto tw = login_user->get_tweets();
    if (tw.empty())//check tweet exict
    {
        throw_method("! No tweet exists.");
    }
    else
    {
        bool flag = false;//for checking tweet id
        for (int j = 0; j < tw.size(); j++)
        {
            if (tw[j]->get_id() == id)
            {
                flag = true;
                std::cout << id << ": " << tw[j]->get_content() << '\n';
                std::cout << "* Enter new text for tweet " << id << ":" << '\n';
                std::string input;
                getline(std::cin >> std::ws, input);
                login_user->edit_tweet(id, input);
                std::cout << "* Tweet has been successfully changed." << '\n';
                sleep;
                system("CLS");
            }
        }
        if (!flag)
        {
            throw_method("! Tweet with this number does not exist.");
        }
    }

}//edit tweet
void Twitterak::like(std::string uname, int id)
{
    auto found_user = Users.find(uname);
    if (found_user != Users.end())//check user exict
    {
        auto tw = found_user->second->get_tweets();
        if (tw.empty())//check tweet exict
        {
            throw_method("! No tweet exists.");
        }
        else
        {
            bool flag_ = false;//for checking tweet id
            for (auto &eachtw : tw)
            {
                if (eachtw->get_id() == id)
                {
                    flag_ = true;
                    bool flag = false;//for checking user has liked or hasn't
                    for (auto &who : found_user->second->who(id))
                    {
                        if (who == login_user->get_usernname_addr())
                        {
                            std::cout << "! You have already liked this tweet." << '\n';
                            flag = true;
                            sleep;
                            system("CLS");
                        }
                    }
                    if (!flag)
                    {
                        found_user->second->like(id, login_user->get_usernname_addr());
                        std::cout << "* Tweet has been successfully liked." << '\n';
                        sleep;
                        system("CLS");
                    }
                }
            }
            if (!flag_)
            {
                throw_method("! Tweet with this number does not exist.");
            }
        }
    } // if
    else
    {
        throw_method("! Username was wrong or does not exict.");
    }

} // like
void Twitterak::print_who(std::string uname, int id)
{
    auto found_user = Users.find(uname);
    if (found_user != Users.end())//for check user exict
    {
        auto tw = found_user->second->get_tweets();
        if (!tw.empty())//for check tweet exict
        {
            bool flag = false;//check tweet id
            for (auto &t : tw)
            {
                if (t->get_id() == id)
                {
                    flag = true;
                    if (t->get_who_like().empty())
                    {
                        throw_method("! This tweet does not have any like.");
                    }
                    else
                    {
                        std::cout << "Users that like tweet " << id << ": " << '\n';
                        for (int i = 0; i < t->get_who_like().size(); i++)
                        {
                            std::cout << *(t->get_who_like()[i]) << '\n';
                        }
                    }
                }
            }
            if (!flag)
            {
                throw_method("! Tweet with this number does not exist.");
            }
        }
        else
        {
            throw_method("! No tweet exists.");
        }

    } // if
    else
    {
        throw_method("! Username was wrong or does not exict");
    }

} // print who_like
void Twitterak::dislike_tweet(std::string username, int id)
{
    auto found_user = Users.find(username);
    if (found_user != Users.end())
    {
        auto tw = found_user->second->get_tweets();
        if (tw.empty())
        {
            throw_method("! No tweet exists.");
        }
        else
        {
            bool flag_ = false;//check tweet id
            for (auto &eachtw : tw)
            {
                if (eachtw->get_id() == id)
                {
                    flag_ = true;
                    bool flag = false;//for check user has liked or hasn't
                    for (auto &who : found_user->second->who(id))
                    {
                        if (who == login_user->get_usernname_addr())
                        {
                            found_user->second->dlike(id, login_user->get_usernname_addr());
                            std::cout << "* Tweet dislike was successful." << '\n';
                            flag = true;
                            sleep;
                            system("CLS");
                        }
                    }
                    if (!flag)
                    {
                        std::cout << "! You did not like this tweet." << '\n';
                        sleep;
                        system("CLS");
                    }
                }
            }
            if (!flag_)
            {
                throw_method("! Tweet with this number does not exist.");
            }
        }
    } // if
    else
    {
        throw_method("! Username was wrong or does not exict.");
    }
} // dislike tweet
void Twitterak::retweet(std::string uname, int id)
{
    auto found_user = Users.find(uname);
    if (found_user != Users.end())
    {
        auto tw = found_user->second->get_tweets();
        if (tw.empty())
        {
            throw_method("! No tweet exists.");
        }
        else
        {
            bool flag_ = false;//for check tweet id
            for (auto &eachtw : tw)
            {
                if (eachtw->get_id() == id)
                {
                    flag_ = true;
                    bool flag = false;//for check user retweet
                    for (auto &who : found_user->second->who_re(id))
                    {
                        if (who == login_user->get_usernname_addr())
                        {
                            std::cout << "! You have already retweet this tweet." << '\n';
                            flag = true;
                            sleep;
                            system("CLS");
                        }
                    }
                    if (!flag)
                    {
                        login_user->retweet(id, found_user->second);

                        std::cout << "* Retweet was successful." << '\n';
                        sleep;
                        system("CLS");
                    }
                }
            }
            if (!flag_)
            {
                throw_method("! Tweet with this number does not exist.");
            }
        }
    } // if
    else
    {
        throw_method("! Username was wrong or does not exict.");
    }
} // retweet
void Twitterak::quote_tweet(std::string uname, int id)
{
    auto found_user = Users.find(uname);
    if (found_user != Users.end())
    {
        auto tw = found_user->second->get_tweets();
        if (tw.empty())
        {
            throw_method("! No tweet exists.");
        }
        else
        {
            bool flag_ = false;
            for (auto &eachtw : tw)
            {
                if (eachtw->get_id() == id)
                {
                    flag_ = true;
                    std::cout << "$ Add a comment: ";
                    std::string input;
                    getline(std::cin >> std::ws, input);
                    login_user->tweet(input + "\n   " + eachtw->get_content());
                    std::cout << "* Quote tweet was successful." << '\n';
                    sleep;
                    system("CLS");
                }
            }
            if (!flag_)
            {
                throw_method("! Tweet with this number does not exist.");
            }
        }
    } // if
    else
    {
        throw_method("! Username was wrong or does not exict.");
    }
}//quote tweet