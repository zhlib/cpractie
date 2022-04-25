#include <stdio.h>
#include <curses.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>
#include <stdlib.h>
#include "../common/bounce.h"


void hello1();
void hello2();
void hello3();
int  hello5();
int  set_ticker(int n_msecs);
void bounce2d();
void set_up();
void wrap_up();
int bounce_or_lose(struct ppball *bp);
void ball_move(int);


#define LEFTEDGE  10
#define RIGHTEDGE 30
#define ROW       10

struct ppball the_ball;

 

int
main()
{
    bounce2d();
}

void hello1() {
   initscr();

   clear();
   move(10,20);
   addstr("Hello, world");
   move(LINES-1,0);
   refresh();
   getch();
   endwin();
}


void hello2() {
    int i;
    
    initscr();
    clear();

    for(i=0; i < LINES; i ++) {
        move(i, i + 1);
        if (i%2 == 0)
            standout();
        addstr("Hello,world");
        if (i%2 == 1)
            standout();
        refresh();

        sleep(1);
        move(i, i + 1);
        addstr("                     ");
    }

    endwin();
}



void hello3() {

    char *message = "Hello";
    char *blank   = "     ";
    int  dir =  +1;
    int  pos = LEFTEDGE;

    initscr();
    clear();

    while(1) {
        move(ROW, pos);
        addstr(message);
        move(LINES-1,COLS-1);
        refresh();
        sleep(1);
        move(ROW, pos);
        addstr(blank);
        pos += dir;
        if (pos >= RIGHTEDGE)
            dir = -1;
        if (pos <= LEFTEDGE)
            dir = +1;
    }

    endwin();
}

int hello5() 
{
    void countdown(int);

    signal(SIGALRM, countdown);
    if (set_ticker(500) == -1)
    {
        perror("set_ticker");
    }else {
        while(1)
        {
            pause();
        }
    }
     return 0;
}


int set_ticker(int n_msecs)
{
    struct itimerval new_timeset;
    long n_sec, n_usecs;
    n_sec   = n_msecs/1000;
    n_usecs = (n_msecs%1000) * 1000L;

    new_timeset.it_interval.tv_sec  = n_sec;
    new_timeset.it_interval.tv_usec = n_usecs;

    new_timeset.it_value.tv_sec  = n_sec;
    new_timeset.it_value.tv_usec = n_usecs;

    return setitimer(ITIMER_REAL, &new_timeset, NULL);
}

void countdown(int signum)
{
    static int num = 10;
    printf("%d..",num--);
    fflush(stdout);
    if(num < 0){
        printf("DONE! \n");
        exit(0);
    }
}


void bounce2d() {

    
    int c;

    set_up();
    while ( ( c = getchar()) != 'Q' ) {
        if(c == 'f') the_ball.x_ttm--;
        else if(c =='s') the_ball.x_ttm++;
        else if(c == 'F')the_ball.y_ttm--;
        else if(c == 'S')the_ball.y_ttm++;
    }

    wrap_up();
}

void set_up()
{
    

    the_ball.y_pos = Y_INIT;
    the_ball.x_pos = X_INIT;
    the_ball.y_ttg = the_ball.y_ttm = Y_TTM;
    the_ball.x_ttg = the_ball.x_ttm = X_TIM;
    the_ball.y_dir = 1;
    the_ball.x_dir = 1;
    the_ball.symbol = DFL_SYMBOL;

    initscr();
    noecho();
    crmode();

    signal(SIGINT,SIG_IGN);
    mvaddch( the_ball.y_pos, the_ball.x_pos, the_ball.symbol); 
    refresh();
    
    signal( SIGALRM, ball_move ) ;
    set_ticker(1000 / TICKS_PER_SEC);
}

void wrap_up()
{
    set_ticker(0);
    endwin();
}

void ball_move(int signum)
{
    int     y_cur, x_cur, moved;

    signal(SIGALRM, SIG_IGN);
    y_cur = the_ball.y_pos;
    x_cur = the_ball.x_pos;
    moved = 0;

    if (the_ball.y_ttm >0 && the_ball.y_ttg -- == 1)
    {
        the_ball.y_pos += the_ball.y_dir;
        the_ball.y_ttg  = the_ball.y_ttm;
        moved = 1;
    }

    if (the_ball.x_ttm > 0 && the_ball.x_ttg -- == 1)
    {
        the_ball.x_pos += the_ball.x_dir;
        the_ball.x_ttg  = the_ball.x_ttm;
        moved = 1;
    }

    if (moved) {
        mvaddch(y_cur, x_cur, BLANK);
        mvaddch(y_cur, x_cur, BLANK);
        mvaddch(the_ball.y_pos, the_ball.x_pos, the_ball.symbol);
        bounce_or_lose(&the_ball);
        move(LINES-1,COLS -1);
        refresh();
    }
    signal(SIGALRM,ball_move);
}

int bounce_or_lose(struct ppball *bp)
{
    int return_val = 0;

    if (bp->y_pos == TOP_ROW){
        bp->y_dir = 1;
        return_val = 1;
    }else if ( bp->y_pos == BOT_ROW){
        bp->y_dir = -1;
        return_val = 1;
    }

    if (bp->x_pos == LEFT_EDE) {
        bp->x_dir = 1;
        return_val = 1;
    }else if (bp->x_pos == RIGHT_EDGE) {
        bp->x_dir = -1;
        return_val = 1;
    }
    return return_val;
}