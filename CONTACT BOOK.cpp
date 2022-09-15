#include<iostream>
#include<cstdlib>
#include<fstream>
#include<iomanip>
#include<stdio.h>
using namespace std;
class Contact
{
private:
    string name;
    int contactNumber;
    string email;
public:
    Contact();
    Contact(string name, int contactNumber, string email);
    string getName();
    int getcontactNumber();
    string getEmail();
    void setName(string newname);
    void setcontactNumber(int newcontactNumber);
    void setEmail(string newemail);
};
class BinarySearchTree
{
private:
    struct tree_node
    {
        tree_node * left;
        tree_node * right;
//ItemType data;
        Contact data;
    }
    ;
    tree_node*root;
public:
    BinarySearchTree()
    {
        root = NULL;
    }
    bool isEmpty() const
    {
        return root == NULL;
    }
    void print_inorder();
    void inorder(tree_node*);
    void insert(Contact);
    void remove(string);
    void search(string key);
    void changecontactNumber(string key, int newnumber);
};
Contact::Contact()
{
}
Contact::Contact(string newname,int newcontactNumber,string newemail)
{
    name=newname;
    contactNumber=newcontactNumber;
    email=newemail;
}
string Contact::getName()
{
    return name;
}
int Contact::getcontactNumber()
{
    return contactNumber;
}
string Contact::getEmail()
{
    return email;
}
void Contact::setName(string newname)
{
    name=newname;
}
void Contact::setcontactNumber(int newcontactNumber)
{
    contactNumber=newcontactNumber;
}
void Contact::setEmail(string newemail)
{
    email=newemail;
}
void BinarySearchTree::insert(Contact p)
{
    tree_node*t=new tree_node;
    tree_node*parent;
    t->data=p;
    t->left=NULL;
    t->right=NULL;
    parent=NULL;
    if(isEmpty())root=t;
    else
    {
        tree_node*curr;
        curr=root;
        while(curr)
        {
            parent=curr;
            if(t->data.getName()>curr->data.getName())curr=curr->right;
            else curr=curr->left;
        }
        if(t->data.getName()<parent->data.getName())
            parent->left=t;
        else
            parent->right=t;
    }
}
void BinarySearchTree::remove(string p)
{
    bool found=false;
    if(isEmpty())
    {
        cout<<" This Tree is empty! "<<endl;
        return;
    }
    tree_node*curr;
    tree_node*parent;
    curr=root;
    while(curr!=NULL)
    {
        if(curr->data.getName()==p)
        {
            found=true;
            break;
        }
        else
        {
            parent=curr;
            if(p>curr->data.getName())curr=curr->right;
            else curr=curr->left;
        }
    }
    if(!found)
    {
        cout<<" Data not found! "<<endl;
        return;
    }
    if((curr->left==NULL&&curr->right!=NULL)||(curr->left!=NULL
            &&curr->right==NULL))
    {
        if(curr->left==NULL&&curr->right!=NULL)
        {
            if(parent->left==curr)
            {
                parent->left=curr->right;
                delete curr;
            }
            else
            {
                parent->right=curr->right;
                delete curr;
            }
        }
        else
        {
            if(parent->left==curr)
            {
                parent->left=curr->left;
                delete curr;
            }
            else
            {
                parent->right=curr->left;
                delete curr;
            }
        }
        return;
    }
    if(curr->left==NULL&&curr->right==NULL)
    {
        if(parent->left==curr)parent->left=NULL;
        else parent->right=NULL;
        delete curr;
        return;
    }
    if(curr->left!=NULL&&curr->right!=NULL)
    {
        tree_node*chkr;
        chkr=curr->right;
        if((chkr->left==NULL)&&(chkr->right==NULL))
        {
            curr=chkr;
            delete chkr;
            curr->right=NULL;
        }
        else
        {
            if((curr->right)->left!=NULL)
            {
                tree_node*lcurr;
                tree_node*lcurrp;
                lcurrp=curr->right;
                lcurr=(curr->right)->left;
                while(lcurr->left!=NULL)
                {
                    lcurrp=lcurr;
                    lcurr=lcurr->left;
                }
                curr->data=lcurr->data;
                delete lcurr;
                lcurrp->left=NULL;
            }
            else
            {
                tree_node*tmp;
                tmp=curr->right;
                curr->data=tmp->data;
                curr->right=tmp->right;
                delete tmp;
            }
        }
        return;
    }
}
void BinarySearchTree::print_inorder()
{
    inorder(root);
}
void BinarySearchTree::inorder(tree_node*p)
{
    if(p!=NULL)
    {
        if(p->left)inorder(p->left);
        cout<<" "<<p->data.getName()<<"\t\t"<<p->data.getcontactNumber()<<"\t\t"<<p->data.getEmail()
            <<endl;
        if(p->right)inorder(p->right);
    }
    else return;
}
void BinarySearchTree::search(string key)
{
    bool found=false;
    if(isEmpty())
    {
        cout<<" This Tree is empty! "<<endl;
        return;
    }
    tree_node*curr;
    tree_node*parent;
    curr=root;
    while(curr!=NULL)
    {
        if(curr->data.getName()==key)
        {
            found=true;
            cout<<"The phone number for "<<key<<" is "<<curr->data.getcontactNumber()<<endl;
            break;
        }
        else
        {
            parent=curr;
            if(key>curr->data.getName())curr=curr->right;
            else curr=curr->left;
        }
    }
    if(!found)
    {
        cout<<" Data not found! "<<endl;
        return;
    }
}
void BinarySearchTree::changecontactNumber(string p,int newnumber)
{
    bool found=false;
    if(isEmpty())
    {
        cout<<" This Tree is empty! "<<endl;
        return;
    }
    tree_node*curr;
    tree_node*parent;
    curr=root;
    while(curr!=NULL)
    {
        if(curr->data.getName()==p)
        {
            found=true;
            break;
        }
        else
        {
            parent=curr;
            if(p>curr->data.getName())curr=curr->right;
            else curr=curr->left;
        }
    }
    if(!found)
    {
        cout<<" Contact not found. "<<endl;
        return;
    }
    curr->data.setcontactNumber(newnumber);
    cout<<"Number changed successfully. "<<endl;
}
void fillTree(BinarySearchTree*b)
{
    ifstream file;
    file.open("phonebook.txt");
    if(!file)
    {
        cout<<" Error opening file. "<<endl;
    }
    string name;
    int contactNumber;
    string email;
    Contact p;
    while(file>>name>>contactNumber>>email)
    {
        p.setName(name);
        p.setcontactNumber(contactNumber);
        p.setEmail(email);
        cout<<p.getName()<<" "<<p.getcontactNumber()<<" "<<p.getEmail()<<endl;
        (*b).insert(p);
    }
    file.close();
}
int main()
{
    BinarySearchTree b;
    int ch;
    string name;
    string key;
    int contactNumber;
    string email;
    Contact tmp;
    Contact tmp1;
    fillTree(&b);
    while(1)
    {
        cout<<endl<<endl;
        cout<<" Binary Search Tree Operations "<<endl;
        cout<<" ----------------------------- "<<endl;
        cout<<" 0. Search "<<endl;
        cout<<" 1. Insertion/Creation "<<endl;
        cout<<" 2. All Contacts Information "<<endl;
        cout<<" 3. Removal "<<endl;
        cout<<" 4. Change a contactNumber "<<endl;
        cout<<" 5. Exit "<<endl;
        cout<<" Enter your choice : ";
        cin>>ch;
        switch(ch)
        {
        case 0:
            cout<<" Enter the name of the Contact to search for: "<<endl;
            cin>>key;
            b.search(key);
            break;
        case 1:
            cout<<" Enter name to be inserted: ";
            cin>>name;
            cout<<endl<<" Enter phone number: "<<endl;
            cin>>contactNumber;
            cout<<" Enter email: ";
            cin>>email;
            tmp.setName(name);
            tmp.setcontactNumber(contactNumber);
            tmp.setEmail(email);
            b.insert(tmp);
            break;
        case 2:
            cout<<endl;
            cout<<" All Contacts Information "<<endl;
            cout<<" ------------------------"<<endl;
            cout<<" NAME\t\tPHONE\t\tEMAIL"<<endl;
            b.print_inorder();
            break;
        case 3:
            cout<<" Enter data to be deleted : ";
            cin>>key;
            b.remove(key);
            break;
        case 4:
            cout<<" Enter the name of the Contact whose number you wish to change: "<<endl;
            cin>>name;
            cout<<endl<<" Enter the new contactNumber: "<<endl;
            cin>>contactNumber;
            cout<<endl;
            b.changecontactNumber(name,contactNumber);
            break;
        case 5:
            return 0;
        }
    }
}
