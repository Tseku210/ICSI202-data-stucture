#ifdef _APPLE_
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <math.h>
#include <stdlib.h>
#include <windows.h>

int n = 3;

void keyboard_color(unsigned char key, int x, int y) {
    switch(key) {
    case 'R': case 'r':
        glColor3f(1.0, 0, 0);
        break;
    case 'G': case 'g':
        glColor3f(0, 1.0, 0);
        break;
    case 'B': case 'b':
        glColor3f(0, 0, 1.0);
        break;
    }
    glutPostRedisplay();
}

void change_shape(int key, int x, int y) {
    if (key == GLUT_KEY_UP) {
        n++;
    } else if (key == GLUT_KEY_DOWN) {
        if (n > 3) {
            n--;
        }
    }
    glutPostRedisplay();
}

static void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    float r = 0.5;
    const float PI = 3.14159f;
    int i;
    glBegin(GL_LINE_LOOP);
    for (i = 0; i < n; i++) {
        float theta = (2*PI*i)/n;
        glVertex2f(r*cos(theta), r*sin(theta));
    }
    glEnd();
    glFlush();
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(10, 10);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutCreateWindow("Shapes");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard_color);
    glutSpecialFunc(change_shape);
    glutMainLoop();

    return EXIT_SUCCESS;
}
