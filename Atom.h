#ifndef ATOM_H_
#define ATOM_H_

#include <vector>
#include <string>
using namespace std;

const double aC_C = 1.42;
const double a = aC_C * sqrt(3);
const vector<double> a1 = {0.5 * sqrt(3) * a,  0.5 * a, 0};
const vector<double> a2 = {0.5 * sqrt(3) * a, -0.5 * a, 0};

#define EPS 0.00001

class Atom
{
private:
	vector<double> coord;
    string name;
public:
	double get_x() const;
	double get_y() const;
	double get_z() const;
    vector<double> get_coord() const;
    string get_name() const;
    void preprocess(const vector<double>);
	void tubize(const vector<double>);
	void print() const;
	Atom(vector<double>);
	Atom(vector<double>, string);
};

vector<Atom> make_cell(const int, const int, const vector<string>);

bool check_inside(const Atom, const vector<double>, const vector<double>);

#endif // ATOM_H_