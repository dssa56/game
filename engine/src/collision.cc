#include <vector>
#include <SDL2/SDL.h>

bool check_collided(SDL_Rect pos_0, SDL_Rect pos_1, float vx, float vy)
{
  if(pos_0.x + pos_0.w + vx >= pos_1.x)
  {
    if(pos_0.x + vx <= pos_1.x + pos_1.w)
    {
      if(pos_0.y + pos_0.h + vy >= pos_1.y)
      {
        if(pos_0.y + vy <= pos_1.y + pos_1.h)
        {
          return true;
        }
      }
    }
  }
  return false;
}

std::vector<bool> check_collision(
                        SDL_Rect mover_position,
                        SDL_Rect static_position,
                        std::vector<float> velocity
                        )
{
  std::vector<bool> collided{false, false};
  collided[0] = check_collided(mover_position, static_position,
                              velocity[0], 0);
  collided[1] = check_collided(mover_position, static_position,
                              0, velocity[1]);
  return collided;
}
