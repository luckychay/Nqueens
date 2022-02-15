/*
 * @Description: 
 * @Version: 
 * @Author: Xuanying Chen
 * @Date: 2022-02-13 18:17:29
 * @LastEditTime: 2022-02-15 16:37:35
 */

// Class representing individual in population
#include <bits/stdc++.h>
using namespace std;

// Function to generate random numbers in given range
int random_num(int start, int end)
{
    int range = (end-start)+1;
    int random_int = start+(rand()%range);
    return random_int;
}

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

class Individual
{
public:
    vector<int> chromosome;
    int fitness;
    Individual(vector<int> chromosome);
    int cal_fitness();

    //crossover methods 
    vector<Individual> order1_crossover(Individual par2);
    vector<Individual> PMX(Individual par2);
    vector<Individual> cycle_crossover(Individual par2);
    
    // mutation methods
    void swap_mutation();
    void insert_mutation();
    void scramble_mutation();
    void inversion_mutation();
};

Individual::Individual(vector<int> chromosome)
{
    this->chromosome = chromosome;
    fitness = cal_fitness();
};
 
// Perform mating and produce new offspring
vector<Individual> Individual::order1_crossover(Individual par2)
{
    int N = this->chromosome.size();

    // randomly pick crossover point 
    int n1,n2,r,l;
    n1 = random_num(0,N-1);
    n2 = random_num(0,N-1);

    if(n1>n2){ r=n1;l=n2; }
    else{ r=n2;l=n1; }
    
    // copy first parts into offsprings
    vector<int> chromosome1 = this->chromosome;
    vector<int> chromosome2 = par2.chromosome;
    
    // cout << l << "\t" << r << endl;
    // cout << "before crossover" << chromosome1 << "\t" << chromosome2 << endl;
    // create second part by inserting values from other parent
    int j = r;
    for(int i=r+1; i<N+l; ++i)
    {
        while(j<N+r+1)
        {
            if (find(chromosome1.begin()+l, chromosome1.begin()+r+1, par2.chromosome[++j%N]) == chromosome1.begin()+r+1)
            {
                chromosome1[i%N] = par2.chromosome[j%N];
                break;
            }
            
        }
    }

    j = r;
    for(int i=r+1; i<N+l; ++i)
    {
        while(j<N+r+1)
        {
            if (find(chromosome2.begin()+l, chromosome2.begin()+r+1, this->chromosome[++j%N]) == chromosome2.begin()+r+1)
            {
                chromosome2[i%N] = this->chromosome[j%N];
                break;
            }
            
        }
    }

    vector<Individual> offsprings = {Individual(chromosome1),Individual(chromosome2)};

    return offsprings;
};
 
// // Partially Mapped Crossover
// vector<Individual> Individual::PMX(Individual par2)
// {
    
// };

// // find two cycles, keep the first one and exchange the second one
// vector<Individual> Individual::cycle_crossover(Individual par2)
// {

// };

// Calculate fittness score, it is the number of
// characters in string which differ from target
// string.
int Individual::cal_fitness()
{
    int N = this->chromosome.size();
    int fit = 0;
    for(int i = 0;i<N;++i)
    {
        for (int j=0;j<N;++j)
        {
            if(abs(this->chromosome[i] - this->chromosome[j]) == abs(i-j) && i != j)
                fit++;
        }    
    }
    return fit;   
};
 
// random swap for mutation
void Individual::swap_mutation()
{
    int len = chromosome.size();
    swap(chromosome[random_num(0, len-1)],chromosome[random_num(0, len-1)]);
};

// randomly pick two positions, move the right to follow the left
// shift the rest along 
void Individual::insert_mutation()
{
    int len = chromosome.size();
    int n1,n2,l,r;
    n1 = random_num(0, len-1);
    n2 = random_num(0, len-1);
    
    if(n1>n2){ r=n1;l=n2; }
    else if(n1<n2){ r=n2;l=n1;}
    else {return;}

    int tmp = chromosome[r];
    for(int i=r;i>l+1;--i)
    {
        chromosome[i]=chromosome[i-1];
    }
    chromosome[l+1] = tmp;
};

// randomly pick a subset of genes and shuffle them 
void Individual::scramble_mutation()
{
    int len = chromosome.size();
    int l,r;
    l = random_num(0, len-1);
    r = random_num(0, len-1);

    l<r?random_shuffle(chromosome.begin()+l,chromosome.begin()+r):  
    random_shuffle(chromosome.begin()+r,chromosome.begin()+l);
};

// randomly pick a subset of genes and reverse them
void Individual::inversion_mutation()
{
    int len = chromosome.size();
    int l,r;
    l = random_num(0, len-1);
    r = random_num(0, len-1);

    l<r?reverse(chromosome.begin()+l,chromosome.begin()+r):  
    reverse(chromosome.begin()+r,chromosome.begin()+l);
};


// Overloading < operator
bool operator<(const Individual &ind1, const Individual &ind2)
{
    return ind1.fitness < ind2.fitness;
}