#include <iostream>
#include <fstream>
#include <map>
#include <vector>
using namespace std ;
class users
{
public :
    string username ;
    string password ;
    void user_register (map < string , string > & keyuser ) //register
    {
        cout << "Enter a username " << endl ;
        cin >> this->username ;
        cout << "Enter password " << endl ;
        cin >> this->password;
        keyuser [username] = password ;
        ofstream file ;
        file.open ("users.txt" , ios::app ) ;
        if (file.is_open()) 
        {
            file << this->username << " " << this->password << endl ;
        }
        else
        {
            cout <<  "Unable to open file" ;
        }
        file.close();
    }
    bool user_login (map < string , string > & keyuser)
    {
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;
        auto it = keyuser.find(username);
        if (it != keyuser.end() && it->second == password) 
        {
            cout << "Login successful\n";
            return true;
        }
        return false;
    }
};