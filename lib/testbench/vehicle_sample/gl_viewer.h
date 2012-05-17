#ifndef GL_VIEWER_H
#define GL_VIEWER_H

#include <GL/glut.h>

#include "gl_camera.h"

class gl_viewer
{
    public:
        gl_viewer();
        virtual ~gl_viewer();

        enum mouse_button
        {
            LEFT_BUTTON = GLUT_LEFT_BUTTON,
            MIDDLE_BUTTON = GLUT_MIDDLE_BUTTON,
            RIGHT_BUTTON = GLUT_RIGHT_BUTTON
        };

        enum mouse_button_state
        {
            BUTTON_UP = GLUT_UP, // button is being released
            BUTTON_DOWN = GLUT_DOWN // button is being pressed
        };

        virtual void init_event() {}
        virtual void draw_event() {}
        virtual void keyboard_event(unsigned char key, int x, int y) {}
        virtual void keyboard_up_event(unsigned char key, int x, int y) {}
        virtual void mouse_click_event(mouse_button button, mouse_button_state button_state, int x, int y) {}
        virtual void mouse_move_event(int x, int y) {}

        // Call before run. Initializes Glut. Glut is a OpenGL helper
        // library designed to allow easy GL window creation on all
        // of the various operating system.

        void init(int argc, char *argv[], int width, int height);


        // Begins the main loop. At this point execution is controlled by
        // glut.
        void run();

    protected:
        // window width & height
        int width, height;

        bool first_click;
        int mouse_last_x, mouse_last_y;
        int mode;
        int delta_x_total, delta_y_total;
        int num_motion_calls_thus_far;
        gl_camera camera;

    private:
        enum CAMERA_STATE { CAM_DOLLY, CAM_ROTATE, CAM_PAN };

        static void glut_display_event_wrapper();
        static void glut_mouse_click_event_wrapper(
            int button, int state, int x, int y
            );
        static void glut_mouse_move_event_wrapper(
            int x, int y
            );
        static void glut_reshape_event_wrapper(int width, int height);

        static gl_viewer* singleton;
};

#endif
