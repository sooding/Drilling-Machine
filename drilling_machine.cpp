// drill.cpp : Defines the entry point for the console application.
//
//*COMPUTER GRAPHICS PROJECT*/

/*ABHISHEK SOOD A (1PI06CS005)*/

/*SIMULATION OF A RADIAL ARM DRILLING MACHINE*/

/*FEATURES:

*/

#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <GL/glut.h>

void draw_pixel(GLint cx, GLint cy);
void plotpixels(GLint h, GLint k, GLint x, GLint y);
void wheel(GLint h, GLint k, GLint r) ;
void mydisplay();
void init();
void base();
int chunkx=260,chunky=-20,chunkx1=320,chunky1=-30,chunkx2=280,chunky2=-40,chunkx3=300,chunky3=-40;

//A global variable to change the drill bit size
double drill_size=10;

int drillduration=0;
//Variables to rotate the machine
int spin_x, spin_y, spin_z;                    
int old_x, old_y, move_z;

//General variables
int h,w,i,screen=0; 

//Variable to check whether power is on and to change color and to show output
int work=2,work_done=0;

//Variable to make horizontal movement of 
int translate=350; 

//Variable to make vertical movements
int movement=0; 

//flag variables to check the key pressed
int left=0,right=0,up=0,down=0,dspd=1;

//
GLfloat angle=0.0,trans_angle=0.0,move_angle=0.0;

//Flag Variable to check the type of object
int oc=0,op=0,ot=0,ocy=0;
int done=0;
int swing=0,swing_angle=10;



void base()
{
	glPushMatrix();
		glColor3f(.35,.15,.29);
	    glTranslatef ( -55,-475,-40 );
		glScalef ( 5.0 , 0.5 , 2.0 );
     	glutSolidCube ( 200 );
	glPopMatrix();
	glPushMatrix();
		glColor3f(0.,0.,0.);
        glTranslatef ( -55,-475,-40 );
		glScalef ( 5.0 , 0.5 , 2.0 );
     	glutWireCube ( 200 );
	glPopMatrix();
	glPushMatrix();
		glColor3f(.35,.15,.29);
		glTranslatef(-350,-350,-70);
		glutSolidCube(170);	
   	glPopMatrix();
	glPushMatrix();
		glColor3f(0.,0.,0.);
		glTranslatef(-350,-350,-70);
		glutWireCube(170);	
   	glPopMatrix();
	glColor3f(0.5,0.5,0.5);
		
}


void arm()
{
		glBegin(GL_LINE_LOOP);
			glVertex3f(-350,275,70);
			glVertex3f(-350,100,70);
			glVertex3f(475,200,70);
			glVertex3f(475,275,70);
		glEnd();
		glBegin(GL_LINE_LOOP);
			glVertex3f(-350,275,-70);
			glVertex3f(-350,100,-70);
			glVertex3f(475,200,-70);
			glVertex3f(475,275,-70);
		glEnd();
		glBegin(GL_LINE_LOOP);
			glVertex3f(-375,300,70);
			glVertex3f(-375,75,70);
			glVertex3f(485,175,70);
			glVertex3f(485,300,70);
		glEnd();
		glBegin(GL_LINE_LOOP);
			glVertex3f(-375,300,-70);
			glVertex3f(-375,75,-70);
			glVertex3f(485,175,-70);
			glVertex3f(485,300,-70);
		glEnd();
		glBegin(GL_LINES);
			glVertex3f(-350,275,70);
			glVertex3f(-350,275,-70);
		glEnd();
		glBegin(GL_LINES);
			glVertex3f(-350,100,70);
			glVertex3f(-350,100,-70);
		glEnd();
		glBegin(GL_LINES);
			glVertex3f(475,200,70);
			glVertex3f(475,200,-70);
		glEnd();
		glBegin(GL_LINES);
			glVertex3f(475,275,70);
			glVertex3f(475,275,-70);
		glEnd();
		glBegin(GL_LINES);
			glVertex3f(-375,300,70);
			glVertex3f(-375,300,-70);
		glEnd();
		glBegin(GL_LINES);
			glVertex3f(-375,75,70);
			glVertex3f(-375,75,-70);
		glEnd();
		glBegin(GL_LINES);
			glVertex3f(485,175,70);
			glVertex3f(485,175,-70);
		glEnd();
		glBegin(GL_LINES);
			glVertex3f(485,300,70);
			glVertex3f(485,300,-70);
		glEnd();
}


//Function to handle the selection of Drill Size in the menu option
void Drill_Size(int id)
{
	drill_size=id;
	glutPostRedisplay();
}
void drawSpokes()
{
	GLUquadricObj *p = gluNewQuadric();
	glColor3f(0,0,0);
	glPushMatrix();
	glTranslatef(-360,200,0);
	glRotatef(90,0.,1.,0.);
	if(left == 1 || right == 1)
	{
		glRotatef(trans_angle,-1.,0.,0.);
	}
	gluQuadricDrawStyle(p, GLU_LINE);
	gluCylinder(p, 3, 3, 100, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-360,200,0);
	glRotatef(90,0.,-1.,0.);
	if(left == 1 || right == 1)
	{
		glRotatef(trans_angle,1.,0.,0.);
	}	
	gluQuadricDrawStyle(p, GLU_LINE);
	gluCylinder(p, 3, 3, 100, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-350,200,0);
	glRotatef(90,-1.,0.,0.);	
	if(left == 1 || right == 1)
	{
		glRotatef(trans_angle,0.,-1.,0.);
	}	
	gluQuadricDrawStyle(p, GLU_LINE);
	gluCylinder(p, 3, 3, 100, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-350,200,0);
	glRotatef(90,1.,0.,0.);	
	if(left == 1 || right == 1)
	{
		glRotatef(trans_angle,0.,1.,0.);
	}	
	gluQuadricDrawStyle(p, GLU_LINE);
	gluCylinder(p, 3, 3, 100, 10, 10);
	glPopMatrix();	 
	glColor3f(0.5,0.5,0.5);
}

//Function to handle the selection of Object in the menu option
void Obj_Type(int id1)
{
	
	if(id1 == 1)
	{
		//cube flag is selected and all flags are set to 0
		oc=1;op=0;ot=0;ocy=0; 
		glutPostRedisplay();				
	}

	if(id1 == 2)
	{
		//Parellolpiped flag is selected and all flags are set to 0
		oc=0;op=1;ot=0;ocy=0;
		glutPostRedisplay();				
	}

	if(id1 == 3)
	{
		//Triangle flag is selected and all flags are set to 0
		oc=0;op=0;ot=1;ocy=0;
		glutPostRedisplay();
	}
		
	if(id1 == 4)
	{
		//cylinder flag is selected and all flags are set to 0
		oc=0;op=0;ot=0;ocy=1;
		glutPostRedisplay();
	}

}

void reshape(int width, int height)
{
    
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity ();
}
void chunks(){

	
	glPushMatrix();
	glTranslatef(chunkx+(rand()%50),chunky+(rand()%50),0);
	glutSolidSphere(10,20,20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(chunkx1+(rand()%50),chunky1+(rand()%50),0);
	glutSolidSphere(5,20,20);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(chunkx2+(rand()%50),chunky2+(rand()%50),0);
	glutSolidSphere(10,20,20);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(chunkx3+(rand()%50),chunky3+(rand()%50),0);
	glutSolidSphere(7,20,20);
	glPopMatrix();

}


void drillbit(){

	GLUquadricObj *p = gluNewQuadric();
	glPushMatrix();
	glTranslatef(translate,movement+125,-70);
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glColor3f(.5,.5,.5);
	glutWireCube(50);
	glPopAttrib();
	glPopMatrix();
	 
	 /*Drill Bit*/
	 //Cylinder of the drill bit
	glPushMatrix();
	glTranslatef(translate,movement+95,-70);		
	glRotatef(90,1.,0,0.);
	glRotatef(angle,0.,0.,1.);
	gluQuadricDrawStyle(p, GLU_LINE);
	gluCylinder(p,drill_size, drill_size, 50, 10, 10);
	glPopMatrix();
	//Cone of the drill bit
	glPushMatrix();
	glTranslatef(translate,movement+45,-70);
	glRotatef(90,1.,0,0);
	glRotatef(angle,0.,0.,1.);
	gluQuadricDrawStyle(p, GLU_LINE);
	gluCylinder(p,drill_size, 0, 50, 10, 10);
	glPopMatrix();
	 
}


void
output(int x, int y, char *string)
{
  int len, i;

  glRasterPos2f(x, y);
  len = (int) strlen(string);
  for (i = 0; i < len; i++) {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]);
  }
}

void first_screen()
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);
		glColor3f(0.,0.,0.);
		output(-370, 370, "SIMULATION OF RADIAL ARM DRILLING MACHINE");
		output(100, -300, "BY");
		output(100, -350, "ABHISHEK SOOD A (1PI06CS005)");
	glPopAttrib();
	glPushAttrib(GL_ALL_ATTRIB_BITS);
		glColor3f(0.5,0.5,0.5);
        output(200, -550, "press y to continue ");
	glPopAttrib();
}

void controls_screen()
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);
		glColor3f(0.,0.,0.);
		output(-370, 500, "MACHINE CONTROLS");
		output(-370, 300, "I - Upward movement of the drill bit");
		output(-370, 250, "J - Horizontal movement of the drill unit towards left ");
		output(-370, 200, "K - Downward movement of the drill bit");
        output(-370, 150, "L - Horizontal movement of the drill unit towards right");
		output(-370, 100, "A - Stop the movements");
		output(-370, 50, "LEFT CLICK AND DRAG TO ROTATE THE MACHINE");
		output(-370, 0, "RIGHT CLICK TO SELECT FROM THE MENU");
	glPopAttrib();
	glPushAttrib(GL_ALL_ATTRIB_BITS);
		glColor3f(0.5,0.5,0.5);
		output(200, -550, "press y to continue ");
		output(-600, -550, "press t to go back ");
	glPopAttrib();
}

void last_screen()
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);
		glColor3f(0.,0.,0.);
		output(-170,370, "THANK YOU");
	glPopAttrib();
	glPushAttrib(GL_ALL_ATTRIB_BITS);
		glColor3f(0.5,0.5,0.5);
		output(-600, -550, "press t to go back ");
	glPopAttrib();
}


void mydisplay()
{
	//Pointer to a newly created Quadric object to draw cylinders and cone
	GLUquadricObj *p = gluNewQuadric();
	glClear(GL_COLOR_BUFFER_BIT);
	//Load identity to Projection Matrix and clear. 
	glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-700,700,-700,700,-700,700);
    glEnd();
	if(screen == 0)
	{
		first_screen();
	}
	else if(screen == 2)
	{
	output(200, -600, "press y to continue ");
	output(-600, -600, "press t to go back ");
	glPushMatrix();
	glRotatef(spin_x, 0, 1, 0);
  	//Draw Base of the machine
	base();
	
	//switch
	if(work == 2)
	{
		glPushMatrix();
		glColor3f(1.0,0.,0.);
		glTranslatef(-350,-350,15);		
		glutSolidSphere(10,20,20);
		glPopMatrix();
	}
	else if(work == 1)
	{
		if(drillduration>100){
			chunks();
		}
		work_done=1;
		glPushMatrix();					
		glColor3f(0.0,1.0,0.0);
		glTranslatef(-350,-350,15);		
		glutSolidSphere(10,12,12);
		glPopMatrix();
		drillduration++;
		if(drillduration>1000)
		{
			drillduration=0;
			work=2;
		}
		
	}
	glColor3f(0.5,0.5,0.5);
	
		//Column 
		glPushMatrix();
		glTranslatef(-350,430,-70);
		glRotatef(90,1,0,0);	
		glColor3f(.35,.15,.29);
		gluQuadricDrawStyle(p, GLU_FILL);
		gluCylinder(p, 70, 70, 700, 50, 50);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(-350,430,-70);
		glRotatef(90,1,0,0);
		glPushAttrib(GL_CURRENT_BIT);
			    glColor3f(.5,.5,.5);
				gluQuadricDrawStyle(p, GLU_LINE);
		gluCylinder(p, 70, 70, 700, 50, 50);
		glPopAttrib();
		glPopMatrix();

		glColor3f(0,0,0);
		/*WHEEL*/
		//Draw the tyre cylinder
		glPushMatrix();
		glTranslatef(-350,200,0);
		glRotatef(90,0.,0.,1.);

		//If the horizontal movement of drill unit is happening the left wheel rotates
	
		if(left == 1 || right == 1)
		{
			glRotatef(trans_angle,0.,0.,1.);
		}
		gluQuadricDrawStyle(p, GLU_LINE);
		gluCylinder(p, 90, 90, 30, 12, 12);
		glPopMatrix();
	  		
		drawSpokes();
		glColor3f(0.5,0.5,0.5);
		//Arm
	 	glPushMatrix();
	
			glTranslatef(0,0,-70);
			glColor3f(.35,.15,.29);
			arm();
	glPopMatrix();

	 
		 //Motor2
		glPushMatrix();
	 			glTranslatef(translate,390,-70);
				glPushAttrib(GL_CURRENT_BIT);
				glColor3f(0.,0.,0.);
				glutSolidCube(85);
				glPopAttrib();
				glPushAttrib(GL_CURRENT_BIT);
				glColor3f(0.5,0.5,0.5);
				glutWireCube(85);
				glPopAttrib();
	    glPopMatrix();
	
	 //drill column
		glPushMatrix();				
				glTranslatef(translate,350,-70);
				glRotatef(90,1.,0,0);
			    glColor3f(.35,.15,.29);
				gluQuadricDrawStyle(p, GLU_FILL);
				gluCylinder(p, 80, 80, 250, 20, 10);
			glPopMatrix();
			glPushMatrix();				
				glTranslatef(translate,350,-70);
				glRotatef(90,1.,0,0);
				glPushAttrib(GL_ALL_ATTRIB_BITS);
			    glColor3f(.5,.5,.5);
				gluQuadricDrawStyle(p, GLU_LINE);
				gluCylinder(p, 80, 80, 250, 50, 50);
				glPopAttrib();
			glPopMatrix();
				  /*small wheel*/
	  //Draw the tyre of the small right wheel
			glColor3f(0,0,0);
			glPushMatrix();
			glTranslatef(translate,200,0);
			glRotatef(90,0.,0.,1.);			
			if(up == 1 || down == 1)
			{
				glRotatef(move_angle,0.,0.,1.);
			}
				gluQuadricDrawStyle(p, GLU_LINE);
				gluCylinder(p, 60, 60, 30, 15, 15);
	 glPopMatrix();
	 
	//Draw the horizontal spoke of the wheel
	 	  glPushMatrix();
			glTranslatef(translate,200,0);
			glRotatef(90,0.,1.,0.);	
				if(up == 1 || down == 1)
			{
				glRotatef(move_angle,-1.,0.,0.);
			}
				gluQuadricDrawStyle(p, GLU_LINE);
				gluCylinder(p, 3, 3, 75, 10, 10);
		glPopMatrix();
	
glPushMatrix();
			glTranslatef(translate,200,0);
			glRotatef(90,0.,-1.,0.);	
				if(up == 1 || down == 1)
			{
				glRotatef(move_angle,1.,0.,0.);
			}
				gluQuadricDrawStyle(p, GLU_LINE);
				gluCylinder(p, 3, 3, 75, 10, 10);
		glPopMatrix();


	//Draw the vertical spoke of the wheel
	 glPushMatrix();
		glTranslatef(translate,200,0);
			glRotatef(90,1.,0.,0.);		
			if(up == 1 || down == 1)
			{
				glRotatef(move_angle,0.,1.,0.);
			}
				gluQuadricDrawStyle(p, GLU_LINE);
				gluCylinder(p, 3, 3, 75, 10, 10);
	 glPopMatrix();
	
	 glPushMatrix();
		glTranslatef(translate,200,0);
			glRotatef(90,-1.,0.,0.);		
			if(up == 1 || down == 1)
			{
				glRotatef(move_angle,0.,-1.,0.);
			}
				gluQuadricDrawStyle(p, GLU_LINE);
				gluCylinder(p, 3, 3, 75, 10, 10);
	 glPopMatrix();
	
	 
	 glColor3f(0.5,0.5,0.5);
	 /*This part of the code is to made in a stepwise opening subjected to changes later*/
	 //Drill Box
	drillbit();
	/*Till here*/	
	glPushMatrix();
			glTranslatef(280,-300,0.);
			glColor3f(0.7,0.3,0.4);
			glutSolidCube(300);
		
			glColor3f(0.,0.,0.);
			glutWireCube(300);
			glPopMatrix();		
	
	 //Motor1
		glPushMatrix();
	 			glTranslatef(-350,445,-70);
				glPushAttrib(GL_CURRENT_BIT);
				glColor3f(0.,0.,0.);
				glutSolidCube(90);
				glPopAttrib();
				glPushAttrib(GL_CURRENT_BIT);
				glColor3f(0.5,0.5,0.5);
				glutWireCube(90);
				glPopAttrib();
	    glPopMatrix();
		glColor3f(0.5,0.5,0.5);
	/*OBJECTS*/
	//If cube is selected as object display it
	if(oc == 1)
	{	
		glPushMatrix();	
		glTranslatef(320,-70,0.);
			glutSolidCube(155);
		glPopMatrix();
	}
	//If parallelopiped is selected as object display it
	if(op == 1)
	{
		glPushMatrix();	
		glTranslatef(275,-80,-70);
		glScalef(50,30,3);
		glutWireCube(5);
		glPopMatrix();
	
		glPushMatrix();	
		glTranslatef(275,-80,-70);
		glScalef(50,30,3);
		glutSolidCube(5);
		glPopMatrix();
	}
	//If triangle is selected as object display it
	if(ot == 1)
	{
		glPushMatrix();	
		glTranslatef(275,-150,0.);
			glBegin(GL_LINE_LOOP);
					glVertex3f(0,0,-90);
					glVertex3f(90,0,-90);
					glVertex3f(65,0,90);
			glEnd();
			glBegin(GL_LINE_LOOP);
					glVertex3f(0,100,-90);
					glVertex3f(90,100,-90);
					glVertex3f(65,100,90);
			glEnd();
			glBegin(GL_LINES);
					glVertex3f(0,0,-90);
					glVertex3f(0,100,-90);
					glVertex3f(90,0,-90);
					glVertex3f(90,100,-90);
					glVertex3f(65,0,90);
					glVertex3f(65,100,90);
			glEnd();
			
		glPopMatrix();
	}
	//If cylinder is selected as object display it
	if(ocy == 1)
	{
		glPushMatrix();	
		glTranslatef(320,0,-70);
		 GLUquadricObj *q = gluNewQuadric();
				glRotatef(90,1.,0,0);				
				gluQuadricDrawStyle(q, GLU_FILL);
				gluCylinder(q, 45, 45, 160, 10, 10);		
		glPopMatrix();
	}

	glPopMatrix();
	/*OUTPUT*/
	//If display the output option is selected in the menu options
	glPushMatrix();
	glRotatef(15,0,1,0);
	if(done == 1)
	{
	//If object selected is cube display the result after output at the right top of the screen
        if(oc == 1)
	{	
		glPushMatrix();	
		glTranslatef(500,500,0.);
		glRotatef(90,1.,0.,0.);
			glutWireCube(93);
				glRotatef(90,1.,0,0);				
				gluQuadricDrawStyle(p, GLU_FILL);
				gluCylinder(p, drill_size, drill_size, 50, 10, 10);	
		glPopMatrix();
	}
	//If object selected is parallelopiped display the result after output at the right top of the screen
	if(op == 1)
	{
		glPushMatrix();	
		glTranslatef(500,500,0.);
		glRotatef(90,1.,0.,0.);
			   glBegin(GL_LINE_LOOP);
					glVertex3f(0,0,-90);					
					glVertex3f(0,50,-90);
					glVertex3f(0,50,90);
					glVertex3f(0,0,90);
					
				glEnd();
				glBegin(GL_LINE_LOOP);
					glVertex3f(130,0,-90);
					glVertex3f(130,50,-90);										
					glVertex3f(130,50,90);
					glVertex3f(130,0,90);
				glEnd();
				glBegin(GL_LINES);
					glVertex3f(0,0,-90);
					glVertex3f(130,0,-90);
					glVertex3f(0,50,-90);
					glVertex3f(130,50,-90);
					glVertex3f(0,0,90);
					glVertex3f(130,0,90);
					glVertex3f(0,50,90);		
					glVertex3f(130,50,90);
				glEnd();
		glPopMatrix();
				glPushMatrix();
				glTranslatef(565,500,0.);
				glRotatef(90,0.,0.,1.);				
				gluQuadricDrawStyle(p, GLU_FILL);
				gluCylinder(p, drill_size, drill_size, 50, 10, 10);	
				glPopMatrix();
	}
      //If object selected is triangle display the result after output at the right top of the screen
	if(ot == 1)
	{
		glPushMatrix();	
		glTranslatef(500,500,0.);
		glRotatef(90,1.,0.,0.);
			glBegin(GL_LINE_LOOP);
					glVertex3f(0,0,-90);
					glVertex3f(90,0,-90);
					glVertex3f(65,0,90);
			glEnd();
			glBegin(GL_LINE_LOOP);
					glVertex3f(0,50,-90);
					glVertex3f(90,50,-90);
					glVertex3f(65,50,90);
			glEnd();
			glBegin(GL_LINES);
					glVertex3f(0,0,-90);
					glVertex3f(0,50,-90);
					glVertex3f(90,0,-90);
					glVertex3f(90,50,-90);
					glVertex3f(65,0,90);
					glVertex3f(65,50,90);
			glEnd();			
		glPopMatrix();
		glPushMatrix();
				glTranslatef(550,550,0.);
				glRotatef(90,0.,0.,1.);					
				gluQuadricDrawStyle(p, GLU_FILL);
				gluCylinder(p, drill_size, drill_size, 50, 10, 10);	
		glPopMatrix();
	}
	//If object selected is cylinder display the result after output at the right top of the screen
	if(ocy == 1)
	{
		glPushMatrix();	
		glTranslatef(500,500,0.);
		glRotatef(90,1.,0.,0.);
		 GLUquadricObj *q = gluNewQuadric();
				glRotatef(90,1.,0,0);				
				gluQuadricDrawStyle(q, GLU_FILL);
				gluCylinder(q, 45, 45, 50, 10, 10);		
				gluCylinder(q, drill_size, drill_size, 50, 10, 10);	
		glPopMatrix();
	}}
	//Remember the glPushMatrix intially in the display funtion? This is where it ends.
glPopMatrix();
	//Finish
}
else if(screen == 1)
{
	controls_screen();
}
else if(screen == 3)
{
	last_screen();
}
  glFlush();
}

void init()
{
	w = glutGet(GLUT_WINDOW_WIDTH);
    h = glutGet(GLUT_WINDOW_HEIGHT);
	glClear(GL_COLOR_BUFFER_BIT );	
	glClearColor(1,1,1,1);
	glColor3f(0.5,0.5,0.5);
	gluPerspective(90.0, (GLfloat) w/(GLfloat) h, 1.0, 200.0);
}

//Function to Handle the left menu options
//The left menu has all submenus except the 4th option which displays the output by setting done==1
//ANd only in the condition where any one of the object type is placed on the drilling table
//i.e. eithertriangle or cube or cylinder or parallelopiped

void left_menu(int id2)
{
	if(id2 == 4)
	{
			if(work_done== 1 && (oc == 1 || ot == 1 ||op == 1 || ocy == 1))
			{
				done=1;
				glutPostRedisplay();
				
			}
	}
	if(id2 == 5)
	{
		done=0,oc=0,op=0,ot=0,ocy=0;
		work=2;
		work_done=0;
		glutPostRedisplay();
	}
	
	
	if(id2 == 3)
		exit(0);
}


//Mouse function here only takes care of the rotation of the object
void mouse(int button, int state, int x, int y)
{

	if(GLUT_RIGHT_BUTTON && work == 2)
	{	
				old_x = x - spin_x;
				old_y = y - spin_y;        
	}	
    glutPostRedisplay();

}


void idle(void)
{
    glutPostRedisplay();
}

//Rotates the drilling machine
void motion(int x, int y)
{
        spin_x = x - old_x;
        spin_y = y - old_y;
     glutPostRedisplay();
}

void mykey(unsigned char key, int x, int y)
{
	
	switch(key)
	{
	case 'j': case 'J':	left=1;right=0;						
							break;
	case 'l': case 'L':  right=1;left=0;						 	
							break;
	case 'i': case 'I': up=1;down=0;						 	
							break;
	case 'k': case 'K':  up=0;down=1;						 	
							break;
	case 'a': case 'A':  up=0;down=0;left=0;right=0;
							break;	
	case 'y': case 'Y':   if(screen<3)
						  {
						 	screen++;
						  }
						break;

	case 't':  case 'T': if(screen>0)
						 { 
						   screen--;
					     }		       
						 break;

	case 27:exit(0);
	}
}

void mytimer(int value)
{
	if(work==2){
	//For horizontal leftward movement of drill unit
	//Change the trans_angle value  and redraw the image
    if (translate != 100 && left == 1 )
   	{	
		if(trans_angle<0)
		{
			trans_angle=0.0;
		}
		if(trans_angle>360)
		{
			trans_angle=trans_angle-360;
		}
		trans_angle=trans_angle+2;
		glutPostRedisplay();
		trans_angle=trans_angle+2;
		glutPostRedisplay();
		translate=translate-2;
		glutPostRedisplay();
	}
		
	//For horizontal rightward movement of drill unit
	//Change the trans_angle value  and redraw the image	
   if (translate != 450 && right == 1)
   {
	   	if(trans_angle>0)
	    {
		   trans_angle=0.0;
		}
		if(trans_angle<-360)
		{
			trans_angle=trans_angle+360;
		}
	    trans_angle=trans_angle-2;
	    glutPostRedisplay();
		trans_angle=trans_angle-2;
	    glutPostRedisplay();
		translate=translate+2;
		glutPostRedisplay();
	}
	}
	//For vertical upward movement of drill unit
	//Change the move_angle value  and redraw the image
	if(work==2){
	if(movement != 0)
	{
     	if(move_angle>0)
		{
			move_angle=0.0;
		}
		if(move_angle<-360)
		{	
			move_angle=move_angle+360;
		}
		move_angle=move_angle-2;
	    glutPostRedisplay();
		move_angle=move_angle-2;
	    glutPostRedisplay();
        movement++;
		glutPostRedisplay();
	}}
	
	if(work==1){
	//For vertical downward movement of drill unit
	//Change the trans_angle value  and redraw the image
	if( movement != -30)
	{
		if(move_angle<0)
		{
			move_angle=0.0;
		}
		if(move_angle>360)
		{
			move_angle=move_angle-360;
		}
		move_angle=move_angle+2;
		glutPostRedisplay();
		move_angle=move_angle+2;
		glutPostRedisplay();
		movement--;
		glutPostRedisplay();
	}
	    
        //If the power is on then increase the drilling 
	//speed by increasing the angle of rotation
	
	
		angle=angle+dspd;
		if(angle>360)
		{
			angle=angle-360;
		}
		glutPostRedisplay();
	}
	glutTimerFunc(100,mytimer,100);
	
}

//FUnction to handle the switch on and switch off the power if selected from the submenu.
void w_state(int id)
{
	//Switch on the Power 
	if(id == 1&&(oc==1||ot==1||ocy==1||op==1))
	{
		work=1;
		move_angle=0;
		glutPostRedisplay();
	}
	//Switch off the Power
	if(id == 2)
	{
		work=2;
		move_angle=0;
		glutPostRedisplay();
	}
}

//Function to handle the option of changing drill speed in the sub-menu
void Speed(int id4)
{
	switch(id4)
	{
	case 1: dspd++; break;
	case 2: dspd--; break;
	}
}

int main(int argc, char** argv)
{
	int menu, submenu1, submenu2,submenu3,submenu4;
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(700,700);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Drilling Machine");
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
    glutMotionFunc(motion);
	printf("Left Click and select details \n");
	submenu4 = glutCreateMenu(Speed);
			 glutAddMenuEntry("Increase Drilling Speed", 1);
			 glutAddMenuEntry("Decrease Drilling Speed", 2);
	submenu3=glutCreateMenu(w_state);
			 glutAddMenuEntry("Switch On",1);
			 glutAddMenuEntry("Switch off",2);
	submenu2=glutCreateMenu(Drill_Size);
			glutAddMenuEntry("10 cm", 10);
			glutAddMenuEntry("15 cm", 15);
			glutAddMenuEntry("20 cm", 20);
			glutAddMenuEntry("25 cm", 25);
	submenu1=glutCreateMenu(Obj_Type);		
			 glutAddMenuEntry("Cube", 1);
			 glutAddMenuEntry("Parellelopiped", 2);
			 glutAddMenuEntry("Triangle", 3);
			 glutAddMenuEntry("Cylinder", 4);
	menu =  glutCreateMenu(left_menu);	
		    glutAddSubMenu("Object Type", submenu1);			
			glutAddSubMenu("Drill Bit Size:", submenu2);
			glutAddSubMenu("Power", submenu3);
			glutAddSubMenu("Drilling Speed", submenu4);
			glutAddMenuEntry("Reset",5);
			glutAddMenuEntry("See Output",4);
		    glutAddMenuEntry("Exit",3);			
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	printf("Right Click and move the machine \n");
	printf("Controls: \n i = Move Main Column left \n j = Move Main Column right \n k = Move Drill Box Down \n l = Move Drill Box Up \n");
	init();	
	glutDisplayFunc(mydisplay);
	glutKeyboardFunc(mykey);
	glutTimerFunc(100,mytimer,100);
	glutIdleFunc(idle);
	glutMainLoop();
	return 0;
}
