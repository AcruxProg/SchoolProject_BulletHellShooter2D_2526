#include "Enemy.h"
#include "Game.h"
#include <cmath>
using namespace Gfx;



Enemy::Enemy(vec2 position,SDL_Texture* texture,EnemyBehavior enemy_behavior) : Entity(position,vec2(0,0),EntityType::ENEMY,texture),enemyBehavior(enemy_behavior)
{
    dimension =vec2(40,40);
    m_baseX=position.x;
    
    
    if (enemy_behavior==EnemyBehavior::Straight)
    {
        m_speedY=200.0f;
        healthPoint=2;
        scoreValue=50;
    }
    else //Only 2 type in the state of the game so i used if/esle
    {
        m_speedY=100.0f;
        healthPoint=2;
        scoreValue=100;
    }
}

void Enemy::Update(float deltaTime)
{
    position.y+=m_speedY*deltaTime;
    
    
    if (enemyBehavior==EnemyBehavior::Wave)
    {
        m_waveTime+=deltaTime;
        position.x=m_baseX+ sin(m_waveTime*m_waveFrequency)*m_waveAmplitude;
    }
    
    if (position.y > DISPLAY_HEIGHT)
        toBeDestroyed=true;
    
}

void Enemy::Render(SDL_Renderer* renderer)
{
    // I will be using the same ship sprite sheet but chaning the color
    
    const uint32_t c_animFrame= (SDL_GetTicks() /ANIM_FRAME_MS)%ANIM_FRAME_COUNT;
    const SDL_FRect c_srcRect={static_cast<float>(c_animFrame) * 64.0f,0.0f,64.0f,64.0f};
    
    const SDL_FRect c_dst={position.x,position.y,dimension.x,dimension.y};
    
    
    if (enemyBehavior==EnemyBehavior::Straight)
        SDL_SetTextureColorMod(texture,255,0,0); //RED
    else
        SDL_SetTextureColorMod(texture,0,255,0); // Green
    
    
    
    SDL_SetTextureBlendMode(texture,SDL_BLENDMODE_BLEND);
    SDL_RenderTextureRotated(renderer,texture,&c_srcRect,&c_dst,180.0,nullptr,SDL_FLIP_NONE);
    
    
    
    SDL_SetTextureColorMod(texture,255,255,255);
    
    
    
    
}







