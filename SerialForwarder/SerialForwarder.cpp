// SerialForwarder.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
const char *SerialPort = 
#ifdef WIN32
"COM3";
#else
	"/dev/ttyACM0";
#endif

using namespace boost::asio;
using boost::asio::ip::tcp;


#ifdef UNICODE
int wmain()
#else
int main()
#endif
{
	io_service ioSvc;
	serial_port serial(ioSvc, SerialPort);
	serial.set_option(serial_port_base::baud_rate(115200));

	tcp::acceptor acc(ioSvc, tcp::endpoint(tcp::v4(), 34678));

	tcp::socket sock(ioSvc);
	acc.accept(sock);

	char space[8];
	for (;;)
	{
		int count = read(serial, buffer(space, sizeof(space)));
		if (count == 0)
			break;

		write(sock, buffer(space, sizeof(space)));
	}
	
	return 0;
}

