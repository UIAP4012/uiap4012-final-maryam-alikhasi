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
    void edit(const string& name, const string& newid , const long int & newnumber , const long double & newprice ) // edit product
    {
      Store * tmp = head ;
      while (tmp != nullptr)
      {
        if (tmp->name == name)
        {
          tmp->Number = newnumber ;
          tmp->ID = newid ;
          tmp->price = newprice ;
          return ;
        }else
          tmp = tmp->next ;
      }
    }
    void print() 
    {
      Store * tmp = head ;
      while (tmp != nullptr)
      {
        cout << "  name : " << tmp->name << "  ID : " << tmp->ID << "   number : " << tmp->Number << "   price : " << tmp->price << endl ;
        tmp = tmp->next ; 
      }
    }
    void invoice (string name , int n , string change)
    {
        Store * tmp = head ;
        while (tmp != nullptr)
        {
            if (tmp->name == name)
            {
                // read money file
                double money = 1 ;
                if (change != "Rial")
                {
                    ifstream infile ("money.txt");
                    while (! infile.eof())
                    {
                        double m1, m2;
                        string c1, c2;
                        infile >> m1 >> c1 >> m2 >> c2;
                        if (c2 == change){
                            money = m2;
                            break;
                        }
                    }
                    infile.close();
                }
                // Invoice printing
                tmp->Number = tmp->Number - n ;
                long double total_f = n*tmp->price ;
                long double total = (n*tmp->price)*money ;
                long double change_price = tmp->price*money ;
                cout << "Product Name :" << tmp->name << "   The number of purchases :" << n ; 
                cout << "   Unit amount :" << change_price << "   Total amount paid :" << total <<  endl ; 

                //write History of invoices
                ofstream file ;
                file.open ("History of invoices.txt" , ios::app ) ;
                if (file.is_open()) 
                {
                    file << "Product Name :" << tmp->name << "   The number of purchases :" << n ; 
                    file << "   Unit amount :" << tmp->price << "   Total amount paid :" << total_f <<  endl ;
                    file << "*********************************************************" << endl ;
                }
                else
                {
                    cout <<  "Unable to open file" ;
                }
                file.close() ;

                //write csv file 
                ofstream myfile ("invoice.csv");
                if (myfile.is_open())
                {
                    myfile << "Product Name,The number of purchases,Unit amount,Total amount paid\n" ;
                    myfile << name << "," << n << "," << tmp->price << "," << total_f << endl ;
                }
                else
                {
                    cout <<  "Unable to open file" ;
                }
                myfile.close() ;
                return ;
            }   
            else
                tmp = tmp->next ;
        }
    }
    void datafile ()
    {
        // Save inventory of product in the file
        Store * tmp = head ; 
        ofstream file ;
        file.open ("inventory.txt" ) ;
        if (file.is_open()) 
        {
            while (tmp != nullptr)
            {
                file << tmp->name << endl ;
                file << tmp->ID << endl ;
                file << tmp->Number << endl ;
                file << tmp->price << endl ;
                tmp = tmp->next ; 
            }
        }
        else
        {
            cout <<  "Unable to open file" ;
        }
        file.close() ;
    }   
};