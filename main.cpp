#include "Game.h"


int main()
{
    //Initialize game
    Game game;

    //Game loop
    while (game.getWindow())
    {
        //Update
        game.update();

        //Render
        game.render();
    }

    return 0;
}

