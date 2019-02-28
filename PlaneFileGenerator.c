design_plane(int f,const* char file){
    float c = side / 2.0;
    char* str = malloc(sizeof(char)*1024*1024);
    sprintf(str,"2\n1 2 3\n1 3 4\n4\n %.5f, 0.0, -%.5f\n-%.5f, 0.0, -%.5f\n-%.5f, 0.0,  %.5f\n %.5f, 0.0,  %.5f \n",c,c,c,c,c,c,c,c);
    write_on_file(str,patch);
}
