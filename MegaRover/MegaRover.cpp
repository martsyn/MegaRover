// MegaRover.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "SimulatedSensorSource.h"

using namespace std;
using namespace boost::asio;


void glfwErrorCallback(int error, const char* description)
{
	cerr << description << endl;
}

int _tmain()
{
	io_service ioSvc;

	if (!glfwInit())
		return -1;

	glfwSetErrorCallback(glfwErrorCallback);

	auto window = glfwCreateWindow(640, 640, "Hellow", nullptr, nullptr);

	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	
	glfwMakeContextCurrent(window);

	//SimulatedSensorSource src(ioSvc);
	SimulatedSensorSource src;

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.f, 0.2f, 0.2f, 0.f);
		glClear(GL_COLOR_BUFFER_BIT);

		auto s = src.read();

		float len = sqrtf((float) s.cpx*s.cpx + s.cpy*s.cpy /*+ s.cpz*s.cpz*/);
		float angle = atan2f(s.cpy, s.cpx);
		cout << "X=" << s.cpx << "\tY=" << s.cpy << "\tZ=" << s.cpz << " len=" << len << " angle=" << angle << endl;

		glMatrixMode (GL_PROJECTION);
		glLoadIdentity();
		glOrtho (-10, 10, -10, 10, 0, 1);
		glMatrixMode (GL_MODELVIEW);
		glDisable(GL_DEPTH_TEST);


		glBegin(GL_LINES);
		glVertex2f(0, 0) ;
		float scale = 5.0f/len;
		glVertex3f(s.cpy*scale, s.cpx*scale, /*s.cpz*scale*/ 0);
		glEnd();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

