#include <iostream>
#include "GrPlot.h"

class RectStash{

public:
	// Dynamically allocated vector of bytes:
	std::vector<Rect*> r;
  
	// Functions!

	Rect *first(){
		return r[0];
	}
  
	int add(Rect* element){
		r.push_back(element);
		return r.size();
	}
  
	int count() {
		return r.size(); // Number of elements in CStash
	}

	void erase(Rect* i){
		for(std::vector<Rect*>::iterator i = r.begin(); i!= r.end(); i++){
			delete(*i);
		}	
	}
};
