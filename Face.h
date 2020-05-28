#ifndef FACE_H
#define FACE_H
#include <vector>///used only for the management of Vectors...
#include <iostream>
using namespace std;

//for faces, it can contain triangles and quads as well, the four variable contain which is that
struct Face{
	
		public:
		Face(int facen,int f1,int f2,int f3);
		Face(int facen,int f1,int f2,int f3,int f4);
        int facenum;
        bool four;
        int faces[4];
		void imprime();
};

#endif // FACE_H