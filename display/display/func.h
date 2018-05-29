#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <time.h>
#include <float.h>

#define INF 1.0e9
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

#define FU 0.5 //缩放因子
#define CR 0.8 //杂交控制参数 

class Function {
	public:
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
		/*void PSO();
		void DE();
		void Init_x();
		void get_funcnum(int input);*/
	private:
		double *OShift,*M,*y,*z,*x_bound;
		int ini_flag=0,n_flag,func_flag,*SS;
		/*-------------------------------------------------------
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
		int funcnum; //存储当前函数序号*/
};
