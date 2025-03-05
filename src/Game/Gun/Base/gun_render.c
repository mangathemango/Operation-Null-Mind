#include <gun.h>

void Gun_Render() {
    Animation_Render(gunAnimation, 
                    Vec2_Subtract(
                        player.state.position,
                        Vec2_Divide(gunAnimData.spriteSize, 2)
                    ), 
                    gunAnimData.spriteSize);
}