
#include "okno.h"


int main() {
  
    //silnik gry 
    window okno;
    // game loop

    //inicjacja losowego nasienia 
    srand(static_cast<unsigned>(time(0)));

    while (okno.running()) {
        //update 
        okno.okno_update();
        //render
        okno.okno_render();

    }
    return 0;
}

/*
to do 

*/
