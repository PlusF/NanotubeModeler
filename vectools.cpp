#include <iostream>
#include <vector>
#include <cmath>
#include "vectools.h"
using namespace std;

vector<double>& operator+=(vector<double> &self, const vector<double> &other)
{
    if (self.size() != other.size()){
        cout << "can't calc plus(+) between different shape vector" << endl;
        exit(EXIT_FAILURE);
    }
	for (int i = 0; i < (int)self.size(); i++)
	{
		self[i] += other[i];
	}
    return self;
}

vector<double> operator+(const vector<double> &self, const vector<double> &other)
{
	vector<double> result = self;
	result += other;
	return result;
}

vector<double>& operator-=(vector<double> &self, const vector<double> &other)
{
    if (self.size() != other.size()){
        cout << "can't calc minus(-) between different shape vector" << endl;
        exit(EXIT_FAILURE);
    }
	for (int i = 0; i < (int)self.size(); i++)
	{
		self[i] -= other[i];
	}
    return self;
}

vector<double> operator-(const vector<double> &self, const vector<double> &other)
{
	vector<double> result = self;
	result -= other;
	return result;
}

vector<double>& operator*=(vector<double> &self, const double a)
{
	for (int i = 0; i < (int)self.size(); i++)
	{
		self[i] *= a;
	}
    return self;
}

vector<double> operator*(const vector<double> &self, const double a)
{
	vector<double> result = self;
	result *= a;
	return result;
}

vector<double> operator*(const double a, const vector<double> &self)
{
	vector<double> result = self;
	result *= a;
	return result;
}

vector<double>& operator/=(vector<double> &self, const double a)
{
	for (int i = 0; i < (int)self.size(); i++)
	{
		self[i] /= a;
	}
    return self;
}

vector<double> operator/(const vector<double> &self, const double a)
{
	vector<double> result = self;
	result /= a;
	return result;
}

double dot(const vector<double> vec1, const vector<double> vec2)
{
    if (vec1.size() != vec2.size()){
        cout << "can't calc dot between different shape vector" << endl;
        exit(EXIT_FAILURE);
    }
    double sum = 0;
    for (int i = 0; i < vec1.size(); i++)
    {
        sum += vec1[i] * vec2[i];
    }
	return sum;
}

double norm(const vector<double> vec)
{
	return sqrt(dot(vec, vec));
}

vector<double> cross(const vector<double> vec1, const vector<double> vec2)
{
    if (vec1.size() != 3 || vec2.size() != 3)
    {
        cout << "can't calc cross between such vectors" << endl;
        exit(EXIT_FAILURE);
    }

    vector<double> result(3);
	result[0] =  vec1[1] * vec2[2] - vec1[2] * vec2[1];
	result[1] =  vec1[2] * vec2[0] - vec1[0] * vec2[2];
	result[2] =  vec1[0] * vec2[1] - vec1[1] * vec2[0];

    return result;
}

vector<double> mul_mat_vec(const vector< vector<double> > mat, const vector<double> vec)
{
    if (mat[0].size() != vec.size())
    {
        cout << "can't multiply between such matrix and vector" << endl;
        exit(EXIT_FAILURE);
    }
    vector<double> result(vec.size());
    for (int i = 0; i < mat.size(); i++)
    {
        result[i] = dot(mat[i], vec);
    }

    return result;
}

vector< vector<double> > transpose_mat(const vector< vector<double> > mat)
{
    vector< vector<double> > result;
    vector<double> row;
    for (int i = 0; i < mat[0].size(); i++)
    {
        row.clear();
        for (int j = 0; j < mat.size(); j++)
        {
            row.push_back(mat[j][i]);
        }
        result.push_back(row);
    }

    return result;
}

vector< vector<double> > mul_mat(const vector< vector<double> > mat_1, const vector< vector<double> > mat_2)
{
    if (mat_1[0].size() != mat_2.size())
    {
        cout << "can't multiply between such matrixes" << endl;
        exit(EXIT_FAILURE);
    }

    vector< vector<double> > result;
    vector< vector<double> > mat_2_t = transpose_mat(mat_2);
    vector<double> row;
    for (int i = 0; i < mat_1.size(); i++)
    {
        row.clear();
        for (int j = 0; j < mat_2_t.size(); j++)
        {
            row.push_back(dot(mat_1[i], mat_2_t[j]));
        }
        result.push_back(row);
    }

    return result;
}

vector<double> rotate_3d(const vector<double> coord, const vector<double> angle)
{
    double px = angle[0];
    double py = angle[1];
    double pz = angle[2];

    vector< vector<double> > Rx = {
        {1, 0, 0},
        {0, cos(px), sin(px)},
        {0, -sin(px), cos(px)}
    };
    vector< vector<double> > Ry = {
        {cos(py), 0, -sin(py)},
        {0, 1, 0},
        {sin(py), 0, cos(py)}
    };
    vector< vector<double> > Rz = {
        {cos(pz), sin(pz), 0},
        {-sin(pz), cos(pz), 0},
        {0, 0, 1}
    };

    vector < vector<double> > R = mul_mat(Rz, Ry);
    R = mul_mat(R, Rx);

    return mul_mat_vec(R, coord);
}
