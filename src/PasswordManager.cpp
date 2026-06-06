#include "../include/PasswordManager.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <random>
#include <iomanip>
#include <cstdlib>

using namespace std;

void PasswordManager::write()
{
    ofstream file("../data/passwords.txt", ios::out);

    for (auto c : cred)
    {
        file << c.website
             << "|"
             << c.username
             << "|"
             << encrypt(c.password)
             << endl;
    }

    file.close();
}

void PasswordManager::addCredentials()
{
    Credentials c;

    cout << "Enter website: ";
    cin >> c.website;

    cout << "Enter username: ";
    cin >> c.username;

    cout << "Enter password: ";
    cin >> c.password;

    cred.push_back(c);

    write();

    cout << "Credentials added successfully!" << endl;
}

void PasswordManager::loadCredentials()
{
    cred.clear();

    ifstream file("../data/passwords.txt");

    if (!file)
    {
        cout << "No password file found." << endl;
        return;
    }

    string line;

    while (getline(file, line))
    {
        stringstream ss(line);

        string website;
        string username;
        string password;

        getline(ss, website, '|');
        getline(ss, username, '|');
        getline(ss, password, '|');

        Credentials c;

        c.website = website;
        c.username = username;
        c.password = decrypt(password);

        cred.push_back(c);
    }

    file.close();
}

void PasswordManager::viewCredentials()
{
    if (cred.empty())
    {
        cout << "No credentials stored." << endl;
        return;
    }

    for (auto &c : cred)
    {
        cout << "\nWebsite: " << c.website;
        cout << "\nUsername: " << c.username;
        cout << "\nPassword: " << c.password;
        cout << "\n---------------------\n";
    }
}

void PasswordManager::searchCredential()
{
    cout << "Enter username to search: ";

    string target;
    cin >> target;

    bool found = false;

    for (auto &c : cred)
    {
        if (c.username == target)
        {
            found = true;

            cout << "\nCredential Found" << endl;
            cout << "Website: " << c.website << endl;
            cout << "Username: " << c.username << endl;
            cout << "Password: " << c.password << endl;
        }
    }

    if (!found)
    {
        cout << "Credential Not Found" << endl;
    }
}

void PasswordManager::deleteCredential()
{
    cout << "Enter username to delete: ";

    string target;
    cin >> target;

    bool found = false;

    auto it = cred.begin();

    while (it != cred.end())
    {
        if (it->username == target)
        {
            it = cred.erase(it);

            found = true;

            cout << "Credential Deleted" << endl;
        }
        else
        {
            ++it;
        }
    }

    if (!found)
    {
        cout << "Credential Not Found" << endl;
    }

    write();
}

void PasswordManager::updateCredential()
{
    cout << "Enter username: ";

    string username;
    cin >> username;

    bool found = false;

    for (auto &c : cred)
    {
        if (c.username == username)
        {
            found = true;

            string newPassword;

            cout << "Enter new password: ";
            cin >> newPassword;

            c.password = newPassword;

            cout << "Password Changed Successfully" << endl;
        }
    }

    if (!found)
    {
        cout << "Credential Not Found" << endl;
    }

    write();
}

void PasswordManager::generatePassword()
{
    int length;

    cout << "Enter password length: ";
    cin >> length;

    if (length <= 0)
    {
        cout << "Invalid length." << endl;
        return;
    }

    string chars =
        "abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "0123456789"
        "!@#$%^&*";

    random_device rd;
    mt19937 gen(rd());

    uniform_int_distribution<> dist(0, chars.size() - 1);

    string password;

    for (int i = 0; i < length; i++)
    {
        password += chars[dist(gen)];
    }

    cout << "Generated Password: " << password << endl;
}

bool PasswordManager::login()
{
    ifstream file("master.txt");

    if (!file)
    {
        cout << "Master password file not found." << endl;
        return false;
    }

    string storedPassword;
    getline(file, storedPassword);

    file.close();

    for (int i = 1; i <= 3; i++)
    {
        string enteredPassword;

        cout << "Attempt " << i << "/3" << endl;
        cout << "Enter Master Password: ";

        cin >> enteredPassword;

        if (enteredPassword == storedPassword)
        {
            cout << "Login Successful!" << endl;
            return true;
        }

        cout << "Incorrect Password!" << endl;
    }

    cout << "Too many failed attempts." << endl;

    return false;
}

void PasswordManager::changeMasterPassword()
{
    string newPassword;

    cout << "Enter new master password: ";
    cin >> newPassword;

    ofstream file("master.txt");

    file << newPassword;

    file.close();

    cout << "Master password updated successfully." << endl;
}

string PasswordManager::encrypt(string text)
{
    char key = 'K';

    stringstream ss;

    for (char c : text)
    {
        unsigned char encrypted = c ^ key;

        ss << hex
           << setw(2)
           << setfill('0')
           << (int)encrypted;
    }

    return ss.str();
}

string PasswordManager::decrypt(string text)
{
    char key = 'K';

    string result;

    for (size_t i = 0; i < text.length(); i += 2)
    {
        string byteString = text.substr(i, 2);

        char encrypted =
            (char)strtol(byteString.c_str(), nullptr, 16);

        result += encrypted ^ key;
    }

    return result;
}
