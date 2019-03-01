void design_sphere(float radius, int slices, int stacks, const char* patch) {
	float r = radius;
	float height = radius;
    int max = slices*(stacks-1)+2;
    TAD_ARRAY_LIST() l1 = ARRAY_LIST(max);
    TAD_ARRAY_LIST() l2 = ARRAY_LIST(max);
    TAD_ARRAY_LIST() l3;
    TAD_ARRAY_LIST() l4;
    float alfaXoZ = (2*M_PI)/slices;
    float betaYoX = (2*radius)/stacks;
    int m1,m2;
    //cria ponto superior
    TAD_POINT p;
    p = POINT(0.0,radius,0.0);
    addElem(l1,p);
    //cria pontos intermédios
    for(m1=1;m1<stacks;m1++){ // itera circulos (muda o raio, alfaXoZ volta ao inicio)
    	height -= betaYoX; // calcula altura do circulo
        r = sqrt((radius*radius)-(height*height)); // muda o raio para o circulo correspondente
    	for(m2=0;m2<slices;m2++){ // itera vertices(muda o alfaXoZ)
            p = POINT(r*cos(m2*alfaXoZ),height,r*sin(m2*alfaXoZ));
            addElem(l1,p);
    	}
    }
    //cria ultimo ponto
    p = POINT(0.0,-radius,0.0);
    addElem(l1,p);
    // tenho stack + 1 camadas para ligar, a 1ª e a ultima têm 1 vertice
    for(m1=0;m1<stacks;m1++){ // vertices nas pontas = nº de slices
        for(m2=1;m2<=slices;m2++){ //  vertices interiores = nº de slices * 2
            if(m1==0){

                if(m2 == 1){
                    addElem(l2,POINT(getElem(l1,1),getElem(l1,slices),getElem(l1,2)));
                }
                else{
                    addElem(l2,POINT(getElem(l1,1),getElem(l1,m2),getElem(l1,m2+1)));
                }

            } else if(m1 == 3){
                
                if(m2 == 1){
                    addElem(l2,POINT(getElem(l1,max),getElem(l1,max-1),getElem(l1,max-slices)));
                }
                else{
                    addElem(l2,POINT(getElem(l1,max),getElem(l1,max-slices+m2-1),getElem(l1,max-slices+m2-2)));
                }

            } else{
                
                if(m2 == 1){
                    addElem(l2,POINT(getElem(l1,m1*slices+m2),getElem(l1,(m1+1)*slices+m2),getElem(l1,m1*slices+m2+1)));
                    addElem(l2,POINT(getElem(l1,m1*slices+m2+1),getElem(l1,(m1-1)*slices+m2+1),getElem(l1,m1*slices+m2)));
                }
                else{
                    addElem(l2,POINT(getElem(l1,(m1-1)*slices+m2),getElem(l1,m1*slices+m2),getElem(l1,m1*slices+m2+1)));
                    addElem(l2,POINT(getElem(l1,m1*slices+m2+1),getElem(l1,(m1-1)*slices+m2+1),getElem(l1,(m1-1)*slices+m2)));
                }

            }
        }
    }
    filter(l2,l3,l4);
}