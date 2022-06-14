#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>
#include <string>
#include "NanoTube.h"
#include "Atom.h"
#include "vectools.h"
using namespace std;


Atom::Atom(vector<double> coord_init)
{
	this->coord = coord_init;
	this->name = "Carbon";
}

Atom::Atom(vector<double> coord_init, const string name)
{
	this->coord = coord_init;
	this->name = name;
}

double Atom::get_x() const {return this->coord[0];}
double Atom::get_y() const {return this->coord[1];}
double Atom::get_z() const {return this->coord[2];}
vector<double> Atom::get_coord() const {return this->coord;}
string Atom::get_name() const {return this->name;}

void Atom::print() const
{
	cout
	<< setw(16) << "x"
	<< setw(16) << "y"
	<< setw(16) << "z"
	<< endl;
	cout << fixed;
	cout
	<< setw(16) << setprecision(2) << this->coord[0]
	<< setw(16) << setprecision(2) << this->coord[1]
	<< setw(16) << setprecision(2) << this->coord[2]
	<< endl;
}

void Atom::preprocess(const vector<double> Ch)
{
	double cos = Ch[0] / norm(Ch);
	double sin = Ch[1] / norm(Ch);
	double x1 = cos * coord[0] + sin * coord[1];
	double y1 = -sin * coord[0] + cos * coord[1];
	coord[0] = x1;
	coord[1] = y1;
}

void Atom::tubize(const vector<double> Ch)
{
	this->preprocess(Ch);

	double pi = 3.141592653589793;
	double theta = this->coord[0] / norm(Ch) * 2 * pi;

	this->coord[0] = sin(theta) * norm(Ch) / pi / 2;
	this->coord[2] = cos(theta) * norm(Ch) / pi / 2;
}

vector<Atom> make_cell(const int n, const int m, const vector<string> atom_types)
{
	vector<double> next = {aC_C, 0, 0};
	vector<double> coord_1 = n * a1 + m * a2;
	vector<double> coord_2 = coord_1 + next;
	Atom ret_1(coord_1, atom_types[0]);
	Atom ret_2(coord_2, atom_types[1]);
	vector<Atom> ret = {ret_1, ret_2};
	return ret;
}

bool check_inside(const Atom a, const vector<double> Ch, const vector<double> T)
{
	vector<double> origin = {0, 0, 0};
	vector<double> coord = a.get_coord();
	vector<double> vec1 = origin - coord;
	vector<double> vec2 = Ch - coord;
	vector<double> vec3 = Ch + T - coord;
	vector<double> vec4 = T - coord;

	double val1 = cross(vec1, vec2)[2];
	double val2 = cross(vec2, vec3)[2];
	double val3 = cross(vec3, vec4)[2];
	double val4 = cross(vec4, vec1)[2];

	if (val1 > - EPS && val2 > - EPS && val3 > - EPS && val4 > - EPS)
	{
		return true;
	}
	return false;
}
