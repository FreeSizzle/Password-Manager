#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

class Credentials
{
public:
    string website;
    string username;
    string password;
};

vector<Credentials> cred;
void addCredentials();
void loadCredentials();
void viewCredentials();
void searchCredential();
void deleteCredential();
void updateCredential();
void menu()
{
    cout << endl
         << "Password Manager" << endl
         << endl
         << "1. Add Credential  " << endl
         << "2. View Credentials" << endl
         << "3. Search Credential" << endl
         << "4. Delete Credential" << endl
         << "5. Update Credential"<<endl
         << "6. Exit" << endl;
    int x;
    cin >> x;
    cin.ignore();
    switch (x)
    {
    case 1:
        addCredentials();
        break;

    case 2:
        viewCredentials();
        break;
    case 3:
        searchCredential();
        break;
    case 4:
        deleteCredential();
        break;
    case 5:
        updateCredential();
        break;
    case 6:
        cout << "Exiting program" << endl;
        exit(0);
    default:
        cout << "Enter valid credential" << endl;
    }
}
void write(){
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
void addCredentials()
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
void loadCredentials()
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
void viewCredentials()
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
void searchCredential()
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
void deleteCredential()
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
void updateCredential()
{
    string s;
    cout << "Enter username:" << endl;
    cin >> s;
    for (auto c : cred)
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
int main()
{
    loadCredentials();
    while (true)
    {
        menu();
    }
    return 0;
}
