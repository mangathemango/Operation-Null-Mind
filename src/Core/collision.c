#include <collision.h>
#include <environment.h>


typedef struct {
    bool top;
    bool bottom;
    bool left;
    bool right;
} CollisionSides;

// Function for checking whether player and brick are colliding or not
// Returns which sides are colliding
void Check_Collision(SDL_Rect a, SDL_Rect b, int *collisionFlag) {
    // Calculate the edges of both rectangles
    int leftA = a.x;
    int rightA = a.x + a.w;
    int topA = a.y;
    int bottomA = a.y + a.h;
    
    int leftB = b.x;
    int rightB = b.x + b.w;
    int topB = b.y;
    int bottomB = b.y + b.h;

    // Check for collision
    if (rightA > leftB && 
        leftA < rightB && 
        bottomA > topB && 
        topA < bottomB) {
        *collisionFlag = 1;

        // Calculate overlap amounts to determine collision side
        int overlapLeft = rightA - leftB;
        int overlapRight = rightB - leftA;
        int overlapTop = bottomA - topB;
        int overlapBottom = bottomB - topA;

        // Find the smallest overlap to determine which side collided
        int minOverlap = overlapLeft;
        if (overlapRight < minOverlap) minOverlap = overlapRight;
        if (overlapTop < minOverlap) minOverlap = overlapTop;
        if (overlapBottom < minOverlap) minOverlap = overlapBottom;

        // Set collision flag based on the smallest overlap
        if (minOverlap == overlapLeft) *collisionFlag |= 0x1;     // Left collision
        if (minOverlap == overlapRight) *collisionFlag |= 0x2;    // Right collision
        if (minOverlap == overlapTop) *collisionFlag |= 0x4;      // Top collision
        if (minOverlap == overlapBottom) *collisionFlag |= 0x8;   // Bottom collision
    } else {
        *collisionFlag = 0;
    }
}