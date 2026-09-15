#pragma once
#include"../Engine/Entity.h"

constexpr int COLLECTABLE_SIZE=24;

enum class CollectableType
{
    WeaponUpgrade
    ,UpLife
};

class Collectable : public Entity
{
public:
    
    Collectable(vec2 position,CollectableType type);
    ~Collectable() override = default;
    
    
    void Update(float deltaTime) override;
    void Render(SDL_Renderer* renderer) override;
    
    CollectableType collectableType;
    
private:
    
    float m_fallSpeed=50.0f;
    float m_pusleTimer=0.0f;
};
