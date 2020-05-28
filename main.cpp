#include <stdio.h>
#include <stdlib.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include <armadillo>
#include "Transform.hpp"
#include "CargaText.h"
#include "Face.h"
#include "Vertice.h"
#include <iostream>

using namespace std;

int main( void )
{
    arma::frowvec eye = {15.0, 0.0, 9.9};
    arma::frowvec camera = {0.0, 0.0, 0.0};
    
    GLFWwindow* window;
	
    Load sol;
    sol.loadObject("roca.obj");

    if( !glfwInit() )
    {
        fprintf( stderr, "Fallo al inicializar GLFW\n" );
        getchar();
        return -1;
    }

    window = glfwCreateWindow(1024, 768, "Sistema Solar", NULL, NULL);
	
    if( window == NULL ) {
        fprintf( stderr, "Fallo al abrir la ventana de GLFW.\n" );
        getchar();
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

//  Proyecciones
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);

    float ar = width / height;

//  Proyección en paralelo
    glViewport(0, 0, width, height);
    glOrtho(-ar, ar, -1.0, 1.0, -20.0, 20.0);

//  Proyección en perspectiva
//   glFrustum(-ar, ar, -ar, ar, 2.0, 4.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    Transform Tr = Transform();
    float t_angle = 0.0f;
    
	
    do {
        glClear( GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT );

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(eye[0], eye[1], eye[2], 
                camera[0], camera[1], camera[2], 
                0.0, 1.0, 0.0);

		float vel = 5.0f;
        // Dibujar el Sol
        arma::fmat transf_sol = Tr.S(0.3, 0.3, 0.3);
		sol.DibujaObj(transf_sol,-2.0,0.5,vel,t_angle);
		
		/*std::vector< Vertice> p_vertices = sol.get_faces_verts();
		std::vector< Vertice> sol_vertices;

	  for ( unsigned int i=0; i<p_vertices.size(); i++ ) {
            arma::fcolvec v = p_vertices[i].h();
            arma::fcolvec vp = transf_sol * v;
            Vertice rv = Vertice(vp[0],vp[1],vp[2]);
           // rv.setValue(arma::trans(vp));
            sol_vertices.push_back(rv);
			
        }
	*/
     /* glColor3f(1.0, 1.0, 0.0);
		glBegin(GL_TRIANGLES);//comienza la funcion de creacion de caras de 3 lados
        for ( unsigned int i=0; i<sol_vertices.size(); i++ ) {
            arma::frowvec vert = sol_vertices[i].getValue();
            glVertex3f(vert[0], vert[1], vert[2]);
        }
		glEnd();*/
		
        // Fin dibujado del Sol

        // Dibujar la Tierra
      //  t_angle = (t_angle < 360.0f) ? t_angle+5.0 : 0.0f;

      //  arma::fmat transf_tierra = Tr.R(0.0f, 1.0f, 0.0f, t_angle) * Tr.T(-0.7, 0.0, 0.0) * Tr.S(0.4, 0.4, 0.4) * transf_sol;
		
     /* std::vector< Vertice > tierra_vertices;
	  for ( unsigned int i=0; i<tierra.v.size(); i++ ) {
            arma::fcolvec v = tierra.v[i].getV();
            arma::fcolvec vp = transf_tierra * v;
            Vertice rv = Vertice();
            rv.Vertice(arma::trans(vp));
            tierra_vertices.push_back(rv);
        }
		
        glColor3f(0.0, 0.0, 1.0);
       glBegin(GL_TRIANGLES);//comienza la funcion de creacion de caras de 3 lados
        for ( unsigned int i=0; i<tierra_vertices.size(); i++ ) {
            arma::frowvec vert = tierra_vertices[i].getValue();
            glVertex3f(vert[0], vert[1], vert[2]);
        }
		glEnd();*/
        // Fin dibujado de la Tierra
		
		//dibujar la luna
       // l_angle = (l_angle <360.0f) ? l_angle+1.0 : 0.0f;
		//arma::fmat transf_luna
		
		glfwSwapBuffers(window);
        glfwPollEvents();

    } while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0 );

    glfwTerminate();

    return 0;
}