#include "cec17_test_func.cpp"
#include <random>
#include <iostream>
using namespace std;

void my_test(double *, double *, int, int, int);
void DE(int);
int get_one(int, int, int);
double _fi(int, int, int);
double _cri(int);

int _mx = 50;
int _nx = 10;
double x[500];
double _min = -100;
double _max = 100;
int iter_times = 10000;
double F = 0.5;
double h[500]; //mutate
double cr = 0.8;
double v[500]; //cross
double Fl = 0.1;
double Fu = 0.9;
double f[50];
double f_min;
double f_max;
double f_total;
double f_ave;
double x_best[10];
double fv[50];
double crl = 0.1;
double cru = 0.6;

int main() {
    DE(1);
    return 0;
}

void DE(int _funcnum) {
    //(1)种群初始化
    for (int i = 0; i < _mx; i++) {
        for (int j = 0; j < _nx; j++) {
            x[i*_mx+j] = _min + (rand()%100/(double)101) * (_max - _min);
        }
    }
    
    for (int g = 0; g < iter_times; g++) {
        cec17_test_func(x, f, _nx, _mx, _funcnum);
        f_min = f[0];
        f_max = f[0];
        f_total = f[0];
        for (int j = 0; j < _nx; j++) {
            x_best[j] = x[j];
        }
        for (int i = 1; i < _mx; i++) {
            if(f_min > f[i]) {
                f_min = f[i];
                for (int j = 0; j < _nx; j++) {
                    x_best[j] = x[i*_mx+j];
                }
            }
            if(f_max < f[i]) {
                f_max = f[i];
            }
            f_total += f[i];
        }
        f_ave = f_total/_mx;
        cout << "iter times: " << g << ", fitness :" << f_min << endl;
        //(2)变异
        for (int i = 0; i < _mx; i++) {
            int p1 = get_one(i, -1, -1);
            int p2 = get_one(i, p1, -1);
            int p3 = get_one(i, p1, p2);
            double Fi = _fi(p1, p2, p3);
            for (int j = 0; j < _nx; j++) {
                h[i*_mx+j] = x[p1*_mx+j] + Fi*(x[p2*_mx+j] - x[p3*_mx+j]);
            }
            //(3)交叉
            double cri = _cri(i);
            if ((rand()%100/(double)101) <= cri) {
                for (int j = 0; j < _nx; j++) {
                    v[i*_mx+j] = h[i*_mx+j];
                }
            }
            else {
                for (int j = 0; j < _nx; j++) {
                    v[i*_mx+j] = x[i*_mx+j];
                }
            }
        }
        //(4)选择
        cec17_test_func(v, fv, _nx, _mx, _funcnum);
        for (int i = 0; i < _mx; i++) {
            if (fv[i] < f[i]) {
                for (int j = 0; j < _nx; j++) {
                    x[i*_mx+j] = v[i*_mx+j];
                }
            }
        }
    }
    
    
}

int get_one(int i = -1, int p1 = -1, int p2 = -1) {
    int r = rand() % _mx;
    while (r == i || r == p1 || r == p2) {
        r = rand() % _mx;
    }
    return r;
}

double _fi(int p1, int p2, int p3) {
    double fb, fm, fw;
    if (f[p1] < f[p2]) {
        if (f[p1] < f[p3]) {
            fb = f[p1];
            fm = (f[p2] < f[p3]) ? f[p2] : f[p3];
            fw = (f[p2] >= f[p3]) ? f[p2] : f[p3];
        }
        else {
            fb = f[p3];
            fm = f[p1];
            fw = f[p2];
        }
    }
    else {
        if (f[p2] < f[p3]) {
            fb = f[p2];
            fm = (f[p1] < f[p3]) ? f[p1] : f[p3];
            fw = (f[p1] >= f[p3]) ? f[p1] : f[p3];
        }
        else {
            fb = f[p3];
            fm = f[p2];
            fw = f[p1];
        }
    }
    double fi = Fl + (Fu - Fl)*((fm-fb)/(fw-fb));
    return fi;
}

double _cri(int i) {
    double cri = crl;
    if(f[i] > f_ave) {
        cri = crl + (cru - crl) * ((f[i]-f_min)/(f_max-f_min));
    }
    return cri;
}

void my_test(double *x, double *f, int nx, int mx, int func_num) {
    for (int i = 0; i < mx; i++) {
        int tmp = 0;
        for (int j = 0; j < nx; j++) {
            tmp += x[j] * pow(-2, j);
        }
        f[i] = tmp;
    }
}