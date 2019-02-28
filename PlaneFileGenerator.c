designPlane(int f,const* char file){
    float c = f%2;
	glBegin(GL_TRIANGLES);
    
	glColor3f(255,0,0);
    glVertex3f(  -c, 0.0f, -c );
    glVertex3f(  -c, 0.0f,  c );
    glVertex3f(   c, 0.0f, -c );

    glVertex3f(  c, 0.0f, -c );
    glVertex3f( -c, 0.0f,  c );
    glVertex3f(  c, 0.0f,  c );
	glEnd();
    
    glEnable(GL_CULL_FACE);

	// End of frame
	glutSwapBuffers();
}