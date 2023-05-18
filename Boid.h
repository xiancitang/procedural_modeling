#include <iostream>
#include "vec.h"


class Boid {

public:
	Vec3<double>  position;
	Vec3<double>  velocity;
	Vec3<double>  acceleration;

 
	Boid(Vec3<double>  pos) {
		position = pos;
		velocity = Vec3<double>(0.0, 0.0, 0.0);
		acceleration = Vec3<double>(0.0, 0.0,0.0);
	}


}; 