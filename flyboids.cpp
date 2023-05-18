//
//#include "modelerview.h"
//#include "modelerapp.h"
//#include "modelerdraw.h"
//#include <FL/gl.h>
//#include "modelerglobals.h"
//#include "Flock.cpp"
//#include "animationcheck.h"
//
//class SampleModel : public ModelerView 
//{
//public:
//	Flock* flock;
//
//	double fRand(double fMin, double fMax)
//	{
//		double f = (double)rand() / RAND_MAX;
//		return fMin + f * (fMax - fMin);
//	}
//
//    SampleModel(int x, int y, int w, int h, char *label) 
//        : ModelerView(x,y,w,h,label) {
//
//		flock = new Flock();
//		for (int i = 0; i < 6; i++) {
//			Vec3<double> p = { fRand(0, 1),fRand(0, 1),fRand(0, 1) };
//			Boid* b = new Boid(p);
//			flock->addBoid(*b);
//		}
//	}
//
//    virtual void draw();
//};
//
//
//ModelerView* createSampleModel(int x, int y, int w, int h, char *label)
//{ 
//    return new SampleModel(x,y,w,h,label); 
//}
//
//
//
//
//void SampleModel::draw()
//{
//
//    ModelerView::draw();
//
//
//	vector<Boid> all = flock->boids;
//	for (Boid i : all) {
//		Vec3<double> b = i.position;
//		glPushMatrix();
//		glTranslated(b[0], b[1], b[2]);
//		drawSphere(0.2);
//		if (i.velocity.length() != 0) {
//			drawLine(i.position[0], i.position[1], i.position[2], i.velocity[0], i.velocity[1], i.velocity[2]);
//		}
//		glPopMatrix();
//	}
//
//	flock->move_all_boids_to_new_positions();
//
//	if (animation_check){
//		flock->move_all_boids_to_new_positions();
//}
//
//}
//
//int main()
//{
//    ModelerControl controls[NUMCONTROLS];
//    controls[XPOS] = ModelerControl("X Position", -5, 5, 0.1f, 0);
//    controls[YPOS] = ModelerControl("Y Position", 0, 5, 0.1f, 0);
//    controls[ZPOS] = ModelerControl("Z Position", -5, 5, 0.1f, 0);
//    controls[HEIGHT] = ModelerControl("Height", 1, 2.5, 0.1f, 1);
//	controls[ROTATE] = ModelerControl("Rotate", -135, 135, 1, 0);
//
//    ModelerApplication::Instance()->Init(&createSampleModel, controls, NUMCONTROLS);
//    return ModelerApplication::Instance()->Run();
//}
//
