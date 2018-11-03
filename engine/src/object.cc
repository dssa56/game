#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <string>
#include "config.h"
#include "collision.h"

class GameState
{
public:
  GameState();
  void update();
  void render();
private:
  PlayerObject player;
  std::vector<MobileObject> mobiles;
  std::vector<GameObject> statics;
  Canvas canvas;
}

void GameState::GameState()
{
  std::vector<MobileObject> mobiles;
  std::vector<GameObject> statics;
  PlayerObject player;
  MobileObject square_0(SQUARE_TXT_PATH, SQUARE_0_INIT_POS);
  mobiles.push_back(square_0);
  MobileObject square_1(SQUARE_TXT_PATH, SQUARE_1_INIT_POS);
  mobiles.push_back(sqaure_1);
  GameObject big_square(BIG_SQUARE_TXT_PATH, BIG_SQUARE_INIT_POS);
  statics.push_back(big_square);
}

void GameState::render()
{
  update();
  canvas.display_scene();
}

void GameState::update()
{
  for(auto& mob: mobiles)
    mob.update(player, statics);
}

class GameObject
{
public:
  GameObject(){};
  GameObject(std::string txt_path, Canvas& canv, SDL_Rect pos);
protected:
  SDL_Texture* texture;
  SDL_Rect position;
private:
  friend class Canvas;
}

GameObject::GameObject(std::string txt_path, Canvas& canv, SDL_Rect pos)
  :position{pos}
{
  SDL_Surface* surf = SDL_LoadBMP(txt_path.c_str());
  SDL_Texture* texture = SDL_CreateTextureFromSurface(canv.renderer, surf);
  SDL_DestroySurface(surf);
}

class MobileObject: public GameObject
{
public:
  using GameObject::GameObject;
  void update(GameObject& player; std::vector<GameObject> stats);
  void collide(std::vector<float>& velocity, std::vector<GameObject> stats);
  void move(std::vector<float>& velocity);
}

MobileObject::update(PlayerObject& player; std::vector<GameObject> stats)
{
  std::vector<float> velocity{0, 0};
  velocity[0] = (player.position.x > position.x) ? 1 : -1;
  velocity[1] = (player.position.y > position.y) ? 1 : -1;
  this.collide(velocity, stats);
  this.move(velocity);
}

MobileObject::collide(std::vector<float>& velocity,
                        std::vector<GameObject> stats)
{
  for(auto& stat : stats)
  {
    std::vector<bool> is_collided = (
        check_collision(position, stat.position, velocity));
    if(is_collided[0])
      velocity[0] = 0;
    if(is_collided[1])
      velocity[1] = 0;
  }
}

MobileObject::move(std::vector<float> velocity)
{
  position.y += velocity[0];
  position.x += velocity[1];
}

class PlayerObject: GameObject
{
public:
  using GameObject::GameObject;
  void update(std::vector<int> move);
}

PlayerObject::update(std::vector<int> move)
{
  std::vector<float> velocity = move;
  for(auto& v : velocity)
    v *= PLAYER_VELOCITY;
  this.collide(velocity, stats);
  this.move(velocity);
}

class Canvas
{
public:
  Canvas();
  void display_scene(std::vector<MobileObject> mobs,
                     std::vector<GameObject> stats);
  SDL_Renderer* get_renderer(){return renderer;}
private:
  friend class GameObject;
  SDL_Window *window;
  SDL_Renderer *renderer;
}

Canvas::Canvas()
{
  window = SDL_CreateWindow("SquareGame", SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED, 640, 480,
                                          SDL_WINDOW_SHOWN);
  if (window == nullptr)
  {
    std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << "\n";
  }
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (renderer == nullptr)
  {
    std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << "\n";
  }
}

template <typename T>
void render_loop(SDL_Renderer *ren, std::vector<T>objs)
{
  for(auto& obj: objs)
    SDL_RenderCopy(renderer, obj.texture, NULL, obj.position);
}

void Canvas::display_scene(std::vector<MobileObject> mobs,
                      std::vector<GameObject> stats)
{
  render_loop(renderer, mobs);
  render_loop(renderer, stats);
  SDL_RenderPresent(renderer);
  SDL_Delay(RENDER_TIME_DELAY);
}
