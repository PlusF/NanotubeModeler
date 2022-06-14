#include <vector>
#include <cmath>
#include "Bond.h"
#include "vectools.h"
using namespace std;

Bond::Bond(const vector<double> coord_1, const vector<double> coord_2)
{
	this->coord = (coord_1 + coord_2) / 2;
	vector<double> theta_y_z = calc_rotation(coord_1, coord_2);
	this->angle = {0, theta_y_z[0], theta_y_z[1]};
}

vector<double> Bond::get_coord() const {return this->coord;}
vector<double> Bond::get_angle() const {return this->angle;}

vector<double> calc_rotation(vector<double> coord_1, vector<double> coord_2)
{
	vector<double> theta_y_z(2);

	if (coord_1[2] < coord_2[2])
	{
		vector<double> coord_tmp = coord_1;
		coord_1 = coord_2;
		coord_2 = coord_tmp;
	}

	vector<double> center = (coord_1 + coord_2) / 2;
	double length = norm(coord_1 - coord_2);
	double theta_y = acos((coord_1[2] - center[2]) / (length / 2));

	vector<double> half = {0, 0, length / 2};
	vector<double> before_1 = center + half;
	vector<double> before_2 = center - half;

	vector<double> angle = {0, theta_y, 0};
	vector<double> mid_1 = rotate_3d((before_1 - center), angle) + center;
	vector<double> mid_2 = rotate_3d((before_2 - center), angle) + center;

	double theta_loc = atan2(coord_1[1] - center[1], coord_1[0] - center[0]);
	double theta_mid = atan2(mid_1[1] - center[1], mid_1[0] - center[0]);
	double theta_z = theta_loc - theta_mid;

	theta_y_z[0] = -theta_y;
	theta_y_z[1] = theta_z;

	return theta_y_z;
}