// Tetris.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <algorithm>
#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

#define HEIGHT 18
#define WIDTH  12

struct vector2D {
	int x;
	int y;
};

class Shape {
public:
	unsigned char ID;
	int x;
	int y;
	vector2D* vectors;
	int vec_size;
public:
	Shape() {
		this->ID = 1;
		this->x = 0;
		this->y = 0;
		this->vectors = NULL;
		this->vec_size = 0;
	}
	Shape(unsigned char id, int x, int y, vector2D* vector, int vec_size) {
		this->ID = id;
		this->x = x;
		this->y = y;
		if (this->vectors) {
			delete this->vectors;
		}
		this->vectors = vector;
		this->vec_size = vec_size;
	}
	~Shape() {
		delete this->vectors;
	}

	void copy(Shape* copy) {
		this->ID = copy->ID;
		this->x = copy->x;
		this->y = copy->y;
		if (this->vectors) {
			delete this->vectors;
		}
		this->vectors = new vector2D[copy->vec_size];
		for (int i = 0; i < copy->vec_size; i++) {
			this->vectors[i].x = copy ->vectors[i].x;
			this->vectors[i].y = copy ->vectors[i].y;
		}
		this->vectors = copy->vectors;
		this->vec_size = copy->vec_size;
	}
	void rotateLeft() {
		for (int i = 0; i < vec_size; i++) {
			int x = vectors[i].x;
			int y = vectors[i].y;

			vectors[i].x = y;
			vectors[i].y = -x;
		}
	}
	void rotateRight() {
		for (int i = 0; i < vec_size; i++) {
			int x = vectors[i].x;
			int y = vectors[i].y;

			vectors[i].x = -y;
			vectors[i].y = x;
		}
	}
	bool detectCollidoin(unsigned char* world, int width, int height) {
		for (int i = 0; i < vec_size; i++) {
			if (x + vectors[i].x < 0 || x + vectors[i].x > width - 1) { // if shape is out of boundrie
				return true;
			}
			if (y + vectors[i].y < 0 || y + vectors[i].y > height - 1) { // if shape is out of boundrie
				return true;
			}
			if (world[(x + vectors[i].x) + (y + vectors[i].y) * width] != 0) { // if shape is overlaping onther shape
				return true;
			}
		}
		return false;
	}

};



class Tetris : public olc::PixelGameEngine
{
public:
	olc::Pixel color;
	int scorre = 0;
	float Time = 0;
	float update_time = 1;
	int block_size = 10;
	int Xres = 240;
	int Yres = 256;
	int nWorldWidth = WIDTH;
	int nWorldHeight = HEIGHT;
	int moves = 0;
	bool Game_Over = false;
	Shape* cur_shape ;
	vector2D shapes[8][4] = { { {-1,0},{0,0},{1,0},{0,1} },
							{ {-1,0},{0,0},{1,0},{1,1} },
							{ {-1,0},{0,0},{1,0},{1,1} },
							{ {-1,1},{0,1},{0,0},{1,0} },
							{ {-1,0},{0,0},{0,1},{1,1} },
							{ {-1,0},{0,0},{1,0},{1,-1} },
							{ {-1,0},{0,0},{1,0},{2,0} },	
							{ {-1,0},{0,0},{0,1},{-1,1} } };
	unsigned char* world;
private:
	int width_offset = 0;
	int height_offset = 0;
public:
	Tetris()
	{
		// Name you application
		sAppName = "Tetris";
		world = new unsigned char[nWorldHeight * nWorldWidth];
	}
	void moveleft() {
		Shape s;
		s.x = cur_shape->x;
		s.y = cur_shape->y;
		s.vectors = new vector2D[4];
		for (int i = 0; i < cur_shape->vec_size; i++) {
			s.vectors[i].x = cur_shape->vectors[i].x;
			s.vectors[i].y = cur_shape->vectors[i].y;
		}
		s.vec_size = cur_shape->vec_size;
		s.x += 1;
		if (!s.detectCollidoin(world, nWorldWidth, nWorldHeight)) {
			cur_shape->x += 1;
		}
	}
	void moveRight() {
		Shape s;
		s.x = cur_shape->x;
		s.y = cur_shape->y;
		s.vectors = new vector2D[4];
		for (int i = 0; i < cur_shape->vec_size; i++) {
			s.vectors[i].x = cur_shape->vectors[i].x;
			s.vectors[i].y = cur_shape->vectors[i].y;
		}
		s.vec_size = cur_shape->vec_size;
		s.x -= 1;
		if (!s.detectCollidoin(world, nWorldWidth, nWorldHeight)) {
			cur_shape->x -= 1;
		}
	}
	bool moveDown() {
		Shape s;
		s.x = cur_shape->x;
		s.y = cur_shape->y;
		s.vectors = new vector2D[4];
		for (int i = 0; i < cur_shape->vec_size; i++) {
			s.vectors[i].x = cur_shape->vectors[i].x;
			s.vectors[i].y = cur_shape->vectors[i].y;
		}
		s.vec_size = cur_shape->vec_size;
		s.y += 1;
		if (!s.detectCollidoin(world, nWorldWidth, nWorldHeight)) {
			cur_shape->y += 1;
			return true;
		}
		else {
			return false;
		}
	}
	void Rotateleft() {
		Shape s;
		s.x = cur_shape->x;
		s.y = cur_shape->y;
		s.vectors = new vector2D[4];
		for (int i = 0; i < cur_shape->vec_size; i++) {
			s.vectors[i].x = cur_shape->vectors[i].x;
			s.vectors[i].y = cur_shape->vectors[i].y;
		}
		s.vec_size = cur_shape->vec_size;
		s.rotateLeft();
		if (!s.detectCollidoin(world, nWorldWidth, nWorldHeight)) {
			cur_shape->rotateLeft();
		}
	}
	void RotateRight() {
		Shape s;
		s.x = cur_shape->x;
		s.y = cur_shape->y;
		s.vectors = new vector2D[4];
		for (int i = 0; i < cur_shape->vec_size; i++) {
			s.vectors[i].x = cur_shape->vectors[i].x;
			s.vectors[i].y = cur_shape->vectors[i].y;
		}
		s.vec_size = cur_shape->vec_size;
		s.rotateRight();
		if (!s.detectCollidoin(world, nWorldWidth, nWorldHeight)) {
			cur_shape->rotateRight();
		}
	}
	void printShape() {
		for (int i = 0; i < cur_shape->vec_size; i++) {
			world[(cur_shape->x + cur_shape->vectors[i].x) + ((cur_shape->y + cur_shape->vectors[i].y) * nWorldWidth)] = cur_shape->ID;
		}
	}
	void RemoveShape() {
		for (int i = 0; i < cur_shape->vec_size; i++) {
			world[(cur_shape->x + cur_shape->vectors[i].x) + ((cur_shape->y + cur_shape->vectors[i].y) * nWorldWidth)] = 0;
		}
	}
	bool detect_line(int y) {
			for (int x = 0; x < nWorldWidth; ++x)
			{
				if (world[x + (y * nWorldWidth)] == 0)
				{
					return false;
				}
			}
			return true;
	}
	void delete_update_screen(int y) {

		for (int i = y; i > 0; i--) 
			for (int x = 0; x < nWorldWidth; x++) {
				world[x + (i * nWorldWidth)] = world[x + ((i - 1) * nWorldWidth)];
			}
	}
	olc::Pixel get_color(int i) {
		switch (i)
		{
			case 0:
				return olc::BLACK;
				break;
			case 1:
				return olc::GREEN;
				break;
			case 2:
				return olc::RED;
				break;
			case 3:
				return olc::BLUE;
				break;
			case 4:
				return olc::MAGENTA;
				break;
		}
	}

public:
	bool OnUserCreate() override
	{
		cur_shape = new Shape((unsigned char)1, nWorldWidth / 2, 2, NULL, 4);

		block_size = Yres / nWorldHeight;
		width_offset = (Xres - nWorldWidth * block_size) / 2;
		for (int y = 0; y < nWorldHeight; ++y)
			for (int x = 0; x < nWorldWidth; ++x)
			{
				world[x + (y * nWorldWidth)] = 0;
			}
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{	
		if (!Game_Over) {
			srand(time(NULL));
			if (cur_shape->vectors != NULL) {
				Time += fElapsedTime;
				float fMouseX = GetMouseX();
				float fMouseY = GetMouseY();
				/*if (GetMouse(0).bReleased) {
					int i = ((int)fMouseX - width_offset) / block_size + (((int)fMouseY - height_offset) / block_size) * nWorldWidth;
					world[i] = 1;
				}*/
				if (GetKey(olc::D).bReleased) {
					RemoveShape();
					moveleft();
					printShape();
				}
				if (GetKey(olc::A).bReleased) {
					RemoveShape();
					moveRight();
					printShape();
				}
				if (GetKey(olc::K).bReleased) {
					RemoveShape();
					Rotateleft();
					printShape();
				}
				if (GetKey(olc::L).bReleased) {
					RemoveShape();
					RotateRight();
					printShape();
				}
				if (GetKey(olc::S).bHeld)
					update_time = 0.1;
				else
					update_time = 1;
				if (Time > update_time) {
					RemoveShape();
					if (!moveDown()) {
						if (moves == 0)
							Game_Over = true;//Game  Over
						printShape();
						cur_shape->vectors = NULL;

						for (int y = nWorldHeight - 1; y > -1; y--)
						{
							if (detect_line(y)) {
								delete_update_screen(y);
								y += 1;
								scorre += 100;
							}
						}
					}
					else
					{
						printShape();
						moves += 1;
					}
					Time = 0;
				}
			}
			else {
				scorre += 50;
				cur_shape->vectors = shapes[rand() % 8];
				cur_shape->ID = 1 + rand() % 4;
				cur_shape->x = nWorldWidth / 2;
				cur_shape->y = 1;
				
				printShape();
				moves = 0;
			}
		}
		else {
			if (GetKey(olc::ENTER).bReleased) {
				scorre = 0;
				Time = 0;
				update_time = 1;
				moves = 0;
				for (int y = 0; y < nWorldHeight; ++y)
					for (int x = 0; x < nWorldWidth; ++x)
					{
						world[x + (y * nWorldWidth)] = 0;
					}
				Game_Over = false;
			}
		}

		Clear(olc::BLACK);
		if (!Game_Over) {
			DrawString(width_offset, 1, "scorre " + std::to_string(scorre));
			DrawLine(width_offset, height_offset, width_offset, (height_offset + nWorldHeight) * block_size); // left wall
			DrawLine(width_offset + nWorldWidth * block_size, height_offset, width_offset + nWorldWidth * block_size, height_offset + nWorldHeight * block_size); // right wall
			DrawLine(width_offset, height_offset + nWorldHeight * block_size, width_offset + nWorldWidth * block_size, height_offset + nWorldHeight * block_size);

			for (int y = 0; y < nWorldHeight; ++y)
				for (int x = 0; x < nWorldWidth; ++x)
				{
					if (world[x + (y * nWorldWidth)] != 0)
					{
						FillRect(width_offset + x * block_size, height_offset + y * block_size, block_size, block_size, get_color(world[x + (y * nWorldWidth)]));
						DrawRect(width_offset + x * block_size, height_offset + y * block_size, block_size, block_size);
					}
				}

		}
		else {
			DrawString(width_offset, 1, "GameOver \n scorre :" + std::to_string(scorre));
			
			DrawString(width_offset, (nWorldHeight - 1)* block_size, "Press -Enter- to restart");
		}
		return true;
	}
};

int main()
{
	Tetris demo;
	demo.Xres = 240;
	demo.Yres = 256;
	if (demo.Construct(demo.Xres, demo.Yres, 3, 3))
		demo.Start();
	return 0;
}
