#include "Face.h"
#include "Vertice.h"
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include "Transform.hpp"
#include <armadillo>
#ifndef CARGARTEXT__H //definimos nuestra biblioteca 
#define CARGARTEXT_H

using namespace std;//hacemos mencion del espacio que estemos creando

struct Load{//creamos estructura de tipo load para poder utilizar la el metodo loadObject
	public:
	    void loadObject(const char* filename);//hacemos referencia en el metodo contenido en la estructura
		std::vector<Vertice> v;	//lista donde se guardaran todos los vertices del archivo
        vector<Vertice> vn;
		std::vector<Face> f; 
		arma::fmat transf;
		//void set_faces_verts(vector<Vertice> x);
		//vector <Vertice> get_faces_verts();
		void DibujaObj(arma::fmat trans,float a,float b,float c,float d);
};

#endif //cerramos nuestra biblioteca
