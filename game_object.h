#pragma once

namespace Tmpl8
{

    class Game_Object
    {
    public:
        Game_Object(vec2 position, vec2 direction, float collision_radius, allignments allignment, Sprite* rocket_sprite);
        ~Game_Object();

        void tick();
        void draw(Surface* screen);

        bool intersects(vec2 position_other, float radius_other) const;

        vec2 position;
        vec2 speed;

        float collision_radius;

        bool active;

        allignments allignment;

        int current_frame;
        Sprite* rocket_sprite;
    };

} // namespace Tmpl8