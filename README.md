# C++ implementation of island GA for solving n-queens problem

Simply run the solver.exe in Windows Powershell, then input the number of queens as you want.

During running time, the program will print generation number and fitness score. When the fitness score doesn't change for 30 generations, the program will stop. The results will be saved into a txt file and the time consuming will be output to the screen.

In total 5 islands with a size of 100 are used, and migration will happen every 100 generations exchanging 30 individuals.

For variation, only order1 crossover method is used for combination while 4 catgory of methods are used for mutation, i.e. swap_mutation, insert_mutation, scramble_mutation, inversion_mutation. The mutation method will be chosen randomly for every iteration of each population.   

For selection, best 2 out of 5 randomly chosen individuals are used to generate offsprings. The offsprings will replace the ones which have lowest fitness score among all individuals with higher fitness score than themselves to build new population(note fitness score is being minimized here).

Some efforts have been made to find unique solutions, but the workload would be a bit huge to filter out all solutions. As some comments in solver.cpp indicates, only permutations with the same order but different start point will be identify as same solutions. More work will be done later since I think the tearm "unique solution" Prof. mentioned is not the same with the one referred in these links.
https://en.wikipedia.org/wiki/Eight_queens_puzzle
https://oeis.org/A002562
https://oeis.org/A000170

For more information about the N-Queens problem, please refer to http://www.durangobill.com/N_Queens.html.
