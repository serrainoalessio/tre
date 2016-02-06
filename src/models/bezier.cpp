#include "models/bezier.hpp"

//TODO bad bad bad code
float binomial(float n, float k){
    float num, den;

	den = 1;
	num = 1;
	for (int i =  1  ; i <= k   ; i = i+1) den *= i;
	for (int j = n-k+1; j<=n; j=j+1)       num *= j;

    return num/den;
}

/* gc = number of generators, sc = number of samples */
Bezier::Bezier(int gc,int sc): W(sc, gc), W_inv(gc, sc), B(gc,2), C(sc,2) {
    generators.reserve(gc);
    points.resize(sc);

    B.setData((float*) &generators[0]);
    C.setData((float*) &points[0]);

    //compute the weight matrix
    float step = 1.0f/(sc - 1);
    for(int j = 0;j < sc;j++){
        float t = step*j;
        for(int i = 0;i < gc;i++){
            W(i,j) = binomial(gc-1,i)*pow(1-t,gc-i-1)*pow(t,i);
        }
    }

    W.invert(W_inv);
}

void Bezier::computePoints(){
    W.multiply(B,C);
}

void Bezier::computeGenerators(){
    W_inv.multiply(C,B);
}
