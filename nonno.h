#include <getopt.h>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <fstream>
using namespace std;

extern string filename;

void getOptions(int argc, char **argv);

void printHelp(char *command);

class Solver{
    public: 
    void read();
    void print();
    void solve();
    bool partcolcheck(size_t colnum, size_t torow);
    bool rowcheck(size_t rownum);
    bool rowsolve(size_t rownum);
    //private:
    vector<vector<vector<int>>> grid;
    size_t dimensions;
    vector<vector<size_t>> colclues;
    vector<vector<size_t>> rowclues;
    vector<vector<int>> puzzle; // 0 = empty, 1 = filled
    vector<vector<int>> totalrowpatterns;
    void makesolutions(const vector<int>& clues, size_t currclue, size_t currpos, vector<int>& currsolution, vector<vector<int>>& total);
    vector<vector<int>> totalrowsolutions(vector<int>& clues);
    private:
};