#include <iostream>
#include "glut_window.h"
#include "Vec.h"

class Rect {
	
public:
	float x, y, l, h, r, g, b;
	bool selected;
	std::vector<Vec*> points;

	Rect(){
		x = 0;
		y = 0;
		l = 0;
		h = 0;
		r = 0;
		g = 0;
		b = 0;
		selected =false;
	}

	Rect(float x, float y, float l, float h, float r, float g, float b){
		this->x = x;
		this->y = y;
		this->l = l;
		this->h = h;
		this->r = r;
		this->g = g;
		this->b = b;
		selected = false;
	}

	bool contains(const Rect *r){
		float r_top, r_bot, r_left, r_right;
		if(r->x == 0 && r->y == 0){
			return false;
		}
		r_top = y;
		r_bot = y-h;
		r_left = x;
		r_right = x + l;

		return (r_top >= r->y && r_bot <= r->y && r_left <= r->x && r_right >= r->x);
	}

	void reset()
	{
		x = -.1;
		y = .1;
		l = .2;
		h = .2;
		r = 1;
		g = .5;
		b = 0;
		selected =false;
	}

	

	virtual void handle(float xM, float yM){
		points.push_back(new Vec((xM - x)/l, (y- yM)/(h-.1)));
	}

	virtual void draw(){
		//Smooth points and lines
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_LINE_SMOOTH);
		glHint(GL_LINE_SMOOTH, GL_NICEST);
		glEnable(GL_POINT_SMOOTH);
		glHint(GL_POINT_SMOOTH, GL_NICEST);


		//Draw Backround color
		glBegin( GL_POLYGON );
      	glColor3f (r, g, b);
		glVertex2d (x,y);
		glVertex2d (x + l, y);
		glVertex2d (x + l, y - h);
		glVertex2d (x, y - h);
		glEnd();



	}

};