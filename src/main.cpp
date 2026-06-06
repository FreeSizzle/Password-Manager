#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <random>
using namespace std;

string masterPassword = "Manage";

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
        string encrypt(string text);
        string decrypt(string text);
        void write();
        void changeMasterPassword();
        bool login();

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
         << "7. Change Master Password" << endl
         << "8. Exit"<<endl;
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
             << encrypt(c.password)
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
        c.password = decrypt(password);

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
bool PasswordManager::login()
{
    ifstream file("../data/master.txt");

    if(!file)
    {
        cout << "Master password file not found." << endl;
        return false;
    }

    string storedPassword;
    getline(file, storedPassword);

    file.close();

    string enteredPassword;

    cout << "Enter Master Password: ";
    cin >> enteredPassword;

    if(enteredPassword == storedPassword)
    {
        cout << "Login Successful!" << endl;
        return true;
    }

    cout << "Incorrect Password!" << endl;
    return false;
}
void PasswordManager::changeMasterPassword()
{
    string newPassword;

    cout << "Enter new master password: ";
    cin >> newPassword;

    ofstream file("../data/master.txt");

    file << newPassword;

    file.close();

    cout << "Master password updated successfully." << endl;
}
#include <iomanip>
#include <sstream>

string PasswordManager::encrypt(string text)
{
    char key = 'K';

    stringstream ss;

    for(char c : text)
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

    for(size_t i = 0; i < text.length(); i += 2)
    {
        string byteString = text.substr(i, 2);

        char encrypted =
            (char)strtol(byteString.c_str(), nullptr, 16);

        result += encrypted ^ key;
    }

    return result;
}
int main()
{
    PasswordManager manager;

    if(!manager.login())
    {
        return 0;
    }

    manager.loadCredentials();

    while(true)
    {
        menu(manager);
    }

    return 0;
}
