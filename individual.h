/*
 * @Description: 
 * @Version: 
 * @Author: Xuanying Chen
 * @Date: 2022-02-13 18:17:29
 * @LastEditTime: 2022-02-13 20:42:25
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

class Individual
{
public:
    vector<int> chromosome;
    int fitness;
    Individual(vector<int> chromosome);
    vector<Individual> mate(Individual parent2);
    int cal_fitness();
};

Individual::Individual(vector<int> chromosome)
{
    this->chromosome = chromosome;
    fitness = cal_fitness();
};
 
// Perform mating and produce new offspring
vector<Individual> Individual::mate(Individual par2)
{
    int N = this->chromosome.size();
    // randomly pick crossover point 
    int r = random_num(0,N-1);

    // copy first parts into offsprings
    vector<int> chromosome1 = vector<int>(this->chromosome.begin(),this->chromosome.begin()+r);
    vector<int> chromosome2 = vector<int>(par2.chromosome.begin(),par2.chromosome.begin()+r);

    // create second part by inserting values from other parent
    for(int i=r+1; i<N; ++i)
    {
        if (std::find(chromosome1.begin(), chromosome1.end(), par2.chromosome[i]) == chromosome1.end())
        {
            chromosome1.push_back(par2.chromosome[i]);
        }
        if (std::find(chromosome2.begin(), chromosome2.end(), this->chromosome[i]) == chromosome2.end())
        {
            chromosome2.push_back(this->chromosome[i]);
        }
    }

    for(int i=0; i<r+1; ++i)
    {
        if (std::find(chromosome1.begin(), chromosome1.end(), par2.chromosome[i]) == chromosome1.end())
        {
            chromosome1.push_back(par2.chromosome[i]);
        }
        if (std::find(chromosome2.begin(), chromosome2.end(), this->chromosome[i]) == chromosome2.end())
        {
            chromosome2.push_back(this->chromosome[i]);
        }
    }

    vector<Individual> offsprings;
    offsprings.push_back(Individual(chromosome1)); 
    offsprings.push_back(Individual(chromosome2)); 

    return offsprings;
};
 
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
 
// Overloading < operator
bool operator<(const Individual &ind1, const Individual &ind2)
{
    return ind1.fitness < ind2.fitness;
}
 