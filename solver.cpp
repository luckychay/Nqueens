/*
 * @Description: 
 * @Version: 
 * @Author: Xuanying Chen
 * @Date: 2022-02-05 10:39:54
 * @LastEditTime: 2022-02-14 20:07:42
 */

// C++ program to create target string, starting from
// random string using Genetic Algorithm

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

// create chromosome or permutation of genes
vector<int> create_gnome(vector<int> GENES)
{
    vector<int> gnome = GENES;
    random_shuffle(gnome.begin(),gnome.end());
    return gnome;
}

//Initial Population
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

int calculate_all_fit(vector<Population> islands)
{
    int sum = 0;
    for(int i =0; i<islands.size(); ++i)
    {
        sum += islands[i].cal_fitness();
    }
    return sum;
}

// random swap for mutation
void mutated_chromosome(vector<int> &chromosome)
{
    int len = chromosome.size();
    int r = random_num(0, len-1);
    int l = random_num(0, len-1);
    swap(chromosome[r],chromosome[l]);
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

    if(p==a.head)
    {
        return true;
    }
    else
    {
        return false;
    }
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

        if(tmp==all_fitness)
        {
            fit_count++;
        }
        else
        {
            fit_count = 0;
        }

        // migrating every epoch
        if(generation && (generation % MIGRATION_INTERVAL == 0))
        {
            for(int i=0; i<ISLAND_NUM; ++i)
            {
                for(int j=0; j<MIGRATION_SIZE; ++j)
                {
                    int r = random_num(0,POPULATION_SIZE-1);
                    if(i==ISLAND_NUM-1)
                    {
                        swap(islands[i].individuals[r],islands[0].individuals[r]); 
                    }
                    else
                    {
                        swap(islands[i].individuals[r],islands[i+1].individuals[r]); 
                    }
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
                vector<Individual> offsprings = parent1.mate(parent2);

                // Perform survivor selection
                for(int j=0;j < offsprings.size();++j)
                {
                    // 80% offspring mutation probability, mutation is a necessity
                    float p = random_num(0, 100)/100;
                    if(p <= MUTATION_RATE)
                    {   
                        mutated_chromosome(offsprings[j].chromosome);
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

    for(auto sol:solutions)
    {
        LinkedList l;
        for(int i=0;i<sol.size();++i)
        {
            l.insert(sol[i]);
        }
        linkedSolutions.push_back(l);
        res << sol << endl;
    }
    res.close();

    for(int i=0; i<linkedSolutions.size();++i)
    {
        for(int j=i+1; j<linkedSolutions.size();++j)
        {
            if(compare(linkedSolutions[i],linkedSolutions[j]))
            {
                // TODO: pointer memory management
                linkedSolutions.erase(linkedSolutions.begin()+j);                
            }
        }
    }
    ofstream uni_res;
    uni_res.open(to_string(N)+"_queens_unique_solutions.txt");
    for(auto i:linkedSolutions)
    {
        vector tmp = i.to_vector();
        uni_res << tmp <<endl;
    }
    uni_res.close();

    if(solutions.size())
    {   
        // 
        printf("In total %d solutions found within %dms for the %d queens problem.",
                linkedSolutions.size(),en-be,N); 
    }
    else
    {
        cout << "No solution found!" << endl;
    }

    return 0;
}

// 0.99 mutation rate
// not same offsprings number with parents: 325s 201s 355s 466s 159s

// same offsprings number with parents: 166s  56s 60s 44s

// 0.80 mutation rate
// not same offsprings number with parents: 243s 221s 328S 292S 287S 186S

// same offsprings number with parents: 80s 83s 36s 54s 47s