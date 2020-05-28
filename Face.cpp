#include "Face.h"
#include <iostream>

        Face::Face(int facen,int f1,int f2,int f3) { //constructor for triangle
				facenum = facen;
			    faces[0]=f1;
                faces[1]=f2;
                faces[2]=f3;
                four=false;
        }
		
		
       Face::Face(int facen,int f1,int f2,int f3,int f4) { //overloaded constructor for quad
                facenum = facen;
				faces[0]=f1;
                faces[1]=f2;
                faces[2]=f3;
                faces[3]=f4;
                four=true;
        }
		
		void Face::imprime(){
			printf("---------Edges----------\n");
			for(int i =0; i < 4; i++){
				printf("%d  \t ",faces[i]);
				
			}
			printf("\n");
		}