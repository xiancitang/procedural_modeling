#include "modelerview.h"
#include "modelerapp.h"
#include "modelerdraw.h"
#include <FL/gl.h>
#include "modelerglobals.h"
#include <string>
#include <vector>
#include "Flock.cpp"
#include "animationcheck.h"

#if _MSC_VER >= 1300

#include <iostream>

#else //  _MSC_VER >= 1300

#include <iostream.h>
#include "meshmodel.h"

#endif // _MSC_VER >= 1300

using namespace std;


string fulltext;
double angle;

class PlantModel : public ModelerView
{
public:
	Flock* flock;

	// random double generater between certain range
	double dRand(double dMin, double dMax)
	{
		double d = (double)rand() / RAND_MAX;
		return dMin + d * (dMax - dMin);
	}

	// full text generator using grammer defined
	void generateFulltext(string s, int depth)
	{
		if (depth == 0) {
			fulltext = s;
			return;
		}

		string nextS;

		for (int i = 0; i < s.length(); i++) {
			if (s[i] == '0') {
				nextS += "1[0]0^{0}0^1";
				continue;
			}
			if (s[i] == '1') {
				nextS += "10";
				continue;
			}
			nextS += s[i];
		}
		generateFulltext(nextS, depth - 1);
	}

	PlantModel(int x, int y, int w, int h, char *label)
		: ModelerView(x, y, w, h, label) { 
	
		// initate boids
		flock = new Flock();
		for (int i = 0; i < 6; i++) {
			Vec3<double> p = { dRand(0.1, 1),dRand(0, 1),dRand(0, 1) };
			Boid* b = new Boid(p);
			flock->addBoid(*b);
		}
		
	}

	virtual void draw();
};


ModelerView* createPlantModel(int x, int y, int w, int h, char *label)
{
	return new PlantModel(x, y, w, h, label);
}





void PlantModel::draw()
{

	ModelerView::draw();

	// draw boids
	glPushMatrix();
	vector<Boid> all = flock->boids;
	for (Boid i : all) {
		Vec3<double> b = i.position;
		glPushMatrix();
		setAmbientColor(.1f, .1f, .1f);
		setDiffuseColor(COLOR_GREEN);
		glTranslated(-0.05, 0, -0.05);
		glTranslated(b[0], b[1], b[2]);
		drawSphere(0.1);
		if (i.velocity.length() != 0 && VAL(ORIENTATION)>0.5) {
			Vec3<double> d1 = i.position /10;
			Vec3<double> d2 = i.velocity/ 10;
			glPushMatrix();
			setAmbientColor(.1f, .1f, .1f);
			setDiffuseColor(COLOR_RED);
			drawLine(d1[0], d1[1], d1[2], d2[0], d2[1], d2[2]);
			glPopMatrix();
		}
		glPopMatrix();
	}

	flock->update_all_boids_to_new_positions(VAL(MIN_DISTANCE_ADJUST), angle, VAL(PECEP_DISTANCE));
	// every draw , angle increase a bit, so target get updated, boids will fly around tree in a circle 
	angle = angle+0.011;


	if (animation_check) {
		flock->update_all_boids_to_new_positions(VAL(MIN_DISTANCE_ADJUST), angle,VAL(PECEP_DISTANCE));
		angle = angle + 0.011;
	}

	glPopMatrix();



	glPushMatrix();
	// draw the floor
	setAmbientColor(.1f, .1f, .1f);
	setDiffuseColor(COLOR_BLUE);
	glPushMatrix();
	glTranslated(-5, 0, -5);
	glScaled(2, 1, 2);
	drawBox(5, 0.01f, 5);
	glPopMatrix();

	// draw the plant model
	setAmbientColor(.1f, .1f, .1f);
	int c = VAL(COLOR);
	switch (c) {
	case 1:
		setDiffuseColor(COLOR_MAGENTA);
		break;
	case 2:
		setDiffuseColor(COLOR_YELLOW);
		break;
	case 3:
		setDiffuseColor(COLOR_CYAN);
		break;
	}

	
	
	glPushMatrix();
	glTranslated(VAL(X), VAL(Y), VAL(Z));
	glRotated(-90, 1.0, 0.0, 0.0);

	// generate text based on recursion depth
	generateFulltext("0", VAL(RECURSION_DEPTH));


	for (char c : fulltext) {
		switch (c) {

			case '0':
				drawCylinder(VAL(TALLNESS), 0.1, 0.1);
				glTranslated(0.0, 0.0, VAL(TALLNESS));
				drawSphere(VAL(LEAF_SIZE));
				break;
			case '1':
				drawCylinder(VAL(TALLNESS), VAL(BRANCH_WIDTH), VAL(BRANCH_WIDTH));
				glTranslated(0.0, 0.0, VAL(TALLNESS));
				break;
			case '[':
				glPushMatrix();
				glRotated(VAL(BRANCH_ANGLE), 1.0, 0.0, 0.0);
				break;

			case ']':
				glPopMatrix();
				glPushMatrix();
				glRotated(-VAL(BRANCH_ANGLE), 1.0, 0.0, 0.0);
				break;

			case '{':
				glPushMatrix();
				glRotated(VAL(BRANCH_ANGLE), 0.0, 1.0, 0.0);
				break;

			case '}':
				glPopMatrix();
				glPushMatrix();
				glRotated(-VAL(BRANCH_ANGLE), 0.0, 1.0, 0.0);
				break;

			case '^':
				glPopMatrix();
				break;
		}
	}

	glPopMatrix();
	glPopMatrix();
}

int main()
{
	ModelerControl controls[PCONTROLS];
	controls[X] = ModelerControl("X", -5, 5, 0.1f, 0);
	controls[Y] = ModelerControl("Y", 0, 5, 0.1f, 0);
	controls[Z] = ModelerControl("Z", -5, 5, 0.1f, 0);
	controls[BRANCH_ANGLE] = ModelerControl("BRANCH_ANGLE", 20, 60, 5, 45);
	controls[RECURSION_DEPTH] = ModelerControl("RECURSION_DEPTH", 1.0, 5.0, 1.0, 3.0);
	controls[TALLNESS] = ModelerControl("TALLNESS", 0.3, 0.5, 0.05, 0.3);
	controls[COLOR] = ModelerControl("COLOR", 1, 3, 1,1);
	controls[LEAF_SIZE] = ModelerControl("LEAF_SIZE", 0.01, 0.2,0.005, 0.02);
	controls[BRANCH_WIDTH] = ModelerControl("BRANCH_WIDTH", 0.03, 0.1, 0.01, 0.07);
	controls[MIN_DISTANCE_ADJUST] = ModelerControl("MIN_DISTANCE_ADJUST", 10, 1000, 100, 100);
	controls[PECEP_DISTANCE] = ModelerControl("PERCEP_DISTANCE", 10, 200, 100, 50);
	controls[ORIENTATION] = ModelerControl("ORIENTATION", 0,1, 1, 1);

	ModelerApplication::Instance()->Init(&createPlantModel, controls, PCONTROLS);
	return ModelerApplication::Instance()->Run();
}
