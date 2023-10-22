#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
float x,y;
int W,H, n = 6;
static void display(void){
    float r, theta;
    const float pi = 3.14159f;
    int i;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    for(int k=0; k < 5;k++){
        for(int f = 0;f < 4;f++){
            r = 0.02;
            glViewport(W/5*k,H/4*f,W/5,H/4);
            for(int j = 0; j < 50;j++){
            glBegin(GL_LINE_LOOP);
                for(i = 0;i<n;i++){
                    theta = (2*pi*i)/n;
                    if((f%2==0 && k%2==0) || (k%2!=0 && f%2!=0)){
                        glVertex2f(r*cos(theta-j), r*sin(theta-j));
                    }
                    else glVertex2f(r*cos(theta+j), r*sin(theta+j));
                }
                glEnd();
                r+=0.008;
                glFlush();
            }
        }
    }

}

static void DisplaySinex(void) {
    float degtorads, x;
    int i;
    degtorads = 3.14159/180.0;
    glClear(GL_COLOR_BUFFER_BIT);
    for(i = 0; i < 5; i++){
        glViewport(rand() % 100, rand() % 50, 100, 50);
        glBegin(GL_LINE_STRIP);
        for(x = 0.0; x <= 360.0; x += 1.0){
            glColor3f(1.0f, (1.0-(float) x / 360.0), 0.0f);
            glVertex2f(x, sin(x*degtorads));
        }
        glEnd();
    }
    glFlush();
}

static void resize(GLsizei w, GLsizei h){
    W=w;
    H=h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-0.25,0.25 ,-0.25, 0.25, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(W,H);
    glClear(GL_COLOR_BUFFER_BIT);
    glutCreateWindow("Pattern");

    glutDisplayFunc(DisplaySinex);
    glutReshapeFunc(resize);
    glClearColor(0,0,0,1);
    glutMainLoop();
    return EXIT_SUCCESS;
}
