#ifndef VERTICE_H
#define VERTICE_H
#include <armadillo>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
struct Vertice{
	public:
        float x,y,z;
		//arma::fcolvec matriz;
		
        Vertice(float a,float b,float c);
		Vertice();
		arma::frowvec getValue();
		void setValue(arma::fcolvec trans);
		arma::fcolvec h();
};

#endif // VERTICE_H