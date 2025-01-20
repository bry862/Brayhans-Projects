//
/*
Name: Brayhan Morrobel
Instructors: Tong Yi and Ryan
Assignemnt: Lab 2
Part: C

*/

#include "Board.hpp"
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <utility>


using namespace std;

Board::Board() : Board(3, 3) {

}

Board :: Board(int m, int n){

    numRows = m;
    numCols = n;

    //declare size of panel
    if ((m>=2) && (n>=2)){
        panel = new int* [m];

        for (int i =0; i< m; i++) {

            panel [i] = new int[n];
            
        }
    }

    else {
        m = 3; 
        n = 3; 
        panel = new int* [m];

        for (int i = 0; i<m; i++){
            panel [i] = new int[n];
        }
    }

    //By now we have a m by n empty board
    //Assign values to each cell
    int value = 1; 

    for (int i=0; i<m; i++){
        for (int j=0; j<n; j++){
            panel[i][j]= value++;
        }
    }

    randomize();
}

Board::Board(int** arr, int m, int n) : Board(3, 3){    
    
    int value = 1; 

    for (int i =0; i< m; i++){
        delete[] panel[i]; 
    }

    delete panel;

    panel = new int*[m];

    for ( int i =0; i< m; i++){

        panel[i] = new int[n];
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            panel[i][j] = arr[i][j];
        }
    }

    getInfo();


}

Board :: ~Board(){

    for (int i = 0; i < numRows; ++i) {
        delete[] panel[i]; 
    }

    delete[] panel;

    //the dangiling pointer problem
    panel = NULL;
}

void Board :: randomize(){

    //srand(time(0));

    int m = numRows;
    int n = numCols;

    int* temp_arr = new int[m * n];
    
    //Fill de array ordelly
    for (int i=0; i< (m*n); i++){
        temp_arr[i] = i+1;
    }

    int currentLastIndex = (m*n) -1;

    while (currentLastIndex > 0){
    
        int k = rand() % (currentLastIndex + 1);

        int temp = temp_arr[k];
        temp_arr[k] = temp_arr[currentLastIndex];
        temp_arr[currentLastIndex] = temp;

        currentLastIndex--;
    }

    int index =0;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            panel[i][j] = temp_arr[index++];
        }
    }

    delete[] temp_arr;

    getInfo();

}

//Helper Funtion
void printSeparateLine(int numCols) {
    cout << "+";
    for (int i = 0; i < numCols; ++i)
        cout << "-----+";
    cout << endl;

    }

void Board::display() const { 

    printSeparateLine(numCols); //bc we pront line every row, before the num

    for( int i =0; i< numRows; i++){
        

        cout<<"|";
        for(int j=0; j<numCols; j++){
            if ( panel[i][j] == numRows * numCols){
                cout<<setw(6)<< "|";
            }
            else {
            cout<<setw(3)<<panel[i][j]<<setw(3)<< "|";
            }
        } 

        cout<<endl;

        printSeparateLine(numCols);

    }

    
}

bool Board:: valueCorrect(int row, int col) const {

    int expectedValue = row * numCols + col +1;

    if (panel[row][col] == expectedValue && panel[row][col] != numRows * numCols) {
        return true;
    }

    else {
        return false;
    }


} 

void Board::getInfo(){

    numCorrect = 0;

    for (int i =0; i< numRows; i++){
        for(int j=0; j<numCols; j++){

            if(valueCorrect(i, j)){
                numCorrect++;
            }

            if (panel[i][j] == numRows * numCols){
                emptyCellRow = i;
                emptyCellCol =j;
            }
        }
    }
}

//TASK C: 
void Board :: slideUp () {


    if ((emptyCellRow+1 >= numRows)){

        //cant slide up here, return
        return;
       
    }

    if (valueCorrect(emptyCellRow +1, emptyCellCol)){
        numCorrect--;
    }

    swap( panel[emptyCellRow][emptyCellCol], panel[emptyCellRow+1][emptyCellCol]);

    if (valueCorrect(emptyCellRow, emptyCellCol)){

        numCorrect++;
    }

    //updat emepty cell. I dont really get the nee dfor this line if we did swap above
    emptyCellRow++;

    display();
}

void Board :: slideDown (){

    if ((emptyCellRow-1) < 0){
        return;
    }

    if (valueCorrect(emptyCellRow-1, emptyCellCol)){
        numCorrect--;
    }

    swap (panel[emptyCellRow][emptyCellCol], panel[emptyCellRow-1][emptyCellCol]);

    if (valueCorrect(emptyCellRow, emptyCellCol)){
        numCorrect++;
    }

    emptyCellRow--;

    display();

}

void Board :: slideLeft (){

    if (emptyCellCol +1 < 0){
        return;
    }

    if (valueCorrect(emptyCellRow, emptyCellCol+1)){
        numCorrect--;
    }

    swap(panel[emptyCellRow][emptyCellCol], panel[emptyCellRow][emptyCellCol+1]);
    
    if (valueCorrect(emptyCellRow, emptyCellCol)){
        numCorrect--;
    }

    emptyCellCol++;

    display();
}

void Board :: slideRight (){

    if (emptyCellCol -1 < 0){
        return;
    }

    if (valueCorrect(emptyCellRow, emptyCellCol-1)){
        numCorrect--;
    }

    swap(panel[emptyCellRow][emptyCellCol], panel[emptyCellRow][emptyCellCol-1]);
    
    if (valueCorrect(emptyCellRow, emptyCellCol)){
        numCorrect++;
    }

    emptyCellCol--;

    display();
}

//Task D

void Board::play() {
    display();
    int move = 0;
    while (true) { //TODO: fill in condition
        char ch = getchar();
        if (ch == 'S' || ch == 's') //STOP
            break;

        if (ch == 27) { // if the first value is esc
            getchar(); // skip the [
            switch (getchar()) { // the real value
                case 'A':
                
                    move++;
                    std::cout << "\nMove " << std::setw(4) << move << ": ";
                    std::cout << "Slide UP." << std::endl;
                    slideUp();
                    break;
                case 'B':
                    move++;
                    std::cout << "\nMove " << std::setw(4) << move << ": ";
                    std::cout << "Slide DOWN." << std::endl;
                    slideDown();
                    break;
                case 'C':
                    move++;
                    std::cout << "\nMove " << std::setw(4) << move << ": ";
                    std::cout << "Slide RIGHT." << std::endl;
                    slideRight();
                    break;
                case 'D':
                    move++;
                    std::cout << "\nMove " << std::setw(4) << move << ": ";
                    std::cout << "Slide LEFT." << std::endl;
                    slideLeft();
                    break;
            }
        }
    }

    std::cout << "\nCongratulations. Total number of moves is " << move << "." << std::endl;
}
