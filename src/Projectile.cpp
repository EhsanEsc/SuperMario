
#include "Projectile.h"
using namespace std;

const int PDIM = 12;
const int FIRE_SPEED = 8;
const int FIRE_LIFE_TIME = 30;

Projectile::Projectile(Rectangle pos, Dir dir, int time)
{
    shape.set_rect(Rectangle(pos.x,pos.y+pos.h-DIM/2,PDIM,PDIM));
    if(dir == Dir::LEFT)
      shape.set_vx(-FIRE_SPEED);
    else
      shape.set_vx(FIRE_SPEED);

    btime = time;

    texture.add_dir("origin","assets/sprites/projectiles");
    texture.set_dir("origin");

    texture.add_state("normal",2);
    texture.set_state("normal");

    texture.set_name("fire");
}

Shape& Projectile::get_shape() { return shape; }
bool Projectile::out_of_time(int timer) { return timer-btime>=FIRE_LIFE_TIME; }
void Projectile::draw(Window& win, Rectangle camera) { texture.draw(win, camera, shape.get_rect()); }
