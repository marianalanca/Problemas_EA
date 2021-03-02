#include <iostream>
#include <vector>
#include <list>
#include <tuple>
#include <string>
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

        for (int i=0; i<size; i++){
            line.clear();

            for(int j=0; j<size;j++){
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
    bool shiftLeft(int& move){
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

            if(j-1 != col){
                board[i][j-1]=0;
                board[i][col] = value;
            }

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
              }

              j++;
            }

           }

        }while(j<size);
      }
      if (!isUpdated) move = 2;
      else move = -1;
      return isUpdated;
    }

    //RIGHT
    bool shiftRight(int &move){
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

                    if(j+1 != col){
                        board[i][j+1]=0;
                        board[i][col] = value;
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
                            isUpdated = true;
                        }

                        j--;
                    }
                }
            }while(j>=0);
        }
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
        for(j = 0; j< size; j++){ //i conta a coluna

            line = 0, i = 0; //j é o seguinte

            do{
                value = board[i][j];
                i++;

                if(value != 0){

                    if(i-1 != line){
                        board[i-1][j]=0;
                        board[line][j] = value;
                    }

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
        if (!isUpdated) move = 3;
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
        for(j = 0; j < size; j++){ //i conta a coluna

            line = size-1, i = size-1; //j é o seguinte

            do{
            value = board[i][j];
            i--;

            // cout << value << " ";

            if(value != 0){

                if(i+1 != line){
                    board[i+1][j]=0;
                    board[line][j] = value;
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
                    isUpdated = true;
                }
                i--;
                }
            }
            }while(i>=0); //enquanto não chega ao final da linha/coluna
        }
        if (!isUpdated) move = 4; // there was no shift so there is no need to try it again later
        else move = -1;
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
        return vector_occ.size() == 1 && get<1>(*vector_occ.begin()) == 1;
    }
};


// PUTA XDDDD
// IMPROVE
void countMoves(Board board, int counter, int& best, int previous_move){ // mudarss counter
    Board aux;
    if (counter > board.max_moves) {
        return;
    }
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
        if (previous_move != 1 && aux.shiftRight(previous_move)) { // if the shift was tried previously with no result, there is no need to try again
            //cout << "shiftRight()" << '\t'<< "count: " << counter<< '\t'<< "best:" <<best << '\n';
            countMoves(aux, counter, best, previous_move);
        }
        aux = board;
        if (previous_move != 2 && aux.shiftLeft(previous_move)) { //Tipo aqui tu só entras se houver um merge, certo?
            //cout << "shiftLeft()" << '\t'<< "count: " << counter << '\t'<< "best:" <<best <<'\n';
            countMoves(aux, counter, best, previous_move);
        }

        aux = board;
        if (previous_move != 1 && aux.shiftTop(previous_move)) {
            //cout << "shiftTop()" << '\t'<< "count: " << counter << '\t'<< "best:" <<best << '\n';
            countMoves(aux, counter, best, previous_move);
        }

        aux = board;
        if (previous_move != 1 && aux.shiftBottom(previous_move)) {
            //cout << "shiftBottom()" << '\t'<< "count: " << counter << '\t'<< "best:" <<best << '\n';
            countMoves(aux, counter, best, previous_move);
        }
    }
    return;
}

void printMoves(Board board) {
    if (board.isPossible(board.vector_occ)) {

        int best = board.max_moves +1;
        countMoves(board, 0, best, -1);

        if (best > board.max_moves) {
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
        cin >> board.size >> board.max_moves;

        board.buildBoard();

        printMoves(board);
    }

    return 0;
}
