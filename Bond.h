#ifndef BOND_H_
#define BOND_H_

#include <vector>
using namespace std;

class Bond
{
private:
	vector<double> coord;
	vector<double> angle;
public:
	Bond(const vector<double>, const vector<double>);
	vector<double> get_coord() const;
	vector<double> get_angle() const;
};

vector<double> calc_rotation(vector<double>, vector<double>);

#endif //BOND_H_