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
    vector<tuple<int, int>> vector_occ;

    void buildBoard(){
        string buffer;
        vector<int> line;
        int aux;

        for (int i=0; i<board_size; i++){
            line.clear();

            for(int j=0; j<board_size;j++){
                cin >> aux;
                line.insert(line.end(), aux);

                if(aux != 0){
                    buildVector(aux);
                }

            }
            board.insert(board.end(), line);
        }
    }

    void buildVector(int num){
        vector<tuple<int, int>>::iterator it;

        if(vector_occ.empty()){
            vector_occ.emplace_back(num, 1);
        }
        else{

            for(it = vector_occ.begin(); it < vector_occ.end(); it++){

                if(get<0>(*it) == num){
                    get<1>(*it) ++;
                    return;
                }
                else if(get<0>(*it) > num){
                    vector_occ.insert(it, make_tuple(num, 1));
                    return;
                }
            }

            if(it == vector_occ.end()){
                vector_occ.emplace_back(make_tuple(num, 1));
            }
        }
    }

    void updateVector(int num){ //numero que se fez merge
        vector<tuple<int, int>>::iterator it;
        int num2 = num*2;

        for(it = vector_occ.begin(); it < vector_occ.end(); it++){

            if(get<0>(*it) == num && get<1>(*it)>=2){
                get<1>(*it) -= 2;
                if(get<1>(*it) == 0){
                    vector_occ.erase(it);
                }
                else{
                    it++;
                }
                break;
            }
        }


        if(it < vector_occ.end()){

            if(get<0>(*it) == num2){
                get<1>(*it) += 1;
            }
            else if(get<0>(*it) > num2){
                vector_occ.insert(it, make_tuple(num2, 1));
            }
        }
        else{
            vector_occ.emplace_back(make_tuple(num2, 1));
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

    void printVector(){
        for (vector<tuple<int, int>>::iterator row= vector_occ.begin(); row < vector_occ.end(); row++) {
            cout << get<0>(*row) << "," << get<1>(*row) << " ";
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
                updateVector(value);
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
      if (!isUpdated) move = 1;
      else move = -1;
      return isUpdated;
    }

    //RIGHT
    bool shiftRight(int& move){
      int i, j;
      int col;
      int value, value_next;
      bool isUpdated = false;

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
                updateVector(value);
                col--;
                break;
              }
              else if( value_next != 0){
                board[i][j] = 0;
                board[i][--col] = value_next;
                value = value_next;
                //isUpdated = true;
              }

              j--;
            }

           }

        }while(j>=0);
      }
      //cout << "isupdated: " << isUpdated << '\n';
      if (!isUpdated) move = 1;
      else move = -1;
      return isUpdated;
    }

    //TOP
    bool shiftTop(int& move){
        int i, j;
        int line;
        int value, value_next;
        bool isUpdated = false;

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
                        updateVector(value);
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
        if (!isUpdated) move = 2;
        else move = -1;
        return isUpdated;
    }

    //BOTTOM
    bool shiftBottom(int& move){
        int i, j;
        int line;
        int value, value_next;
        bool isUpdated = false;

        // percorrer todas as colunas
        for(j = 0; j < board_size; j++){ //i conta a coluna

            line = board_size-1, i = board_size-1; //j é o seguinte

            do{
            value = board[i][j];
            i--;

            // cout << value << " ";

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
                    updateVector(value);
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
        if (!isUpdated) move = 2; // there was no shift so there is no need to try it again later
        else move = -1;
        return isUpdated;
    }

    bool isPossible( vector<tuple<int, int>> vector_aux){

        vector<tuple<int, int>>::iterator it;
        int soma = 0;

        for(it = vector_aux.begin(); it < vector_aux.end(); it++){

            soma += get<0>(*it) * get<1>(*it);

        }

        return floor(log2(soma)) == log2(soma);
    }

    bool isCompleted () {
        return vector_occ.size() == 1 && get<1>(*vector_occ.begin()) == 1;
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
    if (!(counter < best && counter < max_moves &&
         !(best - counter < 2 &&
         (board.vector_occ.size() > 1  || get<1>(*board.vector_occ.begin()) > 2)))) {
        return;
    }

    counter++;
    //board.printBoard();
    //cout << "prev_move: " << previous_move << '\n';
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
    if (board.isPossible(board.vector_occ)) {

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
