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

void menu()
{
    cout << endl;
    cout << "Password Manager" << endl
         << endl;
    cout << "1. Add Credential  " << endl;
    cout << "2. View Credentials" << endl;
    cout << "3. Exit" << endl;
    int x;
    cin >> x;
    switch (x)
    {
    case 1:
        addCredentials();
        break;

    case 2:
        viewCredentials();
        break;
    case 3:
        cout << "Exiting program" << endl;
        exit(0);
    default:
        cout << "Enter valid credential" << endl;
    }
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
    ofstream file("../data/passwords.txt", ios::app);
    if (!file)
    {
        cout << "Error opening file\n";
        return;
    }
    file << c.website
         << "|"
         << c.username
         << "|"
         << c.password
         << endl;
    file.close();
    cout << "Credentials added succesfully!" << endl;
}
void loadCredentials()
{
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
        c.password = password;
        c.username = username;
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
int main()
{
    loadCredentials();
    while (true)
    {
        menu();
    }
    return 0;
}
