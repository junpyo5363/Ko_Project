#include "Switch.h"

Switch::Switch(float x, float y) {
	X = x;
	Y = y;

}
bool Switch::Click(float x, float y) {
	float a = (x > X) ? x - X : X - x;
	float b = (y > Y) ? y - Y : Y - y;
	if ((a < MAP::ROW*0.05) && (b < MAP::ROW*0.05)) return 1;
	return 0;
}