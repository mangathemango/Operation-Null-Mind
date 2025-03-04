#include <player.h>
#include <app.h>

/*
*   Renders the player sprite based on the player's position.
*/
int Player_Render() {
    Animation_Render(player.config.animation, 
                    Vec2_Subtract(
                        player.state.position,
                        Vec2_Divide(player.config.spriteSize, 2)
                    ), 
                    player.config.spriteSize);
    return 0;
}




