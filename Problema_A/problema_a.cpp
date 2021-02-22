#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

class Board {
  public:
    vector<vector<int>> board;
    int max_moves;
    int size;

    void buildBoard(){
        string buffer;
        vector<int> line;
        int aux;

        //cout << size << " " << max_moves << endl;

        for (int i=0; i<size; i++){
            getline(cin, buffer);

            line.clear();
            istringstream block(buffer);

            for(int j=0; j<size;j++){
                block >> aux;
                line.push_back(aux);
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
                j = col;
                break;
              }
              /*
              else if(j == size - 1){
                board[i][j] = 0;
                board[i][col] = value_next;
                break;
              }*/

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
                            j = col;
                            break;
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
                    j = line;
                    break;
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
                    i = line;
                    break;
                }
                i--;
                }
            }
            }while(i>=0); //enquanto não chega ao final da linha/coluna
        }
    }
};

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
        board.printBoard();
    }


    return 0;
}
