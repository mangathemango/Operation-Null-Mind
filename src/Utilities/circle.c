#include <app.h>
#include <circle.h>
#include <math.h>

void DrawFilledCircle(Vec2 center, int radius, SDL_Color color)
{
    SDL_SetRenderDrawColor(app.resources.renderer, color.r, color.g, color.b, color.a);
    for (int w = 0; w < radius * 2; w++)
    {
        for (int h = 0; h < radius * 2; h++)
        {
            int dx = radius - w; // horizontal offset
            int dy = radius - h; // vertical offset
            if ((dx*dx + dy*dy) <= (radius * radius))
            {
                SDL_RenderDrawPoint(app.resources.renderer, center.x + dx, center.y + dy);
            }
        }
    }
}

bool IsRectOverlappingCircle(SDL_Rect rect, Vec2 circleCenter, float radius) {
    // Find closest point on rectangle to circle center
    float closestX = fmaxf(rect.x, fminf(circleCenter.x, rect.x + rect.w));
    float closestY = fmaxf(rect.y, fminf(circleCenter.y, rect.y + rect.h));
    
    // Calculate distance from closest point to circle center
    float distanceX = circleCenter.x - closestX;
    float distanceY = circleCenter.y - closestY;
    float distanceSquared = distanceX * distanceX + distanceY * distanceY;
    
    // Check if distance is less than radius
    return distanceSquared <= radius * radius;
}