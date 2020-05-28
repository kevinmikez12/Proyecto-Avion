#include "Vertice.h"
#include <armadillo>
#include <stdio.h>
#include <stdlib.h>

		Vertice::Vertice(float a,float b,float c) {
		x=a;
		y=b;
		z=c;
		}
		
		Vertice::Vertice() {
		}
		
	/* void Vertice::setValue(arma::fcolvec trans){
			matriz = trans;
			x = matriz.at(0);
			y = matriz.at(1);
			z = matriz.at(2);
	}*/
	
	arma::frowvec Vertice::getValue(){
	    arma::frowvec ren;
		ren.at(0) = x;
		ren.at(1) = y;
		ren.at(2) = z;
		ren.at(3) = 1;
		return (ren);
	}
	
	arma::fcolvec Vertice::h(){
			arma::fcolvec vh = {{x},
											  {y},
											  {z},
											  {1}};
											  return (vh);
	}