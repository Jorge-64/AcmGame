#ifndef WEAPON_H
#define WEAPON_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <cmath>
#include "mesh.h"

class Weapon
{
    public :
        Weapon();
        ~Weapon();
        void set_model(char *);
        void set_type(unsigned int index);
        void set_position(double x_val, double y_val, double z_val);
        void draw(float angle);
        void update(bool toggle);
        void activate();
        bool is_active();
    private :
        Mesh model;
        double red;
        double green;
        double blue;

        double rel_x;
        double rel_y;
        double rel_z;

        unsigned int value;
        unsigned int weapon_index;

        unsigned int attack_power;
        unsigned int attack_speed;
        double animation_speed;

        unsigned int knock_back;
        unsigned int adhesion;
        unsigned int recoil;

        unsigned int reboot_timer;

        double current_index;
        double max_index;
        bool free;
        bool active;
        GLUquadricObj *p;
};

#endif
