//ACM GameDev Spring 2012

#include "application.h"

#include <iostream>
#include <cassert>

using namespace std;

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "lib/input.h"
#define PI 3.14159265358979323846264338328

void draw_terrain();

application::application()
: solid(true)
{}

application::~application()
{}

// triggered once after the OpenGL context is initialized
void application::init_event()
{
    //cout << "CAMERA CONTROLS: \n  LMB: Rotate \n  MMB: Pan \n  LMB: Dolly" << endl;
    //cout << "KEYBOARD CONTROLS: \n  '=': Toggle wireframe mode" << endl;
    cout << "CONTROLS:\n WASD: move \n QE: open doors \n F1: quit" << endl;

    const GLfloat ambient[] = { 0.15, 0.15, 0.15, 1.0 };
    const GLfloat diffuse[] = { 0.6, 0.6, 0.6, 1.0 };
    const GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };

    // enable a light
    glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, specular);
    glEnable(GL_LIGHT1);

    // enable depth-testing, colored materials, and lighting
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    // normalize normals so lighting calculations are correct
    // when using GLUT primitives
    glEnable(GL_NORMALIZE);

    // enable smooth shading
    glShadeModel(GL_SMOOTH);

    // set the cameras default coordinates
    camera.set_distance(30);//originally 20
    camera.set_elevation(30);
    camera.set_twist(270);

    t.reset();
    //
    Vehicle car_1(true,0,2.5,-3);
    //Vehicle car_2(false,0,2.5,3);
    vehicles.push_back(car_1);
    //vehicles.push_back(car_2);
}
// triggered each time the application needs to redraw
void application::draw_event()
{
    Input::nextFrame();
    if(Input::down(Key::quit)) exit(0);

    // apply our camera transformation
    camera.apply_gl_transform();

    // set the position of the light
    const GLfloat light_pos1[] = { 0.0, 10.0, 0.0, 1 };
    glLightfv(GL_LIGHT1, GL_POSITION, light_pos1);

    // draws the terrain and frame at the origin
    draw_terrain();

    //focus camera to the vehicle
    camera.set_focal_point(vehicles[0].x_pos + 3.2 * cos(vehicles[0].direction * PI / 180.0),vehicles[0].y_pos + 2,vehicles[0].z_pos + 3.2 * -sin(vehicles[0].direction * PI / 180.0));

    //use the mouse to rotate the camera
    //camera.add_twist(Input::mouseX()*Input::getMouseSensitivity());
    //camera.add_elevation(Input::mouseY()*Input::getMouseSensitivity());

    camera.add_twist(vehicles[0].direction + vehicles[0].turn);
    camera.add_distance(vehicles[0].speed);

    for(unsigned int i = 0; i < vehicles.size(); ++i){
        if(vehicles[i].use_keys)
            vehicles[i].draw(t.elapsed()*180, Input::down(Key::moveForward),
                                              Input::down(Key::moveBackward),
                                              Input::down(Key::turnLeft),
                                              Input::down(Key::turnRight),
                                              Input::pressed(Key::leftDoor),
                                              Input::pressed(Key::rightDoor));
        else
            vehicles[i].draw(t.elapsed()*180, Input::down(Key::car2moveForward),
                                              Input::down(Key::car2moveBackward),
                                              Input::down(Key::car2turnLeft),
                                              Input::down(Key::car2turnRight),
                                              Input::pressed(Key::car2leftDoor),
                                              Input::pressed(Key::car2rightDoor));
    }
}

void draw_terrain()
{
    glDisable(GL_LIGHTING);
    glLineWidth(2.0);

    //
    // Draws the coordinate frame at origin
    //
    glPushMatrix();
    glScalef(1, 1, 1);
    glBegin(GL_LINES);

    // x-axis
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(1.0, 0.0, 0.0);

    // y-axis
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 1.0, 0.0);

    // z-axis
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 1.0);
    glEnd();
    glPopMatrix();

    //
    // Draws a grid along the x-z plane
    //
    glLineWidth(1.0);
    glColor3f(.20, .20, .20);
    glBegin(GL_LINES);

    int ncells = 250;
    int ncells2 = ncells/2;

    for (int i= 0; i <= ncells; i++)
    {
        int k = -ncells2;
        k +=i;
        glVertex3f(ncells2,0,k);
        glVertex3f(-ncells2,0,k);
        glVertex3f(k,0,ncells2);
        glVertex3f(k,0,-ncells2);
    }
    glEnd();
    glEnable(GL_LIGHTING);
}
