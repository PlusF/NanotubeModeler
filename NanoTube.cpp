#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include "NanoTube.h"
#include "Atom.h"
#include "Bond.h"
#include "vectools.h"
using namespace std;


NanoTube::NanoTube(const int n, const int m, const string atom_type)
{
	if (n < m)
	{
		cout << "m must be shorter than n" << endl;
		exit(EXIT_FAILURE);
	}
	if (atom_type == "C")
	{
		this->atom_types = {"Carbon", "Carbon"};
	}
	else if (atom_type == "BN")
	{
		this->atom_types = {"Boron", "Nitrogen"};
	}
	else
	{
		cout << "atom type must be 'C' or 'BN'." << endl;
		exit(EXIT_FAILURE);
	}
	this->n = n;
	this->m = m;
	this->Ch = n * a1 + m * a2;
	this->dR = gcd(2 * m + n, 2 * n + m);
	this->t1 = (2 * m + n) / this->dR;
	this->t2 = -(2 * n + m) / this->dR;
	this->T = this->t1 * a1 + this->t2 * a2;
	this->l = 50 / norm(this->T) + 1;
	this->T *= (double) this->l;
	this->N = 2 * (n * n + n * m + m * m) / this->dR;
}

void NanoTube::place_atom()
{
	for (int i = 0; i < (this->n + this->t1 + 1) * this->l; i++)
	{
		for (int j = this->t2 * this->l; j < (this->m + 1) * this->l; j++)
		{
			vector<Atom> cell = make_cell(i, j, this->atom_types);
			if (check_inside(cell[0], this->Ch, this->T))
			{
				this->Atom_list.push_back(cell[0]);
			}
			if (check_inside(cell[1], this->Ch, this->T))
			{
				this->Atom_list.push_back(cell[1]);
			}
		}
	}

}

void NanoTube::tubize_all()
{
	// Chを基準に長方形→チューブ状に整形
	for (int i = 0; i < this->Atom_list.size(); i++)
	{
		this->Atom_list[i].tubize(this->Ch);
	}
}

void NanoTube::delete_dpl()
{
	vector<int> dpls;
	double distance;
	
	for (int i = 0; i < this->Atom_list.size(); i++)
	{
		for (int j = i + 1; j < this->Atom_list.size(); j++)
		{
			distance = norm(this->Atom_list[j].get_coord() - this->Atom_list[i].get_coord());
			if (distance < EPS)
			{
				dpls.push_back(j);
			}
		}
	}
	sort(dpls.begin(), dpls.end(), greater<int>());  // eraseで除くために降順で並べ替え
	for (int i = 0; i < dpls.size(); i++)
	{
		this->Atom_list.erase(this->Atom_list.begin() + dpls[i]);
	}
}

void NanoTube::find_bond()
{
	vector<double> coord_1, coord_2;
	double distance;
	
	// 全原子間の距離を計算し、aC_Cに近いペアをピックアップ
	for (int i = 0; i < this->Atom_list.size(); i++)
	{
		coord_1 = this->Atom_list[i].get_coord();
		for (int j = i + 1; j < this->Atom_list.size(); j++)
		{
			coord_2 = this->Atom_list[j].get_coord();
			distance = norm(coord_1 - coord_2);
			if (aC_C - 0.1 < distance && distance < aC_C + 0.1)
			{
				Bond b(coord_1, coord_2);
				this->Bond_list.push_back(b);
			}
		}
	}
}

void NanoTube::to_csv() const
{
	// for atoms
	string filename = "atoms_" + to_string(this->n) + "_" + to_string(this->m) + ".csv";
	vector<int> number = {0, 0, 0};  // B, C, N
	int type = 1;
	string name;
	double x, y, z;
	ofstream ofs1(filename.c_str());
	ofs1 << ",x,y,z" << endl;
	for (int i = 0; i < this->Atom_list.size(); i++)
	{
		name = this->Atom_list[i].get_name();
		if (name == "Boron") type = 0;
		else if (name == "Carbon") type = 1;
		else if (name == "Nitrogen") type = 2;
		name += "_" + to_string(number[type]);
		number[type] += 1;
		x = this->Atom_list[i].get_x();
		y = this->Atom_list[i].get_y();
		z = this->Atom_list[i].get_z();
		ofs1 << name << "," << x << "," << y << "," << z << endl;
	}

	// for bonds
	filename = "bonds_" + to_string(this->n) + "_" + to_string(this->m) + ".csv";
	ofstream ofs2(filename.c_str());
	vector<double> coord;
	vector<double> angle;
	ofs2 << ",x,y,z,theta_x,theta_y,theta_z" << endl;
	for (int i = 0; i < this->Bond_list.size(); i++)
	{
		name = "Bond_" + to_string(i);
		ofs2 << name;
		coord = this->Bond_list[i].get_coord();
		angle = this->Bond_list[i].get_angle();
		for (int j = 0; j < 3; j++)  // x, y, z
		{
			ofs2 << "," << coord[j];
		}
		for (int j = 0; j < 3; j++)  // theta_x, theta_y, theta_z
		{
			ofs2 << "," << angle[j];
		}
		ofs2 << endl;
	}

}

int gcd(const int a, const int b)
{
    if (a%b == 0)
    {
        return b;
    }
    else
    {
        return gcd(b, a%b);
    }
}
