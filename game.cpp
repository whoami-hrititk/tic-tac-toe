#include<ncurses.h>
 
bool xturn = true;
bool oturn = false;

char board[7][14] = {
    "~~~~~~~~~~~~~",
    "|   |   |   |",
    "~~~~~~~~~~~~~",
    "|   |   |   |",
    "~~~~~~~~~~~~~",
    "|   |   |   |",
    "~~~~~~~~~~~~~"
};

void play(int cordy, int cordx){
    if(xturn){
        mvaddch(cordy, cordx, 'X');
        xturn = false;
        oturn = true;
    }else if(oturn){
        mvaddch(cordy, cordx, 'O');
        oturn = false;
        xturn = true;
    }
    refresh();
    return;
}
void fillBoxes(){
    
    return;
}

void displayTurn(int y, int x, int cordy, int cordx){
    attron(A_BOLD);
    if (xturn){
        mvprintw(y,x,"TURN: X, X= %d, Y=%d",cordx,cordy);
        
    }else if(oturn){
        mvprintw(y,x,"TURN: O, X= %d, Y=%d",cordx,cordy);
    }else{
        mvprintw(y-2,x+5, "This box is already filled!");
    }
    attroff(A_BOLD);
    refresh();
    return;
}

void playTurn(int& cordy, int& cordx, int borderUp, int borderDown, int borderLeft, int borderRight){
    move(cordy, cordx);
    int c = getch();
    if(c == KEY_ENTER || c == 10){
        play(cordy, cordx);
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
    //curs_set(0);
   
    printBoard((y/2)-5,(x/2)-5);
    while(true){
        displayTurn((y/2)-10, (x/2)-10, cordy, cordx);
        playTurn(cordy, cordx, borderUp, borderDown, borderLeft, borderRight);
        mvprintw(0,0,"Y=%d, X=%d", cordy, cordx);
        
    }
    getch();
    refresh;
    endwin();
    return 0;
}