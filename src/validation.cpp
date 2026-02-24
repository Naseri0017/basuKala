#include "validation.hpp"
#include <fstream>
#include <stdexcept>
#include <iostream>

using namespace std;


void Info::set_user_name(string un) {
    user_name = un;
}

void Info::set_password(string pass) {
    password = pass;
}

void Info::set_inventory(unsigned long in) {
    inventory = in;
}

void Info::set_score(unsigned long sc) {
    Score = sc;
}

string Info::get_user_name()  {
    return user_name;
}

string Info::get_password() {
    return password;
}

unsigned long Info::get_inventory() {
    return inventory;
}

unsigned long Info::get_score()  {
    return Score;
}


size_t Validation::hashFunction(const std::string &key) const
{
    size_t hash = 0;
    for (char c : key)
        hash = hash * 131 + c;
    return hash % capacity;
}

void Validation::rehash()
{
    size_t oldCapacity = capacity;
    capacity *= 2;

    Info **oldTable = table;
    table = new Info *[capacity];

    for (size_t i = 0; i < capacity; i++)
        table[i] = nullptr;

    count = 0;

    for (size_t i = 0; i < oldCapacity; i++)
    {
        if (oldTable[i] != nullptr)
            insertInternal(oldTable[i]);
    }

    delete[] oldTable;
}

void Validation::insertInternal(Info *user)
{
    size_t index = hashFunction(user->get_user_name());

    while (table[index] != nullptr)
        index = (index + 1) % capacity;

    table[index] = user;
    count++;
}

Validation::Validation(size_t initialSize)
{
    capacity = initialSize;
    count = 0;

    table = new Info *[capacity];
    for (size_t i = 0; i < capacity; i++)
        table[i] = nullptr;

    ifstream file(path, ios::binary);

    if (file.is_open())
    {
        while (true)
        {
            size_t nameSize;
            if (!file.read(reinterpret_cast<char *>(&nameSize), sizeof(nameSize)))
                break;

            string name(nameSize, ' ');
            file.read(&name[0], nameSize);

            size_t passSize;
            file.read(reinterpret_cast<char *>(&passSize), sizeof(passSize));

            string pass(passSize, ' ');
            file.read(&pass[0], passSize);

            unsigned long inv;
            unsigned long score;

            file.read(reinterpret_cast<char *>(&inv), sizeof(inv));
            file.read(reinterpret_cast<char *>(&score), sizeof(score));

            Info *user = new Info;
            user->set_user_name(name);
            user->set_password(pass);
            user->set_inventory(inv);
            user->set_score(score);

            if ((double)count / capacity >= LOAD_FACTOR)
                rehash();

            insertInternal(user);
        }
        file.close();
    }
}

Validation::~Validation()

{
    
    ofstream file(path, ios::binary | ios::trunc);

    if (file.is_open())
    {
        for (size_t i = 0; i < capacity; i++)
        {
            if (table[i] != nullptr)
            {
                size_t nameSize = table[i]->get_user_name().size();
                size_t passSize = table[i]->get_password().size();

                file.write(reinterpret_cast<char *>(&nameSize), sizeof(nameSize));
                file.write(table[i]->get_user_name().c_str(), nameSize);

                file.write(reinterpret_cast<char *>(&passSize), sizeof(passSize));
                file.write(table[i]->get_password().c_str(), passSize);

                unsigned long inv = table[i]->get_inventory();
                unsigned long score = table[i]->get_score();

                file.write(reinterpret_cast<char *>(&inv), sizeof(inv));
                file.write(reinterpret_cast<char *>(&score), sizeof(score));

                delete table[i];
            }
        }
        file.close();
    }
    delete[] table;
}

Info &Validation::findUser(const std::string &name,
                           const std::string &password)
{
    size_t index = hashFunction(name);
    size_t start = index;

    while (table[index] != nullptr)
    {
        if (table[index]->get_user_name() == name)
        {
            if (table[index]->get_password() == password)
                return *(table[index]);
            else
                throw runtime_error("Incorrect password");
        }

        index = (index + 1) % capacity;
        if (index == start)
            break;
    }

    throw runtime_error("User not found");
}

Info &Validation::findAdmin(const std::string &name,
                            const std::string &password)
{
    if (name != "ted")
        throw runtime_error("Access denied");

    try{

    return findUser(name, password);}
    catch( ... ){
        throw;
    }
}

void Validation::createAccount(const std::string &name,
                               const std::string &pass)
{
    if (name == "ted")
        throw runtime_error("Invalid username");

    try {
        findUser(name, pass);
        throw runtime_error("User already exists");
    } catch (...) {}

    if ((double)count / capacity >= LOAD_FACTOR)
        rehash();

    Info *user = new Info;
    user->set_user_name(name);
    user->set_password(pass);
    user->set_inventory(0);
    user->set_score(0);

    insertInternal(user);
}

void Validation::showAllBalances() const
{
    cout << "---- Current Accounts ----\n";
    for (size_t i = 0; i < capacity; i++)
    {
        if (table[i] != nullptr)
        {
            cout << "Name: " << table[i]->get_user_name()
                 << " | Balance: " << table[i]->get_inventory()
                 << " | Score: " << table[i]->get_score()
                 << "\n";
        }
    }
    cout << "--------------------------\n";
}
void Validation::updateScore(const std::string &name, int points) {
    size_t index = hashFunction(name);
    size_t start = index;

    while (table[index] != nullptr) {
        if (table[index]->get_user_name() == name) {
            unsigned long currentScore = table[index]->get_score();
            table[index]->set_score(currentScore + points);
            return; 
        }
        index = (index + 1) % capacity;
        if (index == start) break;
    }
}