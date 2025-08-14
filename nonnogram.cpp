#include "nonno.h"
int main(int argc, char *argv[]) {
    //speed things up 
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
  
    //process command line 
    getOptions(argc, argv);
    //string command;
    //cout<<"hi\n";
    Solver solver;
    solver.solve();
    // solver.read();
    // solver.print();
    
//     if(!solver.rowcheck(4)){
//         cout<<"works";
//     }



//      solver.puzzle[0] = {0, 1, 1, 1, 0};//pass
//     solver.puzzle[1] = {0, 1, 0, 1, 1}; //pass
//     solver.puzzle[2] = {0, 1, 1, 1, 1};//pass
//     solver.puzzle[3] = {1, 1, 1, 1, 1};//pass
//     //fail
//     for (size_t r = 0; r < solver.dimensions; ++r) {
//     cout << "Row " << r << ": " << (solver.rowcheck(r) ? "PASS" : "FAIL") << "\n";
// }
     //int row_length = 5;

     //testing for generating patterns
    // vector<int> clues = {};  // Means: block of 2, gap, block of 1

    // vector<vector<int>> patterns = solver.totalrowsolutions(clues);

    // cout << "Patterns for clues {2, 1} in row length " << solver.dimensions<< ":\n";
    // for (auto& p : patterns) {
    //     for (int cell : p)
    //         cout << (cell ? "■" : "□"); // ■ for filled, □ for empty
    //     cout << "\n";
    // }

}