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
    vector<tuple<int, int>> vector_occ;
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

            //cout << "Teste " << num << ": " << get<0>(*it) << " -> " << get<1>(*it) <<"\n";

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
    bool shiftLeft(){
      int i, j;
      int col;
      int value, value_next;
      bool isUpdated = false;

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
                isUpdated = true;
              }

              j++;
            }

           }

        }while(j<size);
      }
      return isUpdated;
    }

    //RIGHT
    bool shiftRight(){
        int i, j;
        int col;
        int value, value_next;
        bool isUpdated = false;

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
                            isUpdated = true;
                        }

                        j--;
                    }
                }
            }while(j>=0);
        }
        return isUpdated;
    }

    //TOP
    bool shiftTop(){
        int i, j;
        int line;
        int value, value_next;
        bool isUpdated = false;

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
                        isUpdated = true;
                    }
                    i++;
                }
            }
            }while(i<size); //enquanto não chega ao final da linha/coluna
        }
        return isUpdated;
    }

    //BOTTOM
    bool shiftBottom(){
        int i, j;
        int line;
        int value, value_next;
        bool isUpdated = false;

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
                    isUpdated = true;
                }
                i--;
                }
            }
            }while(i>=0); //enquanto não chega ao final da linha/coluna
        }
        return isUpdated;
    }

    bool isPossible( vector<tuple<int, int>> vector_aux){

        vector<tuple<int, int>>::iterator it;
        tuple<int, int> tuple_aux;

        if(vector_aux.empty()){
            return  false;
        }

        if(vector_aux.size() == 1 && get<1>(*vector_aux.begin())  == 1 ){ // se existir apenas um elemento
            return true;
        }

        if(get<1>(*vector_aux.begin()) % 2 != 0){ // se primeiro valor for impar, um deles vai ficar sem par
            return false;
        }

        tuple_aux = make_tuple(get<0>(*vector_aux.begin())* 2, get<1>(*vector_aux.begin())/2);
        vector_aux.erase(vector_aux.begin());

        for(it = vector_aux.begin(); it < vector_aux.end(); it++){
            if(get<0>(*it) == get<0>(tuple_aux)){
                get<1>(*it) += get<1>(tuple_aux);
                return isPossible(vector_aux);
            }
            else if(get<0>(*it) > get<0>(tuple_aux)){
                vector_aux.insert(it, tuple_aux);
                return isPossible(vector_aux);
            }
        }

        return true;
    }

    bool isCompleted () {
        // DEBUG
        //cout << "VECTOR: " << vector_occ.size() << " " << get<1>(*vector_occ.begin()) << '\n';
        //printVector();

        if (vector_occ.size()==1 && get<1>(*vector_occ.begin()) == 1){
            return true;
        }
        return false;
    }
};


// PUTA XDDDD

void countMoves(Board board, int counter, int& best){ // mudar counter
    Board aux;
    if (board.isCompleted()){
        //cout << "count: " << counter << '\t' << "best: " << best << '\n';
        if (counter < best) {
            best = counter;
        }
        return;
    }
    if (counter <= best) { // se for maior do que o best já não é necessário continuar
        counter++;
        aux = board;
        if (aux.shiftRight()) {
            //cout << "shiftRight()" << '\t'<< "count: " << counter<< '\t'<< "best:" <<best << '\n';
            countMoves(aux, counter, best);
        }
        aux = board;
        if (aux.shiftLeft()) { //Tipo aqui tu só entras se houver um merge, certo?
            //cout << "shiftLeft()" << '\t'<< "count: " << counter << '\t'<< "best:" <<best <<'\n';
            countMoves(aux, counter, best);
        }

        aux = board;
        if (aux.shiftTop()) {
            //cout << "shiftTop()" << '\t'<< "count: " << counter << '\t'<< "best:" <<best << '\n';
            countMoves(aux, counter, best);
        }

        aux = board;
        if (aux.shiftBottom()) {
            //cout << "shiftBottom()" << '\t'<< "count: " << counter << '\t'<< "best:" <<best << '\n';
            countMoves(aux, counter, best);
        }
    }
    return;
}

void printMoves(Board board) {
    int best = board.max_moves +1;
    countMoves(board, 0, best);
    //cout << best << '\n';

    if (best > board.max_moves) {
        cout << "no solution" << '\n';
    } else {
        cout << best << '\n';
    }
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

        //cout << "Is Possible? " << board.isPossible(board.vector_occ) << "\n";
        //board.printBoard();

        printMoves(board);
    }

    return 0;
}
