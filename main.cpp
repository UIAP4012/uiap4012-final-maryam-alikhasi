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
class Store 
{
public:
    string ID ;
    string name ;
    long int Number ;
    long double price ;
    Store * next;
    Store(const string & name ,const string& id , const long int & number , const long double & price ) //Constructor
    {
        this->name = name ;
        this->ID = id ;
        this->Number = number ;
        this->price = price ;
        this->next = nullptr ;
    }
};
class storelist 
{
public:
    Store * head;
    storelist() //Constructor
    {
      head = nullptr ;
    }
    ~storelist() //destructor 
    {
      Store * T = this->head ;
      while ( this->head != nullptr )
      {
        this->head = head->next;
        delete T;
        T = this-> head ;
      }
    }
    void addpro(const string& name , const string& id , const long int & number , const long double & price)
    {
        Store * tmp = new Store( name , id , number , price) ;
        tmp->next = nullptr ;
        if (head == nullptr)
        {
            head = tmp ;
        }
        else 
        {
            Store * saver = head ;
            while (saver->next != nullptr) 
            {      
                
                saver = saver->next ;
            }
            saver->next = tmp ; // push back    
        }
    }
    void remove(const string & name) // delete product with name 
    {
      Store *p = head;
      Store *n = NULL;
      if(p->name == name)  
      {
        head = head->next;
        delete p;
        return ;
      }
      while (true)
      {
        n = p;
        p = p->next;
        if (p->name == name)
        {
          n->next = p->next ;  
          delete p;
          break;
        }
      }
    }
   
};