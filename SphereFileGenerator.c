void design_sphere(float radius, int slices, int stacks, const char* patch) {
	float r = radius;
	float height = radius;
    int max = slices*(stacks-1)+2;
    float alfaXoZ = (2*M_PI)/slices;
    float betaYoX = (2*radius)/stacks;
    char* str = malloc(sizeof(char)*1024*1024);
    char* tmp = malloc(sizeof(char)*1024*1024);
    int m1,m2;
        // nº de ligações de vertices
    sprintf(tmp,"%d\n",max);
    strcat(str,tmp);
    // tenho stack + 1 camadas para ligar, a 1ª e a ultima têm 1 vertice
    for(m1=0;m1<stacks;m1++){ // vertices nas pontas = nº de slices
        for(m2=1;m2<=slices;m2++){ //  vertices interiores = nº de slices * 2
            if(m1==0){

                if(m2 == 1){
                    sprintf(tmp,"%d, %d, %d\n",1,slices+1,2);
                    strcat(str,tmp);
                }
                else{
                    sprintf(tmp,"%d, %d, %d\n",1,m2,m2+1);
                    strcat(str,tmp);
                }

            } else if(m1 == 3){
                
                if(m2 == 1){
                    sprintf(tmp,"%d, %d, %d\n",max,max-1,max-slices);
                    strcat(str,tmp);
                }
                else{
                    sprintf(tmp,"%d, %d, %d\n",max,max-slices+m2-1,max-slices+m2-2);
                    strcat(str,tmp);
                }

            } else{
                
                if(m2 == 1){
                    sprintf(tmp,"%d, %d, %d\n",m1*slices+m2,(m1+1)*slices+m2,m1*slices+m2+1);
                    strcat(str,tmp);
                    sprintf(tmp,"%d, %d, %d\n",m1*slices+m2+1,(m1-1)*slices+m2+1,m1*slices+m2);
                    strcat(str,tmp);
                }
                else{
                    sprintf(tmp,"%d, %d, %d\n",(m1-1)*slices+m2,m1*slices+m2,m1*slices+m2+1);
                    strcat(str,tmp);
                    sprintf(tmp,"%d, %d, %d\n",m1*slices+m2+1,(m1-1)*slices+m2+1,(m1-1)*slices+m2);
                    strcat(str,tmp);
                }

            }
        }
    }
    // Inserir número de vertices desenhados 
    sprintf(tmp,"%d\n",max);
    strcat(str,tmp);
    //cria ponto superior
    sprintf(tmp,"%.5f, %.5f, %.5f\n",0.0,radius,0.0);
    strcat(str,tmp);
    //cria pontos intermédios
    for(m1=1;m1<stacks;m1++){ // itera circulos (muda o raio, alfaXoZ volta ao inicio)
    	height -= betaYoX; // calcula altura do circulo
        r = sqrt((radius*radius)-(height*height)); // muda o raio para o circulo correspondente
    	for(m2=0;m2<slices;m2++){ // itera vertices(muda o alfaXoZ)
    		sprintf(tmp,"%.5f, %.5f, %.5f\n",r*cos(m2*alfaXoZ), height,r*sin(m2*alfaXoZ));
            strcat(str,tmp);
    	}
    }
    //cria ultimo ponto
    sprintf(tmp,"%.5f, -%.5f, %.5f\n",0.0,radius,0.0);
    strcat(str,tmp);
}