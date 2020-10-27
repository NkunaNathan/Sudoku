#include<iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <cctype>
#include <iomanip>
#include <utility>

#include <algorithm>
#include <vector>
#include <array>

using namespace std;

static int sizeOfGrid(0);
static pair<int, int> PAIR;

void printSudoku(int **p, int rowSize, int columnSize);
bool used_in_row(int **grid, int row, int num);
bool used_in_col(int **grid, int col, int num);
bool used_in_box(int **grid, int box_start_rpw, int box_start_col, int num);
bool is_safe(int **grid, int row, int col, int num);
std::pair<int, int> get_unassigned_location(int **grid);
bool solve_soduko(int **grid);
char toLetter(int value);


// urelated function
void rowUsed(int **grid);

int main(/*int argc, char *argv[]*/)
{
    // declaration of a dynamic board
    int **sudoku;
    //    getting the grid size
    string wsString;
    cout << "Enter grid data" << endl;
    getline(cin,wsString);
    int len = wsString.length();
    int valueC(0);
    for(int i= 0; i < len ; i++){
        if(wsString[i] != '\n'){
            if(isspace(wsString.at(i)) == 0){
                 valueC++;
            }
        }
     }

    // updating the static value that will be used in the code
    sizeOfGrid = valueC;
    PAIR = make_pair(valueC, valueC);
//    cout << "PAIR values" << "Pair 1 " << PAIR.first << " Pair 2 " << PAIR.second << endl;
//    cout <<"Static grid size and value "<< valueC << sizeOfGrid << endl;


    // Creating the sudoku grid
//    char sudoku[valueC][valueC];
    // created the rows of the board
    sudoku = new int* [valueC];
    // creating the columns of the board
    for(int row(0); row < valueC; row++ )
        sudoku[row] = new int [valueC];
    // the end

//    putting elements inside the board

    for(int i(0); i < valueC; i++){
        for(int x(0); x < len; x++){
            if(wsString[x] != '\n'){
                if(isspace(wsString.at(x)) == 0){
					//we could subtract '0' and not subtract 48 and other numbers but i figured that a bit too late
					//and i choose not to fix this, i like it the way it is
//                    cout << "Is it a digit? " << isdigit(wsString.at(x)) << endl;
                    if(sizeOfGrid == 9){
                        int dig = wsString.at(x)-48;
    //                    wsString.at(x);
                        sudoku[i][x/2] = dig;
                    }
                    else if(sizeOfGrid == 16){
                        if(wsString.at(x) <= 57){
                            int dig = wsString.at(x)-48;
                            sudoku[i][x/2] = dig;
                        }else if(wsString.at(x) >= 65 && wsString.at(x) <= 90){
                            int dig = wsString.at(x)-55;
                            sudoku[i][x/2] = dig;

                        }
                    }
                    else if(sizeOfGrid == 25){
                        sudoku[i][x/2] = wsString.at(x);
                    }
                }
            }
        }
        if(i < valueC-1){
//            cout << "enter data" << endl;
            getline(cin,wsString);
        }
    }
    cout << endl << endl;
//    printSudoku(sudoku, valueC, valueC);
//    cout << endl<< endl << endl;
///*
    if (true == solve_soduko(sudoku))
    {
//        cout << "Is solver True? " << solve_soduko(sudoku) << endl;
        printSudoku(sudoku, valueC, valueC);;
    }
    else
    {
        cout << "No solution exists for the given Soduko" << endl << endl;
    }
//    */
//    printSudoku(sudoku, valueC, valueC);
    cout << endl;
//    rowUsed(sudoku);
//    cout << endl;
    return 0;
}


//function deffinations

// prining fuction
void printSudoku(int **p, int rowSize, int columnSize)
{
//    char characters;
    for (int row = 0; row < rowSize; row++){
        for (int col = 0; col < columnSize; col++)
            if(p[row][col] >= 10){
                cout << toLetter(p[row][col]) << ' ';
            }else{
                cout << p[row][col] << ' ';
            }
            cout << endl;
        }
}



void rowUsed(int **grid){
    for(int col(0); col < sizeOfGrid; col++){
        for(int row(0); row < sizeOfGrid; row++){
            for(int n(0); n < sizeOfGrid; n++){
                cout << (grid[row][col] == n)<< ' ';

            }
            cout << endl;
        }
    }
}

//#################################################################################################################################


// Returns a boolean which indicates whether any assigned entry
// in the specified row matches the given number.
bool used_in_row(int **grid, int row, int num)
{
    for (int col = 0; col < sizeOfGrid; col++)
        if (grid[row][col] == num)
        {
            return true;
        }
    return false;
}

// Returns a boolean which indicates whether any assigned entry
// in the specified column matches the given number.
bool used_in_col(int **grid, int col, int num)
{
    for (int row = 0; row < sizeOfGrid; row++){
//        cout << "Used in column "<< (grid[row][col] == num) << endl;
        if (grid[row][col] == num)
        {
            return true;
        }
    }
    return false;
}

// Returns a boolean which indicates whether any assigned entry
// within the specified 3x3 box matches the given number.
bool used_in_box(int **grid, int box_start_rpw, int box_start_col, int num)
{
    for (int row = 0; row < sqrt(sizeOfGrid); row++)
        for (int col = 0; col < sqrt(sizeOfGrid); col++)
            if (grid[row + box_start_rpw][col + box_start_col] == num)
            {
                return true;
            }
    return false;
}

// Returns a boolean which indicates whether it will be legal to assign
// num to the given row,col location.
bool is_safe(int **grid, int row, int col, int num)
{
    // Check if 'num' is not already placed in current row,
    // current column and current 3x3 box
    int modValue = sqrt(sizeOfGrid);
    return !used_in_row(grid, row, num) &&
        !used_in_col(grid, col, num) &&
        !used_in_box(grid, row - row % modValue, col - col % modValue, num);
}

// Searches the grid to find an entry that is still unassigned. If
// found, the reference parameters row, col will be set the location
// that is unassigned, and true is returned. If no unassigned entries
// remain, false is returned.
std::pair<int, int> get_unassigned_location(int **grid)
{
    for (int row(0); row < sizeOfGrid; row++){
        for (int col(0); col < sizeOfGrid; col++){
            //            cout << "If it's equal to zero is true? " << (grid[row][col] == 0) << endl;
            if (grid[row][col] == 0)
            {
                return std::make_pair(row, col);
            }
        }
    }
    return PAIR;
}

// Takes a partially filled-in grid and attempts to assign values to
// all unassigned locations in such a way to meet the requirements
// for Sudoku solution (non-duplication across rows, columns, and boxes)
bool solve_soduko(int **grid)
{
    // If the Soduko grid has been filled, we are done
//    cout << "in Solver" << endl << endl << endl << endl;
//    cout << "The static variable "  << sizeOfGrid << endl;
//    cout << "Are pair the same 1 =  " << (PAIR == get_unassigned_location(grid))<< endl;

    if (PAIR == get_unassigned_location(grid))
    {
        return true;
    }

    // Get an unassigned Soduko grid location
    std::pair<int, int> row_and_col = get_unassigned_location(grid);
    int row = row_and_col.first;
    int col = row_and_col.second;

//    cout << "Row " << row << " Column " << col;

    // Consider digits 1 to 9
    for (int num = 1; num <= sizeOfGrid; num++)
    {
        // If placing the current number in the current
        // unassigned location is valid, go ahead
        if (is_safe(grid, row, col, num))
        {
            // Make tentative assignment
            grid[row][col] = num;

            // Do the same thing again recursively. If we go
            // through all of the recursions, and in the end
            // return true, then all of our number placements
            // on the Soduko grid are valid and we have fully
            // solved it
            if (solve_soduko(grid))
            {
                return true;
            }

            // As we were not able to validly go through all
            // of the recursions, we must have an invalid number
            // placement somewhere. Lets go back and try a
            // different number for this particular unassigned location
            grid[row][col] = 0;
        }
    }

    // If we have gone through all possible numbers for the current unassigned
    // location, then we probably assigned a bad number early. Lets backtrack
    // and try a different number for the previous unassigned locations.
    return false;
}


char toLetter(int value){
    return value + 55;
}

//#################################################################################################################################
