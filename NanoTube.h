#ifndef NANOTUBE_H_
#define NANOTUBE_H_

#include <vector>
#include <cmath>
#include "Atom.h"
#include "Bond.h"
#include "vectools.h"
using namespace std;


class NanoTube
{
private:
	int n, m;
	vector<string> atom_types;
	vector<double> Ch;
	int dR;
	int t1;
	int t2;
	vector<double> T;
	int l;
	int N;

	vector<Atom> Atom_list;
	vector<Bond> Bond_list;
public:
	NanoTube(const int, const int, const string);
	void place_atom();
	void tubize_all();
	void delete_dpl();
	void find_bond();
	void to_csv() const;
};

int gcd(const int, const int);

#endif // NANOTUBE_H_