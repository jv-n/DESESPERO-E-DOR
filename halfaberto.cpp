#include <iostream>
#include <string>
#include <sstream>
#include <cmath>

using namespace std;

class node
{
    public:
    int id;
    int peso;
    int rank;
    node* left;
    node* right;
};

int main ()
{
    string name;
    string title;

    cout << "Enter yor name: " << endl;
    getline(cin, name);

    stringstream count_name(name);
    string last_name;
    for(int i = 0; i<2; i++)
    {
        count_name >> last_name;
    }

    cout << "Hello, Mr. " << last_name << endl << "Please, enter your title: ";

    getline(cin, title);

    stringstream count_title(title);
    string first_title;

    count_title >> first_title;
    if(first_title.compare("President") == 0)
    {
        cout << "ACCESS GRANTED"<< endl <<"Welcome, Mr. " << first_title << endl;
    } else if (first_title.compare("Chief") == 0 || first_title.compare("Secretary") == 0 )
    {
         cout << "ACCESS GRANTED"<< endl <<"Welcome, " << first_title << " " << last_name << endl;
    } else cout << "ACCESS DENIED" << endl;

    return 0;
}