#pragma once

namespace Tmpl8
{

    class Game_Object
    {
    public:
        virtual void tick() = 0;
        virtual void draw(Surface* screen) = 0;

        vec2 position;
        int current_frame;
        Sprite* rocket_sprite;
    };

} // namespace Tmpl8