/*C3-1*/

//g1772011
//���V�X�e���w��3�N
//�Έ�Y��

#include <stdlib.h>
#include "GL/glut.h"
#include "GL/gl.h"
#include "GL/glu.h"
#include "myShape.h"
#include <stdio.h>
#define KEY_ESC 27

//static double time = 0;

void display(void)
{
	//time += 0.001;

	glClear(GL_COLOR_BUFFER_BIT);

	int i, num = 3;

	static double spd = 0;
	spd += 0.0000001;
	static double posy = 0;
	posy += spd;
//	printf("%lf, %lf\n", spd, posy);


	glPushMatrix();

	//�J���������P�b�g��Ǐ]
	gluLookAt(0, 30, 10,   0, posy , -20,   0, 1, 0);

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINES);/*�n�ʂ̃O���b�h*/
	for (i = -350; i < 360; i += 2) {
		glVertex3f(0.5 * (float)i, 0, -350.0);
		glVertex3f(0.5 * (float)i, 0, 350.0);
		glVertex3f(-150.0, 0, 2 * (float)i);
		glVertex3f(150.0, 0, 2 * (float)i);
	}

	glEnd();

	glTranslatef(0.0, 0 + posy, -20.0);
	glRotatef(posy * 10, 0, 1, 0);


	glPushMatrix();/*���W�n�̕ۑ�*/
	glTranslatef(0.0, 2.0, 0.0);
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	glutWireCone(1.0, 2.0, 12, 3);/*��[�̕`��*/
	glPopMatrix();/*���W�n�̕���*/

	glPushMatrix();/*���W�n�̕ۑ�*/
	glTranslatef(0.0, 1.0, 0.0);
	myWireCylinder(1.0, 2.0, 12); /*2�i�ڂ̕`��*/
	glPopMatrix();/*���W�n�̕���*/

	glPushMatrix();/*���W�n�̕ۑ�*/
	glTranslatef(0.0, -1.0, 0.0);
	myWireCylinder(1.0, 2.0, 12);/*1�i�ڂ̕`��*/
	glPopMatrix();/*���W�n�̕���*/


	glPushMatrix();/*���W�n�̕ۑ�*/
	glTranslatef(0.0, -2.4, 0.0);
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	glutWireCone(1.0 / 2, 2.0 / 2, 12, 3);/*��[�̕`��*/
	glPopMatrix();/*���W�n�̕���*/

	for (int i = 0; i < num; ++i)
	{
		glPushMatrix();
		glColor3f(1, 0, 0);

		glRotatef(i * 360.0 / num, 0, 1, 0);

		glTranslatef(1.5, -1, 0);


		glScalef(1, 2, 0.1);


		glutWireCube(1);

		glPopMatrix();
	}

	glColor3f(1, 1, 1);

	glPopMatrix();/*���W�n�̕���*/
	glFlush();
}
void myKbd(unsigned char key, int x, int y)
{
	if (key == KEY_ESC) exit(0);
}


void idle(void)/*�C�x���g���Ȃ����idle���˂Ɏ��s�����*/
{
	glutPostRedisplay();/*�f�B�X�v���C�R�[���o�b�N�o�b�N�֐�(display)�����s*/
}


void myInit(char *progname)
{
	int width = 500, height = 500;
	float aspect = (float)width / (float)height;

	glutInitWindowPosition(0, 0);
	glutInitWindowSize(width, height);
	glutInitDisplayMode(GLUT_RGBA);
	glutCreateWindow(progname);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glutKeyboardFunc(myKbd);

	glMatrixMode(GL_PROJECTION);
	/*���e�ϊ��s��X�^�b�N�𑀍�ΏۂƂ���*/
	glLoadIdentity();/*�s��X�^�b�N���N���A*/
	gluPerspective(30.0, aspect, 1.0, 200.0);
	glMatrixMode(GL_MODELVIEW);/*�􉽕ϊ��s��X�^�b�N�𑀍�Ώۂ���*/
}
int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	myInit(argv[0]);
	glutIdleFunc(idle);
	glutDisplayFunc(display);
	glutMainLoop();
	return(0);
}