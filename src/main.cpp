#include "../include/PasswordManager.h"
#include <iostream>

using namespace std;

void menu(PasswordManager &manager)
{
    cout << endl
         << "Password Manager" << endl
         << endl
         << "1. Add Credential" << endl
         << "2. View Credentials" << endl
         << "3. Search Credential" << endl
         << "4. Delete Credential" << endl
         << "5. Update Credential" << endl
         << "6. Generate Password" << endl
         << "7. Change Master Password" << endl
         << "8. Exit" << endl;

    int x;
    cin >> x;
    cin.ignore();

    switch (x)
    {
    case 1:
        manager.addCredentials();
        break;

    case 2:
        manager.viewCredentials();
        break;

    case 3:
        manager.searchCredential();
        break;

    case 4:
        manager.deleteCredential();
        break;

    case 5:
        manager.updateCredential();
        break;

    case 6:
        manager.generatePassword();
        break;

    case 7:
        manager.changeMasterPassword();
        break;

    case 8:
        cout << "Exiting program..." << endl;
        exit(0);

    default:
        cout << "Enter a valid menu item." << endl;
    }
}

int main()
{
    PasswordManager manager;

    if (!manager.login())
    {
        return 0;
    }

    manager.loadCredentials();

    while (true)
    {
        menu(manager);
    }

    return 0;
}
