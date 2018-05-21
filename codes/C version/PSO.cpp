#include <bits/stdc++.h>
//#include "cec17_test_func.cpp"
using namespace std;

double dx[5005]; //pos
double f[505];	//value
double v[5005];	//speed
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
int times = 100;

void fx(double *x, double *f, int dim, int sz, int num){
	for(int i = 0; i < sz; i++){
		f[i] = 0; 
		for(int j = 0; j < dim; j++){
			f[i] += x[i * dim + j] * x[i * dim + j];
		}
	}
}

void PSO(int func_num){
	//��ʼ�� 
	global_best_val = 1e9;
	for(int i = 0; i < sz; i++){
		local_best_val[i] = 1e9;
		for(int j = 0; j < dim; j++){
			dx[i * dim + j] = pos_min + (pos_max - pos_min) * (rand() % 1001) / 1000;
			v[i * dim + j] = v_min + (v_max - v_min) * (rand() % 1001) / 1000;
		}
	}
	//���� 
	for(int t = 0; t < times; t++){
		//cec17_test_func(dx, f, dim, sz, func_num);
		fx(dx, f, dim, sz, func_num);
		//�޸ľֲ���ȫ������ֵ 
		for(int i = 0; i < sz; i++){
			if(local_best_val[i] > f[i]){
				for(int j = 0; j < dim; j++){
					local_best_pos[i * dim + j] = dx[i * dim + j];
				}
				local_best_val[i] = f[i];
			}
			if(global_best_val > f[i]){
				for(int j = 0; j < dim; j++){
					global_best_pos[j] = dx[i * dim + j];
				}
				global_best_val = f[i];
			}
		}
		//�����ٶȲ��޸�����λ�� 
		for(int i = 0; i < sz; i++){
			for(int j = 0; j < dim; j++){
				double local_diff = local_best_pos[i * dim + j] - dx[i * dim + j];
				double global_diff = global_best_pos[j] - dx[i * dim + j];
				v[i * dim + j] += 2.0 * (rand() % 10000 / 10000.0) * local_diff + 2.0 * (rand() % 10000 / 10000.0) * global_diff;
				dx[i * dim + j] += v[i * dim + j];
			}
		}
		printf("Times: %d, Best: %.6f\n", t, global_best_val);
		for(int i = 0; i < dim; i++){
			printf("%.2f, ", global_best_pos[i]);
		}
		puts("");
	}
}

int main(){
	srand(time(0));
	PSO(1);
	system("pause");
}
