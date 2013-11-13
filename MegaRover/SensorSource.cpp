#include "stdafx.h"
#include "SensorSource.h"

const char *SerialPort =
#ifdef WIN32
	"COM3";
#elif
	"/dev/ttyACM0";
#endif

using namespace boost::asio;
using ip::tcp;

SensorSource::SensorSource(io_service &ioSvc)
	: source(ioSvc)
{
	tcp::resolver resolver(ioSvc);
	tcp::resolver::query query("192.168.137.130", "34678");
	connect(source, resolver.resolve(query));
}

SensorValues SensorSource::read()
{
	for (;;)
	{
		char c;
		::read(source, buffer(&c, 1));
		if (c == 0x3d)
		{
			::read(source, buffer(&c, 1));
			if (c == 0x5c)
				break;
		}
	}

	SensorValues s;
	::read(source, buffer(&s, sizeof(s)));

	return s;
}