#include "../include/life.h"
#include "../include/history.h"
int main(int argc, char ** argv)
{
    /* No stream */ 
    Cell c1 (0,1);
    Cell c2 (2,2);
    Cell c3 (3,3);
    Cell c4 (4,4);
    Life life (2,2);
    life.add(c1);
    life.add(c2);
    life.add(c3);
    life.add(c4);

    History h(10);
    life.print();
    /* No main 
    streamRead(argc,argv,&life,&h);
    l.print();
    while(!l.gameover(h)){
        l.update();
        l.print();
    }*/   
}
