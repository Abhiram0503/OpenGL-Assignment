#include <gl/glut.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <cstdlib>
#include <ctime>
#include <thread>

#define MAX 100000

double array[MAX][2];

GLfloat redBallPositionY = 0.3;
GLfloat redBallDirection = -0.001;
GLfloat rotationAngle = 0.0;

GLfloat cx = 0.5f;
GLfloat cy = 0.5f;
GLfloat cz = 0.5f;

GLfloat sx = -0.5f;
GLfloat sy = 0.5f;
GLfloat sz = 0.5f;


GLfloat cox = 0.5f;
GLfloat coy = -0.5f;
GLfloat coz = 0.5f;


void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    glEnable(GL_LIGHTING);

    glEnable(GL_LIGHT0);
    GLfloat light1_position[] = { 0.0, 2.0, 0.0, 0.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, light1_position);


    GLfloat green[] = { 0, 1, 0, 1 };
    GLfloat black[] = { 0, 0, 0, 1 };

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, green);
    glMaterialfv(GL_FRONT, GL_SPECULAR, black);
    glMaterialfv(GL_FRONT, GL_SHININESS, black);


    //gluLookAt(1, 1, 2, 1, 1, 1, 1, 5, 2); //--- working

    //glPushMatrix();
    //glTranslatef( 1, 1, 1);
    glutWireSphere(1, 30, 30);
    //glPopMatrix();



    GLfloat red[] = { 1, 0, 0, 1 };
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, red);
    glPushMatrix();
    glTranslatef(cx, cy, cz);
    glutSolidSphere(0.3, 50, 50);
    glPopMatrix();

    GLfloat yellow[] = { 1, 1, 0, 1 };
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, yellow);
    glPushMatrix();
    glTranslatef(sx, sy, sz);
    glRotatef(0.0, 0.0, 1.0, 0.0);
    glutSolidCube(0.3);
    glPopMatrix();


    GLfloat ncol[] = { 0, 1, 1, 1 };
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, yellow);
    glPushMatrix();
    glTranslatef(cox, coy, coz);
    glRotatef(rotationAngle, 0.0, 1.0, 1.0);
    glutSolidCone(0.2, 0.5, 10, 10);
    glPopMatrix();


    //GLfloat green[] = { 0, 1, 0, 1 };
    //glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, green);
    //glPushMatrix();
    //glTranslatef(1, 1, 1);
    //glutWireSphere(1, 30, 30);
    //glPopMatrix();

    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2f(-0.9, 0.9); // Set position for text
    char text[50];
    sprintf_s(text, "cx: %.2f, cy: %.2f, cz: %.2f", cx, cy, cz);
    for (int i = 0; text[i] != '\0'; i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text[i]); // Render each character
    }


    glFlush();
}

GLfloat getRandomNumber(GLfloat a, GLfloat b) {
    GLfloat min;
    GLfloat max;
    if (a <= b) {
        min = a;
        max = b;
    }
    else {
        min = b;
        max = a;
    }

    // Initialize the random seed using the current time
    //std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Generate a random number between 0 and RAND_MAX
    GLfloat random_fraction = static_cast<GLfloat>(std::rand()) / RAND_MAX;

    // Scale and shift the random fraction to the desired range
    return min + random_fraction * (max - min);
}

void keys(unsigned char key, int x, int y) {
    if (key == 'w' && (sqrt(sx * sx + sy * sy + sz * sz)) <= 1.0) {
        if (sy + 0.2 < 0.6)
            sy = sy + 0.2;
    }

    if (key == 's' && (sqrt(sx * sx + sy * sy + sz * sz)) <= 1.0) {
        if (sy - 0.2 > -0.6)
            sy = sy - 0.2;
    }

    if (key == 'a' && (sqrt(sx * sx + sy * sy + sz * sz)) <= 1.0) {
        if (sx - 0.2 > -0.6)
            sx = sx - 0.2;
    }

    if (key == 'd' && (sqrt(sx * sx + sy * sy + sz * sz)) <= 1.0) {
        if (sx + 0.2 < 0.6)
            sx = sx + 0.2;
    }
}


void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        GLfloat tx = (x - 250) / 250.0;
        GLfloat ty = (250 - y) / 250.0;

        if (sqrt(tx * tx + ty * ty + coz * coz) < 1) {
            cox = (x - 250) / 250.0; // Map x-coordinate to OpenGL coordinates
            coy = (250 - y) / 250.0; // Map y-coordinate to OpenGL coordinates
        }
    }
}



void idle() {
    GLfloat cx1;
    GLfloat cy1;
    GLfloat cz1;





    cx1 = getRandomNumber(-0.7, 0.7);
    cy1 = getRandomNumber(-0.7, 0.7);
    cz1 = getRandomNumber(-0.7, 0.7);
    cx = cx1;
    cy = cy1;
    cz = cz1;


    rotationAngle += 1;
    glutPostRedisplay();

    std::this_thread::sleep_for(std::chrono::milliseconds(50));
}


int main(int argc, char* argv[])
{

    glutInit(&argc, argv);


    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);


    glutCreateWindow("My First OpenGL Window");


    glEnable(GL_DEPTH_TEST);


    glutDisplayFunc(display);

    glutKeyboardFunc(keys);

    glutIdleFunc(idle);

    glutMouseFunc(mouse);

    glutMainLoop();

    return 0;
}