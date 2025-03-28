/**
 * @file death_layout.c
 * @brief Implements the death screen
 *
 * Manages the pause screen UI layout, button interactions,
 * and transitions between game and pause states.
 *
 * @author Darren
 * @date 2025-03-28
 */

 #include <death.h>
 #include <UI_text.h>
 #include <input.h>
 #include <app.h>
 #include <sound.h>
 
 static UIElement* youTextElement = NULL;
 static UIElement* resumeTextElement = NULL;
 static UIElement* diedTextElement = NULL;
 
 /**
  * @brief [Start] Initializes the pause menu UI elements
  * 
  * Creates the text elements that make up the pause menu screen,
  * positioning them appropriately on the screen.
  */
 void Death_Start() {
 
     youTextElement = UI_CreateText(
         "You", 
         (SDL_Rect) {
             app.config.screen_width / 2 - 20, 
             app.config.screen_height / 2 - 50, 
             0, 
             0
         }, 
         (SDL_Color){255, 255, 255, 255}, 
         4.0f, 
         UI_TEXT_ALIGN_RIGHT, 
         app.resources.textFont
     );

     diedTextElement = UI_CreateText(
        "died", 
        (SDL_Rect) {
            app.config.screen_width / 2, 
            app.config.screen_height / 2 - 50, 
            0, 
            0
        }, 
        (SDL_Color){255, 0, 0, 255}, 
        4.0f, 
        UI_TEXT_ALIGN_LEFT, 
        app.resources.textFont
    );
 
     resumeTextElement = UI_CreateText(
         "Press ESC to start over", 
         (SDL_Rect) {
             app.config.screen_width / 2, 
             app.config.screen_height / 2 + 50, 
             0, 
             0
         }, 
         (SDL_Color){255, 255, 255, 255}, 
         1.0f, 
         UI_TEXT_ALIGN_CENTER, 
         app.resources.textFont
     );
 }
 
 /**
  * @brief [PostUpdate] Processes user input for the pause menu
  * 
  * Checks for the ESC key press to return to the game
  * from the pause menu.
  */
 void Death_Update() {
     if (Input->keyboard.keys[SDL_SCANCODE_ESCAPE].pressed) {
         app.state.currentScene = SCENE_MENU;
         Sound_Play_Music("Assets/Audio/Music/mainMenu.wav", -1);
     }
 }
 
 /**
  * @brief [Render] Draws the death scene to the screen
  * 
  * Renders the "Death" header and instructions for resuming
  * the game.
  */
 void Death_Render() {
     UI_RenderText(youTextElement);
     UI_RenderText(resumeTextElement);
     UI_RenderText(diedTextElement);
 }