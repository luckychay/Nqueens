/*
 * @Description: Solver for n-queens problem using island Genetic Algorithm
 * @Version: 
 * @Author: Xuanying Chen
 * @Date: 2022-02-05 10:39:54
 * @LastEditTime: 2022-02-15 16:48:52
 */

#include <numeric>
#include <windows.h>
#include "population.h"
#include "linkedList.h"
 
// Number of individuals in each generation
#define POPULATION_SIZE 100
#define ISLAND_NUM 5
#define MIGRATION_INTERVAL 100
#define MIGRATION_SIZE 5
#define MUTATION_RATE 0.80
#define TERMINATION_SIZE 30

// Valid Genes
vector<int> generate_genes(int N)
{
    vector<int> GENES;
    for(int i=0; i<N;  ++i)
    {
        GENES.push_back(i+1); 
    }
    return GENES;
}

// Create chromosome or permutation of genes
vector<int> create_gnome(vector<int> GENES)
{
    vector<int> gnome = GENES;
    random_shuffle(gnome.begin(),gnome.end());
    return gnome;
}

// Initial Population
vector<Individual> create_individuals(vector<int> GENES)
{
    vector<Individual> individuals;
    for(int i = 0;i<POPULATION_SIZE; ++i)
    {
        vector<int> gnome = create_gnome(GENES);
        individuals.push_back(Individual(gnome));
    }

    return individuals;
}

// Calculate overall fitness of the islands
int calculate_all_fit(vector<Population> islands)
{
    int sum = 0;
    for(int i =0; i<islands.size(); ++i)
    {
        sum += islands[i].cal_fitness();
    }
    return sum;
}

void draw_solution(vector<int> solution)
{
    for(int i=0; i<solution.size();++i)
    {
        for(int j=0;j<solution.size();++j)
        {
            if(j+1==solution[i])
                cout << "Q " ;
            else
                cout << "0 " ;
        }
        cout << endl;
    }  
}
// compare wheather two circular linked list has the same permutation if 
// the start point can be anywhere  
bool compare(LinkedList a, LinkedList b)
{
    Node* bh = b.find(a.head->next->data);
    Node* p = a.head->next;
    while(p!=a.head)
    {
        if(bh==b.head)
            bh = b.head->next;
        if(p->data!=bh->data)
            break;
        p = p->next;
        bh = bh->next;
    }

    return p==a.head?true:false;
}

// Driver code
int main()
{
    srand((unsigned)(time(0)));

    time_t begin = time(0);
    DWORD be = GetTickCount();

    // Some varaibles to be used later
    int N = 0;
    int all_fitness = 0;
    int fit_count = 0;
    vector<Population> islands;
    set<vector<int>> solutions;
    set<vector<int>> unique_solutions;
    vector<int> GENES;

    cout << "Please input the number of queens:" << endl;
    cin >> N;

    GENES = generate_genes(N);

    // create islands
    for(int i=0; i<ISLAND_NUM; ++i)
    {
        vector<Individual> individuals = create_individuals(GENES);
        islands.push_back(Population(individuals));
    }

    int generation = 0;
    int tmp = 0;
    
    while(1) 
    {
        // terminate if the overall fitness of all the islands 
        // doesn't change for certain generations
        if(fit_count>=TERMINATION_SIZE)
        {
            break;
        }

        // watch the overall fitness
        tmp==all_fitness?fit_count++:fit_count = 0;

        // migrating every epoch, the number of exchanged individuals 
        // is defined by MIGRATION_SIZE
        if(generation && (generation % MIGRATION_INTERVAL == 0))
        {
            for(int i=0; i<ISLAND_NUM; ++i)
            {
                for(int j=0; j<MIGRATION_SIZE; ++j)
                {
                    int r = random_num(0,POPULATION_SIZE-1);
                    swap(islands[i].individuals[r],islands[(i+1)%ISLAND_NUM].individuals[r]); 
                }
                
            }
        }
        // sort populations in increasing order of fitness score
        for(auto pop=islands.begin(); pop!=islands.end();++pop)
        {

            Population population = *pop;

            sort(population.individuals.begin(), population.individuals.end());

            // generate new offsprings for new generation
            for(int k=0; k < POPULATION_SIZE; ++k)
            {
                // Perform parent selection, randomly pick 5 parents and
                // take the best two to do crossover
                vector<Individual> parents;
                int r;
                for(int i=0; i<5; ++i)
                {
                    r = random_num(0, POPULATION_SIZE-1); 
                    parents.push_back(population.individuals[r]);
                }

                sort(parents.begin(),parents.end());
                Individual parent1 = parents[0];
                Individual parent2 = parents[1];
                vector<Individual> offsprings = parent1.order1_crossover(parent2);

                // Perform survivor selection
                for(int j=0;j < offsprings.size();++j)
                {
                    // cout <<"after crossover: " << offsprings[j].chromosome << endl;
                    // 80% offspring mutation probability, mutation is a necessity
                    float p = random_num(0, 100)/100;
                    if(p <= MUTATION_RATE)
                    {   
                        // choose mutation methods randomly
                        switch (rand()%4)
                        {
                            case 0:
                                offsprings[j].swap_mutation();
                                break;
                                
                            case 1:
                                offsprings[j].insert_mutation();
                                break;
                                
                            case 2:
                                offsprings[j].scramble_mutation();
                                break;
                                
                            case 3:    
                                offsprings[j].inversion_mutation();
                                break;
                                
                        }
                        offsprings[j].fitness = offsprings[j].cal_fitness();
                    }

                    // replace the first one with 
                    // higher fitness score than offspring
                    for(int i =POPULATION_SIZE-1;i>=0;--i)
                    {
                        if (population.individuals[i].fitness >= offsprings[j].fitness)
                        {
                            population.individuals[i] = offsprings[j];
                            break;
                        }
                    }
                    
                    // replace the worst one directly
                    // population[POPULATION_SIZE-1] = offsprings[j];
                    // sort(population.begin(), population.end());
                    
                    *pop = population;
                }
            }
        
        }

        tmp=all_fitness;
        all_fitness = calculate_all_fit(islands);

        cout<< "Generation: " << generation << "\n";
        cout<< "Fitness: " << all_fitness << "\n";
 
        generation++;
    }

    time_t end = time(0);
    DWORD en = GetTickCount();

    for(int i=0;i<islands.size();++i)
    {
        vector<vector<int>> s = islands[i].get_solutions();
        solutions.insert(s.begin(),s.end());
    }

    vector<LinkedList> linkedSolutions;
    ofstream res;
    res.open(to_string(N)+"_queens_solutions.txt");

    // save and put all the solutions into circular linked lists
    for(auto sol:solutions)
    {
        // LinkedList l;
        // for(int i=0;i<sol.size();++i)
        // {
        //     l.insert(sol[i]);
        // }
        // linkedSolutions.push_back(l);
        res << sol << endl;
    }
    res.close();

    // // Only can remove duplicate solutions
    // // such as {1, 3, 5, 2, 4} and {2, 4, 1, 3, 5}
    // for(int i=0; i<linkedSolutions.size();++i)
    // {
    //     for(int j=i+1; j<linkedSolutions.size();++j)
    //     {
    //         if(compare(linkedSolutions[i],linkedSolutions[j]))
    //         {
    //             // TODO: pointer memory management
    //             linkedSolutions.erase(linkedSolutions.begin()+j--);                
    //         }
    //     }
    // }
    // // Save unique solutions into file
    // ofstream uni_res;
    // uni_res.open(to_string(N)+"_queens_unique_solutions.txt");
    // for(auto i:linkedSolutions)
    // {
    //     vector tmp = i.to_vector();
    //     uni_res << tmp <<endl;
    // }
    // uni_res.close();

    if(solutions.size())
    {   
        printf("In total %d solutions found within %dms for the %d queens problem.",
               solutions.size(),en-be,N); 
    }
    else
    {
        printf("No solution found!");
    }

    return 0;
}

// 0.99 mutation rate
// not same offsprings number with parents: 325s 201s 355s 466s 159s

// same offsprings number with parents: 166s  56s 60s 44s

// 0.80 mutation rate
// not same offsprings number with parents: 243s 221s 328S 292S 287S 186S

// same offsprings number with parents: 80s 83s 36s 54s 47s