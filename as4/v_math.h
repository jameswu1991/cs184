#ifndef v_math_h
#define v_math_h

#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>
#include <math.h>

using namespace std;

void v_print(vector<float> a);
vector<float> getVector(float x, float y, float z);
vector<float> getVector(float r[], int length);

vector<float> v_scale(vector<float> v, float s);
vector<float> v_add(vector<float> v, vector<float> w);
vector<float> v_sub(vector<float> v, vector<float> w);
vector<float> v_mul(vector<float> v, vector<float> w);

float v_sum(vector<float> v);
float magnitude(vector<float> v);
float dot(vector<float> x, vector<float> y);
vector<float> normalize(vector<float> v);

float getZ(float x, float y, float radius);
vector<float> reflection(vector<float> light, vector<float> surface_normal);

#endif