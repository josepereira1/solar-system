#include <generatorCone.h>

void write_on_file(const char* data, const char* path) {

	FILE *fp = fopen(path, "w");
    if (fp != NULL)
    {
        fputs(data, fp);
        fclose(fp);
    }
}

void design_sphere(float radius, int slices, int stacks, const char* patch) {

}

void design_plane(float side, const char* patch) {
	float c = side / 2.0;
    char* str = malloc(sizeof(char)*1024*1024);
    sprintf(str,"2\n1 2 3\n1 3 4\n4\n %.5f, 0.0, -%.5f\n-%.5f, 0.0, -%.5f\n-%.5f, 0.0,  %.5f\n %.5f, 0.0,  %.5f \n",c,c,c,c,c,c,c,c);
    write_on_file(str,patch);
}

void design_box(float x, float y, float z, int divisions, const char* patch) {
	if(divisions == 0) {

	}
	else {
		
	}
}

TAD_ARRAYLIST design_cone(float radius, float height, int slices, int stacks, const char* patch) {
	float angle = (2*M_PI)/slices;
	TAD_POINT p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12;
    TAD_ARRAYLIST l = ARRAY_LIST(300);
    float tmp1, tmp2, fraction_height;

  	for(int i = 0; i < stacks; i++){
    	for(int j = 0; j < slices; j++){
	      	tmp1 = (radius - (radius/stacks)*i);
	      	tmp2 = (radius - (radius/stacks)*(i+1));
	      	fraction_height = (height/stacks)*i;

		    if(i == 0){ //  a base tem que ser voltada para baixo
		     	p1 = POINT(tmp1*sin(angle*j),  fraction_height, tmp1*cos(angle*j));
		        p2 = POINT(0.0,  (height/stacks)*i, 0.0);
		        p3 = POINT(tmp1*sin(angle*(j+1)),  fraction_height, tmp1*cos(angle*(j+1)));
		    }/*else{
		        p1 = POINT(tmp1*sin(angle*(j+1)),  fraction_height, tmp1*cos(angle*(j+1)));
		        p2 = POINT(0.0,  (height/stacks)*i, 0.0);
		        p3 = POINT(tmp1*sin(angle*j),  fraction_height, tmp1*cos(angle*j));
		    }*/

	      //  para não desenhar os triângulos interiores basta comentar as 3 linhas acima do else

	      	p4 = POINT(tmp1*sin(angle*(j+1)),  fraction_height, tmp1*cos(angle*(j+1)));
	      	p5 = POINT(tmp2*sin(angle*(j+1)), fraction_height+((height/stacks)), tmp2*cos(angle*(j+1)));
	      	p6 = POINT(tmp1*sin(angle*j),  fraction_height, tmp1*cos(angle*j));

	      	p7 = POINT(tmp2*sin(angle*(j+1)), fraction_height+((height/stacks)), tmp2*cos(angle*(j+1)));
	      	p8 = POINT(tmp2*sin(angle*j), fraction_height+((height/stacks)), tmp2*cos(angle*j));
	      	p9 = POINT(tmp1*sin(angle*j),  fraction_height, tmp1*cos(angle*j));
	      
	      	addElem(l,p1);
	      	addElem(l,p2);
	      	addElem(l,p3);
	      	addElem(l,p4);
	      	addElem(l,p5);
	      	addElem(l,p6);
	      	addElem(l,p7);
	      	addElem(l,p8);
	      	addElem(l,p9);
    	}
  	}
  return l;
}

int main(int argc, char** argv) {
	if(argc <= 1) {
		perror("Insufficient parameters!\n");
		exit(1);
	}
	if(strcmp(argv[1],"sphere")==0) {
		if(argc < 6) {
			perror("Insufficient parameters to generate sphere!\n");
			exit(1);
		}
		design_sphere(atof(argv[2]),atoi(argv[3]),atoi(argv[4]),argv[5]);
	}
	else if(strcmp(argv[1],"plane")==0) {
		if(argc < 4) {
			perror("Insufficient parameters to generate plane!\n");
			exit(1);
		}
		design_plane(atof(argv[2]),argv[3]);
	}
	else if(strcmp(argv[1],"box")==0) {
		if(argc < 7) {
			perror("Insufficient parameters to generate box!\n");
			exit(1);
		}
		if(argc < 6)
			design_box(atof(argv[2]),atof(argv[3]),atof(argv[4]),0,argv[5]);
		else 
			design_box(atof(argv[2]),atof(argv[3]),atof(argv[4]),atoi(argv[5]),argv[6]);
	}
	else if(strcmp(argv[1],"cone")==0) {
		if(argc < 7) {
			perror("Insufficient parameters to generate cone!\n");
			exit(1);
		}
		design_cone(atof(argv[2]),atof(argv[3]),atoi(argv[4]),atoi(argv[5]),argv[6]);
	}
	else {
		perror("Invalid geometric figure!\n");
		exit(2);
	}
	return 0;
}