#include <GL/glut.h>
#include "engine.h"
#include <map>
#include <iostream>

Eigen::Vector3f cam_pos(0,0,0);
const float cam_speed =0.1;
std::map<unsigned char, bool> keys_pressed;

void render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    glOrtho(cam_pos[0]-10,cam_pos[0]+10,cam_pos[1]-10,cam_pos[1]+10,cam_pos[2]+0, cam_pos[2]+20);

    engine::get_instance()->draw();
    glutSwapBuffers();
}

void idle_event()
{
    glutPostRedisplay();
}

void mouse_event(int button, int state, int x, int y)
{
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        engine::get_instance()->mouse_click(x,y);
    }
}

void keyboard_event(unsigned char key, int x, int y)
{
    keys_pressed[key]=true;
}

void keyboard_up_event(unsigned char key, int x, int y)
{
    keys_pressed[key]=false;
}

void update_event(int ms)
{
    if(keys_pressed['w'])
        cam_pos[1]+= cam_speed;

    if(keys_pressed['s'])
        cam_pos[1]-= cam_speed;

    if(keys_pressed['a'])
        cam_pos[0]-= cam_speed;

    if(keys_pressed['d'])
        cam_pos[0]+= cam_speed;


    engine::get_instance()->keyboard_event(keys_pressed);

    glutPostRedisplay();

    glutTimerFunc(ms, update_event, ms);
}

int main(int argc, char ** argv)
{
    engine::get_instance()->initialize();

    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutInitDisplayMode(GLUT_RGBA | GLUT_ALPHA | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("kalman_filter_pos");
    glClearColor(1,1,1,0);
    glEnable(GL_POINT_SMOOTH);

    glutDisplayFunc(render);
    glutKeyboardFunc(keyboard_event);
    glutKeyboardUpFunc(keyboard_up_event);
    glutMouseFunc(mouse_event);
    glutTimerFunc(33, update_event, 33);
    glutIdleFunc(idle_event);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);


    glutIgnoreKeyRepeat(true);

    glutMainLoop();

    return 0;
}
