/*
  CEC17 Test Function Suite for Single Objective Optimization
  Noor Awad (email: noor0029@ntu.edu.sg) 
  Sep. 10th 2016
*/

#include "cec17_test_func.cpp"
#include <WINDOWS.H>    
#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <random>
#include <bits/stdc++.h>
using namespace std;

void my_test(double *, double *, int, int, int);
void DE(double *, double *, int, int, int);
void PSO(int);
int get_one(int, int, int, int);
double _fi(double *,int, int, int);
double _cri(double *, int);

//void cec17_test_func(double *, double *,int,int,int);

double *OShift,*M,*y,*z,*x_bound;
int ini_flag=0,n_flag,func_flag,*SS;
/*int _mx = 50;
int _nx = 10;
double x[500];*/
double _min = -10;
double _max = 10;
int iter_times = 1000;
double F = 0.5;
double h[500]; //mutate
double cr = 0.8;
double v[500]; //cross
double Fl = 0.1;
double Fu = 0.9;
//double f[50];
double f_min;
double f_max;
double f_total;
double f_ave;
double x_best[10];
double fv[50];
double crl = 0.1;
double cru = 0.6;

double dx[5005]; //pos
double _f[505];	//value
double _v[5005];	//speed
double global_best_pos[505];
double global_best_val;
double local_best_pos[5005];
double local_best_val[505];
int dim = 2;	//dimension
int sz = 50;	//number
double pos_max = 10;
double pos_min = -10;
double v_max = 10;
double v_min = -10;
int times = 1000;

int main()
{
	int i,j,k,n,m,func_num;
	double *f,*x;
	FILE *fpt;
	char FileName[30];
	m=50;
	n=2;
	x=(double *)malloc(m*n*sizeof(double));
	f=(double *)malloc(sizeof(double)  *  m);

	for (i = 0; i < 10; i++)
	{
		func_num=i+1;
        if(func_num == 2) continue; 
		sprintf(FileName, "input_data/shift_data_%d.txt", func_num);
		fpt = fopen(FileName,"r");
		if (fpt==NULL)
		{
			printf("\n Error: Cannot open input file for reading \n");
		}
		
		printf("begin\n");

		if (x==NULL)
			printf("\nError: there is insufficient memory available!\n");

		for(k=0;k<n;k++)
		{
				fscanf(fpt,"%lf",&x[k]);
				//printf("%lf\n",x[k]);
		}

		

		fclose(fpt);

			for (j = 0; j < n; j++)
			{
				x[1*n+j]=0.0;
				//printf("%lf\n",x[1*n+j]);
			}
		
		
		for (k = 0; k < 1; k++)
		{
			cec17_test_func(x, f, n,m,func_num);
			for (j = 0; j < 2; j++)
			{
				//printf(" f%d(x[%d]) = %lf,",func_num,j+1,f[j]);
			}
			printf("\n");
		}
		printf("target\n");
		DE(x, f, m, n, func_num);
		printf("\nthen\n");
        srand(time(0));
        PSO(func_num);
	}
	free(x);
	free(f);
	free(y);
	free(z);
	free(M);
	free(OShift);
	free(x_bound);
    system("pause");
	return 0;
}

void DE(double *x, double *f, int _mx, int _nx, int _funcnum) {
    //(1)种群初始化
    for (int i = 0; i < _mx; i++) {
        for (int j = 0; j < _nx; j++) {
            x[i*_nx+j] = _min + (rand()%100/(double)101) * (_max - _min);
        }
    }
    
	printf("begin the %d func\n", _funcnum);

    for (int g = 0; g < iter_times; g++) {
        my_test(x, f, _nx, _mx, _funcnum);
        //cec17_test_func(x, f, _nx, _mx, _funcnum);
        f_min = 1e9;
        f_max = f[0];
        f_total = f[0];
        for (int j = 0; j < _nx; j++) {
            x_best[j] = x[j];
        }
        for (int i = 1; i < _mx; i++) {
            if(f_min > f[i]) {
                f_min = f[i];
                for (int j = 0; j < _nx; j++) {
                    x_best[j] = x[i*_nx+j];
                }
            }
            if(f_max < f[i]) {
                f_max = f[i];
            }
            f_total += f[i];
        }
        f_ave = f_total/_mx;
        if (g % 50 == 0)
        printf("iter times: %d, fitness :%f\n",g, f_min);
        //(2)变异
        for (int i = 0; i < _mx; i++) {
            int p1 = get_one(_mx, i, -1, -1);
            int p2 = get_one(_mx, i, p1, -1);
            int p3 = get_one(_mx, i, p1, p2);
            double Fi = _fi(f, p1, p2, p3);
            for (int j = 0; j < _nx; j++) {
                h[i*_nx+j] = x[p1*_nx+j] + Fi*(x[p2*_nx+j] - x[p3*_nx+j]);
            }
            //(3)交叉
            double cri = _cri(f, i);
            if ((rand()%100/(double)101) <= cri) {
                for (int j = 0; j < _nx; j++) {
                    v[i*_nx+j] = h[i*_nx+j];
                }
            }
            else {
                for (int j = 0; j < _nx; j++) {
                    v[i*_nx+j] = x[i*_nx+j];
                }
            }
        }
        //(4)选择
        my_test(v, fv, _nx, _mx, _funcnum);
        //cec17_test_func(v, fv, _nx, _mx, _funcnum);
        for (int i = 0; i < _mx; i++) {
            if (fv[i] < f[i]) {
                for (int j = 0; j < _nx; j++) {
                    x[i*_nx+j] = v[i*_nx+j];
                }
            }
        }
    }
    
    
}

int get_one(int _mx, int i = -1, int p1 = -1, int p2 = -1) {
    int r = rand() % _mx;
    while (r == i || r == p1 || r == p2) {
        r = rand() % _mx;
    }
    return r;
}

double _fi(double *f, int p1, int p2, int p3) {
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

double _cri(double *f, int i) {
    double cri = crl;
    if(f[i] > f_ave) {
        cri = crl + (cru - crl) * ((f[i]-f_min)/(f_max-f_min));
    }
    return cri;
}

void my_test(double *x, double *f, int nx, int mx, int func_num) {
    cec17_test_func(x, f, nx, mx, func_num);
    /*for (int i = 0; i < mx; i++) {
        double tmp = 0;
        for (int j = 0; j < nx; j++) {
            tmp += x[i*nx+j] * pow(-2, j);
        }
        f[i] = fabs(tmp);
    }*/
}

void PSO(int func_num){
	//��ʼ�� 
	global_best_val = 1e9;
	for(int i = 0; i < sz; i++){
		local_best_val[i] = 1e9;
		for(int j = 0; j < dim; j++){
			dx[i * dim + j] = pos_min + (pos_max - pos_min) * (rand() % 1001) / 1000;
			_v[i * dim + j] = v_min + (v_max - v_min) * (rand() % 1001) / 1000;
		}
	}
	//���� 
	for(int t = 0; t < times; t++){
		//cec17_test_func(dx, f, dim, sz, func_num);
		my_test(dx, _f, dim, sz, func_num);
		//�޸ľֲ���ȫ������ֵ 
		for(int i = 0; i < sz; i++){
			if(local_best_val[i] > _f[i]){
				for(int j = 0; j < dim; j++){
					local_best_pos[i * dim + j] = dx[i * dim + j];
				}
				local_best_val[i] = _f[i];
			}
			if(global_best_val > _f[i]){
				for(int j = 0; j < dim; j++){
					global_best_pos[j] = dx[i * dim + j];
				}
				global_best_val = _f[i];
			}
		}
		//�����ٶȲ��޸�����λ�� 
		for(int i = 0; i < sz; i++){
			for(int j = 0; j < dim; j++){
				double local_diff = local_best_pos[i * dim + j] - dx[i * dim + j];
				double global_diff = global_best_pos[j] - dx[i * dim + j];
				_v[i * dim + j] += 0.8 * (rand() % 10000 / 10000.0) * local_diff + 0.8 * (rand() % 10000 / 10000.0) * global_diff;
				dx[i * dim + j] += _v[i * dim + j];
			}
		}
        if (t % 50 == 0) {
		printf("Times: %d, Best: %.6f", t, global_best_val);
		//for(int i = 0; i < dim; i++){
			//printf("%.2f, ", global_best_pos[i]);
		//}
		puts("");
        }
	}
}