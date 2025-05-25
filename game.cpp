#include<ncurses.h>
 
bool xturn = true;
bool oturn = false;
bool xwin = false;
bool owin = false;

int countTurn = 0;

char board[7][14] = {
    "~~~~~~~~~~~~~",
    "|   |   |   |",
    "~~~~~~~~~~~~~",
    "|   |   |   |",
    "~~~~~~~~~~~~~",
    "|   |   |   |",
    "~~~~~~~~~~~~~"
};



// winning combinations for 'X' or 'O'
bool checkMatch(char turn){
    if(board[1][2] == turn && board[1][6] == turn && board[1][10] == turn) return true;
    else if(board[3][2] == turn && board[3][6] == turn && board[3][10] == turn) return true;
    else if(board[5][2] == turn && board[5][6] == turn && board[5][10] == turn) return true;
    else if(board[1][10] == turn && board[3][10] == turn && board[5][10] == turn) return true;
    else if(board[1][6] == turn && board[3][6] == turn && board[5][6] == turn) return true;
    else if(board[1][2] == turn && board[3][2] == turn && board[5][2] == turn) return true;
    else if(board[1][2] == turn && board[3][6] == turn && board[5][10] == turn) return true;
    else if(board[1][10] == turn && board[3][6] == turn && board[5][2] == turn) return true;
    else return false;
}


//to fill boxes with "X" or  "O"
bool fillBoxes(int cordy, int cordx, char turn, bool isSelect){
    if(cordy == 8 && cordx == 37 && isSelect && board[1][2] == ' ')  board[1][2] = turn;
    else if(cordy == 8 && cordx == 41 && isSelect && board[1][6] == ' ')  board[1][6] = turn;
    else if(cordy == 8 && cordx == 45 && isSelect && board[1][10] == ' ')  board[1][10] = turn;
    else if(cordy == 10 && cordx == 37 && isSelect && board[3][2] == ' ')  board[3][2] = turn;
    else if(cordy == 10 && cordx == 41 && isSelect && board[3][6] == ' ')  board[3][6] = turn;
    else if(cordy == 10 && cordx == 45 && isSelect && board[3][10] == ' ')  board[3][10] = turn;
    else if(cordy == 12 && cordx == 37 && isSelect && board[5][2] == ' ')  board[5][2] = turn;
    else if(cordy == 12 && cordx == 41 && isSelect && board[5][6] == ' ')  board[5][6] = turn;
    else if(cordy == 12 && cordx == 45 && isSelect && board[5][10] == ' ')  board[5][10] = turn;
    else {
        mvprintw(4,10, "This board is already filled!");
        return false;
    }
    mvprintw(4,10, "                               ");
    return true;
}

void play(int cordy, int cordx, bool& isSelect){
    char X = 'X';
    char O = 'O';
    if(xturn && isSelect && fillBoxes(cordy, cordx, X, isSelect)){
        mvaddch(cordy, cordx, X);
        if (checkMatch(X)) xwin = true;
        xturn = false;
        oturn = true;
    }else if(oturn && isSelect && fillBoxes(cordy, cordx, O, isSelect)){
        mvaddch(cordy, cordx, O);
        if (checkMatch(O)) owin = true;
        oturn = false;
        xturn = true;
    } 
    isSelect = false;
    countTurn++;
    refresh();
    return;
}


void displayTurn(int y, int x, int cordy, int cordx){
    attron(A_BOLD);
    if (xturn){
        mvprintw(y,x,"PLAYER TURN: X");
        
    }else if(oturn){
        mvprintw(y,x,"PLAYER TURN: O");
    }
    attroff(A_BOLD);
    refresh();
    return;
}

void playTurn(int& cordy, int& cordx, int borderUp, int borderDown, int borderLeft, int borderRight){
    move(cordy, cordx);
    int c = getch();
    bool isSelect = false;
    if(c == KEY_ENTER || c == 10){
        isSelect = true;
        play(cordy, cordx, isSelect);
        return;
    }
    if(c == KEY_UP && cordy > borderUp ) cordy-= 02;
    else if(c == KEY_DOWN && cordy < borderDown) cordy += 2;
    else if(c == KEY_RIGHT && cordx < borderRight ) cordx += 4;
    else if(c == KEY_LEFT && cordx > borderLeft) cordx -= 4;
    
    return;
}

void printBoard(int y, int x){
    for(int i=0; i<7; i++){
        for(int j=0; j < 13 ;j++){
            mvaddch(y+i,x+j, board[i][j]);
            
        }
    }
    move(y+1,x+2);
    refresh();
    return;
}

int main(){
    int x,y;
    int cordx, cordy;
    int borderUp, borderDown, borderLeft, borderRight;
    initscr();

    start_color();
    keypad(stdscr, true);
    noecho();
    getmaxyx(stdscr, y, x);
    cordy = (y/2)-4;
    cordx = (x/2)-3;
    borderUp = (y/2)-4;
    borderLeft = (x/2)-3;
    borderRight = (x/2)+2;
    borderDown = (y/2);
    
   
    printBoard((y/2)-5,(x/2)-5);
    while(true){
        if(countTurn == 9){
            mvprintw (5,30, "Game Draw");
            break;
        }
        displayTurn((y/2)-10, (x/2)-10, cordy, cordx);
        playTurn(cordy, cordx, borderUp, borderDown, borderLeft, borderRight);
        if(xwin){
            mvprintw (5,30, "Player X won");
            xwin = false;
            break;
        }
        else if (owin){
            mvprintw (5,30, "Player O won");
            owin = false;
            break;
        }
    }
    curs_set(0);
    getch();
    refresh();
    endwin();
    return 0;
}
