#pragma once
#include "../Engine/Entity.h"



constexpr uint32_t ANIM_FRAME_MS = 200;
constexpr uint32_t ANIM_FRAME_COUNT=2;


enum class EnemyBehavior
{
        Straight,
        Wave
};


class Enemy : public Entity
{
public:
        
        Enemy(vec2 position,SDL_Texture*,EnemyBehavior enemyBehavior);
        ~Enemy() override = default;
        
        void Update(float deltaTime) override;
        void Render(SDL_Renderer* renderer) override;
        
        EnemyBehavior enemyBehavior;
        int healthPoint=1;
        int scoreValue=100;
        
        
private:
        float m_baseX = 0.01f;
        float m_speedY=120.0f;
        
        float m_waveTime=0.0f;
        float m_waveAmplitude=100.0f;
        float m_waveFrequency=3.0f;
        
        
        
        
    
};
