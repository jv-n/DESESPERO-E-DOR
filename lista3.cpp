#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class node
{
    public:
    int id;
    int peso;
    int rank;
    int bf;
    int altura;
    node* left;
    node* right;
};

node* add(node* root, int id_val, int byte_val);

int main ()
{
    string line;
    string num1;
    int id;
    int total_stream;
    string function;

    node* root = nullptr;
    
    do{
        getline(cin, line);

        stringstream options(line);
    
        options >> function;
        
        if(function == "ADD")
        {
            options >> num1;
            id = stoi(num1);
            string num2;
            options >> num2;
            int wei = stoi(num2);

            total_stream+=wei;

            root = add(root, id, wei);

            cout << total_stream << endl;            

        } else if(function == "RNK")
        {
            options >> num1;
            id = stoi(num1);
            cout << ranking(root, id) << endl; 
        } else if (function == "WEI")
        {

        }
    } while (function!= "END");

    return 0;
}

node* add(node* root, int id_val, int byte_val)
{
    if(root == nullptr)
    {
        node* temp = new node;
        temp->left = nullptr;
        temp->right = nullptr;
        temp->id = id_val;
        temp->peso = byte_val;
        temp->bf = 0;
        temp->altura = 1;
        return temp;
    }
    if(root->id == id_val)
    {
        root->peso+=byte_val;
        root->altura = 0;
        return root;
    }
    if(id_val<root->id)
    {
        root->rank+=byte_val;
        root->left = add(root->left, id_val, byte_val);
        root->bf-=root->altura;
    } else
    root->right = add(root->right, id_val, byte_val);

    if(root->altura == 0)
    {
        return root;
    }
    else if(root->bf == 0)
    {
        return root;
    }
    else if(root->bf == 1 || root->bf == -1)
    {
        root->altura = 1;
        return root;
    }
    else if(root->bf == -2)
    {
        node* left = new node;
        left = root->left;
        if(left->bf = 1)
        {
            root->left = rotate_left(left);
            delete left;  
        }
        root->altura = 0;
        return rotate_right(root);
    }
    else if(root->bf == 2)
    {
        node* right = new node;
        right = root->right;
        if(right->bf == -1)
        {
            root->right = rotate_right(right);
            delete right;
        }
        root->altura = 0;
        return rotate_left(root);
    }
}

node* rotate_left(node* root)
{
    node* raizR = new node;
    node* raizL = new node;
    raizR = root->right;
    raizL = raizR->left;
    root->right = raizL;
    raizR->left = root;

    root->bf-=1;
    if(raizR->bf > 0)
    {
        root->bf-=raizR->bf;
    }

    raizR->bf-=1;
    if(root->bf<0)
    {
        raizR->bf+=root->bf;
    }

    delete raizL;
    return raizR;

}
node* rotate_right(node* root)
{
    node* raizR = new node;
    node* raizL = new node;
    
    raizL = root->left;
    raizR = raizL->right;
    root->left = raizR;
    raizR->right = root;

    root->bf-=1;
    if(raizL->bf > 0)
    {
        root->bf-=raizL->bf;
    }

    raizL->bf-=1;
    if(root->bf<0)
    {
        raizL->bf+=root->bf;
    }
    delete raizR;
    return raizL;

}

int ranking(node* root, int val)
{
    node* cur = new node;
    cur = root;

    while(cur->id!= val)
    {
        if(val<cur->id)
        {
            cur = cur->left;
        }
        else cur = cur->right;
        if(cur == nullptr)
        {
            return 0;
        }
    }

    return cur->rank;
}