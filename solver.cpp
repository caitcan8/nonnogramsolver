#include "nonno.h"

//function to read in nonnogram clues 
void Solver::read(){
    //format is dimensions(square) row clues then column clues with the number of clues in front for each
     ifstream file(filename);
    if(!file){
        cerr<<"Could not open "<<filename<<"\n";
    }
    file>>dimensions;
    size_t numclues;
    size_t clue;
    for(size_t i = 0; i < dimensions; ++i){
        //read in row clues 
        file>>numclues;
        vector<size_t> clues;
        for(size_t i = 0; i < numclues; ++i){
            //add all clues for specific row
            file>>clue; 
            clues.push_back(clue);
        }
        //add row to total row vector
        rowclues.push_back(clues);
    }
    for(size_t i = 0; i < dimensions; ++i){
        //read in col clues 
        file>>numclues;
        vector<size_t> clues;
        for(size_t i = 0; i < numclues; ++i){
            //add all clues for specific row
            file>>clue; 
            clues.push_back(clue);
        }
        //add row to total row vector
        colclues.push_back(clues);
    }
    //initialize the puzzle to the right dimensions but unfilled 
    puzzle.resize(dimensions, vector<int>(dimensions, 0));
}

void Solver::print(){
    for(size_t i = 0; i < dimensions; ++i){
        for(size_t j = 0; j<dimensions; ++j){
            cout<<puzzle[i][j];
        }
        cout<<"\n";
    }
}

bool Solver::rowcheck(size_t rownum){
    size_t currpos = 0;
    for(size_t i = 0; i < rowclues[rownum].size(); ++i){
        //loop through total number of clues for that row 
        size_t count = 0; //to keep track of how many are marked for the clue already 
        for(int j = 0; j < int(rowclues[rownum][i]); ++j){
            //loop through each clue 
            if(puzzle[rownum][currpos] == 1){
                ++count;
                ++currpos;
            }
            else{
                j = -1;
                count = 0;
                ++currpos; 
                if(currpos >= dimensions){
                    //if its zeros and goes off the end 
                    return false;
                }
                if(count > 0){
                    return false;
                }
            }

        }
        if(count != rowclues[rownum][i] && puzzle[rownum][currpos] != 0){
            //must be a zero in between clues 

            return false;
        }
        ++currpos;
    }
    //if clues all fit make sure any left over spots are filled with zeros
    if(currpos-1 < dimensions){
        for(size_t i = currpos-1; i < dimensions; ++i){
            if(puzzle[rownum][i] == 1){
                return false;
            }
        }
    }
    return true;
}

void Solver::makesolutions(const vector<int>& clues, size_t currclue, size_t currpos, vector<int>& currsolution, vector<vector<int>>& total){
    //base case
    if(currclue == clues.size()){
        //all clues placed 
        for(size_t i = currpos; i < dimensions; ++i){
            currsolution[i] = 0; //everything else is zeros
        }
        total.push_back(currsolution);
        return;
    }
    size_t cluelength = size_t(clues[currclue]);
    for(size_t pos = currpos; pos + cluelength <= dimensions; ++pos){
        //put all zeros before the curr position
        for(size_t i = currpos; i < pos; ++i ){
            currsolution[i] = 0;
        }
        //fill clue spots with 1
        for(size_t i = pos; i < pos + cluelength; ++i){
            currsolution[i] = 1;
        }
        //account for gap between clues
        if(currclue + 1 < clues.size()){
            if(pos + cluelength >= dimensions){
                //doesn't work if it goes outside dimensions
                continue;
            }
            currsolution[pos + cluelength] = 0;//fill gap with 0
            //now make recursive call
            makesolutions(clues, currclue + 1, pos + cluelength + 1, currsolution, total);

        }
        else{
            //fill the rest with zeros if no more clues
            for(size_t i = pos + cluelength; i < dimensions; ++i){
                currsolution[i] = 0;
            }
            total.push_back(currsolution);//add it to total solutions for row
        }
    }
}
vector<vector<int>>  Solver::totalrowsolutions(vector<int>& clues){
    vector<vector<int>> total;
    vector<int> pattern(dimensions, 0);
    makesolutions(clues, 0, 0, pattern, total);
    return total;
}


void Solver::solve(){
    read(); //read in data
    //make a grid of all possible row solutions
    
    for(size_t i = 0; i < dimensions; ++i){
        vector<int> clues(rowclues[i].begin(), rowclues[i].end());
        //add to grid
        grid.push_back(totalrowsolutions(clues));
    }

    //start at row 0
    //rowsolve(0);
    if (rowsolve(0)) {
        cout << "Solution found:\n";
        print();
    } else {
        cout << "No solution exists.\n";
    }

}

bool Solver::partcolcheck(size_t colnum, size_t torow){
    // size_t currpos = 0;
    // for(size_t i = 0; i < colclues[colnum].size(); ++i){
    //     size_t count = 0;
    //     for(int j = 0; j < int(colclues[colnum][i]); ++j){
    //         if(currpos > torow) return true;

    //         if(puzzle[currpos][colnum] == 1){
    //             ++count;
    //             ++currpos;
    //         } else {
    //             j = -1;
    //             count = 0;
    //             ++currpos;
    //             if(currpos > torow) return true;
    //         }
    //     }
    //     if(currpos <= torow && count != colclues[colnum][i] && puzzle[currpos][colnum] != 0){
    //         return false;
    //     }
    //     ++currpos;
    // }
    // for(size_t r = currpos; r <= torow; ++r){
    //     if(puzzle[r][colnum] == 1) return false;
    // }
    // return true;



    const auto& clues = colclues[colnum];
    size_t clueindex = 0;   // which clue we're matching
    size_t currlen  = 0;   // length of current contiguous 1-run

    // Scan rows 0..torow in this column
    for (size_t r = 0; r <= torow; ++r) { //loop all rows to the row number given
        int curr = puzzle[r][colnum]; 

        if (curr == 1) {
            //if its filled add to the current length
            // No extra blocks beyond number of clues
            if (clueindex >= clues.size()) return false;

            ++currlen;

            //cant be longer than clue length
            if (currlen > clues[clueindex]) return false;
        } else { // cell == 0 closes any open run
            if (currlen > 0) {
                // CLOSED run inside observed rows must match exactly
                if (clues.empty() || clueindex >= clues.size()) return false; //doesnt match exactly 
                if (currlen != clues[clueindex]) return false; //if its not filled and not the correct length then it isnt right 

                //next clue so increment 
                ++clueindex;
                currlen = 0;
            }
        }
    }

    
    if (torow < dimensions - 1) {
        return true;
    }

    // Final row: require exact match.
    if (currlen > 0) {
        // curr clue
        if (clueindex >= clues.size() || currlen != clues[clueindex]) return false; 
        ++clueindex;
        currlen = 0;
    }

    //must have solved all clues 
    return (clueindex == clues.size());
}

bool Solver::rowsolve(size_t rownum){
    //try each pattern for the row
    //put pattern into puzzle
    //use colcheckpartial to verify or prune
    //if valid, move to next row (recursive)
    //if row == dimensions then ur done 
    //if no pattern works backtrack



    //base case
     if (rownum == dimensions) {
        // check all columns up to final row 
        for (size_t col = 0; col < dimensions; ++col) {
            if (!partcolcheck(col, dimensions - 1)) return false;
        }
        return true;
    }

    // final row patterns 
    for (const auto &pattern : grid[rownum]) {
        puzzle[rownum] = pattern;

        // check columns 
        bool valid = true;
        for (size_t col = 0; col < dimensions; ++col) {
            if (!partcolcheck(col, rownum)) {
                valid = false;
                break;
            }
        }

        if (valid && rowsolve(rownum + 1)) {
            return true; // theres a solution 
        }
    }

    return false; //no solution, this is where backtracking would occur from the recursion 
}