/*
 * @Description: 
 * @Version: 
 * @Author: Xuanying Chen
 * @Date: 2022-02-14 14:57:55
 * @LastEditTime: 2022-02-15 16:25:52
 */
#include <vector>
#include <bits/stdc++.h>
#include "linkedList.h"

// overloading << operator
template <typename T> 
ostream& operator<<(ostream& out, vector<T>& v)
{
    if (!v.empty()) {
        out << '[';
        copy(v.begin(), v.end()-1, ostream_iterator<T>(out, ", "));
        copy(v.end()-1,v.end(),ostream_iterator<T>(out, ""));
        out << "]";
    }
    return out;
}

int random_num(int start, int end)
{
    int range = (end-start)+1;
    int random_int = start+(rand()%range);
    return random_int;
}

bool compare(LinkedList a, LinkedList b)
{
    Node* bh = b.find(a.head->next->data);
    Node* p = a.head->next;
    while(p!=a.head)
    {
        
        if(bh==b.head)
            bh = b.head->next;
        // cout << p->data << "\t" << bh->data << endl;
        if(p->data!=bh->data)
            break;
        p = p->next;
        bh = bh->next;
    }

    if(p==a.head)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int main()
{
   vector<vector<int>> a={{1, 3, 5, 2, 4},
                        {1, 4, 2, 5, 3},
                        {2, 4, 1, 3, 5},
                        {2, 5, 3, 1, 4},
                        {3, 1, 4, 2, 5},
                        {3, 5, 2, 4, 1},
                        {4, 1, 3, 5, 2},
                        {4, 2, 5, 3, 1},
                        {5, 2, 4, 1, 3},
                        {5, 3, 1, 4, 2}};
    
    vector<LinkedList> linkedSolutions;

    for(int i=0; i<a.size();++i)
    {
        LinkedList t;
        for(int j=0; j<a[0].size();++j)
        {
            t.insert(a[i][j]);
        }
        linkedSolutions.push_back(t); 
    }

    for(int i=0; i<linkedSolutions.size();++i)
    {
        for(int j=i+1; j<linkedSolutions.size();++j)
        {
            if(compare(linkedSolutions[i],linkedSolutions[j]))
            {
                // TODO: pointer memory management
                linkedSolutions.erase(linkedSolutions.begin()+j--); 
            }
        }
    }

    cout << linkedSolutions.size() <<endl;
    return 0;
}
