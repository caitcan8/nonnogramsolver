#include "nonno.h"
string filename;
void printHelp(char *command) {
    cout << "Usage: " << command << " \n";
    cout << "This program is used to assist in solving a nonnogram. A nonnogram is a puzzle where you must fill cells based on the clues for rows and columns with a single cell gap in between in clue";
}  // printHelp()

void getOptions(int argc, char **argv) {
    // These are used with getopt_long()
    opterr = static_cast<int>(false);  // Let us handle all error output for command line options
    int choice;
    int index = 0;

    // NOLINTBEGIN: getopt is old C code predating C++ style, this usage is from `man getopt`
    option longOptions[] = {
  
        
        {"solve",      required_argument,       nullptr, 'q'},
        {"help",       no_argument,       nullptr, 'h'},
        {nullptr, 0,                nullptr, '\0'}
    };  // longOptions[]
    // NOLINTEND
     while ((choice = getopt_long(argc, argv, "s:h", static_cast<option *>(longOptions), &index)) != -1) {
        switch (choice) {
        case 's' :{ 
           string arg { optarg };
               filename = arg;

          break;
        }    
        case 'h':{
            printHelp(*argv);
            exit(0);
        }

        default:
            cerr << "Unknown Option\n";
            exit(1);

          // switch ..choice
    }  // while

   
} 

 }// getOptions()
