void drawCone(float radius, float height, int slices){
	glBegin(GL_TRIANGLES);

		float angle = (2*M_PI)/slices;


		for(int i = 0; i < slices; i++){
			//	sin(0) = 1	cos(0) = 0
			if(i % 2 == 0)
				glColor3f(255,0,0);
			else
				glColor3f(0,255,0);

			glVertex3f(radius*sin(angle*i),  0.0, radius*cos(angle*i));	
			glVertex3f(0.0,  0.0, 0.0);
			glVertex3f(radius*sin(angle*(i+1)),  0.0, radius*cos(angle*(i+1)));

			glVertex3f(radius*sin(angle*(i+1)),  0.0, radius*cos(angle*(i+1)));
			glVertex3f(0.0,  height, 0.0);	
			glVertex3f(radius*sin(angle*i),  0.0, radius*cos(angle*i));


		}
	glEnd();
}