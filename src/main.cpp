#include <iostream>
#include <string>
#include<vector>
#include<fstream>
using namespace std;

class Credentials{
    public:
        string website;
        string username;
        string password;
};

vector <Credentials> cred;
void addCredentials();

void menu(){
    cout << "Password Manager" << endl << endl;
    cout <<"1. Add Credential  "<<endl;
    cout <<"2. View Credentials"<<endl;
    cout<<"3. Exit"<<endl;
    int x;
    cin>>x ;
    switch (x){
        case 1:
        addCredentials();
        break;
        /*case 2:
        viewCredentials();
        break;*/
        case 3:
        cout<<"Exiting program"<<endl;
        return;
        default:
        cout<<"Enter valid credential"<<endl;
    }
}
void addCredentials(){
    Credentials c;
    cout<<"Enter website:"<<endl;
    cin>>c.website;
    cout<<"Enter username:"<<endl;
    cin>>c.username;
    cout<<"Enter password:"<<endl;
    cin>>c.password;
    cred.push_back(c);
    ofstream file("passwords.txt", ios::app);
    if(!file)
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
    cout<<"Credentials added succesfully!"<<endl;

}
int main()
{
    menu();
    return 0;


}
