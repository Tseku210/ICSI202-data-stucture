#include<GL/glut.h>
#include<stdio.h>
#include <windows.h>
#include<math.h>

float ver [1616][3];
float vt[1970][2];
float vn[1616][3];
int flat[1605][12];

int num_texture=-1;
int screen_width=640;
int screen_height=480;
int id;
int width = 600, height = 500;

double xRot = 0.0f;
double yRot = 0.0f;
double zRot = 0.0f;

void specialKey(int key, int x, int y)
{
    switch(key){
        case GLUT_KEY_UP:
            xRot+=10.0f;
            break;
        case GLUT_KEY_DOWN:
            xRot-=10.0f;
            break;
        case GLUT_KEY_LEFT:
            yRot+=10.0f;
            break;
        case GLUT_KEY_RIGHT:
            yRot-=10.0f;
            break;
    }
    glutPostRedisplay();
}

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();

    glRotatef(xRot,1.0f,0.0f,0.0f);
    glRotatef(yRot,0.0f,1.0f,0.0f);
    glRotatef(zRot,0.0f,0.0f,1.0f);
    glOrtho(-20,20,-20,20,20,-20);

    int i;
    int v = 0;
    int f = 0;
    int n = 0;
    int t = 0;
    char key[256];
    FILE *fin;
    fin = fopen("C:\\Users\\tseng\\Dropbox\\PC\\Downloads\\Character.obj", "r");
    if (fin == NULL)
        printf("\ncan't open input file\n");

    while(!feof(fin)){
        fscanf(fin,"%s", key);
        if(strcmp(key,"v") == 0){
            fscanf(fin,"%f",&ver[v][0]);
            fscanf(fin,"%f",&ver[v][1]);
            fscanf(fin,"%f",&ver[v][2]);
            v = v+1;

        }
        else if(strcmp(key,"vt") ==0 ) {
                fscanf(fin,"%f",&vt[t][0]);
                fscanf(fin,"%f",&vt[t][1]);
                t  = t + 1;
        }
        else if(strcmp(key,"vn") ==0 ){
                fscanf(fin,"%f%f%f",&vn[n][0], &vn[n][1], &vn[n][1]);
                n = n + 1;
        }
        else if(strcmp(key,"f")==0)
        {
            fscanf(fin,"%d",&flat[f][0]);
            fscanf(fin,"%d",&flat[f][1]);
            fscanf(fin,"%d",&flat[f][2]);

            fscanf(fin,"%d",&flat[f][3]);
            fscanf(fin,"%d",&flat[f][4]);
            fscanf(fin,"%d",&flat[f][5]);

            fscanf(fin,"%d",&flat[f][6]);
            fscanf(fin,"%d",&flat[f][7]);
            fscanf(fin,"%d",&flat[f][8]);

            fscanf(fin,"%d",&flat[f][9]);
            fscanf(fin,"%d",&flat[f][10]);
            fscanf(fin,"%d",&flat[f][11]);
            f = f+1;

        }

    }

    //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

    glPushMatrix();
        glRotatef(180,0,1,0);
    for (i = 0; i < 1605; ++i)
    {
        glBegin(GL_QUADS);
        glBindTexture(GL_TEXTURE_2D, id);

        glTexCoord2f(vt[flat[i][1]-1][0]+0.03, vt[flat[i][1]-1][1]);
        glNormal3fv(vn[flat[i][2]-1]);
        glVertex3fv(ver[flat[i][0]-1]);

        glTexCoord2f(vt[flat[i][4]-1][0]+.03, vt[flat[i][4]-1][1]);
        glNormal3fv(vn[flat[i][5]-1]);
        glVertex3fv(ver[flat[i][3]-1]);

        glTexCoord2f(vt[flat[i][7]-1][0]+.03, vt[flat[i][7]-1][1]);
        glNormal3fv(vn[flat[i][8]-1]);
        glVertex3fv(ver[flat[i][6]-1]);

        glTexCoord2f(vt[flat[i][10]-1][0]+.03, vt[flat[i][10]-1][1]);
        glNormal3fv(vn[flat[i][11]-1]);
        glVertex3fv(ver[flat[i][9]-1]);
        glEnd();
    }
    glPopMatrix();
    glutSwapBuffers();

}
int LoadBitmap(char *filename)
{
    int i, j=0;
    FILE *l_file;
    unsigned char *l_texture;
    BITMAPFILEHEADER fileheader;
    BITMAPINFOHEADER infoheader;
    RGBTRIPLE rgb;
    num_texture++;
    if( (l_file = fopen(filename, "rb"))==NULL) return (-1);

    fread(&fileheader, sizeof(fileheader), 1, l_file);

    fseek(l_file, sizeof(fileheader), SEEK_SET);
    fread(&infoheader, sizeof(infoheader), 1, l_file);

    l_texture = (BYTE *) malloc(infoheader.biWidth * infoheader.biHeight * 4);
    memset(l_texture, 0, infoheader.biWidth * infoheader.biHeight * 4);

    for (i=0; i < infoheader.biWidth*infoheader.biHeight; i++)
    {
            fread(&rgb, sizeof(rgb), 1, l_file);
            l_texture[j+0] = rgb.rgbtRed;
            l_texture[j+1] = rgb.rgbtGreen;
            l_texture[j+2] = rgb.rgbtBlue;
            l_texture[j+3] = 255;
            j += 4;
    }

    fclose(l_file);
    glBindTexture(GL_TEXTURE_2D, num_texture);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, infoheader.biWidth, infoheader.biHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, l_texture);
    gluBuild2DMipmaps(GL_TEXTURE_2D, 4, infoheader.biWidth, infoheader.biHeight, GL_RGBA, GL_UNSIGNED_BYTE, l_texture);
    free(l_texture);
    return (num_texture);
}

void myInit(void)
{
    glFrontFace(GL_CW);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_AUTO_NORMAL);
    glEnable(GL_NORMALIZE);
    glEnable(GL_DEPTH_TEST);
    glEndList();
    glShadeModel(GL_SMOOTH);
    glViewport(0,0,screen_width,screen_height);

    glLoadIdentity();
    gluPerspective(45.0f,(GLfloat)screen_width/(GLfloat)screen_height,1.0f,1000.0f);
    glEnable(GL_DEPTH_TEST);
    glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_TEXTURE_2D);

    id=LoadBitmap((char*)"C:\\Users\\tseng\\Dropbox\\PC\\Downloads\\cg-texture.bmp");

    if (id==-1)
    {
        MessageBox(NULL,"Image file: cg-texture.bmp not found", "Character", MB_OK | MB_ICONERROR);
        exit (0);
    }
}
    const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
    const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
    const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    const GLfloat light_position[] = { 10, 10, 10, 1.0};

    const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
    const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
    const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
    const GLfloat high_shininess[] = { 100.0f };

int main(int argc, char *argv[]){
    glutInit(&argc, argv);
    glutInitWindowSize(width,height);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Maya");
    myInit();
    glutDisplayFunc(display);
    glutSpecialFunc(specialKey);

    glClearColor(1,1,1,1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
    glutMainLoop();
    return EXIT_SUCCESS;
}
