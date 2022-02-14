/*
 * @Description: An implementation of double-circular linked list with head pointer 
 * @Version: 
 * @Author: Xuanying Chen
 * @Date: 2022-02-14 14:25:50
 * @LastEditTime: 2022-02-14 20:09:25
 */
#include <iostream>
using namespace std;

class Node
{
public:
    int data;
    Node *next;
    Node *pre;
};

class LinkedList
{
public:
    Node* head;

    LinkedList();
    bool isEmpty();
    void print_data();
    void del(int data);
    void insert(int data);
    Node* find(int data); 
    vector<int> to_vector();

};

LinkedList::LinkedList()
{
    head = new Node();
    head->next = head;
    head->pre  = head;
};

bool LinkedList::isEmpty()
{
    if(head->next==head)
    {
        return true;
    }
    else
    {
        return false;
    }
};

void LinkedList::print_data()
{
    if(isEmpty())
    {
        printf("list is empty!\n");
    }
    else
    {
        printf("list data:\t");
        Node* p = head->next;
        while(p!=head)
        {
            cout << p->data <<" ";
            p = p->next;
        }
    }   
};

void LinkedList::insert(int data)
{ 
    Node* n = new Node();
    n->data = data;

    n->pre = head->pre;
    head->pre->next = n;
    head->pre = n;
    n->next = head;
};

void LinkedList::del(int data)
{
    Node* p = find(data);

    if(p)
    {
        p->pre->next = p->next;
        p->next->pre = p->pre;
        delete p;
    }
    else
    {
        printf("%d not exist in list!",data);
    }
};

Node* LinkedList::find(int data)
{
    Node* p = head->next;
    while(p!=head)
    {
        if(p->data==data)
        {
            break;
        }

        p = p->next;
    }

    return p;
};

vector<int> LinkedList::to_vector()
{
    vector<int> res;
    
    if(isEmpty())
    {
        printf("list is empty!\n");
    }
    else
    {
        Node* p = head->next;
        while(p!=head)
        {
            res.push_back(p->data);
            p = p->next;
        }
    }   

    return res;
}