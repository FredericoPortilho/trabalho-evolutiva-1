#include <iostream>

#include "melodia.h"
#include "affective.h"

#include "EA.hpp"
#include "island_EA.hpp"


template <typename problem_class, typename solution_class>
void solve_problem(size_t problem_size){

    double bestFit;
    for(int i = 0; i<50 ; i++){
        // Create a random problem
    problem_class problem(problem_size);

    // Create a solver for the problem
   island_EA<problem_class,solution_class> solver(problem);
        std::cout << "\n\n---------------------Execucao: " << i << "---------------------\n";

        problem.disp();
        solver.run();
        std::cout << solver.best_fx();
        bestFit += solver.best_fx();


    }

        std::cout << "\n\nMedia: " << bestFit/50;

/*
    // Print final statistics
    int idx = 1;
    for (auto iter = solver.best_solutions_begin(); iter != solver.best_solutions_end(); ++iter) {
        std::cout << "Solution " << idx << ": " << std::endl;
        (*iter)->s.disp(problem);
        std::cout << "Objetive function " << idx << ": " << (*iter)->fx << std::endl;
        std::cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\nxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n\n";
        idx++;
    }*/
};

int main() {
    const size_t problem_size = 12;
    solve_problem<affective,melodia>(problem_size);

    return 0;
}
