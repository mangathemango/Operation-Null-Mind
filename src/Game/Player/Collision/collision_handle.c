#include <environment.h>
#include <player.h>
void Update_Player(PlayerState *player, Wall *wall){
    //Store previous position in case of collision
    float prevx = player->position.x;
    float prevy = player->position.y;
    //Update position based on velocity
    player->position.x += player->position.vx;
    player->position.y += player->position.vy;
    //Sync hitbox with new position
    player->hitbox.x = (int)player->position.x;
    player->hitbox.y = (int)player->position.y;
    //Collision check
    int collisionFlag = 0;
    Check_Collision(player->hitbox, wall->hitbox, &collisionFlag);
    if (collisionFlag) {
        //Revert to previous position if colliding
        player->position.x = prevx;
        player->position.y = prevy;
        player->hitbox.x = (int)prevx;
        player->hitbox.y = (int)prevy;
    }
}

