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

/**
 * @brief Draws a filled half-circle in a specified direction
 * 
 * Renders a half-circle filled with the specified color, oriented
 * in the direction provided by the direction vector.
 * 
 * @param center Center position of the half-circle
 * @param radius Radius of the half-circle
 * @param direction Direction vector determining the orientation
 * @param color Color of the half-circle
 */
void DrawFilledHalfCircle(Vec2 center, int radius, Vec2 direction, SDL_Color color)
{
    // Normalize direction vector to ensure consistent behavior
    direction = Vec2_Normalize(direction);
    
    SDL_SetRenderDrawColor(app.resources.renderer, color.r, color.g, color.b, color.a);
    for (int w = 0; w < radius * 2; w++)
    {
        for (int h = 0; h < radius * 2; h++)
        {
            int dx = radius - w; // horizontal offset
            int dy = radius - h; // vertical offset
            
            // Check if point is within the circle
            if ((dx*dx + dy*dy) <= (radius * radius))
            {
                // Create vector from center to this point
                Vec2 pointVector = {(float)dx, (float)dy};
                
                // Calculate dot product to determine if point is in the facing half
                float dotProduct = Vec2_Dot(direction, pointVector);
                
                // Only draw points in the half-circle facing the direction vector
                if (dotProduct > 0)
                {
                    SDL_RenderDrawPoint(app.resources.renderer, center.x + dx, center.y + dy);
                }
            }
        }
    }
}

/**
 * Creates a half-circle texture oriented in the specified direction
 * 
 * @param radius Radius of the half-circle
 * @param direction Direction vector determining the orientation
 * @param color Color of the half-circle
 * @return SDL_Texture* containing the half-circle
 */
SDL_Texture* CreateHalfCircleTexture(int radius, Vec2 direction, SDL_Color color) {
    // Normalize direction
    direction = Vec2_Normalize(direction);
    
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
    
    // Set draw color for the half-circle
    SDL_SetRenderDrawColor(app.resources.renderer, color.r, color.g, color.b, color.a);
    
    // Draw the filled half-circle
    for (int y = 0; y < diameter; y++) {
        for (int x = 0; x < diameter; x++) {
            int dx = x - radius;
            int dy = y - radius;
            
            // Check if within circle radius
            if ((dx*dx + dy*dy) <= (radius * radius)) {
                // Create vector from center to this point
                Vec2 pointVector = {(float)dx, (float)dy};
                
                // Check if in the correct half
                if (Vec2_Dot(direction, pointVector) > 0) {
                    SDL_RenderDrawPoint(app.resources.renderer, x, y);
                }
            }
        }
    }
    
    // Reset render target back to the default
    SDL_SetRenderTarget(app.resources.renderer, app.resources.screenTexture);
    
    return texture;
}


/**
 * Creates a texture containing an unfilled half-circle outline oriented in a specific direction
 * 
 * @param radius Radius of the half-circle
 * @param direction Direction vector determining the orientation
 * @param color Color of the half-circle outline
 * @param thickness Line thickness (1 for thin outline)
 * @return SDL_Texture* containing the half-circle outline
 */
SDL_Texture* CreateHalfCircleOutlineTexture(int radius, Vec2 direction, SDL_Color color, int thickness) {
    // Normalize direction
    direction = Vec2_Normalize(direction);
    
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
            // For each point, check if it's in the half-circle facing the direction
            Vec2 points[8] = {
                {(float)x, (float)-y},  // 1st octant
                {(float)y, (float)-x},  // 2nd octant
                {(float)y, (float)x},   // 3rd octant
                {(float)x, (float)y},   // 4th octant
                {(float)-x, (float)y},  // 5th octant
                {(float)-y, (float)x},  // 6th octant
                {(float)-y, (float)-x}, // 7th octant
                {(float)-x, (float)-y}  // 8th octant
            };
            
            // Check and draw each point if it's in the half facing the direction
            for (int i = 0; i < 8; i++) {
                if (Vec2_Dot(direction, points[i]) > 0) {
                    SDL_RenderDrawPoint(app.resources.renderer, 
                                       radius + points[i].x, 
                                       radius + points[i].y);
                }
            }
            
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
    
    
    // Reset render target
    SDL_SetRenderTarget(app.resources.renderer, app.resources.screenTexture);
    
    return texture;
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
    
    if (!texture) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to create circle texture: %s", SDL_GetError());
        return NULL;
    }
    
    // Enable alpha blending on the texture
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    
    // Store current render target
    SDL_Texture* prevTarget = SDL_GetRenderTarget(app.resources.renderer);
    
    // Set the render target to our texture
    if (SDL_SetRenderTarget(app.resources.renderer, texture) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to set render target: %s", SDL_GetError());
        SDL_DestroyTexture(texture);
        return NULL;
    }
    
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
    
    // Reset render target back to the previous target
    SDL_SetRenderTarget(app.resources.renderer, prevTarget);
    
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