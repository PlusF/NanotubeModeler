#ifndef VECTOOLS_H_
#define VECTOOLS_H_

#include <vector>
using namespace std;

vector<double>& operator+=(vector<double> &, const vector<double> &);

vector<double> operator+(const vector<double> &, const vector<double> &);

vector<double>& operator-=(vector<double> &, const vector<double> &);

vector<double> operator-(const vector<double> &, const vector<double> &);

vector<double>& operator*=(vector<double> &, const double);

vector<double> operator*(const vector<double> &, const double);

vector<double> operator*(const double, const vector<double> &);

vector<double>& operator/=(vector<double> &, const double);

vector<double> operator/(const vector<double> &, const double);

double dot(const vector<double>, const vector<double>);

double norm(const vector<double>);

vector<double> cross(const vector<double>, const vector<double>);

vector<double> mul_mat_vec(const vector< vector<double> >, const vector<double>);

vector< vector<double> > transpose_mat(const vector< vector<double> >);

vector< vector<double> > mul_mat(const vector< vector<double> >, const vector< vector<double> >);

vector<double> rotate_3d(const vector<double>, const vector<double>);

#endif // VECTOOLS_H_