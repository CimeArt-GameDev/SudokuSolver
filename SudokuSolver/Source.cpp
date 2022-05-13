#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#define N 9


using namespace std;


 vector<vector<int>> readFile() { //Trouve le fichier txt et renvoi un vector de vector de int
     ifstream* file = new ifstream;

     file->open("SudokuGrid.txt", ios::in);
     (file->is_open()) ? cout << "File Opened ! " << endl : cout << "Could not open the file..." << endl;
     string temp;
     vector<int> gridTemp;
     vector<vector<int>> grid;
     
     while (getline(*file, temp)) {
         gridTemp.clear();
         for (char c : temp) {
             gridTemp.push_back(c-'0'); //push la difference entre le char c et le char 0 (donnant la valeur en int depuis les valeur ascii )
         }
         grid.push_back(gridTemp);
         
     }
     return grid;
 }

bool isPresentInCol(int column, int number, vector<vector<int>> grid) { //Verif si le nombre est dans la colonne
    for (int row = 0; row < N; row++)
        if (grid[row][column] == number)
            return true;
    return false;
}
bool isPresentInRow(int row, int number, vector<vector<int>> grid) { //Verif si le nombre est present sur la ligne
    for (int column = 0; column < N; column++)
        if (grid[row][column] == number)
            return true;
    return false;
}
bool isPresentInBox(int boxStartRow, int boxStartColumn, int number, vector<vector<int>> grid) {
    //verif si le nombre est dans le 3x3
    for (int row = 0; row < 3; row++)
        for (int column = 0; column < 3; column++)
            if (grid[row + boxStartRow][column + boxStartColumn] == number)
                return true;
    return false;
}
void sudokuGrid(vector<vector<int>> grid) { //Print le sudoku
    system("cls");
    cout << "Sudoku resolu :" << endl;
    for (int row = 0; row < N; row++) {
        for (int column = 0; column < N; column++) {
            if (column == 3 || column == 6)
                cout << " | ";
            cout << grid[row][column] << " ";
        }
        if (row == 2 || row == 5) {
            cout << endl;
                cout << "-----------------------";
        }
        cout << endl;
    }
}
bool findEmptyPlace(int& row, int& column, vector<vector<int>> grid) { //Trouve une case vide
    for (row = 0; row < N; row++)
        for (column = 0; column < N; column++)
            if (grid[row][column] == 0) //0 est une case vide
                return true;
    return false;
}
bool isValidPlace(int row, int column, int number, vector<vector<int>> grid) {
    //si le nombre n'est pas trouvé dans la ligne, la colonne et le 3x3
    return !isPresentInRow(row, number, grid) && !isPresentInCol(column, number, grid) && !isPresentInBox(row - row % 3,
        column - column % 3, number, grid);
}
bool solveSudoku(vector<vector<int>> &grid) {
    int row, column;
    if (!findEmptyPlace(row, column, grid))
        return true; //lorsque le sudoku est complété
    for (int number = 1; number <= 9; number++) {
        if (isValidPlace(row, column, number, grid)) { //verif si c'est la bonne place, si oui, set la case a ce nombre
            grid[row][column] = number;
            if (solveSudoku(grid)) //recursive sur d'autres cases vides de la grille
                return true;
            grid[row][column] = 0; //lorsque les conditions ne sont pas réunies
        }
    }
    return false;
}
int main() {
    vector<vector<int>> grid = readFile();

    if (solveSudoku(grid) == true)
        sudokuGrid(grid);
    else
        cout << "No solution exists";
}