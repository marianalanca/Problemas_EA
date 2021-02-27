#include <iostream>
#include <vector>
#include <list>
#include <tuple>
#include <string>
#include <sstream>
using namespace std;

class Board {
  public:
    vector<vector<int>> board;
    list<tuple<int, int>> list_occ;
    int max_moves;
    int size;

    void buildBoard(){
        string buffer;
        vector<int> line;
        int aux;
        list<tuple<int, int>> ::iterator it;

        //cout << size << " " << max_moves << endl;

        for (int i=0; i<size; i++){
            getline(cin, buffer);

            line.clear();
            istringstream block(buffer);

            for(int j=0; j<size;j++){
                block >> aux;
                line.push_back(aux);

                if(list_occ.empty()){
                    list_occ.push_back(make_tuple(aux, 1));
                    it =  list_occ.begin();
                } 
                else {
                    //cout << get<0>(*it) << endl;
                    if(get<0>(*it) > aux){
                        list_occ.insert(it, make_tuple(aux, 1));
                    }
                    else if( get<0>(*it) < aux){

                    }
                    else{
                        //*it<1>++;
                    }
                }
                /*
                if (command.compare("MOVE")==0){
                    if (direction.compare("LEFT")==0)
                        it--;
                    else if (direction.compare("RIGHT")==0)
                        it++;

                } else if(command.compare("INSERT")==0) {
                    cin >> input;
                    if (direction.compare("LEFT")==0){
                        l.insert(it, input);
                    }
                    else if (direction.compare("RIGHT")==0){
                        aux = it;
                        ++aux;
                        l.insert(aux, input);
                    }
                }*/

            }
            board.push_back(line);
        }
    }


    // MUDAR
    // list<int>::iterator it= l.begin();
    void printBoard(){
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
        //board.printBoard();
        //countMoves(board,0);
    }

    return 0;
}