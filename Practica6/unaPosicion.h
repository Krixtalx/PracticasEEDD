#pragma once
class unaPosicion
{
	float x, y;
public:
	unaPosicion() { x = 0; y = 0; };
	unaPosicion(float _x, float _y) { x = _x; y = _y; };
	float getX() { return x; };
	float getY() { return y; };
};