#include <cmath>
#include "weapon.h"
//Jorge
//this is the weapon class implementation

Weapon::Weapon()
:model(Mesh()), red(.8), green(.8), blue(.3),
 rel_x(-1), rel_y(0), rel_z(0), value(0), weapon_index(0), attack_power(10), attack_speed(10), animation_speed(1),
 knock_back(0), adhesion(0), recoil(0), reboot_timer(10), current_index(0), max_index(10), free(false),
 active(false)
{
    p = gluNewQuadric();
}
Weapon::~Weapon()
{
    //gluDeleteQuadric(p);
}
void Weapon::set_model(char * file_name){
    model.load(file_name);
}
void Weapon::set_type(unsigned int index){
    weapon_index = index;
}
void Weapon::update(bool toggle){
    switch(weapon_index){
        case 0:
            if(active){
                current_index += .25;
                if(current_index >= max_index)
                    active = false;
            }
            else
            if(current_index > 0){
                current_index -= .25;
            }
            else
            if(toggle)
                active = true;
            draw(-100*current_index/max_index);
            break;
        case 1:
            if(active){
                current_index += .005;
                if(current_index >= max_index)
                    active = false;
            }
            else
            if(current_index > 0){
                current_index = 0;
            }
            else
            if(toggle)
                active = true;
            draw(180*current_index);
            break;
    }
}
void Weapon::draw(float angle){
    switch(weapon_index){
        case 0:
            glPushMatrix();
                glTranslatef(rel_x, rel_y, rel_z);
                glRotatef(angle, 0,0,1);
                model.draw();
            glPopMatrix();
            break;
        case 1:
            glPushMatrix();
                glTranslatef(rel_x, rel_y, rel_z);
                glRotatef(-angle, 0,0,1);
                model.draw();
            glPopMatrix();
            break;
    }
}
bool Weapon::is_active(){
    return active;
}
void Weapon::set_position(double x_val, double y_val, double z_val){
    rel_x = x_val;
    rel_y = y_val;
    rel_z = z_val;
}
