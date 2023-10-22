/*
 * GLUT Shapes Demo Updated
 */





#ifdef __APPLE__
#include <GLUT/glut.h>
#include <window.h>
#else
#include <GL/glut.h>
#endif




#include <stdlib.h>




/* GLUT callback Handlers */




static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3d(1,0,0);




    glPointSize(5.0);
    glBegin(GL_POINTS);
    glVertex2f(0.5, 0.0);
    glVertex2f(0.0,0.5);
    glVertex2f(-0.5, 0.0);
    glEnd();




    glFlush();
}




/* Program entry point */




int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutCreateWindow("GLUT Shapes");
    glutDisplayFunc(display);
    glClearColor(0,0,0,1);
    glutMainLoop();




    return EXIT_SUCCESS;
}
