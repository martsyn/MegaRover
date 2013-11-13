#pragma once

struct SensorValues
{
	short cpx;
	short cpy;
	short cpz;

	SensorValues() { }
	SensorValues(short cpx, short cpy, short cpz)
		: cpx(cpx), cpy(cpy), cpz(cpz) { }
};

class SensorSource
{
public:
	SensorSource(boost::asio::io_service &ioSvc);
	SensorValues read();

private:

	boost::asio::ip::tcp::socket source;
};
