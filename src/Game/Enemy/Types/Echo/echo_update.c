#include <enemy_echo.h>
#include <player.h>

void Echo_Update(EnemyData* data) {
    if (data->state.isDead) return;

    if (Vec2_Distance(data->state.position, player.state.position) < 500) {
        data->state.direction = Vec2_Normalize(Vec2_Subtract(player.state.position, data->state.position));
    } else {
        data->state.direction = Vec2_Zero;
    }
}