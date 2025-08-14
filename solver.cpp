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
    vector<vector<vector<int>>> grid;
    for(size_t i = 0; i < dimensions; ++i){
        vector<int> clues(rowclues[i].begin(), rowclues[i].end());
        //add to grid
        grid.push_back(totalrowsolutions(clues));
    }
    

}