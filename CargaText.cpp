#include <vector>//biblioteca para el  uso de listas en el programa
#include <GL/glu.h>//esta biblioteca nos permite utilizar las funciones para crear los objetos (triangulos,cuadrados,colores,etc)
#include "CargaText.h"//biblioteca para la carga de archivo y creacion de objetos
#include <algorithm>
#include <fstream>
#include <cstdlib>
#include <armadillo>
#include <iostream>
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include "Face.h"
#include "Vertice.h"
#include "Transform.hpp"


using namespace std;

void Load::loadObject(const char* filename)
{
       
	    std::vector<std::string> coord;   //lista donde se guardara el contenido de cada linea
        Load:: v;	//lista donde se guardaran todos los vertices del archivo
        Load:: f; //lista donde se guardaran todos las caras
		Load::vn;
        std::ifstream in(filename);     //cariable que utilizaremos para leer el archivo .obj
        if(!in.is_open())       //si no es abierto regresa un menos 1
        {
                std::cout << "Error al Abrir." << std::endl;
        }
        char buf[256]; //creamos el buffer que guardara el contenido de cada linea en el archivo .obj
        /**ciclo de lectura del archivo**/
        while(!in.eof())
        {
                in.getline(buf,256);//se guardan las lineas con su respectivo valor en la lista
                std::string cad(buf);
				coord.push_back(cad);//coord es el que guarda el contenido de buf antes de actualizar.
        }
        /**ciclo donde se hace la indentificacion de tipo de valores en el archivo**/
        for(int i=0;i<coord.size();i++)
        {
                if(coord[i].c_str()[0]=='#')   //es un comentario(si su primer caracter es #)
                        continue;       //si es asi continuamos con la lectura ya que no nos interesa los comentarios en estos momentos
                else if(coord[i].c_str()[0]=='v' && coord[i].c_str()[1]==' ') //condicional si es un vector 
                {
                        float tmpx,tmpy,tmpz;
                        sscanf(coord[i].c_str(),"v %f %f %f",&tmpx,&tmpy,&tmpz);       //se leen los tres flotantes de de coord y se almacenan en tmpx,tmpy,tmpz
                        Vertice  vert(tmpx,tmpy,tmpz);
						v.push_back(vert);       //al obtener los valores de los flotantes los guardamos en la lista de vectores
                }else if(coord[i].c_str()[0]=='v' && coord[i].c_str()[1]=='n')        //if normal vector
                {
                        float tmpx,tmpy,tmpz;   //do the same thing
                        sscanf(coord[i].c_str(),"vn %f %f %f",&tmpx,&tmpy,&tmpz);
						Vertice nov(tmpx,tmpy,tmpz);
						vn.push_back(nov);
				}else if(coord[i].c_str()[0]=='f')     //si es una cara
                {
                        int a,b,c,d,e;
                        if(count(coord[i].begin(),coord[i].end(),' ')==3)     //condicion si es una cara tipo triangulo (ya que se pueden identificar por sus 3 espacios)
                        {
                  sscanf(coord[i].c_str(),"f %d//%d %d//%d %d//%d",&a,&b,&c,&b,&d,&b);
				  //sscanf(coord[i]->c_str(),"f %d %d %d ",&a,&b,&c);
							   Face cara(b,a,c,d);
							   f.push_back(cara);     //se leen de coord y se almacenan en las variables temporales, y despues se guardan en la lista de tipo cara
                        }else{
                                sscanf(coord[i].c_str(),"f %d//%d %d//%d %d//%d %d//%d",&a,&b,&c,&b,&d,&b,&e,&b);
                                Face cara(b,a,c,d,e);
								f.push_back(cara);   //se hace el mismo proceso que triangulo solo que se llama a un constructor distinto y se acomodan los datos de distinta manera.
                        }
                }
        }
		
		//set_faces_verts(v);
		
		for(int i =0; i<f.size();i++){
			printf("        Face %d :    \n",i+1);
			f[i].imprime();
		}
		/*for(int i=0;i<coord.size();i++)
                coord.clear();
        for(int i=0;i<f.size();i++)
                f.clear();
        for(int i=0;i<v.size();i++)
                v.clear();*/
			
}

void Load::DibujaObj(arma::fmat trans,float posi,float scale,float vel,float angle){
		Transform Tr = Transform();
		
		//angle = (angle < 360.0f) ? angle+vel : 0.0f;
		float a;
		a = angle;
		angle + vel;
		if(a<360){
			a + vel;
		}else{
			a = 0.0;
		}
		//transf = trans * Tr.R(0.0f,1.0f,0.0f,angle) * Tr.T(posi,0.0,0.0) * Tr.S(scale,scale,scale);
		transf = trans*Tr.R(0.0f, 1.0f, 0.0f, angle) * Tr.T(posi, 0.0, 0.0) * Tr.S(scale,scale,scale) ;
		
		std::vector< Vertice> p_vertices = v;
		std::vector< Vertice> sol_vertices;

	  for ( unsigned int i=0; i<p_vertices.size(); i++ ) {
            arma::fcolvec v = p_vertices[i].h();
            arma::fcolvec vp = transf * v;
            Vertice rv = Vertice(vp[0],vp[1],vp[2]);
            sol_vertices.push_back(rv);
        }
		        for(int i=0;i<sol_vertices.size();i++)
                printf(" %d =====>%f, %f, %f \n",i+1,sol_vertices[i].x,sol_vertices[i].y,sol_vertices[i].z);
			
      glColor3f(255, 255, 0);
	  
	  for(int i=0;i<f.size();i++) //ciclo de dibujado
        {
		glBegin(GL_TRIANGLES);//comienza la funcion de creacion de caras de 3 lados
			    glNormal3f(vn[f[i].facenum-1].x,vn[f[i].facenum-1].y,vn[f[i].facenum-1].z);
				glVertex3f(sol_vertices[f[i].faces[0]-1].x,sol_vertices[f[i].faces[0]-1].y,sol_vertices[f[i].faces[0]-1].z);
				glVertex3f(sol_vertices[f[i].faces[1]-1].x,sol_vertices[f[i].faces[1]-1].y,sol_vertices[f[i].faces[1]-1].z);
				glVertex3f(sol_vertices[f[i].faces[2]-1].x,sol_vertices[f[i].faces[2]-1].y,sol_vertices[f[i].faces[2]-1].z);
		glEnd();
		}
		/*glBegin(GL_POLYGON);//comienza la funcion de creacion de caras de 3 lados
        for ( unsigned int i=0; i<sol_vertices.size(); i++ ) {
			arma::fcolvec vert = sol_vertices[i].h();
			glVertex3f(vert[0], vert[1], vert[2]);
           // glVertex3f(sol_vertices[i].x, sol_vertices[i].y, sol_vertices[i].z);
        }
		glEnd();*/
}

/*void Load::set_faces_verts(vector<Vertice> x){
	test = x;
}*/
/*vector <Vertice> Load::get_faces_verts(){
	return test;
}*/