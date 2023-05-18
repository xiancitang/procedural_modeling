#pragma once

#include <vector>
#include "Boid.h"

using namespace std;

class Flock
{
public:
	vector<Boid> boids;

public:
	Flock() {};
	void addBoid(Boid b) {};
	void update_all_boids_to_new_positions(double minD, double angle, double perceptD) {};

private:

	Vec3<double> separate(Boid b, double minD, double perceptD) {};
	Vec3<double> align(Boid b, double perceptD) {};
	Vec3<double> cohesion(Boid b, double perceptD) {};
	double distance(Vec3<double> a, Vec3<double> b) {};
	void borders(Boid b) {};
	void limit_velocity(Boid &b) {};
	Vec3<double> get_target(double angle) {};
	Vec3<double> tend_to_place(Vec3<double> target, Boid b) {};
};