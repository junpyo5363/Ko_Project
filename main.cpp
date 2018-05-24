#include <iostream>
#include <time.h>
#include <vector>

#include "grid.h"
#include "player.h"
#include "zombie.h"
#include "user.h"
#include "floodfill.h"

#define WIDTH 600		// window's width
#define HEIGHT 600		// window's height

//
#define FRAME 30
clock_t start = clock();
clock_t end;
bool FPScontrol(long frame) {
	end = clock();
	if (end - start > 1000 / frame) {
		start = end;
		return true;
	}
	else return false;
}

std::vector<Grid**> maps;
std::vector<User> users;
std::vector<Zombie> zombies;

void defeat(User user) {
	exit(0);
}

void init() {
	//make a maps
	maps.push_back(new Grid*[MAP::ROW]);
	for (std::vector<Grid**>::size_type i = 0; i < maps.size(); ++i) {
		for (int j = 0; j < MAP::ROW; ++j)
			maps[i][j] = new Grid[MAP::COL];
	}
	//fit console size into map
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, MAP::ROW, 0, MAP::COL);

	//initialize random function
	srand(time(NULL));
	//add users & zombies
	User user1(MAP::ROW / 2, MAP::COL / 2, 1.0f, 0.0f, 0.0f);
	user1.setTerritorycolor(1.0f, 199.0 / 255.0, 87.0 / 255.0);
	users.push_back(user1);
	Zombie zombie1;
	zombies.push_back(zombie1);
	//default setting
	maps[0][MAP::ROW / 2][MAP::COL / 2].setState(STATE::ON);

}

void processSpecialKeys(int key, int x, int y) {
	for (std::vector<User>::size_type i = 0; i < users.size(); ++i) {
		if (key == users[i][DIRECTION::RIGHT].key && users[i][DIRECTION::RIGHT].isSpecialKey == true)
			users[i].setDirection(DIRECTION::RIGHT);
		if (key == users[i][DIRECTION::LEFT].key && users[i][DIRECTION::LEFT].isSpecialKey == true)
			users[i].setDirection(DIRECTION::LEFT);
		if (key == users[i][DIRECTION::DOWN].key && users[i][DIRECTION::DOWN].isSpecialKey == true)
			users[i].setDirection(DIRECTION::DOWN);
		if (key == users[i][DIRECTION::UP].key && users[i][DIRECTION::UP].isSpecialKey == true)
			users[i].setDirection(DIRECTION::UP);
		if (key == users[i][DIRECTION::STOP].key && users[i][DIRECTION::STOP].isSpecialKey == true)
			users[i].setDirection(DIRECTION::STOP);
	}
}

void idle() {
	if (!FPScontrol(FRAME)) return;
	zombies[0].move();
	for (std::vector<User>::size_type i = 0; i < users.size(); ++i) {
		//move
		switch (users[i].getDirection()) {
		case DIRECTION::RIGHT:
			if (users[i].getX() < MAP::ROW - 2)
				users[i].setPos(users[i].getX() + 1, users[i].getY());
			break;
		case DIRECTION::LEFT:
			if (users[i].getX() > 1)
				users[i].setPos(users[i].getX() - 1, users[i].getY());
			break;
		case DIRECTION::DOWN:
			if (users[i].getY() > 1)
				users[i].setPos(users[i].getX(), users[i].getY() - 1);
			break;
		case DIRECTION::UP:
			if (users[i].getY() < MAP::COL - 2)
				users[i].setPos(users[i].getX(), users[i].getY() + 1);
			break;
		case DIRECTION::STOP:
			break;
		default:
			break;
		}
		//update state of maps
		int x = static_cast<int>(users[i].getX());
		int y = static_cast<int>(users[i].getY());
		if (users[i].getIsmaking() == true) {
			if (maps[i][x][y].getState() == STATE::OFF) {
				maps[i][x][y].setState(STATE::ING);
			}
			else if (maps[i][x][y].getState() == STATE::ON) {
				users[i].setIsmaking(false);
				FloodFill(maps[i], users[i]);
			}
			else {
				defeat(users[i]);
			}
		}
		else {
			if (maps[i][x][y].getState() == STATE::OFF) {
				users[i].setIsmaking(true);
				maps[i][x][y].setState(STATE::ING);
			}
		}
		//check
		std::cout << users[i].getIsmaking() << std::endl;
		for (int row = MAP::ROW * 3 / 4; row > MAP::ROW / 4; --row) {
			for (int col = MAP::COL / 4 ; col < MAP::COL * 3 / 4; ++col) {
				std::cout << maps[i][col][row].getState() << ' ';
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
		//
		//defeat by zombie
		for (std::vector<Zombie>::size_type j = 0; j < users.size(); ++j) {
			x = static_cast<int>(zombies[j].getX());
			y = static_cast<int>(zombies[j].getY());
			if (maps[i][x][y].getState() == STATE::ING) defeat(users[i]);
		}
	}

	glutPostRedisplay();
}

void renderScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//make a barrier
	glColor3f(0.31f, 0.31f, 0.31f);//Gray
	glBegin(GL_QUADS);
	glVertex2f(0, 0); glVertex2f(0, MAP::COL); glVertex2f(1, MAP::COL); glVertex2f(1, 0);
	glVertex2f(0, 0); glVertex2f(0, 1); glVertex2f(MAP::ROW, 1); glVertex2f(MAP::ROW, 0);
	glVertex2f(MAP::ROW - 1, 0); glVertex2f(MAP::ROW - 1, MAP::COL); glVertex2f(MAP::ROW, MAP::COL); glVertex2f(MAP::ROW, 0);
	glVertex2f(0, MAP::COL - 1); glVertex2f(0, MAP::COL); glVertex2f(MAP::ROW, MAP::COL); glVertex2f(MAP::ROW, MAP::COL - 1);
	glEnd();
	//draw territories
	for (std::vector<User>::size_type i = 0; i < users.size(); ++i) {
		int x = static_cast<int>(users[i].getX());
		int y = static_cast<int>(users[i].getY());
		//draw
		glColor3f(users[i].getTR(), users[i].getTG(), users[i].getTB());
		glBegin(GL_QUADS);
		for (int row = 0; row < MAP::ROW; ++row) {
			for (int col = 0; col < MAP::COL; ++col) {
				//ING
				if (maps[i][row][col].getState() == STATE::ING) {
					glVertex2f(row, col + SIZE / 2.0);
					glVertex2f(row + SIZE / 2.0, col + SIZE);
					glVertex2f(row + SIZE, col + SIZE / 2.0);
					glVertex2f(row + SIZE / 2.0, col);
				}
				//ON
				else if (maps[i][row][col].getState() == STATE::ON) {
					glVertex2f(row, col);
					glVertex2f(row, col + SIZE);
					glVertex2f(row + SIZE, col + SIZE);
					glVertex2f(row + SIZE, col);
				}
			}
		}
		glEnd();
	}
	//draw players
	zombies[0].draw();
	for (std::vector<User>::size_type i = 0; i < users.size(); ++i) {
		users[i].draw();
	}
	glutSwapBuffers();
}

void main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(650, 300);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Drawing Square & Equilateral Triangle");
	init();

	glutDisplayFunc(renderScene);
	glutSpecialFunc(processSpecialKeys);
	glutIdleFunc(idle);

	glutMainLoop();
}
