#include <iostream>
#include <vector>
#include <tuple>
#include <string>
#include <cmath>
using namespace std;

int board_size, max_moves;

class Board {
  public:
    vector<vector<int>> board;
    int occ, sum;

    void buildBoard(){
        string buffer;
        vector<int> line;
        int aux;

        sum = 0, occ = 0;

        for (int i=0; i<board_size; i++){
            line.clear();

            for(int j=0; j<board_size;j++){
                cin >> aux;
                line.insert(line.end(), aux);

                if(aux != 0){
                    occ++;
                    sum += aux;
                   // buildVector(aux);
                }

            }
            board.insert(board.end(), line);
        }
    }

    void printBoard(){
        for (vector<vector<int>>::iterator row= board.begin(); row < board.end(); row++) {
            for (vector<int>::iterator col = row->begin(); col < row->end(); col++)
                cout << *col << " ";
            cout << endl;
        }
        cout << endl;
    }

    // MOVES
    //LEFT
    bool shiftLeft(int& move){
      int i, j;
      int col;
      int value, value_next;
      bool isUpdated = false;
      bool shifted = false;

      for(i = 0; i< board_size; i++){

        col = 0, j = 0;

        do{
          value = board[i][j];
          j++;

          if(value != 0){

            if(j-1 != col){
                board[i][j-1]=0;
                board[i][col] = value;
                isUpdated = true;
            }

            while(j < board_size){

              value_next = board[i][j];

              if(value_next == value){
                board[i][j] = 0;
                board[i][col] = value<<1;
                isUpdated = true;
                shifted = true;
                occ--;
                col++;
                break;
              }
              else if( value_next != 0){
                board[i][j] = 0;
                board[i][++col] = value_next;
                value = value_next;
              }

              j++;
            }

           }

        }while(j<board_size);
      }

      if (!shifted) move = 1;
      else move = -1;
      return isUpdated;
    }

    //RIGHT
    bool shiftRight(int& move){
      int i, j;
      int col;
      int value, value_next;
      bool isUpdated = false, shifted = false;

      for(i = 0; i< board_size; i++){

        col = board_size-1, j = board_size-1;

        do{
          value = board[i][j];
          j--;

          if(value != 0){

            if(j+1 != col){
                board[i][j+1]=0;
                board[i][col] = value;
                isUpdated = true;
            }

            while(j >= 0){

              value_next = board[i][j];

              if(value_next == value){
                board[i][j] = 0;
                board[i][col] = value<<1;
                isUpdated = true;
                shifted = true;
                occ--;
                col--;
                break;
              }
              else if( value_next != 0){
                board[i][j] = 0;
                board[i][--col] = value_next;
                value = value_next;
              }

              j--;
            }

           }

        }while(j>=0);
      }
      if (!shifted) move = 1;
      else move = -1;
      return isUpdated;
    }

    //TOP
    bool shiftTop(int& move){
        int i, j;
        int line;
        int value, value_next;
        bool isUpdated = false;
        bool shifted = false;

        // percorrer todas as colunas
        for(j = 0; j< board_size; j++){ //i conta a coluna

            line = 0, i = 0; //j é o seguinte

            do{
                value = board[i][j];
                i++;

                if(value != 0){

                    if(i-1 != line){
                        board[i-1][j]=0;
                        board[line][j] = value;
                        isUpdated = true;
                    }

                    while(i < board_size){

                    value_next = board[i][j];

                    if(value_next == value){
                        board[i][j] = 0;
                        board[line][j] = value<<1;
                        isUpdated = true;
                        shifted = true;
                        occ--;
                        line++;
                        break;
                    }
                    else if( value_next != 0){
                        board[i][j] = 0;
                        board[++line][j] = value_next;
                        value = value_next;
                    }
                    i++;
                }
            }
            }while(i<board_size); //enquanto não chega ao final da linha/coluna
        }
        if (!shifted) move = 2;
        else move = -1;
        return isUpdated;
    }

    //BOTTOM
    bool shiftBottom(int& move){
        int i, j;
        int line;
        int value, value_next;
        bool isUpdated = false;
        bool shifted = false;

        // percorrer todas as colunas
        for(j = 0; j < board_size; j++){ //i conta a coluna

            line = board_size-1, i = board_size-1; //j é o seguinte

            do{
            value = board[i][j];
            i--;

            if(value != 0){

                if(i+1 != line){
                    board[i+1][j]=0;
                    board[line][j] = value;
                    isUpdated = true;
                }

                while(i >= 0){

                value_next = board[i][j];

                if(value_next == value){
                    board[i][j] = 0;
                    board[line][j] = value<<1;
                    isUpdated = true;
                    shifted = true;
                    occ--;
                    line--;
                    break;
                }
                else if( value_next != 0){
                    board[i][j] = 0;
                    board[--line][j] = value_next;
                    value = value_next;
                }
                i--;
                }
            }
            }while(i>=0); //enquanto não chega ao final da linha/coluna
        }
        if (!shifted) move = 2;
        else move = -1;
        return isUpdated;
    }

    bool isPossible(){
        return floor(log2(sum)) == log2(sum);
    }

    bool isCompleted () {
        return occ == 1;
    }
};

void countMoves(Board &board, int counter, int& best, int previous_move){
    Board aux;

    // acceptance condition
    if (board.isCompleted()){
        //cout << "count: " << counter << '\t' << "best: " << best << '\n';
        if (counter < best) {
            best = counter;
        }
        return;
    }

    // rejection condition
    if (!(counter < best && counter < max_moves && !(best - counter < 2 && board.occ > 2))) {
        return;
    }

    counter++;
    //board.printBoard();
    //if (previous_move!=-1) cout << "prev_move: " << previous_move << '\n';
    if (previous_move != 1) {
        aux = board;
        if (aux.shiftRight(previous_move)) {
            //cout << "shiftLeft()" << '\t'<< "count: " << counter << '\t'<< "best:" <<best <<'\n';
            countMoves(aux, counter, best, previous_move);
        }
    }
    if (previous_move != 2) {
        aux = board;
        if (aux.shiftTop(previous_move)) {
            //cout << "shiftTop()" << '\t'<< "count: " << counter << '\t'<< "best:" <<best << '\n';
            countMoves(aux, counter, best, previous_move);
        }
    }
    if (previous_move != 1) { //Tipo aqui tu só entras se houver um merge, certo?
        aux = board;
        if (aux.shiftLeft(previous_move)) {
            //cout << "shiftLeft()" << '\t'<< "count: " << counter << '\t'<< "best:" <<best <<'\n';
            countMoves(aux, counter, best, previous_move);
        }
    }
    if (previous_move != 2) {
        aux = board;
        if (aux.shiftBottom(previous_move)){
            //cout << "shiftBottom()" << '\t'<< "count: " << counter << '\t'<< "best:" <<best << '\n';
            countMoves(aux, counter, best, previous_move);
        }
    }
    return;
}

void printMoves(Board board) {
    if (board.isPossible()) {

        int best = max_moves +1;
        countMoves(board, 0, best, -1);

        if (best > max_moves) {
            cout << "no solution" << '\n';
        } else {
            cout << best << '\n';
        }
    } else {
        cout << "no solution" << '\n';
    }
}

int main() {
    int num_tables;
    string buffer;

    cin >> num_tables;

    for (int i =0; i<num_tables;i++){

        Board board;

        // get matrix size and max number of moves
        cin >> board_size >> max_moves;

        board.buildBoard();

        //cout << board.isPossible(board.vector_occ) << '\n';

        printMoves(board);
    }

    return 0;
}
