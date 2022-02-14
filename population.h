/*
 * @Description: 
 * @Version: 
 * @Author: Xuanying Chen
 * @Date: 2022-02-13 17:53:41
 * @LastEditTime: 2022-02-14 17:55:10
 */

// Class representing population
#include "individual.h"

class Population
{
public:
    int fitness;
    vector<Individual> individuals;

    Population(vector<Individual> GENES);   
    int cal_fitness();
    vector<vector<int>> get_solutions();
};

Population::Population(vector<Individual> individuals)
{
    this->individuals = individuals;
    fitness = cal_fitness();
};

int Population::cal_fitness()
{
    int fit = 0;
    for(int i=0;i<this->individuals.size();++i)
    {
        fit += this->individuals[i].cal_fitness();
    }
    return fit;   
};

vector<vector<int>> Population::get_solutions()
{
    vector<vector<int>> solutions;
    for(auto indiv:this->individuals)
    {
        if(indiv.fitness==0)
        {
            solutions.push_back(indiv.chromosome);
        }
    }
    return solutions;
};
