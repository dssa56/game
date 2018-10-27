#include <SDL2/SDL.h>

void get_move_from_event(event, &move)
{
    switch(event.type)
    {
      case SDL_KEYDOWN:
        switch(event.key.keysym.sym)
        {
          case SDLK_LEFT:
            move[0] = -1;
            break;
          case SDLK_RIGHT:
            move[0] = 1;
            break;
          case SDLK_UP:
            move[1] = 1;
            break;
          case SDLK_DOWN:
            move[1] = -1;
            break;
          default:
            break;
        } break;
      case SDL_KEYUP:
        switch(event.key.keysym.sym)
        {
          case SDLK_LEFT:
            move[0] = 0;
            break;
          case SDLK_RIGHT:
            move[0] = 0;
            break;
          case SDLK_UP:
            move[1] = 0;
            break;
          case SDLK_DOWN:
            move[1] = 0;
            break;
          default:
            break;
        } break;
  }
}
