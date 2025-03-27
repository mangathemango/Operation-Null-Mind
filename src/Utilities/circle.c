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

SDL_Texture* CreateCircleTexture(int radius, SDL_Color color) {
    // Create a texture with dimensions to fit the circle
    int diameter = radius * 2;
    SDL_Texture* texture = SDL_CreateTexture(
        app.resources.renderer,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_TARGET,
        diameter, 
        diameter
    );
    
    // Enable alpha blending on the texture
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    
    // Set the render target to our texture
    SDL_SetRenderTarget(app.resources.renderer, texture);
    
    // Clear the texture with transparent background
    SDL_SetRenderDrawColor(app.resources.renderer, 0, 0, 0, 0);
    SDL_RenderClear(app.resources.renderer);
    
    // Set draw color for the circle
    SDL_SetRenderDrawColor(app.resources.renderer, color.r, color.g, color.b, color.a);
    
    // Draw the filled circle
    for (int y = 0; y < diameter; y++) {
        for (int x = 0; x < diameter; x++) {
            int dx = radius - x;
            int dy = radius - y;
            if ((dx*dx + dy*dy) <= (radius * radius)) {
                SDL_RenderDrawPoint(app.resources.renderer, x, y);
            }
        }
    }
    
    // Reset render target back to the default
    SDL_SetRenderTarget(app.resources.renderer, app.resources.screenTexture);
    
    return texture;
}

/**
 * Draws an unfilled circle directly to the renderer
 * @param center Center position of the circle
 * @param radius Radius of the circle
 * @param color Color of the circle outline
 */
void DrawCircleOutline(Vec2 center, int radius, SDL_Color color) {
    SDL_SetRenderDrawColor(app.resources.renderer, color.r, color.g, color.b, color.a);
    
    int x = 0;
    int y = radius;
    int d = 3 - 2 * radius;
    
    // Draw octant points
    while (y >= x) {
        // Draw the 8 octant points
        SDL_RenderDrawPoint(app.resources.renderer, center.x + x, center.y - y);
        SDL_RenderDrawPoint(app.resources.renderer, center.x + y, center.y - x);
        SDL_RenderDrawPoint(app.resources.renderer, center.x + y, center.y + x);
        SDL_RenderDrawPoint(app.resources.renderer, center.x + x, center.y + y);
        SDL_RenderDrawPoint(app.resources.renderer, center.x - x, center.y + y);
        SDL_RenderDrawPoint(app.resources.renderer, center.x - y, center.y + x);
        SDL_RenderDrawPoint(app.resources.renderer, center.x - y, center.y - x);
        SDL_RenderDrawPoint(app.resources.renderer, center.x - x, center.y - y);
        
        // Update using Bresenham's algorithm
        if (d < 0) {
            d = d + 4 * x + 6;
        } else {
            d = d + 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
}

/**
 * Creates a texture containing an unfilled circle
 * @param radius Radius of the circle
 * @param color Color of the circle outline
 * @param thickness Line thickness (1 for thin outline)
 * @return SDL_Texture* containing the circle outline
 */
SDL_Texture* CreateCircleOutlineTexture(int radius, SDL_Color color, int thickness) {
    // Create a texture with dimensions to fit the circle
    int diameter = radius * 2;
    SDL_Texture* texture = SDL_CreateTexture(
        app.resources.renderer,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_TARGET,
        diameter, 
        diameter
    );
    
    // Enable alpha blending
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    
    // Set the render target to our texture
    SDL_SetRenderTarget(app.resources.renderer, texture);
    
    // Clear with transparent background
    SDL_SetRenderDrawColor(app.resources.renderer, 0, 0, 0, 0);
    SDL_RenderClear(app.resources.renderer);
    
    // Draw multiple circles for thickness
    SDL_SetRenderDrawColor(app.resources.renderer, color.r, color.g, color.b, color.a);
    
    for (int t = 0; t < thickness; t++) {
        int r = radius - t;
        if (r < 0) break;
        
        int x = 0;
        int y = r;
        int d = 3 - 2 * r;
        
        while (y >= x) {
            // Draw the 8 octant points
            SDL_RenderDrawPoint(app.resources.renderer, radius + x, radius - y);
            SDL_RenderDrawPoint(app.resources.renderer, radius + y, radius - x);
            SDL_RenderDrawPoint(app.resources.renderer, radius + y, radius + x);
            SDL_RenderDrawPoint(app.resources.renderer, radius + x, radius + y);
            SDL_RenderDrawPoint(app.resources.renderer, radius - x, radius + y);
            SDL_RenderDrawPoint(app.resources.renderer, radius - y, radius + x);
            SDL_RenderDrawPoint(app.resources.renderer, radius - y, radius - x);
            SDL_RenderDrawPoint(app.resources.renderer, radius - x, radius - y);
            
            if (d < 0) {
                d = d + 4 * x + 6;
            } else {
                d = d + 4 * (x - y) + 10;
                y--;
            }
            x++;
        }
    }
    
    // Reset render target
    SDL_SetRenderTarget(app.resources.renderer, app.resources.screenTexture);
    
    return texture;
}