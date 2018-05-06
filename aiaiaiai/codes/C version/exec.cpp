#include <iostream>
#include "func.h"
 double *OShift,*M,*y,*z,*x_bound;
 int ini_flag,n_flag,func_flag,*SS;
//---------------------------------------------------
 double x[N*D]; //存储每个粒子的位置 
 double v[N][D]; //存储每个例子的速度 
 double pBest[N*D]; //存储每个粒子的历史最佳位置
 double gBest[D]; //存储每次迭代后的全局最优位置 
 double fgBest; //存储gBest的适应值，即fpBest的最优值
 double fx[N]; //存储每个粒子的适应值
 double fpBest[N]; //存储每个pBest的适应值
//---------------------------------------------------
 double xx[N*D]; //存储每个粒子的位置
 double vv[N][D]; //变异 
 double uu[N*D]; //交叉 
 double f_xx[N]; //fitness(xx[i]) 存储xx中每个粒子的适应度
 double f_uu[N]; //fitness(uu[i]) 存储uu每个粒子的适应度
 double min_fitness; //存储粒子最优适应值
 double best_xx[D]; //存储粒子最优位置
//---------------------------------------------------
 double init[N*D]; //x和xx的初始化数组
 double funcnum; //存储当前函数序号
int main()
{
	Init_x();
	for (int i = 1; i <= 30; ++i)
	{
		funcnum = i;
		printf("f(%d):", i);
		if (i != 2) 
		{
			printf("\tPSO: "); 
			PSO();
			printf("\t\tDE: ");
			DE();
		}
		else printf("\tError!\n");
	}
	// funcnum = 1;
	// PSO();
	// DE();
	return 0;
}
