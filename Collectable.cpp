#include "Collectable.h"
#include "Game.h"
#include "Player.h"

using namespace Gfx;
using namespace std;

Collectable::Collectable(vec2 position, CollectableType type) : Entity(position,vec2(0,0),EntityType::ENEMY,nullptr),collectableType(type)
{
    dimension=vec2(COLLECTABLE_SIZE,COLLECTABLE_SIZE);
}

void Collectable::Update(float deltaTime)
{
    position.y += m_fallSpeed*deltaTime;
    m_pusleTimer += deltaTime;
    
    
    if (position.y >DISPLAY_HEIGHT)
        toBeDestroyed=true;
    
    
}

void Collectable::Render(SDL_Renderer* renderer)
{
    
    const float c_pulse=0.5f+0.5f* sin(m_pusleTimer*6.0f);
    const float c_haloPad = 4.0f + c_pulse * 3.0f;
    
    SDL_FRect halo = { position.x - c_haloPad, position.y - c_haloPad, dimension.x + c_haloPad * 2.0f, dimension.y + c_haloPad * 2.0f };
    
    if (collectableType == CollectableType::WeaponUpgrade)
        SDL_SetRenderDrawColor(renderer, 60, 200, 255, static_cast<uint8_t>(80 + c_pulse * 100));
    else
        SDL_SetRenderDrawColor(renderer, 255, 80, 120, static_cast<uint8_t>(80 + c_pulse * 100));

    
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_RenderFillRect(renderer, &halo);
    
    
    
    //body
    SDL_FRect body = { position.x, position.y, dimension.x, dimension.y };
    if (collectableType == CollectableType::WeaponUpgrade)
        SDL_SetRenderDrawColor(renderer, 0, 120, 220, 255);
    else
        SDL_SetRenderDrawColor(renderer, 220, 0, 60, 255);

    SDL_RenderFillRect(renderer, &body);
    
    
    
    //symbol -- "W" via three vertical bars for weapon, "+" (cross) for life
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    if (collectableType == CollectableType::WeaponUpgrade)
    {
        SDL_FRect b1 = { position.x + 4.0f,  position.y + 4.0f, 3.0f, 16.0f };
        SDL_FRect b2 = { position.x + 10.5f, position.y + 4.0f, 3.0f, 16.0f };
        SDL_FRect b3 = { position.x + 17.0f, position.y + 4.0f, 3.0f, 16.0f };
        SDL_RenderFillRect(renderer, &b1);
        SDL_RenderFillRect(renderer, &b2);
        SDL_RenderFillRect(renderer, &b3);
    }
    else
    {
        SDL_FRect h = { position.x + 4.0f, position.y + 10.0f, 16.0f, 4.0f };
        SDL_FRect v = { position.x + 10.0f, position.y + 4.0f, 4.0f, 16.0f };
        SDL_RenderFillRect(renderer, &h);
        SDL_RenderFillRect(renderer, &v);
    }

    
    
    
    
}
