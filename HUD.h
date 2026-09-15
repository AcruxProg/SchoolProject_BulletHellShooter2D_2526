#pragma once
#include <SDL3/SDL.h>
#include <string>  







class HUD
{
public:
    
    HUD(SDL_Texture* shipTexture) : m_shipTexture(shipTexture) {}
    
    
    void Render(SDL_Renderer* renderer,int lives,int score, bool hasSpread);
    void RenderGameOver(SDL_Renderer* renderer,int totalScore);
    
    
    
private:
    
     const uint8_t SEGMENT_MASKS[10] = //Didn't know if there was a better way instead of hardcoding this 
{
        /*0*/ 0b0111111,
        /*1*/ 0b0000110,
        /*2*/ 0b1011011,
        /*3*/ 0b1001111,
        /*4*/ 0b1100110,
        /*5*/ 0b1101101,
        /*6*/ 0b1111101,
        /*7*/ 0b0000111,
        /*8*/ 0b1111111,
        /*9*/ 0b1101111,
    };
    
    static constexpr float SEGMENT_THICKNESS = 3.0f;
    static constexpr float WEAPON_INDICATOR_SIZE=15.0f;
    
    
    static constexpr float ICON_SIZE = 20.0f;
    static constexpr float ICON_PAD = 6.0f;
    static constexpr float ICON_Y  = 10.0f;
    static constexpr float ICON_X_START = 12.0f;
    
    static constexpr float DIGIT_WIDHT = 18.0f;
    static constexpr float DIGIT_HEIGHT= 32.0f;
    static constexpr float DIGIT_SPACING = 4.0f;
    
    static constexpr float SCORE_Y = 12.0f;
    static constexpr float SCORE_PAD_RIGHT= 12.0f;
    
    
    
    
    static constexpr const char* GAME_OVER_TEXT = "GAME OVER";
    static constexpr const char* GAME_OVER_PROMPT_TEXT="PRESS ESC TO QUIT";
    static constexpr const char* FINAL_SCORE_TEXT = "Final Score :  ";
    
    static constexpr SDL_Color GAME_OVER_COLOR = {255, 60, 60, 255};
    static constexpr SDL_Color FINAL_SCORE_COLOR= {255, 230, 80, 255};
    static constexpr SDL_Color GAME_OVER_PROMPT_COLOR= {220, 220, 220, 255};
    
    static constexpr float GAME_OVER_SCALE=6.0f;
    static constexpr float FINAL_SCORE_SCALE=3.0f;
    static constexpr float GAME_OVER_PROMPT_SCALE=2.0f;
    
    
    
    
    
    static constexpr float GAMEOVER__Y_FRAC  = 0.40f;
    static constexpr float FINAL_SCORE_Y_FRAC  = 0.55f;
    static constexpr float GAMEOVER_PROMPT_Y_FRAC = 0.70f;
    

    
    
    
    SDL_Texture* m_shipTexture = nullptr;
    
    void DrawDigit(SDL_Renderer* renderer,int digit,float x, float y,float w,float h);
    void DrawNumber(SDL_Renderer* renderer,int value,float xRight,float y, float digitW, float digitH,float spacing);
    void DrawTitle(SDL_Renderer* renderer,SDL_Color titleColor,const char* title,const std::string& scoreString,float titleScale,float screenFracY);
    
    
    
    
    
    
    
    
    
    
    
    
    
    
};
