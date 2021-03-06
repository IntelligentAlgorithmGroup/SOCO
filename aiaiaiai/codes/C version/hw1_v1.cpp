/*
  CEC17 Test Function Suite for Single Objective Optimization
  Noor Awad (email: noor0029@ntu.edu.sg) 
  Dec. 20th 2013
*/


//#include <WINDOWS.H>      
#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <time.h>
#include <float.h>

#define INF 1.0e99
#define EPS 1.0e-14
#define E  2.7182818284590452353602874713526625
#define PI 3.1415926535897932384626433832795029

#define N 50 //种群大小 mx
#define D 10 //维数 nx
#define c1 2.0  //加速系数 
#define c2 2.0  //加速系数 
#define w_start 0.9 //惯量权重上界 
#define w_end 0.4 //惯量权重下限 
#define NUM_OF_ITERATOR 1000 //迭代次数 
#define V_max 15  //速度的最大上限 
#define X_max 100 //位置范围的上限 
#define X_min -100 //位置范围的下限 
#define DOUBLE_MAX DBL_MAX //DBL_MAX在float.h中有定义

#define F 0.5 //缩放因子
#define CR 0.8 //杂交控制参数 

void sphere_func (double *, double *, int , double *,double *, int, int); /* Sphere */
void ellips_func(double *, double *, int , double *,double *, int, int); /* Ellipsoidal */
void bent_cigar_func(double *, double *, int , double *,double *, int, int); /* Discus */
void discus_func(double *, double *, int , double *,double *, int, int);  /* Bent_Cigar */
void dif_powers_func(double *, double *, int , double *,double *, int, int);  /* Different Powers */
void rosenbrock_func (double *, double *, int , double *,double *, int, int); /* Rosenbrock's */
void schaffer_F7_func (double *, double *, int , double *,double *, int, int); /* Schwefel's F7 */
void ackley_func (double *, double *, int , double *,double *, int, int); /* Ackley's */
void rastrigin_func (double *, double *, int , double *,double *, int, int); /* Rastrigin's  */
void weierstrass_func (double *, double *, int , double *,double *, int, int); /* Weierstrass's  */
void griewank_func (double *, double *, int , double *,double *, int, int); /* Griewank's  */
void schwefel_func (double *, double *, int , double *,double *, int, int); /* Schwefel's */
void katsuura_func (double *, double *, int , double *,double *, int, int); /* Katsuura */
void bi_rastrigin_func (double *, double *, int , double *,double *, int, int); /* Lunacek Bi_rastrigin */
void grie_rosen_func (double *, double *, int , double *,double *, int, int); /* Griewank-Rosenbrock  */
void escaffer6_func (double *, double *, int , double *,double *, int, int); /* Expanded Scaffer¡¯s F6  */
void step_rastrigin_func (double *, double *, int , double *,double *, int, int); /* Noncontinuous Rastrigin's  */
void happycat_func (double *, double *, int , double *,double *, int, int); /* HappyCat */
void hgbat_func (double *, double *, int , double *,double *, int, int); /* HGBat  */

/* New functions Noor Changes */
void sum_diff_pow_func(double *, double *, int , double *,double *, int, int); /* Sum of different power */
void zakharov_func(double *, double *, int , double *,double *, int, int); /* ZAKHAROV */
void levy_func(double *, double *, int , double *,double *, int, int); /* Levy */
void dixon_price_func(double *, double *, int , double *,double *, int, int); /* Dixon and Price */

void hf01 (double *, double *, int, double *,double *, int *,int, int); /* Hybrid Function 1 */
void hf02 (double *, double *, int, double *,double *, int *,int, int); /* Hybrid Function 2 */
void hf03 (double *, double *, int, double *,double *, int *,int, int); /* Hybrid Function 3 */
void hf04 (double *, double *, int, double *,double *, int *,int, int); /* Hybrid Function 4 */
void hf05 (double *, double *, int, double *,double *, int *,int, int); /* Hybrid Function 5 */
void hf06 (double *, double *, int, double *,double *, int *,int, int); /* Hybrid Function 6 */
void hf07 (double *, double *, int, double *,double *, int *,int, int); /* Hybrid Function 7 */
void hf08 (double *, double *, int, double *,double *, int *,int, int); /* Hybrid Function 8 */
void hf09 (double *, double *, int, double *,double *, int *,int, int); /* Hybrid Function 9 */
void hf10 (double *, double *, int, double *,double *, int *,int, int); /* Hybrid Function 10 */

void cf01 (double *, double *, int , double *,double *, int); /* Composition Function 1 */
void cf02 (double *, double *, int , double *,double *, int); /* Composition Function 2 */
void cf03 (double *, double *, int , double *,double *, int); /* Composition Function 3 */
void cf04 (double *, double *, int , double *,double *, int); /* Composition Function 4 */
void cf05 (double *, double *, int , double *,double *, int); /* Composition Function 5 */
void cf06 (double *, double *, int , double *,double *, int); /* Composition Function 6 */
void cf07 (double *, double *, int , double *,double *, int); /* Composition Function 7 */
void cf08 (double *, double *, int , double *,double *, int); /* Composition Function 8 */
void cf09 (double *, double *, int , double *,double *, int *, int); /* Composition Function 9 */
void cf10 (double *, double *, int , double *,double *, int *, int); /* Composition Function 10 */

void shiftfunc (double*,double*,int,double*);
void rotatefunc (double*,double*,int, double*);
void sr_func (double *, double *, int, double*, double*, double, int, int); /* shift and rotate */
void asyfunc (double *, double *x, int, double);
void oszfunc (double *, double *, int);
void cf_cal(double *, double *, int, double *,double *,double *,double *,int);

void cec17_test_func(double *x, double *f, int nx, int mx,int func_num);
void PSO();
void DE();
void Init_x();

double *OShift,*M,*y,*z,*x_bound;
int ini_flag=0,n_flag,func_flag,*SS;
//-------------------------------------------------------
double x[N*D]; //存储每个粒子的位置 
double v[N][D]; //存储每个例子的速度 
double pBest[N*D]; //存储每个粒子的历史最佳位置
double gBest[D]; //存储每次迭代后的全局最优位置 
double fgBest; //存储gBest的适应值，即fpBest的最优值
double fx[N]; //存储每个粒子的适应值
double fpBest[N]; //存储每个pBest的适应值
//-------------------------------------------------------
double xx[N*D]; //存储每个粒子的位置
double vv[N][D]; //变异 
double uu[N*D]; //交叉 
double f_xx[N]; //fitness(xx[i]) 存储xx中每个粒子的适应度
double f_uu[N]; //fitness(uu[i]) 存储uu每个粒子的适应度
double min_fitness; //存储粒子最优适应值
double best_xx[D]; //存储粒子最优位置
//-------------------------------------------------------
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

void Init_x()
{
	srand(time(0));
	for(int i = 0; i < N; i++)
	{
		for(int j = 0; j < D; j++)
		{
			init[i*D+j] = 200.0*rand()/RAND_MAX - 100; //(-100到100)
		}
	}
}

void PSO()
{
	srand(time(0));
	for(int i = 0; i < N; i++)
	{
		for(int j = 0; j < D; j++)
		{
			v[i][j] = 30.0*rand()/RAND_MAX - 15;
			// x[i][j] = 200.0*rand()/RAND_MAX - 100; 
			// x[i*D+j] = 200.0*rand()/RAND_MAX - 100; 
			x[i*D+j] = init[i*D+j];
			pBest[i*D+j] = x[i*D+j];
		}
	}
	//计算每个粒子适应值，找出全局最优位置 
	cec17_test_func(x, fx, D, N, funcnum); 
	cec17_test_func(pBest, fpBest, D, N, funcnum); 
	int min_index = -1;
	double min_value = DOUBLE_MAX;
	//初始化之后第一次寻找gBest
	for(int i = 0; i < N; i++)
	{
		// double shiying = fit(x[i]);
		double shiying = fpBest[i];
		if(shiying < min_value)
		{
			min_value = shiying;
			min_index = i;
		}
	} 
	for(int i = 0; i < D; i++)
	   gBest[i] = pBest[min_index*D+i];
	fgBest = fpBest[min_index];

	//在这里打印fit(gBest); 
	for(int i = 0; i < NUM_OF_ITERATOR; i++)
	{
	 	double w = w_end + (w_start - w_end)*(NUM_OF_ITERATOR-i)/NUM_OF_ITERATOR;
	 	for(int j = 0; j < N; j++)
	 	{
	 		for(int k = 0; k < D; k++)
	 		{
	 			double rand1 =  ((double)rand())/RAND_MAX;
	 			double rand2 =  ((double)rand())/RAND_MAX;
	 			//更新速度 
	 			v[j][k] = w * v[j][k] + c1 * rand1 * (pBest[j*D+k]-x[j*D+k]) + c2 * rand2 * (gBest[k] - x[j*D+k]);
	 			if(v[j][k] > V_max)//看看速度是否超出最大范围 
	 			  	v[j][k] = V_max;
	 			if(v[j][k] < -V_max)
	 			  	v[j][k] = -V_max;
	 			x[j*D+k] = x[j*D+k] + v[j][k];//更新位置 
	 			if(x[j*D+k] > X_max)//检查位置是否越界 
	 			  	x[j*D+k] = X_max;
	 			if(x[j*D+k] < X_min)
	 			  	x[j*D+k] = X_min;
			 }
			//计算粒子的新位置的适应度
			cec17_test_func(x, fx, D, N, funcnum);
			// if(fit(pBest[j]) > fit(x[j]))
			if (fpBest[j] > fx[j])
			{
				for(int t = 0; t < D; t++)
					pBest[j*D+t] = x[j*D+t];
				fpBest[j] = fx[j];
			}
			// if(fit(pBest[j]) < fit(gBest))
			if (fpBest[j] < fgBest)
			{
				for(int t = 0; t < D; t++)
					gBest[t] = pBest[j*D+t];
				fgBest = fpBest[j];
			}
		}
		//一次迭代完成，打印出全局最佳位置的适应度
		// printf("%lf\n",fit(gBest)); 
		if (i == NUM_OF_ITERATOR - 1) 
		{
			printf("%lf", fgBest);
		}
	}
}

void DE()
{
	srand(time(0));
	//初始化
	for(int i = 0; i < N; i++)
	{
		for(int j = 0; j < D; j++)
		{
			// xx[i*D+j] = X_min + 1.0*rand()/RAND_MAX*(X_max-X_min);
			xx[i*D+j] = init[i*D+j];
		}
	}

	cec17_test_func(xx, f_xx, D, N, funcnum);

	//最小适应值
	min_fitness = DOUBLE_MAX;
	for(int i = 0; i < N; i++)
	{
		// if(min_fitness > fitness[i])
			// min_fitness = fitness[i];
		if (min_fitness > f_xx[i])
		{
			min_fitness = f_xx[i];
			for (int k = 0; k < D; ++k)
				best_xx[k] = xx[i*D+k];
		}

	 }

	 //打印初始最小适应值
	for(int i = 0; i < NUM_OF_ITERATOR; i++)
	{
		//变异操作 
		for(int j = 0; j < N; j++)
		{
			int r1 = rand() % N;
			int r2 = rand() % N;
			int r3 = rand() % N;
			for(int k = 0; k < D; k++)
			{
				vv[j][k] = xx[r1*D+k] + F * (xx[r2*D+k] - xx[r3*D+k]); 
			}
			//交叉
			double p = rand()*1.0/RAND_MAX;
			if(p <= CR)
			{
				for(int k = 0; k < D; k++)
				  uu[j*D+k] = vv[j][k];
			} 
			else
			{
				for(int k = 0; k < D; k++)
				  uu[j*D+k] = xx[j*D+k];
			}
		}

		cec17_test_func(uu, f_uu, D, N, funcnum);
		for (int j = 0; j < N; ++j)
		{
			//选择
			// if(fit(uu[j]) <= fit(xx[j]))
			if (f_uu[j] <= f_xx[j])
			{
				for(int k = 0; k < D; k++)
			    	xx[j*D+k] = uu[j*D+k];	
			    f_xx[j] = f_uu[j];
			    // fitness[j] = f_xx[j];
			} 
			// fitness[j] = fit(xx[j]);
		}

		//得到每一代的最优适应值
		min_fitness = DOUBLE_MAX;
		for(int j = 0; j < N; j++)
		{
			// if(fitness[j] < min_fitness)
			// 	min_fitness = fitness[j];
			if (min_fitness > f_xx[j])
			{
				min_fitness = f_xx[j];
				for (int k = 0; k < D; ++k)
					best_xx[k] = xx[j*D+k];
			}
		} 
		//打印min_fitness; 
		if (i == NUM_OF_ITERATOR-1) 
		{
			printf("%lf\n", min_fitness);
		}
	}	
}

void cec17_test_func(double *x, double *f, int nx, int mx,int func_num)
{
	int cf_num=10,i,j;
	if (ini_flag==1)
	{
		if ((n_flag!=nx)||(func_flag!=func_num))
		{
			ini_flag=0;
		}
	}

	if (ini_flag==0)
	{
		FILE *fpt;
		char FileName[256];
		free(M);
		free(OShift);
		free(y);
		free(z);
		free(x_bound);
		y=(double *)malloc(sizeof(double)  *  nx);
		z=(double *)malloc(sizeof(double)  *  nx);
		x_bound=(double *)malloc(sizeof(double)  *  nx);
		for (i=0; i<nx; i++)
			x_bound[i]=100.0;

		if (!(nx==2||nx==10||nx==20||nx==30||nx==50||nx==100))
		{
			printf("\nError: Test functions are only defined for D=2,10,20,30,50,100.\n");
			return ;
		}
		if (nx==2&&((func_num>=17&&func_num<=22)||(func_num>=29&&func_num<=30)))
		{
			printf("\nError: hf01,hf02,hf03,hf04,hf05,hf06,cf07&cf08 are NOT defined for D=2.\n");
			return ;
		}

		/* Load Matrix M*/
		sprintf(FileName, "input_data/M_%d_D%d.txt", func_num,nx);
		fpt = fopen(FileName,"r");
		if (fpt==NULL)
		{
		    printf("\n Error: Cannot open input file for reading \n");
		    return ;
		}
		if (func_num<20)
		{
			M=(double*)malloc(nx*nx*sizeof(double));
			if (M==NULL)
			{
				printf("\nError: there is insufficient memory available!\n");
				return ;
			}
			for (i=0; i<nx*nx; i++)
			{
				fscanf(fpt,"%lf",&M[i]);
			}
		}
		else
		{
			M=(double*)malloc(cf_num*nx*nx*sizeof(double));
			if (M==NULL)
			{
				printf("\nError: there is insufficient memory available!\n");
				return ;
			}
			for (i=0; i<cf_num*nx*nx; i++)
			{
				fscanf(fpt,"%lf",&M[i]);
			}
		}
		fclose(fpt);
		
		/* Load shift_data */
		sprintf(FileName, "input_data/shift_data_%d.txt", func_num);
		fpt = fopen(FileName,"r");
		if (fpt==NULL)
		{
			printf("\n Error: Cannot open input file for reading \n");
			return ;
		}

		if (func_num<20)
		{
			OShift=(double *)malloc(nx*sizeof(double));
			if (OShift==NULL)
			{
				printf("\nError: there is insufficient memory available!\n");
				return ;
			}
			for(i=0;i<nx;i++)
			{
				fscanf(fpt,"%lf",&OShift[i]);
			}
		}
		else
		{
			OShift=(double *)malloc(nx*cf_num*sizeof(double));
			if (OShift==NULL)
			{
				printf("\nError: there is insufficient memory available!\n");
				return ;
			}
			for(i=0;i<cf_num-1;i++)
			{
				for (j=0;j<nx;j++)
				{
					fscanf(fpt,"%lf",&OShift[i*nx+j]);
				}
				fscanf(fpt,"%*[^\n]%*c"); 
			}
			for (j=0;j<nx;j++)
			{
				fscanf(fpt,"%lf",&OShift[(cf_num-1)*nx+j]);
			}
				
		}
		fclose(fpt);


		/* Load Shuffle_data */
		
		if (func_num>=11&&func_num<=20)
		{
			sprintf(FileName, "input_data/shuffle_data_%d_D%d.txt", func_num, nx);
			fpt = fopen(FileName,"r");
			if (fpt==NULL)
			{
				printf("\n Error: Cannot open input file for reading \n");
				return ;
			}
			SS=(int *)malloc(nx*sizeof(int));
			if (SS==NULL)
			{
				printf("\nError: there is insufficient memory available!\n");
				return ;
			}
			for(i=0;i<nx;i++)
			{
				fscanf(fpt,"%d",&SS[i]);
			}	
			fclose(fpt);
		}
		else if (func_num==29||func_num==30)
		{
			sprintf(FileName, "input_data/shuffle_data_%d_D%d.txt", func_num, nx);
			fpt = fopen(FileName,"r");
			if (fpt==NULL)
			{
				printf("\n Error: Cannot open input file for reading \n");
				return ;
			}
			SS=(int *)malloc(nx*cf_num*sizeof(int));
			if (SS==NULL)
			{
				printf("\nError: there is insufficient memory available!\n");
				return ;
			}
			for(i=0;i<nx*cf_num;i++)
			{
				fscanf(fpt,"%d",&SS[i]);
			}
			fclose(fpt);
		}
		

		n_flag=nx;
		func_flag=func_num;
		ini_flag=1;
		//printf("Function has been initialized!\n");
	}


	for (i = 0; i < mx; i++)
	{
		switch(func_num)
		{
		case 1:	
			bent_cigar_func(&x[i*nx],&f[i],nx,OShift,M,1,1);
			f[i]+=100.0;
			break;
		case 2:	
			//sum_diff_pow_func(&x[i*nx],&f[i],nx,OShift,M,1,1);
			//f[i]+=200.0;
			printf("\nError: This function (F2) has been deleted\n");
			break;
		case 3:	
			zakharov_func(&x[i*nx],&f[i],nx,OShift,M,1,1);
			f[i]+=300.0;
			break;
		case 4:	
			rosenbrock_func(&x[i*nx],&f[i],nx,OShift,M,1,1);
			f[i]+=400.0;
			break;
		case 5:
			rastrigin_func(&x[i*nx],&f[i],nx,OShift,M,1,1);
			f[i]+=500.0;
			break;
		case 6:
			schaffer_F7_func(&x[i*nx],&f[i],nx,OShift,M,1,1);
			f[i]+=600.0;
			break;
		case 7:	
			bi_rastrigin_func(&x[i*nx],&f[i],nx,OShift,M,1,1);
			f[i]+=700.0;
			break;
		case 8:	
			step_rastrigin_func(&x[i*nx],&f[i],nx,OShift,M,1,1);
			f[i]+=800.0;
			break;
		case 9:	
			levy_func(&x[i*nx],&f[i],nx,OShift,M,1,1);
			f[i]+=900.0;
			break;
		case 10:	
			schwefel_func(&x[i*nx],&f[i],nx,OShift,M,1,1);
			f[i]+=1000.0;
			break;
		case 11:	
			hf01(&x[i*nx],&f[i],nx,OShift,M,SS,1,1);
			f[i]+=1100.0;
			break;
		case 12:	
			hf02(&x[i*nx],&f[i],nx,OShift,M,SS,1,1);
			f[i]+=1200.0;
			break;
		case 13:	
			hf03(&x[i*nx],&f[i],nx,OShift,M,SS,1,1);
			f[i]+=1300.0;
			break;
		case 14:	
			hf04(&x[i*nx],&f[i],nx,OShift,M,SS,1,1);
			f[i]+=1400.0;
			break;
		case 15:	
			hf05(&x[i*nx],&f[i],nx,OShift,M,SS,1,1);
			f[i]+=1500.0;
			break;
		case 16:	
			hf06(&x[i*nx],&f[i],nx,OShift,M,SS,1,1);
			f[i]+=1600.0;
			break;
		case 17:	
			hf07(&x[i*nx],&f[i],nx,OShift,M,SS,1,1);
			f[i]+=1700.0;
			break;
		case 18:	
			hf08(&x[i*nx],&f[i],nx,OShift,M,SS,1,1);
			f[i]+=1800.0;
			break;
		case 19:	
			hf09(&x[i*nx],&f[i],nx,OShift,M,SS,1,1);
			f[i]+=1900.0;
			break;
		case 20:	
			hf10(&x[i*nx],&f[i],nx,OShift,M,SS,1,1);
			f[i]+=2000.0;
			break;
		case 21:	
			cf01(&x[i*nx],&f[i],nx,OShift,M,1);
			f[i]+=2100.0;
			break;
		case 22:	
			cf02(&x[i*nx],&f[i],nx,OShift,M,1);
			f[i]+=2200.0;
			break;
		case 23:	
			cf03(&x[i*nx],&f[i],nx,OShift,M,1);
			f[i]+=2300.0;
			break;
		case 24:	
			cf04(&x[i*nx],&f[i],nx,OShift,M,1);
			f[i]+=2400.0;
			break;
		case 25:	
			cf05(&x[i*nx],&f[i],nx,OShift,M,1);
			f[i]+=2500.0;
			break;
		case 26:
			cf06(&x[i*nx],&f[i],nx,OShift,M,1);
			f[i]+=2600.0;
			break;
		case 27:
			cf07(&x[i*nx],&f[i],nx,OShift,M,1);
			f[i]+=2700.0;
			break;
		case 28:
			cf08(&x[i*nx],&f[i],nx,OShift,M,1);
			f[i]+=2800.0;
			break;
		case 29:
			cf09(&x[i*nx],&f[i],nx,OShift,M,SS,1);
			f[i]+=2900.0;
			break;
		case 30:
			cf10(&x[i*nx],&f[i],nx,OShift,M,SS,1);
			f[i]+=3000.0;
			break;
		default:
			printf("\nError: There are only 30 test functions in this test suite!\n");
			f[i] = 0.0;
			break;
		}
		
	}

}

void sphere_func (double *x, double *f, int nx, double *Os, double *Mr, int s_flag, int r_flag) /* Sphere */
{
	int i;
	f[0] = 0.0;
	sr_func (x, z, nx, Os, Mr, 1.0, s_flag, r_flag); /* shift and rotate */	
	for (i=0; i<nx; i++)
	{					
		f[0] += z[i]*z[i];
	}

}

void ellips_func (double *x, double *f, int nx, double *Os,double *Mr, int s_flag, int r_flag) /* Ellipsoidal */
{
    int i;
	f[0] = 0.0;
	sr_func (x, z, nx, Os, Mr,1.0, s_flag, r_flag); /* shift and rotate */
	for (i=0; i<nx; i++)
	{
       f[0] += pow(10.0,6.0*i/(nx-1))*z[i]*z[i];
	}
}

void sum_diff_pow_func (double *x, double *f, int nx, double *Os,double *Mr, int s_flag, int r_flag) /* sum of different power */
{
    int i;
	sr_func (x, z, nx, Os, Mr,1.0, s_flag, r_flag); // shift and rotate 
	f[0] = 0.0; 
	double sum = 0.0;
	for (i=0; i<nx; i++)
	{
		double xi = z[i];
		double newv = pow((abs(xi)),(i+1));
		sum = sum + newv;
	}
	
	f[0] = sum;
}

void zakharov_func (double *x, double *f, int nx, double *Os,double *Mr, int s_flag, int r_flag) /* zakharov */
{
	int i;
	sr_func (x, z, nx, Os, Mr,1.0, s_flag, r_flag); // shift and rotate 
	f[0] = 0.0; 
	double sum1 = 0.0;
	double sum2 = 0.0;
	for (i=0; i<nx; i++)
	{
		double xi = z[i];
		sum1 = sum1 + pow(xi,2);
		sum2 = sum2 + 0.5*(i+1)*xi;
	}
	
	f[0] = sum1 + pow(sum2,2) + pow(sum2,4);
}

/* Levy function */
void levy_func (double *x, double *f, int nx, double *Os,double *Mr, int s_flag, int r_flag) /* Levy */
{
    int i;
	f[0] = 0.0;
	sr_func (x, z, nx, Os, Mr,1.0, s_flag, r_flag); /* shift and rotate */
	
	double *w;
	w=(double *)malloc(sizeof(double)  *  nx);

	double sum1= 0.0;
	for (i=0; i<nx; i++)
	{
	   w[i] = 1.0 + (z[i] - 1.0)/4.0;
	}
	
	double term1 = pow((sin(PI*w[0])),2);
	double term3 = pow((w[nx-1]-1),2) * (1+pow((sin(2*PI*w[nx-1])),2));
	
	double sum = 0.0;

	for (i=0; i<nx-1; i++)
	{
		double wi = w[i];
        double newv = pow((wi-1),2) * (1+10*pow((sin(PI*wi+1)),2));
		sum = sum + newv;
	}
	
	f[0] = term1 + sum + term3;
	free(w);   // ADD THIS LINE to free memory! Thanks for Dr. Janez
}

/* Dixon and Price */
void dixon_price_func (double *x, double *f, int nx, double *Os,double *Mr, int s_flag, int r_flag) /* Dixon and Price */
{
	int i;
	int j;
	sr_func (x, z, nx, Os, Mr,1.0, s_flag, r_flag); // shift and rotate 
	f[0] = 0;
	double x1 = z[0];;
	double term1 = pow((x1-1),2);
	
	double sum = 0;
	for (i=1; i<nx; i++)
	{
		double xi = z[i];
		double xold = z[i-1];
		double newv = i * pow((pow(2*xi,2) - xold),2);
		sum = sum + newv;
	}
	
	f[0] = term1 + sum;
}

void bent_cigar_func (double *x, double *f, int nx, double *Os,double *Mr, int s_flag, int r_flag) /* Bent_Cigar */
{
    int i;
	sr_func (x, z, nx, Os, Mr,1.0, s_flag, r_flag); /* shift and rotate */

	f[0] = z[0]*z[0];
	for (i=1; i<nx; i++)
	{
		f[0] += pow(10.0,6.0)*z[i]*z[i];
	}


}

void discus_func (double *x, double *f, int nx, double *Os,double *Mr, int s_flag, int r_flag) /* Discus */
{
    int i;
	sr_func (x, z, nx, Os, Mr,1.0, s_flag, r_flag); /* shift and rotate */
	f[0] = pow(10.0,6.0)*z[0]*z[0];
	for (i=1; i<nx; i++)
	{
		f[0] += z[i]*z[i];
	}
}

void dif_powers_func (double *x, double *f, int nx, double *Os,double *Mr,int s_flag, int r_flag) /* Different Powers */
{
	int i;
	f[0] = 0.0;
	sr_func (x, z, nx, Os, Mr, 1.0, s_flag, r_flag); /* shift and rotate */

	for (i=0; i<nx; i++)
	{
		f[0] += pow(fabs(z[i]),2+4*i/(nx-1));
	}
	f[0]=pow(f[0],0.5);
}


void rosenbrock_func (double *x, double *f, int nx, double *Os,double *Mr,int s_flag, int r_flag) /* Rosenbrock's */
{
    int i;
	double tmp1,tmp2;
	f[0] = 0.0;
	sr_func (x, z, nx, Os, Mr, 2.048/100.0, s_flag, r_flag); /* shift and rotate */
	z[0] += 1.0;//shift to orgin
	for (i=0; i<nx-1; i++)
	{
		z[i+1] += 1.0;//shift to orgin
		tmp1=z[i]*z[i]-z[i+1];
		tmp2=z[i]-1.0;
		f[0] += 100.0*tmp1*tmp1 +tmp2*tmp2;
	}
}

void schaffer_F7_func (double *x, double *f, int nx, double *Os,double *Mr,int s_flag, int r_flag) /* Schwefel's 1.2  */
{
    int i;
	double tmp;
    f[0] = 0.0;
	sr_func (x, z, nx, Os, Mr, 1.0, s_flag, r_flag); /* shift and rotate */
	for (i=0; i<nx-1; i++)	
	{
		z[i]=pow(y[i]*y[i]+y[i+1]*y[i+1],0.5);
		tmp=sin(50.0*pow(z[i],0.2));
		f[0] += pow(z[i],0.5)+pow(z[i],0.5)*tmp*tmp ;
	}
	f[0] = f[0]*f[0]/(nx-1)/(nx-1);
}

void ackley_func (double *x, double *f, int nx, double *Os,double *Mr,int s_flag, int r_flag) /* Ackley's  */
{
    int i;
    double sum1, sum2;
    sum1 = 0.0;
    sum2 = 0.0;

	sr_func (x, z, nx, Os, Mr, 1.0, s_flag, r_flag); /* shift and rotate */

	for (i=0; i<nx; i++)
	{
		sum1 += z[i]*z[i];
		sum2 += cos(2.0*PI*z[i]);
	}
	sum1 = -0.2*sqrt(sum1/nx);
	sum2 /= nx;
		f[0] =  E - 20.0*exp(sum1) - exp(sum2) +20.0;
}


void weierstrass_func (double *x, double *f, int nx, double *Os,double *Mr,int s_flag, int r_flag) /* Weierstrass's  */
{
    int i,j,k_max;
    double sum,sum2, a, b;
    a = 0.5;
    b = 3.0;
    k_max = 20;
    f[0] = 0.0;

	sr_func (x, z, nx, Os, Mr, 0.5/100.0, s_flag, r_flag); /* shift and rotate */

	for (i=0; i<nx; i++)
	{
		sum = 0.0;
		sum2 = 0.0;
		for (j=0; j<=k_max; j++)
		{
			sum += pow(a,j)*cos(2.0*PI*pow(b,j)*(z[i]+0.5));
			sum2 += pow(a,j)*cos(2.0*PI*pow(b,j)*0.5);
		}
		f[0] += sum;
	}
	f[0] -= nx*sum2;
}


void griewank_func (double *x, double *f, int nx, double *Os,double *Mr,int s_flag, int r_flag) /* Griewank's  */
{
    int i;
    double s, p;
    s = 0.0;
    p = 1.0;

	sr_func (x, z, nx, Os, Mr, 600.0/100.0, s_flag, r_flag); /* shift and rotate */

	for (i=0; i<nx; i++)
	{
		s += z[i]*z[i];
		p *= cos(z[i]/sqrt(1.0+i));
	}
	f[0] = 1.0 + s/4000.0 - p;
}

void rastrigin_func (double *x, double *f, int nx, double *Os,double *Mr,int s_flag, int r_flag) /* Rastrigin's  */
{
    int i;
	f[0] = 0.0;

	sr_func (x, z, nx, Os, Mr, 5.12/100.0, s_flag, r_flag); /* shift and rotate */

	for (i=0; i<nx; i++)
	{
		f[0] += (z[i]*z[i] - 10.0*cos(2.0*PI*z[i]) + 10.0);
	}
}

void step_rastrigin_func (double *x, double *f, int nx, double *Os,double *Mr,int s_flag, int r_flag) /* Noncontinuous Rastrigin's  */
{
    int i;
	f[0]=0.0;
	for (i=0; i<nx; i++)
	{
		if (fabs(y[i]-Os[i])>0.5)
		y[i]=Os[i]+floor(2*(y[i]-Os[i])+0.5)/2;
	}

	sr_func (x, z, nx, Os, Mr, 5.12/100.0, s_flag, r_flag); /* shift and rotate */

	for (i=0; i<nx; i++)
	{
		f[0] += (z[i]*z[i] - 10.0*cos(2.0*PI*z[i]) + 10.0);
	}
}

void schwefel_func (double *x, double *f, int nx, double *Os,double *Mr,int s_flag, int r_flag) /* Schwefel's  */
{
    int i;
	double tmp;
	f[0]=0.0;

	sr_func (x, z, nx, Os, Mr, 1000.0/100.0, s_flag, r_flag); /* shift and rotate */

	for (i=0; i<nx; i++)
	{
		z[i] += 4.209687462275036e+002;
		if (z[i]>500)
		{
			f[0]-=(500.0-fmod(z[i],500))*sin(pow(500.0-fmod(z[i],500),0.5));
			tmp=(z[i]-500.0)/100;
			f[0]+= tmp*tmp/nx;
		}
		else if (z[i]<-500)
		{
			f[0]-=(-500.0+fmod(fabs(z[i]),500))*sin(pow(500.0-fmod(fabs(z[i]),500),0.5));
			tmp=(z[i]+500.0)/100;
			f[0]+= tmp*tmp/nx;
		}
		else
			f[0]-=z[i]*sin(pow(fabs(z[i]),0.5));
		}
		f[0] +=4.189828872724338e+002*nx;

}

void katsuura_func (double *x, double *f, int nx, double *Os,double *Mr,int s_flag, int r_flag) /* Katsuura  */
{
    int i,j;
	double temp,tmp1,tmp2,tmp3;
	f[0]=1.0;
	tmp3=pow(1.0*nx,1.2);

	sr_func (x, z, nx, Os, Mr, 5.0/100.0, s_flag, r_flag); /* shift and rotate */

    for (i=0; i<nx; i++)
	{
		temp=0.0;
		for (j=1; j<=32; j++)
		{
			tmp1=pow(2.0,j);
			tmp2=tmp1*z[i];
			temp += fabs(tmp2-floor(tmp2+0.5))/tmp1;
		}
		f[0] *= pow(1.0+(i+1)*temp,10.0/tmp3);
    }
	tmp1=10.0/nx/nx;
    f[0]=f[0]*tmp1-tmp1;

}

void bi_rastrigin_func (double *x, double *f, int nx, double *Os,double *Mr,int s_flag, int r_flag) /* Lunacek Bi_rastrigin Function */
{
    int i;
	double mu0=2.5,d=1.0,s,mu1,tmp,tmp1,tmp2;
	double *tmpx;
	tmpx=(double *)malloc(sizeof(double)  *  nx);
	s=1.0-1.0/(2.0*pow(nx+20.0,0.5)-8.2);
	mu1=-pow((mu0*mu0-d)/s,0.5);

	if (s_flag==1)
		shiftfunc(x, y, nx, Os);
	else
	{
		for (i=0; i<nx; i++)//shrink to the orginal search range
		{
			y[i] = x[i];
		}
	}
	for (i=0; i<nx; i++)//shrink to the orginal search range
    {
        y[i] *= 10.0/100.0;
    }

	for (i = 0; i < nx; i++)
    {
		tmpx[i]=2*y[i];
        if (Os[i] < 0.0)
            tmpx[i] *= -1.;
    }
	for (i=0; i<nx; i++)
	{
		z[i]=tmpx[i];
		tmpx[i] += mu0;
	}
    tmp1=0.0;tmp2=0.0;
	for (i=0; i<nx; i++)
	{
		tmp = tmpx[i]-mu0;
		tmp1 += tmp*tmp;
		tmp = tmpx[i]-mu1;
		tmp2 += tmp*tmp;
	}
	tmp2 *= s;
	tmp2 += d*nx;
	tmp=0.0;

	if (r_flag==1)
	{
		rotatefunc(z, y, nx, Mr);
		for (i=0; i<nx; i++)
		{
			tmp+=cos(2.0*PI*y[i]);
		}	
		if(tmp1<tmp2)
			f[0] = tmp1;
		else
			f[0] = tmp2;
		f[0] += 10.0*(nx-tmp);
	}
	else
	{
		for (i=0; i<nx; i++)
		{
			tmp+=cos(2.0*PI*z[i]);
		}	
		if(tmp1<tmp2)
			f[0] = tmp1;
		else
			f[0] = tmp2;
		f[0] += 10.0*(nx-tmp);
	}

	free(tmpx);
}

void grie_rosen_func (double *x, double *f, int nx, double *Os,double *Mr,int s_flag, int r_flag) /* Griewank-Rosenbrock  */
{
    int i;
    double temp,tmp1,tmp2;
    f[0]=0.0;

	sr_func (x, z, nx, Os, Mr, 5.0/100.0, s_flag, r_flag); /* shift and rotate */

	z[0] += 1.0;//shift to orgin
    for (i=0; i<nx-1; i++)
    {
		z[i+1] += 1.0;//shift to orgin
		tmp1 = z[i]*z[i]-z[i+1];
		tmp2 = z[i]-1.0;
        temp = 100.0*tmp1*tmp1 + tmp2*tmp2;
         f[0] += (temp*temp)/4000.0 - cos(temp) + 1.0; 
    }
	tmp1 = z[nx-1]*z[nx-1]-z[0];
	tmp2 = z[nx-1]-1.0;
    temp = 100.0*tmp1*tmp1 + tmp2*tmp2;
    f[0] += (temp*temp)/4000.0 - cos(temp) + 1.0 ;
}


void escaffer6_func (double *x, double *f, int nx, double *Os,double *Mr,int s_flag, int r_flag) /* Expanded Scaffer??s F6  */
{
    int i;
    double temp1, temp2;

	sr_func (x, z, nx, Os, Mr, 1.0, s_flag, r_flag); /* shift and rotate */

    f[0] = 0.0;
    for (i=0; i<nx-1; i++)
    {
        temp1 = sin(sqrt(z[i]*z[i]+z[i+1]*z[i+1]));
		temp1 =temp1*temp1;
        temp2 = 1.0 + 0.001*(z[i]*z[i]+z[i+1]*z[i+1]);
        f[0] += 0.5 + (temp1-0.5)/(temp2*temp2);
    }
    temp1 = sin(sqrt(z[nx-1]*z[nx-1]+z[0]*z[0]));
	temp1 =temp1*temp1;
    temp2 = 1.0 + 0.001*(z[nx-1]*z[nx-1]+z[0]*z[0]);
    f[0] += 0.5 + (temp1-0.5)/(temp2*temp2);
}

void happycat_func (double *x, double *f, int nx, double *Os,double *Mr,int s_flag, int r_flag) /* HappyCat, provdided by Hans-Georg Beyer (HGB) */
/* original global optimum: [-1,-1,...,-1] */
{
	int i;
	double alpha,r2,sum_z;
	alpha=1.0/8.0;
	
	sr_func (x, z, nx, Os, Mr, 5.0/100.0, s_flag, r_flag); /* shift and rotate */

	r2 = 0.0;
	sum_z=0.0;
    for (i=0; i<nx; i++)
    {
		z[i]=z[i]-1.0;//shift to orgin
        r2 += z[i]*z[i];
		sum_z += z[i];
    }
    f[0]=pow(fabs(r2-nx),2*alpha) + (0.5*r2 + sum_z)/nx + 0.5;
}

void hgbat_func (double *x, double *f, int nx, double *Os,double *Mr,int s_flag, int r_flag) /* HGBat, provdided by Hans-Georg Beyer (HGB)*/
/* original global optimum: [-1,-1,...,-1] */
{
	int i;
	double alpha,r2,sum_z;
	alpha=1.0/4.0;

	sr_func (x, z, nx, Os, Mr, 5.0/100.0, s_flag, r_flag); /* shift and rotate */

	r2 = 0.0;
	sum_z=0.0;
    for (i=0; i<nx; i++)
    {
		z[i]=z[i]-1.0;//shift to orgin
        r2 += z[i]*z[i];
		sum_z += z[i];
    }
    f[0]=pow(fabs(pow(r2,2.0)-pow(sum_z,2.0)),2*alpha) + (0.5*r2 + sum_z)/nx + 0.5;
}

void hf01 (double *x, double *f, int nx, double *Os,double *Mr,int *S,int s_flag,int r_flag) /* Hybrid Function 1 */
{
	int i,tmp,cf_num=3;
	double fit[3];
	int G[3],G_nx[3];
	double Gp[3]={0.2,0.4,0.4};

	tmp=0;
	for (i=0; i<cf_num-1; i++)
	{
		G_nx[i] = ceil(Gp[i]*nx);
		tmp += G_nx[i];
	}
	G_nx[cf_num-1]=nx-tmp;
	G[0]=0;
	for (i=1; i<cf_num; i++)
	{
		G[i] = G[i-1]+G_nx[i-1];
	}

	sr_func (x, z, nx, Os, Mr, 1.0, s_flag, r_flag); /* shift and rotate */

	for (i=0; i<nx; i++)
	{
		y[i]=z[S[i]-1];
	}
	i=0;
	zakharov_func(&y[G[i]],&fit[i],G_nx[i],Os,Mr,0,0);
	i=1;
	rosenbrock_func(&y[G[i]],&fit[i],G_nx[i],Os,Mr,0,0);
	i=2;
	rastrigin_func(&y[G[i]],&fit[i],G_nx[i],Os,Mr,0,0);
	f[0]=0.0;
	for(i=0;i<cf_num;i++)
	{
		f[0] += fit[i];
	}
}

void hf02 (double *x, double *f, int nx, double *Os,double *Mr,int *S,int s_flag,int r_flag) /* Hybrid Function 2 */
{
	int i,tmp,cf_num=3;
	double fit[3];
	int G[3],G_nx[3];
	double Gp[3]={0.3,0.3,0.4};

	tmp=0;
	for (i=0; i<cf_num-1; i++)
	{
		G_nx[i] = ceil(Gp[i]*nx);
		tmp += G_nx[i];
	}
	G_nx[cf_num-1]=nx-tmp;

	G[0]=0;
	for (i=1; i<cf_num; i++)
	{
		G[i] = G[i-1]+G_nx[i-1];
	}

	sr_func (x, z, nx, Os, Mr, 1.0, s_flag, r_flag); /* shift and rotate */

	for (i=0; i<nx; i++)
	{
		y[i]=z[S[i]-1];
	}
	i=0;
	ellips_func(&y[G[i]],&fit[i],G_nx[i],Os,Mr,0,0);
	i=1;
	schwefel_func(&y[G[i]],&fit[i],G_nx[i],Os,Mr,0,0);
	i=2;
	bent_cigar_func(&y[G[i]],&fit[i],G_nx[i],Os,Mr,0,0);

	f[0]=0.0;
	for(i=0;i<cf_num;i++)
	{
		f[0] += fit[i];
	}
}

void hf03 (double *x, double *f, int nx, double *Os,double *Mr,int *S,int s_flag,int r_flag) /* Hybrid Function 2 */
{
	int i,tmp,cf_num=3;
	double fit[3];
	int G[3],G_nx[3];
	double Gp[3]={0.3,0.3,0.4};

	tmp=0;
	for (i=0; i<cf_num-1; i++)
	{
		G_nx[i] = ceil(Gp[i]*nx);
		tmp += G_nx[i];
	}
	G_nx[cf_num-1]=nx-tmp;

	G[0]=0;
	for (i=1; i<cf_num; i++)
	{
		G[i] = G[i-1]+G_nx[i-1];
	}

	sr_func (x, z, nx, Os, Mr, 1.0, s_flag, r_flag); /* shift and rotate */

	for (i=0; i<nx; i++)
	{
		y[i]=z[S[i]-1];
	}
	
	i=0;
	bent_cigar_func(&y[G[i]],&fit[i],G_nx[i],Os,Mr,0,0);
	i=1;
	rosenbrock_func(&y[G[i]],&fit[i],G_nx[i],Os,Mr,0,0);
	i=2;
	bi_rastrigin_func(&y[G[i]],&fit[i],G_nx[i],Os,Mr,0,0);

	f[0]=0.0;
	for(i=0;i<cf_num;i++)
	{
		f[0] += fit[i];
	}
	
}

void hf04 (double *x, double *f, int nx, double *Os,double *Mr,int *S,int s_flag,int r_flag) /* Hybrid Function 3 */
{
	int i,tmp,cf_num=4;
	double fit[4];
	int G[4],G_nx[4];
	double Gp[4]={0.2,0.2,0.2,0.4};

	tmp=0;
	for (i=0; i<cf_num-1; i++)
	{
		G_nx[i] = ceil(Gp[i]*nx);
		tmp += G_nx[i];
	}
	G_nx[cf_num-1]=nx-tmp;

	G[0]=0;
	for (i=1; i<cf_num; i++)
	{
		G[i] = G[i-1]+G_nx[i-1];
	}

	sr_func (x, z, nx, Os, Mr, 1.0, s_flag, r_flag); /* shift and rotate */

	for (i=0; i<nx; i++)
	{
		y[i]=z[S[i]-1];
	}
	i=0;
	ellips_func(&y[G[i]],&fit[i],G_nx[i],Os,Mr,0,0);
	i=1;
	ackley_func(&y[G[i]],&fit[i],G_nx[i],Os,Mr,0,0);
	i=2;
	schaffer_F7_func(&y[G[i]],&fit[i],G_nx[i],Os,Mr,0,0);
	i=3;
	rastrigin_func(&y[G[i]],&fit[i],G_nx[i],Os,Mr,0,0);
	
	f[0]=0.0;
	for(i=0;i<cf_num;i++)
	{
		f[0] += fit[i];
	}
}

void hf05 (double *x, double *f, int nx, double *Os,double *Mr,int *S,int s_flag,int r_flag) /* Hybrid Function 4 */
{
	int i,tmp,cf_num=4;
	double fit[4];
	int G[4],G_nx[4];
	double Gp[4]={0.2,0.2,0.3,0.3};

	tmp=0;
	for (i=0; i<cf_num-1; i++)
	{
		G_nx[i] = ceil(Gp[i]*nx);
		tmp += G_nx[i];
	}
	G_nx[cf_num-1]=nx-tmp;

	G[0]=0;
	for (i=1; i<cf_num; i++)
	{
		G[i] = G[i-1]+G_nx[i-1];
	}

	sr_func (x, z, nx, Os, Mr, 1.0, s_flag, r_flag); /* shift and rotate */

	for (i=0; i<nx; i++)
	{
		y[i]=z[S[i]-1];
	}
	i=0;
	
	bent_cigar_func(&y[G[i]],&fit[i],G_nx[i],Os,Mr,0,0);
	i=1;
	hgbat_func(&y[G[i]],&fit[i],G_nx[i],Os,Mr,0,0);
	i=2;
	rastrigin_func(&y[G[i]],&fit[i],G_nx[i],Os,Mr,0,0);
	i=3;
	rosenbrock_func(&y[G[i]],&fit[i],G_nx[i],Os,Mr,0,0);
	
	f[0]=0.0;
	for(i=0;i<cf_num;i++)
	{
		f[0] += fit[i];
	}
}
void hf06 (double *x, double *f, int nx, double *Os,double *Mr,int *S,int s_flag,int r_flag) /* Hybrid Function 5 */
{
	int i,tmp,cf_num=4;
	double fit[4];
	int G[4],G_nx[4];
	double Gp[4]={0.2,0.2,0.3,0.3};

	tmp=0;
	for (i=0; i<cf_num-1; i++)
	{
		G_nx[i] = ceil(Gp[i]*nx);
		tmp += G_nx[i];
	}
	G_nx[cf_num-1]=nx-tmp;

	G[0]=0;
	for (i=1; i<cf_num; i++)
	{
		G[i] = G[i-1]+G_nx[i-1];
	}

	sr_func (x, z, nx, Os, Mr, 1.0, s_flag, r_flag); /* shift and rotate */

	for (i=0; i<nx; i++)
	{
		y[i]=z[S[i]-1];
	}
	i=0;
	escaffer6_func(&y[G[i]],&fit[i],G_nx[i],Os,Mr,0,0);
	i=1;
	hgbat_func(&y[G[i]],&fit[i],G_nx[i],Os,Mr,0,0);
	i=2;
	rosenbrock_func(&y[G[i]],&fit[i],G_nx[i],Os,Mr,0,0);
	i=3;
	schwefel_func(&y[G[i]],&fit[i],G_nx[i],Os,Mr,0,0);
	
	f[0]=0.0;
	for(i=0;i<cf_num;i++)
	{
		f[0] += fit[i];
	}
}

void hf07 (double *x, double *f, int nx, double *Os,double *Mr,int *S,int s_flag,int r_flag) /* Hybrid Function 6 */
{
	int i,tmp,cf_num=5;
	double fit[5];
	int G[5],G_nx[5];
	double Gp[5]={0.1,0.2,0.2,0.2,0.3};

	tmp=0;
	for (i=0; i<cf_num-1; i++)
	{
		G_nx[i] = ceil(Gp[i]*nx);
		tmp += G_nx[i];
	}
	G_nx[cf_num-1]=nx-tmp;

	G[0]=0;
	for (i=1; i<cf_num; i++)
	{
		G[i] = G[i-1]+G_nx[i-1];
	}

	sr_func (x, z, nx, Os, Mr, 1.0, s_flag, r_flag); /* shift and rotate */

	for (i=0; i<nx; i++)
	{
		y[i]=z[S[i]-1];
	}
	i=0;
	katsuura_func(&y[G[i]],&fit[i],G_nx[i],Os,Mr,0,0);
	i=1;
	ackley_func(&y[G[i]],&fit[i],G_nx[i],Os,Mr,0,0);
	i=2;
	grie_rosen_func(&y[G[i]],&fit[i],G_nx[i],Os,Mr,0,0);
	i=3;
	schwefel_func(&y[G[i]],&fit[i],G_nx[i],Os,Mr,0,0);
	i=4;
	rastrigin_func(&y[G[i]],&fit[i],G_nx[i],Os,Mr,0,0);

	f[0]=0.0;
	for(i=0;i<cf_num;i++)
	{
		f[0] += fit[i];
	}
}

void hf08 (double *x, double *f, int nx, double *Os,double *Mr,int *S,int s_flag,int r_flag) /* Hybrid Function 6 */
{
	int i,tmp,cf_num=5;
	double fit[5];
	int G[5],G_nx[5];
	double Gp[5]={0.2,0.2,0.2,0.2,0.2};

	tmp=0;
	for (i=0; i<cf_num-1; i++)
	{
		G_nx[i] = ceil(Gp[i]*nx);
		tmp += G_nx[i];
	}
	G_nx[cf_num-1]=nx-tmp;

	G[0]=0;
	for (i=1; i<cf_num; i++)
	{
		G[i] = G[i-1]+G_nx[i-1];
	}

	sr_func (x, z, nx, Os, Mr, 1.0, s_flag, r_flag); /* shift and rotate */

	for (i=0; i<nx; i++)
	{
		y[i]=z[S[i]-1];
	}
	
	i=0;
	ellips_func(&y[G[i]],&fit[i],G_nx[i],Os,Mr,0,0);
	i=1;
	ackley_func(&y[G[i]],&fit[i],G_nx[i],Os,Mr,0,0);
	i=2;
	rastrigin_func(&y[G[i]],&fit[i],G_nx[i],Os,Mr,0,0);
	i=3;
	hgbat_func(&y[G[i]],&fit[i],G_nx[i],Os,Mr,0,0);
	i=4;
	discus_func(&y[G[i]],&fit[i],G_nx[i],Os,Mr,0,0);

	f[0]=0.0;
	for(i=0;i<cf_num;i++)
	{
		f[0] += fit[i];
	}
}

void hf09 (double *x, double *f, int nx, double *Os,double *Mr,int *S,int s_flag,int r_flag) /* Hybrid Function 6 */
{
	int i,tmp,cf_num=5;
	double fit[5];
	int G[5],G_nx[5];
	double Gp[5]={0.2,0.2,0.2,0.2,0.2};

	tmp=0;
	for (i=0; i<cf_num-1; i++)
	{
		G_nx[i] = ceil(Gp[i]*nx);
		tmp += G_nx[i];
	}
	G_nx[cf_num-1]=nx-tmp;

	G[0]=0;
	for (i=1; i<cf_num; i++)
	{
		G[i] = G[i-1]+G_nx[i-1];
	}

	sr_func (x, z, nx, Os, Mr, 1.0, s_flag, r_flag); /* shift and rotate */

	for (i=0; i<nx; i++)
	{
		y[i]=z[S[i]-1];
	}
	
	i=0;
	bent_cigar_func(&y[G[i]],&fit[i],G_nx[i],Os,Mr,0,0);
	i=1;
	rastrigin_func(&y[G[i]],&fit[i],G_nx[i],Os,Mr,0,0);
	i=2;
	grie_rosen_func(&y[G[i]],&fit[i],G_nx[i],Os,Mr,0,0);
	i=3;
	weierstrass_func(&y[G[i]],&fit[i],G_nx[i],Os,Mr,0,0);
	i=4;
	escaffer6_func(&y[G[i]],&fit[i],G_nx[i],Os,Mr,0,0);

	f[0]=0.0;
	for(i=0;i<cf_num;i++)
	{
		f[0] += fit[i];
	}
}


void hf10 (double *x, double *f, int nx, double *Os,double *Mr,int *S,int s_flag,int r_flag) /* Hybrid Function 6 */
{
	int i,tmp,cf_num=6;
	double fit[6];
	int G[6],G_nx[6];
	double Gp[6]={0.1,0.1,0.2,0.2,0.2,0.2};

	tmp=0;
	for (i=0; i<cf_num-1; i++)
	{
		G_nx[i] = ceil(Gp[i]*nx);
		tmp += G_nx[i];
	}
	G_nx[cf_num-1]=nx-tmp;

	G[0]=0;
	for (i=1; i<cf_num; i++)
	{
		G[i] = G[i-1]+G_nx[i-1];
	}

	sr_func (x, z, nx, Os, Mr, 1.0, s_flag, r_flag); /* shift and rotate */

	for (i=0; i<nx; i++)
	{
		y[i]=z[S[i]-1];
	}
	
	i=0;
	hgbat_func(&y[G[i]],&fit[i],G_nx[i],Os,Mr,0,0);
	i=1;
	katsuura_func(&y[G[i]],&fit[i],G_nx[i],Os,Mr,0,0);
	i=2;
	ackley_func(&y[G[i]],&fit[i],G_nx[i],Os,Mr,0,0);
	i=3;
	rastrigin_func(&y[G[i]],&fit[i],G_nx[i],Os,Mr,0,0);
	i=4;
	schwefel_func(&y[G[i]],&fit[i],G_nx[i],Os,Mr,0,0);
	i=5;
	schaffer_F7_func(&y[G[i]],&fit[i],G_nx[i],Os,Mr,0,0);

	f[0]=0.0;
	for(i=0;i<cf_num;i++)
	{
		f[0] += fit[i];
	}
}

void cf01 (double *x, double *f, int nx, double *Os,double *Mr,int r_flag) /* Composition Function 1 */
{
	int i,cf_num=3;
	double fit[3];
	double delta[3] = {10, 20, 30};
	double bias[3] = {0, 100, 200};
	
	i=0;
	rosenbrock_func(x,&fit[i],nx,&Os[i*nx],&Mr[i*nx*nx],1,r_flag);
	i=1;
	ellips_func(x,&fit[i],nx,&Os[i*nx],&Mr[i*nx*nx],1,r_flag);
	fit[i]=10000*fit[i]/1e+10;
	i=2;
	rastrigin_func(x,&fit[i],nx,&Os[i*nx],&Mr[i*nx*nx],1,r_flag);
	cf_cal(x, f, nx, Os, delta,bias,fit,cf_num); 
}

void cf02 (double *x, double *f, int nx, double *Os,double *Mr,int r_flag) /* Composition Function 2 */
{
	int i,cf_num=3;
	double fit[3];
	double delta[3] = {10,20,30};
	double bias[3] = {0, 100, 200};

	i=0;
	rastrigin_func(x,&fit[i],nx,&Os[i*nx],&Mr[i*nx*nx],1,r_flag);
	i=1;
	griewank_func(x,&fit[i],nx,&Os[i*nx],&Mr[i*nx*nx],1,r_flag);
	fit[i]=1000*fit[i]/100;
	i=2;
	schwefel_func(x,&fit[i],nx,&Os[i*nx],&Mr[i*nx*nx],1,r_flag);
	cf_cal(x, f, nx, Os, delta,bias,fit,cf_num);
}

void cf03 (double *x, double *f, int nx, double *Os,double *Mr,int r_flag) /* Composition Function 3 */
{
	int i,cf_num=4;
	double fit[4];
	double delta[4] = {10,20,30,40};
	double bias[4] = {0, 100, 200, 300};
	
	i=0;
	rosenbrock_func(x,&fit[i],nx,&Os[i*nx],&Mr[i*nx*nx],1,r_flag);
	i=1;
	ackley_func(x,&fit[i],nx,&Os[i*nx],&Mr[i*nx*nx],1,r_flag);
	fit[i]=1000*fit[i]/100;
	i=2;
	schwefel_func(x,&fit[i],nx,&Os[i*nx],&Mr[i*nx*nx],1,r_flag);
	i=3;
	rastrigin_func(x,&fit[i],nx,&Os[i*nx],&Mr[i*nx*nx],1,r_flag);
	cf_cal(x, f, nx, Os, delta,bias,fit,cf_num); 
	
}
void cf04 (double *x, double *f, int nx, double *Os,double *Mr,int r_flag) /* Composition Function 3 */
{
	int i,cf_num=4;
	double fit[4];
	double delta[4] = {10,20,30,40};
	double bias[4] = {0, 100, 200, 300};
	
	i=0;
	ackley_func(x,&fit[i],nx,&Os[i*nx],&Mr[i*nx*nx],1,r_flag);
	fit[i]=1000*fit[i]/100;
	i=1;
	ellips_func(x,&fit[i],nx,&Os[i*nx],&Mr[i*nx*nx],1,r_flag);
	fit[i]=10000*fit[i]/1e+10;
	i=2;
	griewank_func(x,&fit[i],nx,&Os[i*nx],&Mr[i*nx*nx],1,r_flag);
	fit[i]=1000*fit[i]/100;
	i=3;
	rastrigin_func(x,&fit[i],nx,&Os[i*nx],&Mr[i*nx*nx],1,r_flag);
	cf_cal(x, f, nx, Os, delta,bias,fit,cf_num);
}

void cf05 (double *x, double *f, int nx, double *Os,double *Mr,int r_flag) /* Composition Function 4 */
{
	int i,cf_num=5;
	double fit[5];
	double delta[5] = {10,20,30,40,50};
	double bias[5] = {0, 100, 200, 300, 400};
	i=0;
	rastrigin_func(x,&fit[i],nx,&Os[i*nx],&Mr[i*nx*nx],1,r_flag);
	fit[i]=10000*fit[i]/1e+3;
	i=1;
	happycat_func(x,&fit[i],nx,&Os[i*nx],&Mr[i*nx*nx],1,r_flag);
	fit[i]=1000*fit[i]/1e+3;
	i=2;
	ackley_func(x,&fit[i],nx,&Os[i*nx],&Mr[i*nx*nx],1,r_flag);
	fit[i]=1000*fit[i]/100;
	i=3;
	discus_func(x,&fit[i],nx,&Os[i*nx],&Mr[i*nx*nx],1,r_flag);
	fit[i]=10000*fit[i]/1e+10;	
	i=4;
	rosenbrock_func(x,&fit[i],nx,&Os[i*nx],&Mr[i*nx*nx],1,r_flag);
	cf_cal(x, f, nx, Os, delta,bias,fit,cf_num);
}		


void cf06 (double *x, double *f, int nx, double *Os,double *Mr,int r_flag) /* Composition Function 4 */
{
	int i,cf_num=5;
	double fit[5];
	double delta[5] = {10,20,20,30,40};
	double bias[5] = {0, 100, 200, 300, 400};
	i=0;
	escaffer6_func(x,&fit[i],nx,&Os[i*nx],&Mr[i*nx*nx],1,r_flag);
	fit[i]=10000*fit[i]/2e+7;
	i=1;
	schwefel_func(x,&fit[i],nx,&Os[i*nx],&Mr[i*nx*nx],1,r_flag);
	i=2;
	griewank_func(x,&fit[i],nx,&Os[i*nx],&Mr[i*nx*nx],1,r_flag);
	fit[i]=1000*fit[i]/100;
	i=3;
	rosenbrock_func(x,&fit[i],nx,&Os[i*nx],&Mr[i*nx*nx],1,r_flag);
	i=4;
	rastrigin_func(x,&fit[i],nx,&Os[i*nx],&Mr[i*nx*nx],1,r_flag);
	fit[i]=10000*fit[i]/1e+3;
	cf_cal(x, f, nx, Os, delta,bias,fit,cf_num);
}

void cf07 (double *x, double *f, int nx, double *Os,double *Mr,int r_flag) /* Composition Function 4 */
{
	int i,cf_num=6;
	double fit[6];
	double delta[6] = {10,20,30,40,50,60};
	double bias[6] = {0, 100, 200, 300, 400, 500};
	i=0;
	hgbat_func(x,&fit[i],nx,&Os[i*nx],&Mr[i*nx*nx],1,r_flag);
	fit[i]=10000*fit[i]/1000;
	i=1;
	rastrigin_func(x,&fit[i],nx,&Os[i*nx],&Mr[i*nx*nx],1,r_flag);
	fit[i]=10000*fit[i]/1e+3;
	i=2;
	schwefel_func(x,&fit[i],nx,&Os[i*nx],&Mr[i*nx*nx],1,r_flag);
	fit[i]=10000*fit[i]/4e+3;
	i=3;
	bent_cigar_func(x,&fit[i],nx,&Os[i*nx],&Mr[i*nx*nx],1,r_flag);
	fit[i]=10000*fit[i]/1e+30;
	i=4;
	ellips_func(x,&fit[i],nx,&Os[i*nx],&Mr[i*nx*nx],1,r_flag);
	fit[i]=10000*fit[i]/1e+10;
	i=5;
	escaffer6_func(x,&fit[i],nx,&Os[i*nx],&Mr[i*nx*nx],1,r_flag);
	fit[i]=10000*fit[i]/2e+7;
	cf_cal(x, f, nx, Os, delta,bias,fit,cf_num); 
}

void cf08 (double *x, double *f, int nx, double *Os,double *Mr,int r_flag) /* Composition Function 4 */
{	
	int i,cf_num=6;
	double fit[6];
	double delta[6] = {10,20,30,40,50,60};
	double bias[6] = {0, 100, 200, 300, 400, 500};
	i=0;
	ackley_func(x,&fit[i],nx,&Os[i*nx],&Mr[i*nx*nx],1,r_flag);
	fit[i]=1000*fit[i]/100;
	i=1;
	griewank_func(x,&fit[i],nx,&Os[i*nx],&Mr[i*nx*nx],1,r_flag);
	fit[i]=1000*fit[i]/100;
	i=2;
	discus_func(x,&fit[i],nx,&Os[i*nx],&Mr[i*nx*nx],1,r_flag);
	fit[i]=10000*fit[i]/1e+10;
	i=3;
	rosenbrock_func(x,&fit[i],nx,&Os[i*nx],&Mr[i*nx*nx],1,r_flag);
	i=4;
	happycat_func(x,&fit[i],nx,&Os[i*nx],&Mr[i*nx*nx],1,r_flag);
	fit[i]=1000*fit[i]/1e+3;
	i=5;
	escaffer6_func(x,&fit[i],nx,&Os[i*nx],&Mr[i*nx*nx],1,r_flag);
	fit[i]=10000*fit[i]/2e+7;
	cf_cal(x, f, nx, Os, delta,bias,fit,cf_num);
}


void cf09 (double *x, double *f, int nx, double *Os,double *Mr,int *SS,int r_flag)
{
	
	int i,cf_num=3;
	double fit[3];
	double delta[3] = {10,30,50};
	double bias[3] = {0, 100, 200};
	i=0;
	hf05(x,&fit[i],nx,&Os[i*nx],&Mr[i*nx*nx],&SS[i*nx],1,r_flag);
	i=1;
	hf06(x,&fit[i],nx,&Os[i*nx],&Mr[i*nx*nx],&SS[i*nx],1,r_flag);
	i=2;
	hf07(x,&fit[i],nx,&Os[i*nx],&Mr[i*nx*nx],&SS[i*nx],1,r_flag);
	cf_cal(x, f, nx, Os, delta,bias,fit,cf_num);
		
}

void cf10 (double *x, double *f, int nx, double *Os,double *Mr,int *SS,int r_flag) 
{
	int i,cf_num=3;
	double fit[3];
	double delta[3] = {10,30,50};
	double bias[3] = {0, 100, 200};
	i=0;
	hf05(x,&fit[i],nx,&Os[i*nx],&Mr[i*nx*nx],&SS[i*nx],1,r_flag);
	i=1;
	hf08(x,&fit[i],nx,&Os[i*nx],&Mr[i*nx*nx],&SS[i*nx],1,r_flag);
	i=2;
	hf09(x,&fit[i],nx,&Os[i*nx],&Mr[i*nx*nx],&SS[i*nx],1,r_flag);
	cf_cal(x, f, nx, Os, delta,bias,fit,cf_num);
}


void shiftfunc (double *x, double *xshift, int nx,double *Os)
{
	int i;
    for (i=0; i<nx; i++)
    {
        xshift[i]=x[i]-Os[i];
    }
}

void rotatefunc (double *x, double *xrot, int nx,double *Mr)
{
	int i,j;
    for (i=0; i<nx; i++)
    {
        xrot[i]=0;
			for (j=0; j<nx; j++)
			{
				xrot[i]=xrot[i]+x[j]*Mr[i*nx+j];
			}
    }
}

void sr_func (double *x, double *sr_x, int nx, double *Os,double *Mr, double sh_rate, int s_flag,int r_flag) /* shift and rotate */
{
	int i;
	if (s_flag==1)
	{
		if (r_flag==1)
		{	
			shiftfunc(x, y, nx, Os);
			for (i=0; i<nx; i++)//shrink to the original search range
			{
				y[i]=y[i]*sh_rate;
			}
			rotatefunc(y, sr_x, nx, Mr);
		}
		else
		{
			shiftfunc(x, sr_x, nx, Os);
			for (i=0; i<nx; i++)//shrink to the original search range
			{
				sr_x[i]=sr_x[i]*sh_rate;
			}
		}
	}
	else
	{	

		if (r_flag==1)
		{	
			for (i=0; i<nx; i++)//shrink to the original search range
			{
				y[i]=x[i]*sh_rate;
			}
			rotatefunc(y, sr_x, nx, Mr);
		}
		else
		for (i=0; i<nx; i++)//shrink to the original search range
		{
			sr_x[i]=x[i]*sh_rate;
		}
	}
}

void asyfunc (double *x, double *xasy, int nx, double beta)
{
	int i;
    for (i=0; i<nx; i++)
    {
		if (x[i]>0)
        xasy[i]=pow(x[i],1.0+beta*i/(nx-1)*pow(x[i],0.5));
    }
}

void oszfunc (double *x, double *xosz, int nx)
{
	// int i,sx;
	// double c1,c2,xx;
 //    for (i=0; i<nx; i++)
 //    {
	// 	if (i==0||i==nx-1)
 //        {
	// 		if (x[i]!=0)
	// 			xx=log(fabs(x[i]));
	// 		if (x[i]>0)
	// 		{	
	// 			c1=10;
	// 			c2=7.9;
	// 		}
	// 		else
	// 		{
	// 			c1=5.5;
	// 			c2=3.1;
	// 		}	
	// 		if (x[i]>0)
	// 			sx=1;
	// 		else if (x[i]==0)
	// 			sx=0;
	// 		else
	// 			sx=-1;
	// 		xosz[i]=sx*exp(xx+0.049*(sin(c1*xx)+sin(c2*xx)));
	// 	}
	// 	else
	// 		xosz[i]=x[i];
 //    }
}


void cf_cal(double *x, double *f, int nx, double *Os,double * delta,double * bias,double * fit, int cf_num)
{
	int i,j;
	double *w;
	double w_max=0,w_sum=0;
	w=(double *)malloc(cf_num * sizeof(double));
	for (i=0; i<cf_num; i++)
	{
		fit[i]+=bias[i];
		w[i]=0;
		for (j=0; j<nx; j++)
		{
			w[i]+=pow(x[j]-Os[i*nx+j],2.0);
		}
		if (w[i]!=0)
			w[i]=pow(1.0/w[i],0.5)*exp(-w[i]/2.0/nx/pow(delta[i],2.0));
		else
			w[i]=INF;
		if (w[i]>w_max)
			w_max=w[i];
	}

	for (i=0; i<cf_num; i++)
	{
		w_sum=w_sum+w[i];
	}
	if(w_max==0)
	{
		for (i=0; i<cf_num; i++)
			w[i]=1;
		w_sum=cf_num;
	}
	f[0] = 0.0;
    for (i=0; i<cf_num; i++)
    {
		f[0]=f[0]+w[i]/w_sum*fit[i];
    }
	free(w);
}
