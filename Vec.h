#include <iostream>
#include <vector>


class Vec{

public:
	float x;
	float y;

	Vec(){
		x = 0;
		y = 0;
	}

	Vec(float x_axis, float y_axis){
		x = x_axis;
		y = y_axis;
	}

	void add(Vec push){
		x += push.getX();
		y += push.getY();
	}

	float getX(){
		return x;
	}

	float getY(){
		return y;
	}

	void print(){
		std::cout << "(" << x << ", " << y << ")" << std::endl;
	}

};


/*class Rect {
	
public:
	float x;
	float y;
	float width;
	float height;
	float r;
	float g;
	float b;

	Rect(){
		x = 0;
		y = 0;
		width = 0;
		height = 0;
		r = 0;
		g = 0;
		b = 0;
	}

	Rect(float a1, float b2, float c3, float d4, float r, float, g, float g){
		x = a1;
		y = b2;
		width = c3;
		height = d4;

	}

	int contains(Vec find){
		if(find.x > x && find.x < (x+width) && find.y < y && find.y > (y-height)){
			return 1;
		}
		else{
			return 0;
		}
	}

};

class RectStash{

public:
	// Dynamically allocated vector of bytes:
	std::vector<Rect*> r;
  
	// Functions!
  
	int add(const Rect* element){
		r.push_back(element);
		return r.size();
	}

	void* fetch(int index){
		return &(r[index]);
	}
  
	int count() {
		return r.size(); // Number of elements in CStash
	}
};*/
