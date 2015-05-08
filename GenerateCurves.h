#include <iostream>
#include <vector>
#include "Vec.h"

class XYData
{
public:
	std::vector<Vec*> v;

	XYData(){
		v.push_back(new Vec(0,0));
	}
	void add(float x, float y){
		v.push_back(new Vec(x,y));
	}

	Vec max(){
		Vec max(0,0);
		for(std::vector<Vec* >::iterator i = v.begin(); i != v.end(); ++i){
			if(max.x < (*i)->x)
				max.x = (*i)->x;
			if(max.y < (*i)->y)
				max.y = (*i)->y;
		}
		return max;
	}

	virtual void generate(float xini, float xend, float inc){
		std::vector<float> x;
		for(float i = xini; i != xend; i += inc){
			x.push_back(i);
		}
	}
	
};

class QuadraticCurve : public XYData{
public:
	float a, b, c;

	QuadraticCurve(float a, float b, float c){
		this->a = a;
		this->b = b;
		this->c = c;
	}

	void generate(float xini, float xend, float inc){
		std::vector<float> x;
		std::vector<float> y;
		//int count = 0;
		for(float i = xini; i <= xend; i += inc){
			x.push_back(i);
			y.push_back(((a*i*i)+(b*i)+(c)));
			//std::cout << "QC x = " << x[count] << " y = " << y[count] << std::endl;
			//count++;
		}
		for(int i = 0; i < x.size(); i++){
			v.push_back(new Vec(x[i], y[i]));
		}
	}
};

class CubicCurve : public XYData
{
public:
	float a, b, c, d;

	CubicCurve(float a, float b, float c, float d){
		this->a = a;
		this->b = b;
		this->c = c;
		this->d = d;
	}
	
	void generate(float xini, float xend, float inc){
		std::vector<float> x;
		std::vector<float> y;
		for(float i = xini; i <= xend; i += inc){
			x.push_back(i);
			y.push_back(((a*i*i*i)+(b*i*i)+(c*i)+(d)));
		}
		for(int i = 0; i < x.size(); i++){
			v.push_back(new Vec(x[i], y[i]));
		}
	}
	
};