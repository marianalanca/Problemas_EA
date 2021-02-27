#include <iostream>
#include <vector>
#include <list>
#include <tuple>
#include <string>
#include <sstream>
#include <bits/stdc++.h>
using namespace std;

class Board {
  public:
    vector<vector<int>> board;
    vector<tuple<int, int>> vector_occ;
    int max_moves;
    int size;

    void buildBoard(){
        string buffer;
        vector<int> line;
        int aux;
        //list<tuple<int, int>> ::iterator it;

        //cout << size << " " << max_moves << endl;

        for (int i=0; i<size; i++){
            getline(cin, buffer);

            line.clear();
            istringstream block(buffer);

            for(int j=0; j<size;j++){
                block >> aux;
                line.push_back(aux);
                
                if(aux != 0){
                    buildVector(aux);
                }
                
            }
            board.push_back(line);
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
                    break;
                }
                else if(get<0>(*it) > num){
                    vector_occ.insert(it, make_tuple(num, 1));
                    break;
                }
            }
        }
    }


    // MUDAR
    void printBoard(){
        // list<int>::iterator it= l.begin();
        for (int i = 0; i < (int) size; i++) {
            for (int j = 0; j < (int) size; j++)
                cout << board[i][j] << " ";
            cout << endl;
        }
        cout << endl;
    }

    // MOVES
    //LEFT
    void shiftLeft(){
      int i, j;
      int col;
      int value, value_next;

      for(i = 0; i< size; i++){

        col = 0, j = 0;

        do{
          value = board[i][j];
          j++;

          if(value != 0){

            board[i][j-1]=0;
            board[i][col] = value;

            while(j < size){

              value_next = board[i][j];

              if(value_next == value){
                board[i][j] = 0;
                board[i][col] = value*2;
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

        }while(j<size);
      }

    }

    //RIGHT
    void shiftRight(){
        int i, j;
        int col;
        int value, value_next;

        for(i = 0; i < size; i++){

            col = size - 1, j = size - 1;

            do{
                value = board[i][j];
                j--;

                if(value != 0){

                    board[i][j+1]=0;
                    board[i][col] = value;

                    while(j >= 0){

                        value_next = board[i][j];

                        if(value_next == value){
                            board[i][j] = 0;
                            board[i][col] = value*2;
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
    }

    //TOP
    void shiftTop(){
        int i, j;
        int line;
        int value, value_next;

        // percorrer todas as colunas
        for(j = 0; j< size; j++){ //i conta a coluna

            line = 0, i = 0; //j é o seguinte

            do{
                value = board[i][j];
                i++;

                if(value != 0){

                    board[i-1][j]=0;
                    board[line][j] = value;

                    while(i < size){

                    value_next = board[i][j];

                    if(value_next == value){
                        board[i][j] = 0;
                        board[line][j] = value*2;
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
            }while(i<size); //enquanto não chega ao final da linha/coluna
        }
    }

    //BOTTOM
    void shiftBottom(){
        int i, j;
        int line;
        int value, value_next;

        // percorrer todas as colunas
        for(j = 0; j < size; j++){ //i conta a coluna

            line = size-1, i = size-1; //j é o seguinte

            do{
            value = board[i][j];
            i--;

            // cout << value << " ";

            if(value != 0){

                board[i+1][j]=0;
                board[line][j] = value;

                while(i >= 0){

                value_next = board[i][j];

                if(value_next == value){
                    board[i][j] = 0;
                    board[line][j] = value*2;
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
    }
  
    bool possible( vector<tuple<int, int>> vector_aux){

        vector<tuple<int, int>>::iterator it;
        tuple<int, int> tuple_aux;

        if(vector_aux.empty()){
            return  false;
        }

        if(get<1>(*vector_aux.begin()) % 2 != 0){
            return false;
        }

        tuple_aux = make_tuple(get<0>(*vector_aux.begin())* 2,get<1>(*vector_aux.begin())/2);
        vector_aux.erase(vector_aux.begin());

        for(it = vector_aux.begin(); it < vector_aux.end(); it++){
            if(get<0>(*it) == get<0>(tuple_aux)){
                get<1>(*it) += get<1>(tuple_aux);
                return possible(vector_aux);
            }
            else if(get<0>(*it) > get<0>(tuple_aux)){
                vector_aux.insert(it, tuple_aux);
                return possible(vector_aux);
            }
        }


        return true;
    }
  
};


int countMoves(Board board, int counter){
    Board aux;
    if (counter>=board.max_moves) {
        return -1; // MUDAR
    } else {
        aux = board;
        aux.shiftTop();
        countMoves(aux, counter + 1);

        aux = board;
        aux.shiftLeft();
        countMoves(aux, counter + 1);

        aux = board;
        aux.shiftRight();
        countMoves(aux, counter + 1);

        aux = board;
        aux.shiftBottom();
        countMoves(aux, counter + 1);
    }
    return 0;
}


int main() {
    int num_tables;
    string buffer;

    //get tables number
    getline(cin, buffer);
    istringstream num(buffer);
    num >> num_tables;

    while(getline(cin, buffer)){

        Board board;

        // get matrix size and max number of moves
        istringstream ss(buffer);
        ss >> board.size >> board.max_moves;

        board.buildBoard();
      
        cout << "Is possible? " << board.possible(board.vector_occ) << "\n";
      
        //board.printBoard();
        //countMoves(board,0);
    }

    return 0;
}
