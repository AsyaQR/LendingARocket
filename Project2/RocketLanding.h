#pragma once

struct Rocket
{
private:

	float x, y, fuel,
		velocityX, velocityY,
		sidePower, centralPower;

public:

	Rocket(float x_ = 0, float y_ = 0, float fuel_ = 70) :
		x(x_), y(y_), fuel(fuel_),
		velocityX(0), velocityY(0),
		sidePower(0), centralPower(0) {}

	float getX()
	{
		return x;
	}

	float getY()
	{
		return y;
	}

	float getVelocityX()
	{
		return velocityX;
	}

	float getVelocityY()
	{
		return velocityY;
	}

	float getFuel()
	{
		return fuel;
	}

	float getSidePower()
	{
		return sidePower;
	}

	float getCentralPower()
	{
		return centralPower;
	}
	
	void setX(float coordinate)
	{
		x = coordinate;
	}

	void setY(float coordinate)
	{
		y = coordinate;
	}

	void setVelocityX(float velocity)
	{
		velocityX = velocity;
	}

	void setVelocityY(float velocity)
	{
		velocityY = velocity;
	}

	void setFuel(float fuel_)
	{
		fuel = fuel_;
	}

	void setSidePower(float power)
	{
		sidePower = power;
	}

	void setCentralPower(float power)
	{
		centralPower = power;
	}
};