#include <stdio.h>
#include <stdlib.h>
#include <climits>
#include <utility>

class matrix
{
    //   num_rows: integer, stores the number of rows
    //   num_cols: integer, stores the number of columns
    //   elements: integer pointer, pointing to a contiguous memory stores a row-major matrix.

    int num_rows;
    int num_cols;
    int *elements;

    // all functions below must be PUBLIC!
public:

    int get_num_rows() { return num_rows; }
    int get_num_cols() { return num_cols; }

    void set_elem(int i, int j, int value)
    {
        if (i < 0 || i >= num_rows || j < 0 || j >= num_cols)
        {
            printf("invalid indices!\n");
        }
        else
        {
            elements[i * num_cols + j] = value;
        }
    }

    int get_elem(int i, int j) const
    {
        if (i < 0 || i >= num_rows || j < 0 || j >= num_cols)
        {
            printf("invalid indices!\n");
            return 'N';
        }
        else
        {
            return elements[i * num_cols + j];
        }
    }

    matrix(int nrow, int ncol)
    {
        if (nrow <= 0 || ncol <= 0)
        {
            printf("invalid dimensions!\n");
        }
        else
        {
            num_rows = nrow;
            num_cols = ncol;
            // printf("allocating memory for the matrix...\n");
            elements = (int *)malloc(num_rows * num_cols * sizeof(int));
        }
    }

    ~matrix()
    {
        // printf("freeing the matrix...\n");
        free(elements);
    }

    // print all elements in the matrix
    void print()
    {
        for (int i = 0; i < num_rows; i++)
        {
            for (int j = 0; j < num_cols; j++)
            {
                printf("%d ", get_elem(i, j));
            }
            printf("\n");
        }
    }

};

class tictactoe{
    matrix board;

    int isvictory(char player){
        for(int i = 0; i < 3; i++){
            if(board.get_elem(i, 0) == player && board.get_elem(i, 1) == player && board.get_elem(i, 2) == player){
                return 1;
            }
            if(board.get_elem(0, i) == player && board.get_elem(1, i) == player && board.get_elem(2, i) == player){
                return 1;
            }
        }
        if(board.get_elem(0, 0) == player && board.get_elem(1, 1) == player && board.get_elem(2, 2) == player){
            return 1;
        }
        if(board.get_elem(0, 2) == player && board.get_elem(1, 1) == player && board.get_elem(2, 0) == player){
            return 1;
        }
        return 0;
    }

    int isfull(){
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                if(board.get_elem(i, j) == '*'){
                    return 0;
                }
            }
        }
        return 1;
    }

    struct result{
        char winner;
        int depth;
    }; typedef struct result result;

    result evaluate(int score, int i, int j, char player, int depth){
        char opponent = (player == 'X') ? 'O' : 'X';
        // play the move
        play(i, j, player);
        
        // did you win?
        if(isvictory(player)){
            board.set_elem(i,j,'*');
            result w = {player, depth};
            return w;
        }else if(isfull()){ 
            // if I did not win, the board is full, it is a draw
            // Note that I cannot lose, if so, I could not proceed to this step.
            board.set_elem(i,j,'*');
            result w = {'*', depth};
            return w;
        }

        //anticipate your opponent's move
        int iiBest = -1, jjBest = -1; int Best = 100; 
        for (int ii =0; ii < 3; ii++){
            for (int jj =0; jj < 3; jj++){
                if(isplayable(ii, jj)){
                    // evaluate my opponent's moves, 
                    result t = evaluate(score, ii, jj, opponent, depth+1);
                    if(t.winner == opponent || t.winner == '*'){
                        // record my opponent's fastest win/draw
                        // to be his next move
                        if(Best > t.depth){
                            iiBest = ii; jjBest = jj;
                            Best = t.depth;
                        }
                    }
                }
            }
        }

        // even if my opponent plays optimally, he cannot win
        if(iiBest == -1){
            board.set_elem(i,j,'*');
            result w = {player, depth};
            return w;
        }

        // evaluate your opponent's best move        
        result ret = evaluate(score, iiBest, jjBest, opponent, depth+1);
        board.set_elem(i,j,'*');
        return ret;
    }

    int isplayable(int i, int j) {
        if (board.get_elem(i, j) == '*') {
            return 1;
        }
        return 0;
    }

public:
    tictactoe(): board(3,3) {
        //initialize the board
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                board.set_elem(i, j, '*');
            }
        }
    }
    
    void play(int i, int j, char player) {
        if(isplayable(i, j)) {
            board.set_elem(i, j, player);
        }
    }
    
    // print the evaluation of the current board
    void compute_scores(char player){
        printf("\nevaluation of the current board: \n");
        printf("-------------------------------\n");
        for (int i =0; i < 3; i++){
            for (int j =0; j < 3; j++){
                if(!isplayable(i, j)){
                    printf("_ "); // not playable
                }else{
                    result s = evaluate(0, i, j, player, 0);
                    if(s.winner == '*')
                        printf("D ", s.depth); // This move results a draw in %d steps
                    else if(s.winner == player)
                        printf("W ", s.depth); // This move results a win
                    else{
                        printf("L", s.depth); // This move results a loss
                    }
                }
            }
            printf("\n");
        }
        printf("-------------------------------\n");   
        printf("W: win, L: loss, D: draw\n");
        printf("under the assumption that your opponent plays optimally\n");
    }

    void print() { 
        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3;j++ ){
                printf("%c ", board.get_elem(i, j));
            }
            printf("\n");
        }
    }

};

int main()
{
    //initialize a random tictactoe board
    tictactoe game;
    game.play(0, 0, 'X');
    game.play(0, 1, 'O');
    game.play(1, 0, 'X');
    game.play(1, 2, 'O');
    game.print();

    game.compute_scores('X');
}