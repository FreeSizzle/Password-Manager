#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <random>
using namespace std;

class Credentials
{
public:
    string website;
    string username;
    string password;
};
class PasswordManager{
    private:
        vector<Credentials> cred;
    public:
        void addCredentials();
        void loadCredentials();
        void viewCredentials();
        void searchCredential();
        void deleteCredential();
        void updateCredential();
        void generatePassword();
        void write();

};
void menu(PasswordManager &manager)
{

    cout << endl
         << "Password Manager" << endl
         << endl
         << "1. Add Credential  " << endl
         << "2. View Credentials" << endl
         << "3. Search Credential" << endl
         << "4. Delete Credential" << endl
         << "5. Update Credential"<<endl
         << "6. Generate Password"<<endl
         << "7. Exit" << endl;
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
        cout << "Exiting program" << endl;
        exit(0);
    default:
        cout << "Enter valid menu item" << endl;
    }
}
void PasswordManager:: write(){
    ofstream file("../data/passwords.txt", ios::out);
    for (auto c : cred)
    {
        file << c.website
             << "|"
             << c.username
             << "|"
             << c.password
             << endl;
    }
    file.close();
}
void PasswordManager::addCredentials()
{
    Credentials c;
    cout << "Enter website:" << endl;
    cin >> c.website;
    cout << "Enter username:" << endl;
    cin >> c.username;
    cout << "Enter password:" << endl;
    cin >> c.password;
    cred.push_back(c);
    write();
    cout << "Credentials added succesfully!" << endl;
}
void PasswordManager::loadCredentials()
{
    cred.clear();
    ifstream file("../data/passwords.txt");
    if (!file)
    {
        cout << "No password file found.\n";
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
        c.password = password;

        cred.push_back(c);
    }
    file.close();
}
void PasswordManager::viewCredentials()
{
    if (cred.empty())
    {
        cout << "No credentials stored.\n";
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
void PasswordManager:: searchCredential()
{
    cout << "Enter username to search :" << endl;
    string target;
    cin >> target;
    int flag = 0;
    for (auto x : cred)
    {
        if (x.username == target)
        {
            cout << "Credential Found" << endl;
            flag = 1;
            cout << x.website << "|" << x.username << "|" << x.password << endl;
        }
    }
    if (flag == 0)
        cout << "Credential Not Found" << endl;
}
void PasswordManager::deleteCredential()
{
    cout << "Enter username to delete:" << endl;
    string target;
    cin >> target;
    auto it = cred.begin();
    int flag = 0;
    while (it != cred.end())
    {
        if (it->username == target)
        {
            it = cred.erase(it);
            cout << "Credential Deleted" << endl;
            flag = 1;
        }
        else
        {
            ++it;
        }
    }
    if (flag == 0)
        cout << "Credential Not Found" << endl;

    write();
}
void PasswordManager::updateCredential()
{
    string s;
    cout << "Enter username:" << endl;
    cin >> s;
    for (auto &c : cred)
    {
        if (c.username == s){
            cout<<"Enter new password:"<<endl;
            string pass;
            cin>>pass;
            c.password = pass;
            cout<<"Password Changed";
        }
    }
    write();
}
void PasswordManager::generatePassword()
{
    int length;

    cout << "Enter password length: ";
    cin >> length;

    string chars =
        "abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "0123456789"
        "!@#$%^&*";

    random_device rd;
    mt19937 gen(rd());

    uniform_int_distribution<> dist(0, chars.size() - 1);

    string password;

    for(int i = 0; i < length; i++)
    {
        password += chars[dist(gen)];
    }

    cout << "Generated Password: " << password << endl;
}
int main()
{
    PasswordManager manager;
    manager.loadCredentials();
    while (true)
    {
        menu(manager);
    }
    return 0;
}
