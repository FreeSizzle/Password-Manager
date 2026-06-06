#ifndef PASSWORDMANAGER_H
#define PASSWORDMANAGER_H

#include <vector>
#include <string>
#include "Credentials.h"

class PasswordManager
{
private:
    std::vector<Credentials> cred;

public:
    void addCredentials();
    void loadCredentials();
    void viewCredentials();
    void searchCredential();
    void deleteCredential();
    void updateCredential();
    void generatePassword();

    std::string encrypt(std::string text);
    std::string decrypt(std::string text);

    void write();

    bool login();
    void changeMasterPassword();
};

#endif
