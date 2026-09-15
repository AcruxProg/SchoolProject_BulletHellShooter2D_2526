#include "HUD.h"
#include "Game.h"
#include <string>


using namespace Gfx;
using namespace std;




void HUD::Render(SDL_Renderer* renderer, int lives, int score, bool hasSpread)
{
    
    
    const SDL_FRect shipSrc={0,0,64,64};
    
    for (int i=0; i<lives; i++)
    {
        SDL_FRect dst ={12.0f+i*(ICON_SIZE+ICON_PAD),ICON_Y,ICON_SIZE,ICON_SIZE};
        SDL_SetTextureColorMod(m_shipTexture,255,255,255);
        SDL_SetTextureBlendMode(m_shipTexture,SDL_BLENDMODE_BLEND);
        SDL_RenderTexture(renderer, m_shipTexture,&shipSrc,&dst);
    }
    
    
    if (hasSpread)
    {
        
        SDL_FRect weaponIndicator ={12.0f + lives*(ICON_SIZE+ICON_PAD)+8.0f,ICON_Y+6.0f,WEAPON_INDICATOR_SIZE,WEAPON_INDICATOR_SIZE};
        SDL_SetRenderDrawColor(renderer,60,200,255,255);
        SDL_RenderFillRect(renderer,&weaponIndicator);
    }
    
   
    
    
    SDL_SetRenderDrawColor(renderer,255,255,80,255);
    DrawNumber(renderer,score,DISPLAY_WIDTH - SCORE_PAD_RIGHT,SCORE_Y,DIGIT_WIDHT,DIGIT_HEIGHT,DIGIT_SPACING);
    
    
}

void HUD::RenderGameOver(SDL_Renderer* renderer, int totalScore)
{
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 180);
    SDL_FRect overlay = { 0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT };
    SDL_RenderFillRect(renderer, &overlay);
    
    
    
    DrawTitle(renderer,GAME_OVER_COLOR,GAME_OVER_TEXT,"",GAME_OVER_SCALE,GAMEOVER__Y_FRAC);
    DrawTitle(renderer,GAME_OVER_PROMPT_COLOR,GAME_OVER_PROMPT_TEXT,"",GAME_OVER_PROMPT_SCALE,GAMEOVER_PROMPT_Y_FRAC);
    
    const string finalScoreText=FINAL_SCORE_TEXT + to_string(totalScore);
    DrawTitle(renderer,FINAL_SCORE_COLOR,nullptr,finalScoreText,FINAL_SCORE_SCALE,FINAL_SCORE_Y_FRAC);
    
   
    
}

void HUD::DrawDigit(SDL_Renderer* renderer, int digit, float x, float y, float w, float h)
{
    if (digit<0 || digit>9)
        return;
    
    const uint8_t mask = SEGMENT_MASKS[digit];
    const float halfH= h*0.5f;
    
    SDL_FRect segment;
    
    if (mask & (1<<0)) 
    {
        segment={x,y,w,SEGMENT_THICKNESS};
        SDL_RenderFillRect(renderer, &segment);
    }
    if (mask & (1 << 1))
    {
        
        segment = { x + w - SEGMENT_THICKNESS, y, SEGMENT_THICKNESS, halfH };        
        SDL_RenderFillRect(renderer, &segment);
    }
    if (mask & (1 << 2))
    {
        segment = { x + w - SEGMENT_THICKNESS, y + halfH, SEGMENT_THICKNESS, halfH };  
        SDL_RenderFillRect(renderer, &segment);
    }
    if (mask & (1 << 3))
    {
        segment = { x, y + h - SEGMENT_THICKNESS, w, SEGMENT_THICKNESS};               
        SDL_RenderFillRect(renderer, &segment);
    }
    
    if (mask & (1 << 4))
    { 
        segment = { x, y + halfH, SEGMENT_THICKNESS, halfH };     
        SDL_RenderFillRect(renderer, &segment); 
    }
    if (mask & (1 << 5))
    { 
        segment = { x, y, SEGMENT_THICKNESS, halfH };                
        SDL_RenderFillRect(renderer, &segment); 
    }
    if (mask & (1 << 6))
    {
        segment = { x, y + halfH - SEGMENT_THICKNESS * 0.5f, w, SEGMENT_THICKNESS }; 
        SDL_RenderFillRect(renderer, &segment);
    }
        
    
    
}

void HUD::DrawNumber(SDL_Renderer* renderer, int value, float xRight, float y, float digitW, float digitH,
    float spacing)
{
    
    if (value<0)
        value=0;
    
    int currentValue=value;
    float posX = xRight-digitW;
    
    do
    {
        DrawDigit(renderer, currentValue%10, posX, y, digitW, digitH); 
        currentValue=currentValue/10;
        posX-=(digitW+spacing);
    }while (currentValue>0);
    
    
}

void HUD::DrawTitle(SDL_Renderer* renderer,SDL_Color titleColor ,const char* title, const std::string& scoreString, float titleScale,float screenFracY)
{
    float titleWidth;
    
    if (title==nullptr)
        titleWidth= static_cast<float>(scoreString.size())* 8.0f * titleScale;
    else
        titleWidth= static_cast<float>(SDL_strlen(title)) *8.0f * titleScale;
    
    
    SDL_SetRenderDrawColor(renderer, titleColor.r, titleColor.g, titleColor.b, titleColor.a);
    SDL_SetRenderScale(renderer, titleScale, titleScale);
    
    if (title==nullptr)
        SDL_RenderDebugText(renderer,(DISPLAY_WIDTH -titleWidth)*0.5f/titleScale,(DISPLAY_HEIGHT *screenFracY)/titleScale,scoreString.c_str());
    else
        SDL_RenderDebugText(renderer,(DISPLAY_WIDTH-titleWidth)*0.5f/titleScale,(DISPLAY_HEIGHT *screenFracY)/titleScale,title);
    
    SDL_SetRenderScale(renderer, 1.0f, 1.0f);
    
}
