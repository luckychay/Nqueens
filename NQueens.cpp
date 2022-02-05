/*
 * @Description: 
 * @Version: 
 * @Author: Xuanying Chen
 * @Date: 2022-02-05 10:39:54
 * @LastEditTime: 2022-02-05 21:58:09
 */
// C++ program to create target string, starting from
// random string using Genetic Algorithm
 
#include <bits/stdc++.h>
#include <vector>
#include <numeric>

using namespace std;
 
// Number of individuals in each generation
#define POPULATION_SIZE 100

// Valid Genes
std::vector<int> generate_genes(int N)
{
    std::vector<int> GENES;
    for(int i=0; i<N;  ++i)
    {
        GENES.push_back(i+1); 
    }
    return GENES;
}

// Function to generate random numbers in given range
int random_num(int start, int end)
{
    int range = (end-start)+1;
    int random_int = start+(rand()%range);
    return random_int;
}
 
// random swap for mutation
void mutated_chromosome(vector<int> &chromosome)
{
    int len = chromosome.size();
    int r = random_num(0, len-1);
    int l = random_num(0, len-1);
    swap(chromosome[r],chromosome[l]);
}
 
// create chromosome or permutation of genes
vector<int> create_gnome(int N,vector<int> GENES)
{
    vector<int> gnome = GENES;
    random_shuffle(gnome.begin(),gnome.end());
    return gnome;
}
 
// Class representing individual in population
class Individual
{
public:
    vector<int> chromosome;
    vector<int> GENES;
    int N;
    int fitness;
    Individual(vector<int> chromosome,vector<int> GENES, int N);
    vector<Individual> mate(Individual parent2);
    int cal_fitness(int N);
};
 
Individual::Individual(vector<int> chromosome,vector<int> GENES,int N)
{
    this->chromosome = chromosome;
    this->GENES = GENES;
    this->N = N;
    fitness = cal_fitness(N);
};
 
// Perform mating and produce new offspring
vector<Individual> Individual::mate(Individual par2)
{
    // randomly pick crossover point 
    int r = random_num(0,this->N-1);

    // copy first parts into offsprings
    vector<int> chromosome1 = vector<int>(this->chromosome.begin(),this->chromosome.begin()+r);
    vector<int> chromosome2 = vector<int>(par2.chromosome.begin(),par2.chromosome.begin()+r);

    // create second part by inserting values from other parent
    for(int i=r+1; i<this->N; ++i)
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
    offsprings.push_back(Individual(chromosome1,this->GENES,this->N)); 
    offsprings.push_back(Individual(chromosome2,par2.GENES,par2.N)); 

    return offsprings;
};
 
 
// Calculate fittness score, it is the number of
// characters in string which differ from target
// string.
int Individual::cal_fitness(int N)
{
    int fitness = 0;
    for(int i = 0;i<N;++i)
    {
        for (int j=0;j<N;++j)
        {
            if(abs(this->chromosome[i] - this->chromosome[j]) == abs(i-j) && i != j)
                fitness++;
        }    
    }
    return fitness;   
};
 
// Overloading < operator
bool operator<(const Individual &ind1, const Individual &ind2)
{
    return ind1.fitness < ind2.fitness;
}
 
// Driver code
int main()
{
    srand((unsigned)(time(0)));

    time_t begin = time(0);

    // Number of queens
    int N;
    std::vector<int> GENES;

    cout << "Please input the number of queens:" << endl;
    cin >> N;

    GENES = generate_genes(N);

    // current generation
    int generation = 0;
 
    vector<Individual> population;
    bool found = false;
 
    // create initial population
    for(int i = 0;i<POPULATION_SIZE; ++i)
    {
        vector<int> gnome = create_gnome(N,GENES);
        population.push_back(Individual(gnome,GENES,N));
    }
 
    while(!found && generation<= 1e4)
    {
        // sort the population in increasing order of fitness score
        sort(population.begin(), population.end());
        // if the individual having lowest fitness score ie.
        // 0 then we know that we have reached to the target
        // and break the loop
        if(population[0].fitness <= 0)
        {
            found = true;
            break;
        }
 
        // Otherwise generate new offsprings for new generation
        vector<Individual> new_generation;

        for(int k=0; k<POPULATION_SIZE; ++k)
        {
            // Perform parent selection, randomly pick 5 parents and
            // take the best two to do crossover
            vector<Individual> parents;
            int r;
            for(int i=0; i<5; ++i)
            {
                r = random_num(0, POPULATION_SIZE-1); 
                parents.push_back(population[r]);
            } 
            sort(parents.begin(),parents.end());
            Individual parent1 = parents[0];
            Individual parent2 = parents[1];
            vector<Individual> offsprings = parent1.mate(parent2);

            // Perform survivor selection, replace the first one with 
            // higher fitness score than offspring
            for(int j=0;j<2;++j)
            {
                // 80% offspring mutation probability
                float p = random_num(0, 100)/100;
                if(p<=0.8)
                {   
                    // cout << "before mutation offsprings[j]: " << offsprings[j].fitness <<" "<< endl;
                    // for(int m=0;m<offsprings[j].chromosome.size();++m)
                    // {
                    //     cout << offsprings[j].chromosome[m] << "\t";
                    // }
                    // cout << endl;
                    mutated_chromosome(offsprings[j].chromosome);
                    offsprings[j].fitness = offsprings[j].cal_fitness(N);
                    // cout << "after mutation offsprings[j]: " << offsprings[j].fitness << "\t" << offsprings[j].cal_fitness(N) <<" "<< endl;
                    // for(int m=0;m<offsprings[j].chromosome.size();++m)
                    // {
                    //     cout << offsprings[j].chromosome[m] << "\t";
                    // }
                    // cout << endl;
                }
                
                for(int i =POPULATION_SIZE-1;i>=0;--i)
                {
                    if (population[i].fitness >= offsprings[j].fitness)
                    {
                        population[i] = offsprings[j];
                        break;
                    }
                }
            }
        }
        cout<< "Generation: " << generation << "\t";
        cout<< "Fitness: " << population[0].fitness << "\n";
 
        generation++;
    }

    time_t end = time(0);

    if(found)
    {
        cout<< "The result configuration for " << N <<" queens problem is: ";
        for(int i =0; i< population[0].chromosome.size();++i)
        {
            cout << population[0].chromosome[i] << " " ;
        }
        cout << endl ;
        cout << (end-begin) << " s used to get the result." << endl;
    }
    else
    {
        cout << "Exceed max generation number!" << endl;
    }
}
