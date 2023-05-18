#include <iostream>
#include "vec.h"
#include <vector>
#include "Boid.h"
#include "algorithm"


class Flock {

public:
	vector<Boid> boids;

	void addBoid(Boid b) {
		boids.push_back(b);
	}

	void update_all_boids_to_new_positions(double minD,double angle, double perceptD) {

		// get target position
		Vec3<double> target = get_target(angle);


		for (auto& b : boids) {

			
		
			Vec3<double> coh = cohesion(b, perceptD);
			Vec3<double> sep = separate(b,minD, perceptD);
			Vec3<double> ali = align(b, perceptD);
			Vec3<double> fly= tend_to_place(target, b);
			
			b.acceleration += coh;
			b.acceleration += sep;
			b.acceleration += ali;
			b.acceleration += fly;
			

			b.velocity += b.acceleration;
			// limit boids' speed before update position
			limit_velocity(b);
			b.position +=b.velocity;
			// limit boids activity area
			borders(b);
			
			// Reset accelertion to 0 each cycle
			b.acceleration = Vec3<double>(0, 0, 0);
			
		}
	}

private:

	// Rule 1 : Cohesion
	// Every boid attempts to move towards the average position of other nearby boids.
	// find center position and the difference between current boid and center position, want to cohension slowly and smoothly ,so divide it by 100
	Vec3<double> cohesion(Boid b, double perceptD) {

		Vec3<double> center;
		int count = 0;

		for (auto& other : boids) {
			if (b.position != other.position) {

				double d = distance(b.position, other.position);
				if (d > 0 && d < perceptD) {
					center += other.position;
					count++;
				}
			}
		}
		Vec3<double> res;
		if (count > 0) {
			center /= count;
		}

		if (center.length() > 0) {
			center.normalize();
		}

		return (center-b.position)/100;

	}

	// Rule 2 : Separation
	// Each boid attempts to maintain a reasonable amount of distance between itself and any nearby boids
	Vec3<double> separate(Boid b, double minD_adjust, double perceptD) {
	
		Vec3<double> c = Vec3<double>(0, 0, 0);
		int count = 0;

		for (auto& other : boids) {
			if (b.position != other.position) {

				double d = distance(other.position, b.position);
				if (d > 0 && d < perceptD) {
					Vec3<double> diff = other.position-b.position;
					diff.normalize();
					diff /= d;
					c += diff;
				    count++;
				}
			}
		}

		if (count > 0) {
			c /= count;
		}

		if (c.length() > 0) {
			c.normalize();
		}
		Vec3<double> res = (-c) /minD_adjust;


		return res;
	}


	// Rule 3 : Alignment
	// Each boid tries to match its velocity with the average velocity of its nearby boids.
	Vec3<double> align(Boid b, double perceptD) {

		Vec3<double> sum;
		int count = 0;

		for (auto& other : boids) {
			if (b.position != other.position) {

				double d = distance(b.position, other.position);
				if (d > 0 && d < perceptD) {
					sum +=other.velocity;
					count++;
				}
			}
		}
		if (count > 0) {
			sum/=count;
		}

		if (sum.length() > 0) {
			sum.normalize();
		}

		return (sum-b.velocity)/100;
	}


	//	Calculate Distance between two vectors
	double distance(Vec3<double> a, Vec3<double> b) {
		Vec3<double> diff = a - b;
		double res = diff.length();
		return res;
	}

	// bounding boids within some area
	void borders(Boid &b) {

		cout << "before border: " << b.position[0] <<" " << b.position[1] <<" " << b.position[2] << "\n";

		double mi = -30, ma = 30;
		double Xmin = mi, Xmax = ma, Ymin = mi, Ymax = ma, Zmin = mi, Zmax= ma;
		Vec3<double> v;

		if (b.position[0] < Xmin)
		{
			b.position[0] = ma;
		}
		else if (b.position[0] > Xmax)
		{ 
			b.position[0] = mi; 
		}

		if (b.position[1] < Ymin) 
		{ b.position[1] = ma; }
		else if (b.position[1] > Ymax)
		{ b.position[1] = mi; }

		if (b.position[2] < Zmin) 
		{ b.position[2] = ma; }
		else if (b.position[2] > Zmax) 
		{ b.position[2] = mi; }


		cout << "after border: " << b.position[0] <<" " << b.position[1] <<" " << b.position[2] << "\n";

	}

	// Limiting boids' speed
	void limit_velocity(Boid &b) {

		cout << "before limit speed: " << b.velocity[0] <<" "<< b.velocity[1] <<" "<< b.velocity[2] << "\n";

		double vlim = 0.2;
		double k = b.velocity.length();
		if (k > vlim)
			b.velocity /= 10;

		cout << "after limit speed : " << b.velocity[0] <<" " << b.velocity[1] <<" "<< b.velocity[2] << "\n";
		
	}


	// Circle around tree; the target are the points along the circle
	Vec3<double> get_target(double angle) {
		Vec3<double> target;
		if(angle>=0){
			target= Vec3<double>(30 * cos(angle), 4, 30 * sin(angle));
		}
		else {
			target = Vec3<double>{ 3,3,5 };
		}
		return target;

	}

	// Fly towards target
	Vec3<double> tend_to_place(Vec3<double> target,Boid b) {

		return (target - b.position)/100;
	}

};

