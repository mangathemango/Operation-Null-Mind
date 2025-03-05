#include <animation.h>
#include <player.h>

#define GUN_SHOTGUN "Beretta 1301 Tactical"
#define GUN_BATTLE_RIFLE "FN SCAR-H"
#define GUN_SMG "KRISS Vector"
#define GUN_ASSAULT_RIFLE "M4A1 URG-I"
#define GUN_PISTOL "Glock 17"

extern AnimationData gunAnimData;

extern Animation* gunAnimation;
void Gun_AnimationInit();
void Gun_AnimationUpdate();
void Gun_Render();
void Gun_Start();
void Gun_Update();