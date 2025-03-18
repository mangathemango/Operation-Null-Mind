#include <enemy.h>

void Enemy_Spawn(EnemyData data, Vec2 position) {
    for (int i = 0; i < ENEMY_MAX; i++) {
        if (!data.state.isDead) continue;
        EnemyData* enemy = &enemies[i];
        enemy->state.isDead = false;
        enemy->state.position = position;
        enemy->state.velocity = Vec2_Zero;
        enemy->state.acceleration = Vec2_Zero;
        enemy->stats.maxHealth = data.stats.maxHealth;
        enemy->state.currentHealth = data.stats.maxHealth;
        enemy->stats.damage = data.stats.damage;
        enemy->stats.speed = data.stats.speed;
        enemy->type = data.type;
        enemy->start = data.start;
        enemy->update = data.update;
        enemy->render = data.render;
        enemy->resources.animation = Animation_Create(&data.animData);
        enemy->state.collider = data.state.collider;
        enemy->state.collider.hitbox.x = position.x;
        enemy->state.collider.hitbox.y = position.y;
        
        enemy->animData = data.animData;
        Collider_Register(&enemy->state.collider, enemy);
        if (enemy->start) enemy->start(enemy);
        break;
    }
}