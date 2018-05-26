#include <iostream>
#include <time.h>
#include "grid.h"
#include "player.h"
#include "zombie.h"
#include "user.h"
#include "floodfill.h"
#include "Square.h"
#include "BUTTON.h"
#include <string>
#define WIDTH 840		// window's width
#define HEIGHT 980		// window's height
#define FRAME 20
#define FONT 	GLUT_BITMAP_TIMES_ROMAN_24
#define INTERFACE 0
#define EASY 1
#define NORMAL 2
#define HARD 3
#define LOCATION(X) (((X)+(1))*(MAP::ROW/2))
#define RSIZE(X) ((X)*(MAP::ROW))
#define WINRATE 70
clock_t start = clock();
clock_t end;
int gameState = 0;
int currentstate=0;
int difficulty = 0;
int player = 2;
std::vector<Grid**> maps;
std::vector<User> users;
std::vector<Zombie> zombies;
std::vector<Square>squares;
std::vector<BUTTON>buttons;
std::vector<double> scores;
bool FPScontrol(long frame) {
	end = clock();
	if (end - start > 1000 / frame) {
		start = end;		
		return true;
	}
	else return false;
}
void draw_string(void *font, std::string str, float x, float y) {
	glRasterPos2f(x, y);
	for (int i = 0; i <str.size(); i++)
		glutBitmapCharacter(font, str[i]);
}
double calculate_rate(Grid** map) {
	double on_num = 0;
	for (int i = 1; i < MAP::ROW - 1; ++i) {
		for (int j = 1; j < MAP::COL - 1; ++j) {
			if (map[i][j].getState() == STATE::ON)  on_num += 1;
		}
	}
	return on_num / ((MAP::ROW - 2) * (MAP::COL - 2)) * 100;
}

void defeat(User user) {
	exit(0);
}
void win(User user) {
	std::cout << "WIN" << std::endl;
	abort();
}

void init() {
	// initalize interfacelocation
	/*float difficulty1 = - 0.7;
	float difficulty2 = - 0.3;
	float difficulty3 =  0.5;
	float difficulty4 =  0.3;
	float difficultysz = 0.05;
	buttons.push_back(BUTTON(LOCATION(difficulty1), LOCATION(difficulty3)));
	buttons.push_back(BUTTON(LOCATION(difficulty2), LOCATION(difficulty3)));

	squares.push_back(Square(LOCATION(difficulty1), LOCATION(difficulty3), 1, 0, 0, RSIZE(difficultysz), RSIZE(difficultysz)));
	squares.push_back(Square(LOCATION(difficulty2), LOCATION(difficulty3), 1, 0, 0, RSIZE(difficultysz), RSIZE(difficultysz)));
	
	buttons.push_back(BUTTON(LOCATION(difficulty1), LOCATION(difficulty4)));
	buttons.push_back(BUTTON(LOCATION(difficulty2), LOCATION(difficulty4)));

	squares.push_back(Square(LOCATION(difficulty1), LOCATION(difficulty4), 1, 0, 0, RSIZE(difficultysz), RSIZE(difficultysz)));
	squares.push_back(Square(LOCATION(difficulty2), LOCATION(difficulty4), 1, 0, 0, RSIZE(difficultysz), RSIZE(difficultysz)));
*/

	//temporary value to experiment
	difficulty = EASY;
	player = 3;

	//initialize random function as random seed
	srand(static_cast<unsigned int>(time(NULL)));
	//fit console size into map
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, MAP::ROW, 0, (MAP::COL * 7) / 6);
	//make a maps
	for (int k = 0; k < player; ++k) {
		maps.push_back(new Grid*[MAP::ROW]);
		for (std::vector<Grid**>::size_type i = 0; i < maps.size(); ++i) {
			for (int j = 0; j < MAP::ROW; ++j)
				maps[i][j] = new Grid[MAP::COL];
		}
		scores.push_back(0.0);
	}
	//add zombies
	switch (difficulty) {
	case EASY:
		for (int k = 0; k < MAP::ROW; ++k) zombies.push_back(Zombie());
		break;
	case NORMAL:
		for (int k = 0; k < MAP::ROW * 1.5; ++k) zombies.push_back(Zombie());
		break;
	case HARD:
		for (int k = 0; k < MAP::ROW * 2; ++k) zombies.push_back(Zombie());
		break;
	default:
		for (int k = 0; k < 1; ++k) zombies.push_back(Zombie());
		break;
	}
	//add users
	if (player == 1) {
		User user1(MAP::ROW / 2, MAP::COL / 2, 1.0f, 0.0f, 0.0f);
		user1.setTerritorycolor(1.0f, 199.0 / 255.0, 87.0 / 255.0);
		users.push_back(user1);
		//default territory
		for (int i = -1; i <= 1; ++i) {
			for (int j = -1; j <= 1; ++j) {
				maps[0][MAP::ROW / 2 + i][MAP::COL / 2 + j].setState(STATE::ON);
			}
		}
	}
	else if (player == 2) {
		User user1(MAP::ROW * 3 / 4, MAP::COL * 3 / 4, 1.0f, 0.0f, 0.0f);
		user1.setTerritorycolor(1.0f, 199.0 / 255.0, 87.0 / 255.0);
		users.push_back(user1);
		User user2(MAP::ROW / 4, MAP::COL / 4, 0.0f, 0.0f, 1.0f);
		user2.setTerritorycolor(102.0 / 255.0, 102.0 / 255.0, 255.0 / 255.0);
		user2.setKey(DIRECTION::RIGHT, 'd', false);
		user2.setKey(DIRECTION::LEFT, 'a', false);
		user2.setKey(DIRECTION::UP, 'w', false);
		user2.setKey(DIRECTION::DOWN, 's', false);
		users.push_back(user2);
		//default territory
		for (int i = -1; i <= 1; ++i) {
			for (int j = -1; j <= 1; ++j) {
				maps[0][MAP::ROW * 3 / 4 + i][MAP::COL * 3 / 4 + j].setState(STATE::ON);
				maps[1][MAP::ROW / 4 + i][MAP::COL / 4 + j].setState(STATE::ON);
			}
		}
	}
	else if (player == 3) {
		User user1(MAP::ROW / 2, MAP::COL * 3 / 4, 1.0f, 0.0f, 0.0f);
		user1.setTerritorycolor(1.0f, 199.0 / 255.0, 87.0 / 255.0);
		users.push_back(user1);
		User user2(MAP::ROW / 4, MAP::COL / 4, 0.0f, 0.0f, 1.0f);
		user2.setTerritorycolor(102.0 / 255.0, 102.0 / 255.0, 255.0 / 255.0);
		user2.setKey(DIRECTION::RIGHT, 'd', false);
		user2.setKey(DIRECTION::LEFT, 'a', false);
		user2.setKey(DIRECTION::UP, 'w', false);
		user2.setKey(DIRECTION::DOWN, 's', false);
		users.push_back(user2);
		User user3(MAP::ROW * 3 / 4, MAP::COL / 4, 1.0f, 153.0 / 255.0, 0.0f);
		user3.setTerritorycolor(204.0 / 255.0, 051.0 / 255.0, 153.0 / 255.0);
		user3.setKey(DIRECTION::RIGHT, '6', false);
		user3.setKey(DIRECTION::LEFT, '4', false);
		user3.setKey(DIRECTION::UP, '8', false);
		user3.setKey(DIRECTION::DOWN, '5', false);
		users.push_back(user3);
		//default territory
		for (int i = -1; i <= 1; ++i) {
			for (int j = -1; j <= 1; ++j) {
				maps[0][MAP::ROW / 2 + i][MAP::COL * 3 / 4 + j].setState(STATE::ON);
				maps[1][MAP::ROW / 4 + i][MAP::COL / 4 + j].setState(STATE::ON);
				maps[2][MAP::ROW * 3 / 4 + i][MAP::COL / 4 + j].setState(STATE::ON);
			}
		}
	}
	//
		//}
}
void processNormalKeys(unsigned char key, int x, int y) {
	for (std::vector<User>::size_type i = 0; i < users.size(); ++i) {
		if (key == users[i][DIRECTION::RIGHT].key && users[i][DIRECTION::RIGHT].isSpecialKey == false)
			users[i].setDirection(DIRECTION::RIGHT);
		if (key == users[i][DIRECTION::LEFT].key && users[i][DIRECTION::LEFT].isSpecialKey == false)
			users[i].setDirection(DIRECTION::LEFT);
		if (key == users[i][DIRECTION::DOWN].key && users[i][DIRECTION::DOWN].isSpecialKey == false)
			users[i].setDirection(DIRECTION::DOWN);
		if (key == users[i][DIRECTION::UP].key && users[i][DIRECTION::UP].isSpecialKey == false)
			users[i].setDirection(DIRECTION::UP);
		if (key == users[i][DIRECTION::STOP].key && users[i][DIRECTION::STOP].isSpecialKey == false)
			users[i].setDirection(DIRECTION::STOP);
	}
}
void processSpecialKeys(int key, int x, int y) {
	for (std::vector<User>::size_type i = 0; i < users.size(); ++i) {
		int x = static_cast<int>(users[i].getX()); int y = static_cast<int>(users[i].getY());
		if (key == users[i][DIRECTION::RIGHT].key && users[i][DIRECTION::RIGHT].isSpecialKey == true && maps[i][x + 1][y].getState() != STATE::ING)
			users[i].setDirection(DIRECTION::RIGHT);
		if (key == users[i][DIRECTION::LEFT].key && users[i][DIRECTION::LEFT].isSpecialKey == true && maps[i][x - 1][y].getState() != STATE::ING)
			users[i].setDirection(DIRECTION::LEFT);
		if (key == users[i][DIRECTION::DOWN].key && users[i][DIRECTION::DOWN].isSpecialKey == true && maps[i][x][y - 1].getState() != STATE::ING)
			users[i].setDirection(DIRECTION::DOWN);
		if (key == users[i][DIRECTION::UP].key && users[i][DIRECTION::UP].isSpecialKey == true && maps[i][x][y + 1].getState() != STATE::ING)
			users[i].setDirection(DIRECTION::UP);
		if (key == users[i][DIRECTION::STOP].key && users[i][DIRECTION::STOP].isSpecialKey == true)
			users[i].setDirection(DIRECTION::STOP);
	}
}

// decide which nan-ii=-do or interface
void processMouse(int button, int state, int x, int y) {
	printf("Mouse button is clicked! (%d, %d, %d, %d)\n", button, state, x, y);
	std::cout << gameState << std::endl;

	//fit mouselocation
	float newx = ((float)x - WIDTH / 2) / (float)(WIDTH / 2);
	float newy = -((float)y - HEIGHT / 2) / (float)(HEIGHT / 2);
	float Xstate = LOCATION(newx);
	float Ystate = LOCATION(newy);
	for (int i = 0; i<4; i++) {
		if (buttons[i].check(Xstate, Ystate)) {
			switch (i) {
			case 0:
				difficulty--;
				break;
			case 1:
				difficulty++;
				break;
			case 2:
				player--;
				break;
			case 3:
				player++;
				break;
			}
		}
	}
	// easy
	// normal
	// hard


}

void idle() {
	//Frame control
	if (!FPScontrol(FRAME)) return;
	//change the location of zombies
	for (std::vector<Zombie>::size_type i = 0; i < zombies.size(); ++i) {
		zombies[i].move(maps);
	}
	for (std::vector<User>::size_type i = 0; i < users.size(); ++i) {
		//check if user success
		if (scores[i] > 50.0) win(users[i]);
		//move
		switch (users[i].getDirection()) {
		case DIRECTION::RIGHT:
			if (users[i].getX() < MAP::ROW - 2) users[i].setPos(users[i].getX() + 1, users[i].getY());
			break;
		case DIRECTION::LEFT:
			if (users[i].getX() > 1)	users[i].setPos(users[i].getX() - 1, users[i].getY());
			break;
		case DIRECTION::DOWN:
			if (users[i].getY() > 1)	users[i].setPos(users[i].getX(), users[i].getY() - 1);
			break;
		case DIRECTION::UP:
			if (users[i].getY() < MAP::COL - 2)	users[i].setPos(users[i].getX(), users[i].getY() + 1);
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
			else if (maps[i][x][y].getState() == STATE::ON) {//Finished making
				users[i].setIsmaking(false);
				FloodFill(maps, i, users[i]);
				//renew score
				for (std::vector<User>::size_type j = 0; j < users.size(); ++j) {
					scores[j] = calculate_rate(maps[j]);
				}
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
		//defeat by zombie
		for (std::vector<Zombie>::size_type j = 0; j < zombies.size(); ++j) {
			x = static_cast<int>(zombies[j].getX());
			y = static_cast<int>(zombies[j].getY());
			if (maps[i][x][y].getState() == STATE::ING) defeat(users[i]);
		}
		//check if zombies are dead
		for (std::vector<Zombie>::size_type j = 0; j < zombies.size(); ++j) {
			x = static_cast<int>(zombies[j].getX());
			y = static_cast<int>(zombies[j].getY());
			if (maps[i][x][y].getState() == STATE::ON) zombies.erase(zombies.begin() + j);
		}
	}

	glutPostRedisplay();
}

void renderScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//make a barrier
	//if (gameState == INTERFACE){
	//	squares[0].draw(0);
	//	squares[1].draw(1);
	//	squares[2].draw(0);
	//	squares[3].draw(1);
	//}
	//if (gameState != INTERFACE){
		//make a barrier
		glColor3f(0.31f, 0.31f, 0.31f);//Gray
		glBegin(GL_QUADS);
		glVertex2f(0, 0); glVertex2f(0, MAP::COL); glVertex2f(1, MAP::COL); glVertex2f(1, 0);
		glVertex2f(0, 0); glVertex2f(0, 1); glVertex2f(MAP::ROW, 1); glVertex2f(MAP::ROW, 0);
		glVertex2f(MAP::ROW - 1, 0); glVertex2f(MAP::ROW - 1, MAP::COL); glVertex2f(MAP::ROW, MAP::COL); glVertex2f(MAP::ROW, 0);
		glVertex2f(0, MAP::COL - 1); glVertex2f(0, MAP::COL); glVertex2f(MAP::ROW, MAP::COL); glVertex2f(MAP::ROW, MAP::COL - 1);
		glEnd();
		//draw territories
		//draw ON
		glBegin(GL_QUADS);
		for (std::vector<User>::size_type i = 0; i < users.size(); ++i) {
			glColor3f(users[i].getTR(), users[i].getTG(), users[i].getTB());
			for (int row = 0; row < MAP::ROW; ++row) {
				for (int col = 0; col < MAP::COL; ++col) {
					if (maps[i][row][col].getState() == STATE::ON) {
						glVertex2f(row, col);
						glVertex2f(row, col + SIZE);
						glVertex2f(row + SIZE, col + SIZE);
						glVertex2f(row + SIZE, col);
					}
				}
			}
		}
		//draw ING
		for (std::vector<User>::size_type i = 0; i < users.size(); ++i) {
			glColor3f(users[i].getTR(), users[i].getTG(), users[i].getTB());
			for (int row = 0; row < MAP::ROW; ++row) {
				for (int col = 0; col < MAP::COL; ++col) {
					if (maps[i][row][col].getState() == STATE::ING) {
						glVertex2f(row, col + SIZE / 2.0);
						glVertex2f(row + SIZE / 2.0, col + SIZE);
						glVertex2f(row + SIZE, col + SIZE / 2.0);
						glVertex2f(row + SIZE / 2.0, col);
					}
				}
			}
		}
		glEnd();
		//draw players
		for (std::vector<Zombie>::size_type i = 0; i < zombies.size(); ++i) zombies[i].draw();
		for (std::vector<User>::size_type i = 0; i < users.size(); ++i) users[i].draw();
		//print score
		glColor3f(1.0f, 1.0f, 1.0f);
		if (player == 1) {
			draw_string(FONT, "Player 1 " + std::to_string(scores[0]).substr(0, 4) + "% / " + std::to_string(WINRATE) + "%", (MAP::ROW * 4) / 7, (MAP::COL * 10) / 9);		}
		else if (player == 2) {
			draw_string(FONT, "Player 1 " + std::to_string(scores[0]).substr(0, 4) + "% / " + std::to_string(WINRATE) + "%", (MAP::ROW * 4) / 7, (MAP::COL * 10) / 9);
			draw_string(FONT, "Player 2 " + std::to_string(scores[1]).substr(0, 4) + "% / " + std::to_string(WINRATE) + "%", (MAP::ROW * 4) / 7, (MAP::COL * 19) / 18);
		}
		//print number of zombies
		switch (difficulty) {
		case EASY:	draw_string(FONT, "EASY MODE", (MAP::ROW) / 20, (MAP::COL * 10) / 9); break;
		case NORMAL:	draw_string(FONT, "NORMAL MODE", (MAP::ROW) / 20, (MAP::COL * 10) / 9); break;
		case HARD:	draw_string(FONT, "HARD MODE", (MAP::ROW) / 20, (MAP::COL * 10) / 9); break;
		default: break;
		}
		draw_string(FONT, "Number of Zombies " + std::to_string(zombies.size()), (MAP::ROW) / 20, (MAP::COL * 19) / 18);
	//}
	glutSwapBuffers();
}

void main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Drawing Square & Equilateral Triangle");
	init();

	glutDisplayFunc(renderScene);
	glutSpecialFunc(processSpecialKeys);
	glutKeyboardFunc(processNormalKeys);
	//glutMouseFunc(processMouse);
	glutIdleFunc(idle);

	glutMainLoop();
}
