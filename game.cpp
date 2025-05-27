#include<ncurses.h>
#include <vector>

struct saveGame{
    int cordy;
    int cordx;
    char turn;
};


std::vector<saveGame> saved;

 
bool xturn = true;
bool oturn = false;
bool xwin = false;
bool owin = false;
bool optSelect = false;
bool gameStarted = false;
bool gamePause = false;
bool isExit = false;

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


char menu[4][13] = {
    " Start Game ",
    "Show History",
    "  Settings  ",
    "    EXIT    "
};

char modes[4][14] = {
    " Multiplayer ",
    "Single Player",
    "  Time Mode  ",
    "Back to Menu "
};

char pauseMenu[4][16] ={
    "    Resume    ",
    "Start New Game",
    "   Save Game  ",
    "   Exit Game  "
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

void showPauseMenu(int y, int x, int opt){
    for(int i = 0; i<4; i++){
        for(int j = 0; j<14; j++){
            if(i == opt){
                attron(COLOR_PAIR(1));
                mvaddch(y+i,x+j, pauseMenu[i][j]);
                attroff(COLOR_PAIR(1));
            }else
                mvaddch(y+i,x+j, pauseMenu[i][j]);
        }
    }
    refresh();
    return;
}

void play(int cordy, int cordx, bool& isSelect){
    char X = 'X';
    char O = 'O';
    if(xturn && isSelect && fillBoxes(cordy, cordx, X, isSelect)){
        mvaddch(cordy, cordx, X);
        saved.push_back({cordy, cordx, X});
        if (checkMatch(X)) xwin = true;
        xturn = false;
        oturn = true;
    }else if(oturn && isSelect && fillBoxes(cordy, cordx, O, isSelect)){
        mvaddch(cordy, cordx, O);
        saved.push_back({cordy, cordx, X});
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
    attron(COLOR_PAIR(2));
    
    if (xturn){
        mvprintw(y,x,"PLAYER TURN: X");
        
    }else if(oturn){
        mvprintw(y,x,"PLAYER TURN: O");
    }
    attroff(COLOR_PAIR(2));
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

    if(c == 27){
        clear();
        gamePause = true;
        return;
    }
    
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

void gameMode(int y, int x, int opt){
    for(int i = 0; i<4; i++){
        for(int j =0; j<13; j++){
            if(i == opt){
                attron(COLOR_PAIR(1));
                mvaddch(y+i,x+j, modes[i][j]);
                attroff(COLOR_PAIR(1));
            }else
                mvaddch(y+i,x+j, modes[i][j]);
        }
    }
    refresh();
    return;
}

void showMenu(int y, int x, int opt){
    for(int i = 0; i<4;i++){
        for(int j = 0; j < 12; j++){
            if(i == opt){
                attron(COLOR_PAIR(1));
                mvaddch(y+i,x+j, menu[i][j]);
                attroff(COLOR_PAIR(1));
            }else{
                mvaddch(y+i,x+j, menu[i][j]);
            }
            
        }
    }
    refresh();
    return;
}

void persistBoard(){
    for(auto turns: saved){
        mvaddch(turns.cordy, turns.cordx, turns.turn);
    }
    refresh();
    return;
}



void keyMovement( int y, int x, int& opt){
    int c = getch();

    //Select key when first menu is displayed and option 1 to be selected.
    if((c == KEY_ENTER || c == 10) && (opt == 0) && !optSelect) {
        clear();
        optSelect = true;
        opt = 0;
        return;
    }

    //Select key when first menu is displayed and option 4 to be selected.
    if((c == KEY_ENTER || c == 10) && (opt == 3) && !optSelect) {
        clear();
        isExit = true;
        return;
    }

    //Select key when game menu is displayed and option 1 to be selected.
    if((c == KEY_ENTER || c == 10) && (opt == 0) && optSelect){
        clear();
        gameStarted = true;
        optSelect = true;
        opt = 0;
        printBoard(y,x);
        return;
    }

    //Select key when game menu is displayed and option 4 to be selected.
    if((c == KEY_ENTER || c == 10) && (opt == 3) && optSelect && !gamePause){
        clear();
        optSelect = false;
        opt = 0;
        return;
    }

    //Select key when pause menu is displayed and option 4 to be selected.
    if((c == KEY_ENTER || c == 10) && (opt == 3) && gamePause && gameStarted){
        clear();
        gamePause = false;
        gameStarted = false;
        opt = 0;
        return;
    }

    if((c == KEY_ENTER || c == 10) && opt == 0 && gamePause && gameStarted){
        clear();
        gamePause = false;
        gameStarted = true;
        opt = 0;
        printBoard(y,x);
        persistBoard();
        return;
    }

    //Key movement UP and DOWN.
    if(c == KEY_DOWN && opt < 3) opt++;
    else if(c == KEY_UP && opt > 0) opt--;

    //Displays the menus
    if(!optSelect && !gameStarted) showMenu(y, x, opt);
    if(optSelect && !gameStarted) gameMode(y, x, opt);
    if(gamePause && gameStarted) showPauseMenu(y,x, opt);
    return;
}


int main(){
    int x,y;
    int cordx, cordy;
    int borderUp, borderDown, borderLeft, borderRight;
    initscr();
    start_color();

    init_pair(1, COLOR_GREEN, COLOR_YELLOW);
    init_pair(2, COLOR_GREEN, COLOR_RED);
    init_pair(3, COLOR_GREEN, COLOR_MAGENTA);

    keypad(stdscr, true);
    noecho();
    getmaxyx(stdscr, y, x);
    cordy = (y/2)-4;
    cordx = (x/2)-3;
    borderUp = (y/2)-4;
    borderLeft = (x/2)-3;
    borderRight = (x/2)+2;
    borderDown = (y/2);
    
    int opt = 0;
    while(true){
        if(isExit) break;
        nodelay(stdscr, true);
        curs_set(0);
            keyMovement((y/2)-5, (x/2)-5, opt);
        curs_set(1);
        nodelay(stdscr, false);


        if(gameStarted){
            attron(COLOR_PAIR(3));
            if(countTurn == 9){
                mvprintw (5,30, "Game Draw");
                break;
            }
            if(!gamePause){
                attroff(COLOR_PAIR(3));
                displayTurn((y/2)-10, (x/2)-10, cordy, cordx);
                playTurn(cordy, cordx, borderUp, borderDown, borderLeft, borderRight);
                attron(COLOR_PAIR(3));
            }
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
            attroff(COLOR_PAIR(3));
        }
    }
    curs_set(0);
    refresh();
    endwin();
    return 0;
}
