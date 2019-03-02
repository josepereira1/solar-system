design_plane(int f,const* char file){
    float c = side / 2.0;
    TAD_ARRAYLIST l = new ARRAYLIST(6);
    addElem(l,POINT(c,0.0,-c));
    addElem(l,POINT(-c,0.0,-c));
    addElem(l,POINT(-c,0.0,c));
    addElem(l,POINT(-c,0.0,c));
    addElem(l,POINT(c,0.0,c));
    addElem(l,POINT(c,0.0,-c));
    filter(l);
}
