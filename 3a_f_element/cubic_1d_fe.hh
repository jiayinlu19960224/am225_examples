#ifndef CUBIC_1D_FE_HH
#define CUBIC_1D_FE_HH

#include "conj_grad.hh"

#include <cstdio>
#include <cmath>

class cubic_1d_fe : public conj_grad {
    public:
        const int n;
        double* const f;
        const double h;
        double g;
        cubic_1d_fe(int n_) : conj_grad(3*n_),
           n(n_), f(new double[3*n+1]), h(1./3/n) {}
        virtual ~cubic_1d_fe() {delete [] f;}
        void init_const();
        void init_slope();
        void init_mms();
        double l2_norm_mms();
        void print_matrix();
        void print(FILE *fp);
        void print(const char* filename);
        inline void print() {print(stdout);}
        virtual void mul_A(double *in,double *out);
    private:
        inline double mms_dsq(double xx,double s) {
            double del=exp(1-xx)*sin(5*M_PI*xx)-s;
            return del*del;
        }
        void assemble_b();
        double *rk;
        double *pk;
        double *zk;
        double *yk;
};

#endif
