// MegaRover.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

using namespace std;
using namespace boost::asio;
using boost::asio::ip::tcp;


struct Sensors
{
	short cpx;
	short cpy;
	short cpz;
};

const char *SerialPort = 
#ifdef WIN32
	"COM3";
#elif
	"/dev/ttyACM0";
#endif

#ifdef UNICODE
int wmain()
#elif
int main()
#endif
{
	io_service ioSvc;

	//serial_port source(ioSvc, SerialPort);
	//source.set_option(serial_port_base::baud_rate(115200));


	tcp::socket source(ioSvc);
	tcp::resolver resolver(ioSvc);
	tcp::resolver::query query("192.168.137.130", "34678");
	connect(source, resolver.resolve(query));

	glfwInit();

	const int XSize = 640, YSize = 640;

	glfwOpenWindow(XSize, YSize, 0, 0, 0, 0, 0, 0, GLFW_WINDOW);

	do
	{
		glClear(GL_COLOR_BUFFER_BIT);

		char c;
		read(source, buffer(&c, 1));
		if (c != 0x3d)
			continue;
		
		read(source, buffer(&c, 1));
		if (c != 0x5c)
			continue;

		Sensors s;
		read(source, buffer(&s,sizeof(s)));

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

		glfwSwapBuffers();
	} while (glfwGetWindowParam(GLFW_OPENED));

	glfwTerminate();
	return 0;
}

