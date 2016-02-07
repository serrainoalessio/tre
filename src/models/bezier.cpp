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
Bezier::Bezier(uint gc, uint sc, uint* indexes):
    generatorCount(gc), sampleCount(sc),
    W(sc, gc), W_inv(gc, sc), Gen(gc,2), GenN(gc,2), Samples(sc,2)
{
    generatorsIndexes = new uint[gc];
    generators = new Point2D[gc];
    generatorsNew = new Point2D[gc];
    samples = new Point2D[sc];

    Gen.setData((float*) &generators[0]);
    GenN.setData((float*) &generatorsNew[0]);
    Samples.setData((float*) &samples[0]);

    //copy locally the generators indexes
    memcpy(generatorsIndexes, indexes, sizeof(uint)*gc);

    //compute the weight matrix
    float step = 1.0f/(sc - 1);
    for(uint j = 0;j < sc;j++){
        float t = step*j;
        for(uint i = 0;i < gc;i++){
            W(i,j) = binomial(gc-1,i)*pow(1-t,gc-i-1)*pow(t,i);
        }
    }

    W.invert(W_inv);
}

void Bezier::setGenerators(vector<Point2D>& points){
    for (size_t i = 0; i < generatorCount; i++) {
        uint index = generatorsIndexes[i];
        if(index >= points.size()){
            cout << CONSOLE_RED << "Error in bezier curve, point index " << index << " is out of range" << CONSOLE_RESET << endl;
        }else{
            generators[i] = points[index];
        }
    }
}

void Bezier::computeSamples(){
    W.multiply(Gen,Samples);
}

void Bezier::computeGenerators(){
    W_inv.multiply(Samples,GenN);
}


void Bezier::draw(Image& img){
    for (size_t i = 0; i < sampleCount; i++) {
        img.add(samples[i][0],samples[i][1],1.0f);
    }
}
