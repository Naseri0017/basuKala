#pragma once

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include"History.hpp"

class Info
{ private:
    std::string user_name;
    std::string password;
    unsigned long inventory;
    unsigned long Score;
    
    public:
    HistoryList history;
    void set_user_name(std::string);
    void set_password(std::string);
    void set_inventory(unsigned long);
    void set_score(unsigned long);
    std::string get_user_name();
    std::string get_password();
    unsigned long get_inventory();
    unsigned long get_score();
};

class Validation
{
private:
    Info **table;
    size_t capacity;
    size_t count;
    const double LOAD_FACTOR = 0.7;

   
    size_t hashFunction(const std::string &key) const;

   
    void rehash();

    void insertInternal(Info *user);

public:
    Validation(size_t initialSize = 11);

    ~Validation();

    Info &findUser(const std::string &name, const std::string &password);

    Info &findAdmin(const std::string &name, const std::string &password);

  
    void createAccount(const std::string &name,
                       const std::string &pass);
    
    void showAllBalances() const;
};
