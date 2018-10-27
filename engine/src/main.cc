#include <SDL2/SDL.h>
#include <vector>
#include "gamestate.h"
#include "keyboard.h"

int main()
{
  GameState gamestate;
  SDL_Event event;
  vector<int> move_xy{0, 0};
  bool quit = false;

  SDL_Init(SDL_INIT_EVERYTHING);

  while(!quit)
  {
    while(SDL_PollEvent(&event))
    {
      if(event.type == SDL_QUIT)
      {
        quit = true;
        break;
      }
      get_move_from_event(event, move_xy);
      gamestate.player.move(move_xy);
      gamestate.render();
    }
  }
}
