/* Calculates delta E based on temperature, density and isospin.  Odd-Even
 * staggering may also be taken into account. 
 * Note: temperature is in unite of T9, density is in unite of log_10(rhoYe)*/




#define MAX_T      100.0
#define MAX_RHO    11.0
#define MIN_T      5.0
#define MIN_RHO    8.0
#define N_T        4
#define N_RHO      4

double grid_T[N_T] = {5.0, 10.0, 30.0, 100.0};
double grid_rho[N_RHO] = {8.0, 9.0, 10.0, 11.0};

double a[N_T][N_RHO] = {{1.77, 1.86, 2.26, 4.01},
	{2.6, 2.67, 2.96, 3.85},
	{2.13, 2.13, 2.36, 2.5},
	{-1.87, -1.86, -1.83, -2.17}};
double b[N_T][N_RHO] = {{-14.2, -13.7, -8.26, 52.8},
	{-10.4, -8.19, 1.94, 55.7},
	{11.6, 13.5, 26.3, 72.4},
	{101.0, 101.0, 103.0, 123.0}};
double c[N_T][N_RHO] = {{3.31, 3.5, 3.37, -1.87},
	{3.62, 3.56, 2.72, -2.25},
	{1.10, 0.894, -0.29, -4.75},
	{-9.99, -10.0, -10.2, -12.5}};
double b_oo[N_T][N_RHO] = {{-29.7, -34.6, -22.6, 45.3},
	{-18.6, -20.0, -10.6, 48.5},
	{13.4, 13.9, 23.4, 68.2},
	{123.0, 123.0, 124.0, 143.0}};
double c_oo[N_T][N_RHO] = {{6.69, 7.83, 7.54, 79},
	{6.52, 6.99, 6.39, 0.452},
	{3.42, 3.37, 2.45, -2.1},
	{-9.99, -10.0, -10.2, -12.5}};
double b_oe[N_T][N_RHO] = {{-20.1, -22.6, -10.7, 54.0},
	{-15.0, -14.6, -1.52, 56.4},
	{8.09, 9.61, 22.4, 69.2},
	{91.7, 91.9, 93.5, 114.0}};
double c_oe[N_T][N_RHO] = {{4.11, 4.85, 4.34, -1.7},
	{4.22, 4.47, 3.56, -2.03},
	{1.46, 1.31, 0.209, -4.34},
	{-9.16, -9.18, -9.35, -11.6}};
double b_ee[N_T][N_RHO] = {{-16.7, -17.8, -9.58, 52.1},
	{-13.7, -12.8, -1.76, 53.7},
	{4.62, 5.83, 19.1, 67.1},
	{72.6, 72.7, 73.9, 91.3}};
double c_ee[N_T][N_RHO] = {{2.25, 2.66, 2.4, -3.16},
	{2.06, 2.24, 1.6, -3.54},
	{-0.665, -0.765, -1.74, -5.99},
	{-10.6, -10.6, -10.7, -12.6}};
double b2_oo[N_T][N_RHO] = {{-138.0, -162.0, -116.0, 177.0},
	{-105.0, -112.0, -70.0, 193.0},
	{48.3, 48.5, 89.2, 295.0},
	{616.0, 616.0, 617.0, 686.0}};
double c2_oo[N_T][N_RHO] = {{5.35, 6.3, 6.92, 3.24},
	{5.97, 6.41, 6.37, 3.00},
	{4.14, 4.16, 3.72, 1.02},
	{-5.0, -5.0, -5.02, -6.19}};
double b2_oe[N_T][N_RHO] = {{-96.3, -104, -60.0, 246},
	{-86.1, -82.9, -20.7, 259},
	{30.2, 33.4, 94.9, 334},
	{505, 505, 508, 593}};
double c2_oe[N_T][N_RHO] = {{3.23, 3.77, 4.05, 0.662},
	{3.77, 4.01, 3.72, 0.395},
	{1.85, 1.82, 1.27, -1.65},
	{-6.72, -6.72, -6.75, -8.04}};
double b2_ee[N_T][N_RHO] = {{-82.4, -82.8, -50.1, 229},
	{-75.5, -70.1, -20.7, 239},
	{17.1, 20.7, 83.5, 323},
	{372, 372, 375, 450}};
double c2_ee[N_T][N_RHO] = {{1.58, 1.83, 2.09, -.812},
	{1.61, 1.79, 1.73, -1.16},
	{-.444, -.467, -.886, -3.41},
	{-8.44, -8.44, -8.46, -9.61}};

/* For the definitions of
 * model0~model4, please refer to PRC,95,025805(2017)*/
//#define USE_MOD0
#define USE_MOD1
//#define USE_MOD2
//#define USE_MOD3
//#define USE_MOD4


double get_inter_val(double rho, double T, int index_rho, int index_T, int A, int Z)
{
	double temp_ij, temp_ij1, temp_i1j, temp_i1j1, delta_e, rho_interval, T_interval;
	double ispin;

#ifdef USE_MOD1
	temp_ij = a[index_T][index_rho];
	temp_ij1 = a[index_T+1][index_rho];
	temp_i1j = a[index_T][index_rho+1];
	temp_i1j1 = a[index_T+1][index_rho+1];
#endif
#ifdef USE_MOD2
	ispin = (A-2.0*Z)/A;
	temp_ij = b[i][j] * ispin + c[i][j];
	temp_ij1 = b[i][j+1] * ispin + c[i][j+1];
	temp_i1j = b[i+1][j] * ispin + c[i+1][j];
	temp_i1j1 = b[i+1][j+1] * ispin + c[i+1][j+1];
#endif
#ifdef USE_MOD3
	N = A - Z;
	ispin = (A-2.0*Z)/A;
	if (N%2 == 1 && Z%2 == 1) {
		temp_ij = b_oo[i][j] * ispin + c_oo[i][j];
		temp_ij1 = b_oo[i][j+1] * ispin + c_oo[i][j+1];
		temp_i1j = b_oo[i+1][j] * ispin + c_oo[i+1][j];
		temp_i1j1 = b_oo[i+1][j+1] * ispin + c_oo[i+1][j+1];
	}
	else if (N%2 == 0 && Z%2 == 0) {
		temp_ij = b_ee[i][j] * ispin + c_ee[i][j];
		temp_ij1 = b_ee[i][j+1] * ispin + c_ee[i][j+1];
		temp_i1j = b_ee[i+1][j] * ispin + c_ee[i+1][j];
		temp_i1j1 = b_ee[i+1][j+1] * ispin + c_ee[i+1][j+1];
	}
	else {
		temp_ij = b_oe[i][j] * ispin + c_oe[i][j];
		temp_ij1 = b_oe[i][j+1] * ispin + c_oe[i][j+1];
		temp_i1j = b_oe[i+1][j] * ispin + c_oe[i+1][j];
		temp_i1j1 = b_oe[i+1][j+1] * ispin + c_oe[i+1][j+1];

	}
#endif
#ifdef USE_MOD4
	N = A - Z;
	ispin = (A-2.0*Z)/A;
	if (N%2 == 1 && Z%2 == 1) {
		temp_ij = b2_oo[i][j] * ispin * ispin + c2_oo[i][j];
		temp_ij1 = b2_oo[i][j+1] * ispin * ispin + c2_oo[i][j+1];
		temp_i1j = b2_oo[i+1][j] * ispin * ispin + c2_oo[i+1][j];
		temp_i1j1 = b2_oo[i+1][j+1] * ispin * ispin + c2_oo[i+1][j+1];
	}
	else if (N%2 == 0 && Z%2 == 0) {
		temp_ij = b2_ee[i][j] * ispin * ispin + c2_ee[i][j];
		temp_ij1 = b2_ee[i][j+1] * ispin * ispin + c2_ee[i][j+1];
		temp_i1j = b2_ee[i+1][j] * ispin * ispin + c2_ee[i+1][j];
		temp_i1j1 = b2_ee[i+1][j+1] * ispin * ispin + c2_ee[i+1][j+1];
	}
	else {
		temp_ij = b2_oe[i][j] * ispin * ispin + c2_oe[i][j];
		temp_ij1 = b2_oe[i][j+1] * ispin * ispin + c2_oe[i][j+1];
		temp_i1j = b2_oe[i+1][j] * ispin * ispin + c2_oe[i+1][j];
		temp_i1j1 = b2_oe[i+1][j+1] * ispin * ispin + c2_oe[i+1][j+1];
	}
#endif

	rho_interval = grid_rho[index_rho+1] - grid_rho[index_rho];
	T_interval = grid_T[index_T+1] - grid_T[index_T];
	delta_e = T * rho * (temp_i1j1 - temp_ij1 - temp_i1j + temp_ij) / rho_interval / T_interval
		+ rho * (grid_T[index_T+1] * (temp_ij1 - temp_ij) - grid_T[index_T] * (temp_i1j1 - temp_i1j)) / rho_interval / T_interval
		+ T * (grid_rho[index_rho+1] * (temp_i1j - temp_ij) - grid_rho[index_rho] * (temp_i1j1 - temp_ij1)) / rho_interval / T_interval
		+ (grid_rho[index_rho+1] * grid_T[index_T+1] * temp_ij - grid_rho[index_rho+1] * grid_T[index_T] * temp_i1j) / rho_interval / T_interval
		+ (grid_rho[index_rho] * grid_T[index_T] * temp_i1j1 - grid_rho[index_rho] * grid_T[index_T+1] * temp_ij1) / rho_interval / T_interval;

	return delta_e;
}

int get_rho_index(double rho)
{
	int i;
	if (rho > MAX_RHO)
		return -1;
	if (rho < MIN_RHO)
		return -2;
	for (i = 0; i < N_RHO-1; i++) {
		if (rho >= grid_rho[i] && rho <= grid_rho[i+1]) {
			return i;
		}
	}

	return -3;
}
int get_T_index(double T)
{
	int i;
	if (T > MAX_T)
		return -1;
	if (T < MIN_T)
		return -2;
	for (i = 0; i < N_T-1; i++) {
		if (T >= grid_T[i] && T <= grid_T[i+1]) {
			return i;
		}
	}

	return -3;
}
double get_delta_e_(double *temperature,
		   double *rho,
		   int *A,
		   int *Z)
{
#ifdef USE_MOD0
	return 2.5;
#endif
	int index_rho, index_T;
	double delta_e;

	index_rho = get_rho_index(*rho);
	index_T = get_T_index(*temperature);

	/* if temperature and density are in the range of the grid, 
	 * use model 0 (return 2.5) */
	if (index_T < 0 || index_rho < 0) 
		return 2.5;
	delta_e = get_inter_val(*rho, *temperature, index_rho, index_T, *A, *Z);

	return delta_e;
}
		   
