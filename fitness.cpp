/*
 * @Description: 
 * @Version: 
 * @Author: Xuanying Chen
 * @Date: 2022-02-08 13:06:34
 * @LastEditTime: 2022-02-08 15:26:42
 */

#include <bits/stdc++.h>
#include <vector>
#include <numeric>
#include <fstream>

using namespace std;
int cal_fitness(vector<int> chromosome, int N)
{
    int fitness = 0;
    for(int i = 0;i<N;++i)
    {
        for (int j=0;j<N;++j)
        {
            if(abs(chromosome[i] - chromosome[j]) == abs(i-j) && i != j)
                fitness++;
        }    
    }
    return fitness;   
};


// int main()
// {
//     vector<int> chromosome;
//     string str= "45 70 72 65 92 3 35 12 81 86 75 44 9 73 36 82 7 10 18 23 37 41 66 33 90 19 54 50 83 38 91 42 74 6 30 93 79 89 14 20 53 68 21 69 60 34 67 78 55 16 25 2 77 1 40 43 80 76 97 17 24 8 100 71 99 95 98 57 48 39 88 49 15 58 31 27 5 13 22 63 11 64 28 85 96 47 52 59 4 84 32 94 61 26 29 87 56 46 51 62";
    
//     string s=" ";
//     string num="";
//     for(int i=0; i<str.size();++i)
//     {
//         if(str[i]!=s[0])
//         {
//             num += str[i];
//         }
//         else
//         {
//             chromosome.push_back(atoi(num.c_str()));
//             num = "";
//         }
//     }
//     chromosome.push_back(atoi(num.c_str()));
    
//     cout << chromosome.size() << endl;
//     int fit = cal_fitness(chromosome,100);
//     cout << fit << endl;
// }

int main()
{
    vector<int> chromosome;
    ifstream infile;
    ofstream outfile;
    infile.open("100_queen_result.txt",ios::in);
    outfile.open("test.txt");

    int tmp;
    while(infile >> tmp)
    {
        cout << tmp << endl;
        chromosome.push_back(tmp);
        outfile << tmp << " ";
    }
    infile.close();
    cout << chromosome.size() << endl;
    int fit = cal_fitness(chromosome,100);
    cout << fit << endl;
    return 0;
}