/*C3-1*/

//g1772011
//情報システム学科3年
//石井雄太

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

	//カメラがロケットを追従
	gluLookAt(0, 30, 10,   0, posy , -20,   0, 1, 0);

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINES);/*地面のグリッド*/
	for (i = -350; i < 360; i += 2) {
		glVertex3f(0.5 * (float)i, 0, -350.0);
		glVertex3f(0.5 * (float)i, 0, 350.0);
		glVertex3f(-150.0, 0, 2 * (float)i);
		glVertex3f(150.0, 0, 2 * (float)i);
	}

	glEnd();

	glTranslatef(0.0, 0 + posy, -20.0);
	glRotatef(posy * 10, 0, 1, 0);


	glPushMatrix();/*座標系の保存*/
	glTranslatef(0.0, 2.0, 0.0);
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	glutWireCone(1.0, 2.0, 12, 3);/*先端の描画*/
	glPopMatrix();/*座標系の復元*/

	glPushMatrix();/*座標系の保存*/
	glTranslatef(0.0, 1.0, 0.0);
	myWireCylinder(1.0, 2.0, 12); /*2段目の描画*/
	glPopMatrix();/*座標系の復元*/

	glPushMatrix();/*座標系の保存*/
	glTranslatef(0.0, -1.0, 0.0);
	myWireCylinder(1.0, 2.0, 12);/*1段目の描画*/
	glPopMatrix();/*座標系の復元*/


	glPushMatrix();/*座標系の保存*/
	glTranslatef(0.0, -2.4, 0.0);
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	glutWireCone(1.0 / 2, 2.0 / 2, 12, 3);/*先端の描画*/
	glPopMatrix();/*座標系の復元*/

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

	glPopMatrix();/*座標系の復元*/
	glFlush();
}
void myKbd(unsigned char key, int x, int y)
{
	if (key == KEY_ESC) exit(0);
}


void idle(void)/*イベントがなければidleがつねに実行される*/
{
	glutPostRedisplay();/*ディスプレイコールバックバック関数(display)を実行*/
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
	/*投影変換行列スタックを操作対象とする*/
	glLoadIdentity();/*行列スタックをクリア*/
	gluPerspective(30.0, aspect, 1.0, 200.0);
	glMatrixMode(GL_MODELVIEW);/*幾何変換行列スタックを操作対象する*/
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