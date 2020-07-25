#include <iostream>
#include "glew.h"
#include "freeglut.h"
#include "string"

using namespace std;

int ucakx = 240;int ucaky = 480;//Ucak x,y
int heli1x = rand() % 430; int heli1y = 30; int heli1yon = 0; int heli1hiz = rand() % 4;//1.helikopter x,y yon=0 sag hareket yon=1 sol hareket
int heli2x = rand() % 430; int heli2y = 130; int heli2yon = 1; int heli2hiz = rand() % 4;//2.helikopter x,y
int heli3x = rand() % 430; int heli3y = 230; int heli3yon = 0; int heli3hiz = rand() % 4;//3.helikopter x,y
int heli4x = rand() % 430; int heli4y = 330; int heli4yon = 1; int heli4hiz = rand() % 4;//4.helikopter x,y
bool heliper = true;
int puan = 0; int level = 0; int can = 3;
bool restart = true;
bool menu = true;

//helikopter random renkleri
double heli1r = (double)rand() / (RAND_MAX); double heli1g = (double)rand() / (RAND_MAX); double heli1b = (double)rand() / (RAND_MAX);
double heli2r = (double)rand() / (RAND_MAX); double heli2g = (double)rand() / (RAND_MAX); double heli2b = (double)rand() / (RAND_MAX);
double heli3r = (double)rand() / (RAND_MAX); double heli3g = (double)rand() / (RAND_MAX); double heli3b = (double)rand() / (RAND_MAX);
double heli4r = (double)rand() / (RAND_MAX); double heli4g = (double)rand() / (RAND_MAX); double heli4b = (double)rand() / (RAND_MAX);

void displayMenu()
{
	glColor3f(1, 0, 0);
	string basla = "Basla! - F1";
	glRasterPos2i(220, 300);
	for (int i = 0; i < basla.length();i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, basla[i]);
	}
}

void ucakKontrol(int helix, int heliy, int heliyon)
{
	if (ucaky <= 0)
	{
		ucakx = 240;
		ucaky = 480;
		puan += 10;
		level++;
	}

	//carpisma kontrolu
	if (heliyon == 0)
	{
		if (ucakx - 25 < helix + 50 &&
			ucakx - 25 + 50 > helix &&
			ucaky<heliy - 25 + 50 &&
			ucaky + 50>heliy - 25)
		{
			ucakx = 240;
			ucaky = 480;
			can = can - 1;
		}
	}
	else if (heliyon == 1)
	{
		if (ucakx - 25 < helix - 50 + 50 &&
			ucakx + 25 > helix - 50 &&
			ucaky<heliy - 25 + 50 &&
			ucaky + 50>heliy - 25)
		{
			ucakx = 240;
			ucaky = 480;
			can = can - 1;
		}
	}
	//Can bittiginde oyundan cikar
	if (can == 0)
	{
		restart = false;
	}

}
//ucak cizer
void ucakCiz(int x, int y) {

	glColor3f(0, 0, 1);
	glBegin(GL_QUADS);
	glVertex2i(x - 2, y);
	glVertex2i(x - 2, y + 50);
	glVertex2i(x + 2, y + 50);
	glVertex2i(x + 2, y);
	glVertex2i(x - 25, y + 10);
	glVertex2i(x + 25, y + 10);
	glVertex2i(x + 25, y + 14);
	glVertex2i(x - 25, y + 14);
	glVertex2i(x - 15, y + 36);
	glVertex2i(x + 15, y + 36);
	glVertex2i(x + 15, y + 40);
	glVertex2i(x - 15, y + 40);
	glEnd();
}

//ucagin klavyeden hareketlerini yapar ve ekran icinde olup olmadigini kontrol eder
void ucakHareketi(int key, int x, int y)
{
	if (key == GLUT_KEY_UP)ucaky = ucaky - 8; //yukariya gittiginde oyunu kazanacagi icin sonsuz gidebilmesine izin veriyoruz.
	if (key == GLUT_KEY_DOWN)if (ucaky <= 640)ucaky = ucaky + 8;
	if (key == GLUT_KEY_LEFT)if (ucakx - 25 >= 0)ucakx = ucakx - 8;
	if (key == GLUT_KEY_RIGHT)if (ucakx + 25 <= 480)ucakx = ucakx + 8;
	if (key == GLUT_KEY_F1)
	{
		menu = !menu;
		if (!restart) {
			restart = true;
			can = 3;
			ucakx = 240;
			ucaky = 480;
			puan = 0;
			level = 0;
		}
	}
	glutPostRedisplay();
}

//hareketli pervane cizimi saga giderken
void pervaneCiz(int x, int y)
{
	if (heliper)
	{
		glColor3f(0, 0, 0);
		glBegin(GL_LINES);
		glVertex2i(x + 11, y - 6);
		glVertex2i(x - 11, y - 6);
		glVertex2i(x, y - 12);
		glVertex2i(x, y - 1);//arka pervane 
		glVertex2i(x + 38, y - 10);
		glVertex2i(x + 38, y - 25);
		glVertex2i(x + 13, y - 20);
		glVertex2i(x + 63, y - 20);//ust pervane 
		glEnd();
	}
	else {
		glColor3f(0, 0, 0);
		glBegin(GL_LINES);
		glVertex2i(x + 10, y - 1);
		glVertex2i(x - 10, y - 11);
		glVertex2i(x - 10, y - 1);
		glVertex2i(x + 10, y - 11);//arka pervane 
		glVertex2i(x + 13, y - 15);
		glVertex2i(x + 63, y - 25);
		glVertex2i(x + 13, y - 25);
		glVertex2i(x + 63, y - 15);//ust pervane 
		glEnd();
	}
}

//hareketli pervane cizimi sola giderken
void tersPervaneCiz(int x, int y)
{
	if (heliper)
	{
		glColor3f(0, 0, 0);
		glBegin(GL_LINES);
		glVertex2i(x - 11, y - 6);
		glVertex2i(x + 11, y - 6);
		glVertex2i(x, y - 12);
		glVertex2i(x, y - 1);//arka pervane 
		glVertex2i(x - 38, y - 10);
		glVertex2i(x - 38, y - 25);
		glVertex2i(x - 13, y - 20);
		glVertex2i(x - 63, y - 20);//ust pervane 
		glEnd();
	}
	else
	{
		glColor3f(0.5, 0.5, 0.5);
		glBegin(GL_LINES);
		glVertex2i(x - 10, y - 1);
		glVertex2i(x + 10, y - 11);
		glVertex2i(x + 10, y - 1);
		glVertex2i(x - 10, y - 11);//arka pervane 
		glVertex2i(x - 13, y - 15);
		glVertex2i(x - 63, y - 25);
		glVertex2i(x - 13, y - 25);
		glVertex2i(x - 63, y - 15);//ust pervane 
		glEnd();
	}

}

//helikopter cizer
void helikopterCiz(int x, int y, double r, double g, double b)
{

	glColor3f(r, g, b);//helikopter rengi
	glBegin(GL_QUADS);
	glVertex2i(x, y + 5);
	glVertex2i(x, y - 5);
	glVertex2i(x + 25, y - 5);
	glVertex2i(x + 25, y + 5);//==kuyruk
	glVertex2i(x + 25, y + 15);
	glVertex2i(x + 50, y + 15);
	glVertex2i(x + 50, y - 15);
	glVertex2i(x + 25, y - 15);//==kafa
	glVertex2i(x + 35, y - 15);
	glVertex2i(x + 40, y - 15);
	glVertex2i(x + 40, y - 20);
	glVertex2i(x + 35, y - 20);
	glColor3f(0.5, 0.5, 0.5);//cam ve ayak rengi
	glVertex2i(x + 37, y);
	glVertex2i(x + 37, y - 12);
	glVertex2i(x + 47, y - 12);
	glVertex2i(x + 47, y);//cam
	glVertex2i(x + 31, y + 15);
	glVertex2i(x + 31, y + 25);
	glVertex2i(x + 33, y + 25);
	glVertex2i(x + 33, y + 15);//ayak
	glVertex2i(x + 44, y + 15);
	glVertex2i(x + 44, y + 25);
	glVertex2i(x + 46, y + 25);
	glVertex2i(x + 46, y + 15);//ayak
	glVertex2i(x + 25, y + 23);
	glVertex2i(x + 25, y + 25);
	glVertex2i(x + 50, y + 25);
	glVertex2i(x + 50, y + 23);//ayak orta cizgi
	glEnd();
}

//ters helikopter cizer
void tersHelikopterCiz(int x, int y, double r, double g, double b)
{

	glColor3f(r, g, b);
	glBegin(GL_QUADS);
	glVertex2i(x, y + 5);
	glVertex2i(x, y - 5);
	glVertex2i(x - 25, y - 5);
	glVertex2i(x - 25, y + 5);//==kuyruk
	glVertex2i(x - 25, y + 15);
	glVertex2i(x - 50, y + 15);
	glVertex2i(x - 50, y - 15);
	glVertex2i(x - 25, y - 15);//==kafa
	glVertex2i(x - 35, y - 15);
	glVertex2i(x - 40, y - 15);
	glVertex2i(x - 40, y - 20);
	glVertex2i(x - 35, y - 20);
	glColor3f(0.5, 0.5, 0.5);//cam ve ayak rengi
	glVertex2i(x - 37, y);
	glVertex2i(x - 37, y - 12);
	glVertex2i(x - 47, y - 12);
	glVertex2i(x - 47, y);//cam
	glVertex2i(x - 31, y + 15);
	glVertex2i(x - 31, y + 25);
	glVertex2i(x - 33, y + 25);
	glVertex2i(x - 33, y + 15);//ayak
	glVertex2i(x - 44, y + 15);
	glVertex2i(x - 44, y + 25);
	glVertex2i(x - 46, y + 25);
	glVertex2i(x - 46, y + 15);//ayak
	glVertex2i(x - 25, y + 23);
	glVertex2i(x - 25, y + 25);
	glVertex2i(x - 50, y + 25);
	glVertex2i(x - 50, y + 23);//ayak orta cizgi
	glEnd();
}

//puan ve kalan hak
void puanYaz()
{
	string yazi = "Puan : " + to_string(puan) + " Kalan Hak : " + to_string(can);
	glRasterPos2i(280, 20);
	for (int i = 0;i < yazi.length();i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, yazi[i]);
	}
	glEnd();
}

//yeniden baslamak icin enter basin yazar
void restartyaz()
{
	string yazi = "Tekrar Oyna - F1";
	glRasterPos2i(140, 320);
	for (int i = 0;i < yazi.length();i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, yazi[i]);
	}
	glEnd();
}

//cizimleri siralar ve surekli cizer
void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	if(!menu)
	{
		if (restart)
		{
			//helikopter yonune gore helikopteri cizer 
			if (heli1yon == 0)
			{
				helikopterCiz(heli1x, heli1y, heli1r, heli1g, heli1b);
				pervaneCiz(heli1x, heli1y);
			}
			else if (heli1yon == 1)
			{
				tersHelikopterCiz(heli1x, heli1y, heli1r, heli1g, heli1b);
				tersPervaneCiz(heli1x, heli1y);
			}

			if (heli2yon == 0)
			{
				helikopterCiz(heli2x, heli2y, heli2r, heli2g, heli2b);
				pervaneCiz(heli2x, heli2y);
			}
			else if (heli2yon == 1)
			{
				tersHelikopterCiz(heli2x, heli2y, heli2r, heli2g, heli2b);
				tersPervaneCiz(heli2x, heli2y);
			}

			if (heli3yon == 0)
			{
				helikopterCiz(heli3x, heli3y, heli3r, heli3g, heli3b);
				pervaneCiz(heli3x, heli3y);
			}
			else if (heli3yon == 1)
			{
				tersHelikopterCiz(heli3x, heli3y, heli3r, heli3g, heli3b);
				tersPervaneCiz(heli3x, heli3y);
			}

			if (heli4yon == 0)
			{
				helikopterCiz(heli4x, heli4y, heli4r, heli4g, heli4b);
				pervaneCiz(heli4x, heli4y);
			}
			else if (heli4yon == 1)
			{
				tersHelikopterCiz(heli4x, heli4y, heli4r, heli4g, heli4b);
				tersPervaneCiz(heli4x, heli4y);
			}

			//ucak cizer	
			ucakCiz(ucakx, ucaky);
			ucakKontrol(heli1x, heli1y, heli1yon);
			ucakKontrol(heli2x, heli2y, heli2yon);
			ucakKontrol(heli3x, heli3y, heli3yon);
			ucakKontrol(heli4x, heli4y, heli4yon);
			puanYaz();
	}
	else if (!restart)
	{
		restartyaz();
	}
}
	else
	{
		displayMenu();
	}

	glFlush();
	glutSwapBuffers();
}

//programin akici calismasini saglar 
void timer(int)
{
	heliper = !heliper;
	//helikopter 1 hareket
	if (heli1yon == 0)
	{
		heli1x = heli1x + heli1hiz + 1 + level;
		if (heli1x + 50 >= 480) {
			heli1x += 50;
			heli1yon = 1;
		}
	}
	else if (heli1yon == 1)
	{
		heli1x = heli1x - heli1hiz - 1 - level;
		if (heli1x - 50 <= 0) {
			heli1x -= 50;
			heli1yon = 0;
		}
	}
	//helikopter 2 hareket
	if (heli2yon == 0)
	{
		heli2x = heli2x + heli2hiz + 1 + level;
		if (heli2x + 50 >= 480) {
			heli2x += 50;
			heli2yon = 1;
		}
	}
	else if (heli2yon == 1)
	{
		heli2x = heli2x - heli2hiz - 1 - level;
		if (heli2x - 50 <= 0) {
			heli2x -= 50;
			heli2yon = 0;
		}
	}
	//helikopter 3 hareket
	if (heli3yon == 0)
	{
		heli3x = heli3x + heli3hiz + 1 + level;
		if (heli3x + 50 >= 480) {
			heli3x += 50;
			heli3yon = 1;
		}
	}
	else if (heli3yon == 1)
	{
		heli3x = heli3x - heli3hiz - 1 - level;
		if (heli3x - 50 <= 0) {
			heli3x -= 50;
			heli3yon = 0;
		}
	}
	//helikopter 4 hareket
	if (heli4yon == 0)
	{
		heli4x = heli4x + heli4hiz + 1 + level;
		if (heli4x + 50 >= 480) {
			heli4x += 50;
			heli4yon = 1;
		}
	}
	else if (heli4yon == 1)
	{
		heli4x = heli4x - heli4hiz - 1 - level;
		if (heli4x - 50 <= 0) {
			heli4x -= 50;
			heli4yon = 0;
		}
	}

	glutPostRedisplay();
	glutTimerFunc(1000.0 / 60.0, timer, 0);
}

//main
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(480, 640);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("2D_PlaneGame");
	glClearColor(1, 1, 1, 0);
	gluOrtho2D(0, 480, 640, 0);
	glutDisplayFunc(display);
	glutTimerFunc(1000.0 / 60.0, timer, 0);
	glutSpecialFunc(ucakHareketi);

	glutMainLoop();
	return 0;
}
