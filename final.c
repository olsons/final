//This program creates a visual display of an acquatic ecosystem

#include "gfx4.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

void createLayout(double *ySun, double **gAngle, int **gDir);
void createDuckHead(double *x1, double *y1, double *beakMovement);
void createBird(double *bX, double *bY, double *i, double *l, double velocity, double *doRotate, double *dX, double *dY, int *numCount);
void createFish(double *fX, double *fY, double *fY2, double *sX, int *eat);
void createMoreFish(double *mX, double *mY);
void createLobster(double *lX, double *lY);
void printGrass(double *gAngle, int *gDir);
void createWhale(double *sX, double *sY);

int main()
{
	gfx_open(800, 800, "Carnival Ride: The Duck");

        //Declare variables of the ride
        char c; //check to see if someone presses a button
	int numCount=0; 
        double i=.01; //used in delta t
	double l=.01;
	double beakMovement=22; //used to help measure when the beak is fully closed (so it can be opened again)
        double deltat=.01;  //used in change of time
        double x1=-10; //Where the duck starts (on left hand of page)
        double y1=156; 
        double bX=400;//the starting point for the bird
	double bY=50;
	double fX=810; //starting point for the fish that are minnows
	double fY=390;
	double fY2=390;
	srand(time(NULL));	
	int eat=rand() % 2; //determines if one of the minnows will be eaten by the whale or not
	double lX=0; //starting point for the lobster
	double lY=600;
	double dX=500; //dead fish
	double dY=200;
	double mX=1; //goldfish 
	double mY=220;
	double doRotate=1;
	double ySun=-5; //the sun is always setting/rising
	int velocity=5; //basic velocity of the bird in the air
	double gAngle=5*M_PI/6; //grass angle
	double *angle=&gAngle;
	int gDir=0; //grass direction (1 is left and 0 is right)
	int *dir=&gDir;
	double sX=-230; //whale
	double sY=390;

        while(1){
                gfx_clear();
		createLayout(&ySun, &angle, &dir); //create the layout of the structure
		createDuckHead(&x1, &y1, &beakMovement);
		createBird(&bX, &bY, &i, &l, velocity, &doRotate, &dX, &dY, &numCount);
		createFish(&fX, &fY, &fY2, &sX, &eat);
		createLobster(&lX, &lY);
		createMoreFish(&mX, &mY);
		createWhale(&sX, &sY);
                gfx_flush();

                //Check if the user has decided to quit the program
                if (gfx_event_waiting())
                {
                        c=gfx_wait();
                        if (c=='q')
                        {
                                break;
                        }
                }
		
                usleep(8000);
	}
	return 0;
}

//Create the structure/support for the ride (what will hold up the duck)
void createLayout(double *ySun, double **gAngle, int **gDir){
	//Create a filled in sun
	if (*ySun<=110){
		gfx_color(186, 240, 255);
		gfx_fill_rectangle(0,0, 800,200); //blue sky
	}
	else if(*ySun<=170){
		gfx_color(255, 188, 154);
		gfx_fill_rectangle(0,0, 800,200); //pink sky
	}
	else if(*ySun<=200){
		gfx_color(255, 128, 64);
		gfx_fill_rectangle(0,0, 800,200);  //pink-orange beautiful sunset
	}
	else{
		gfx_color(0,0,0);
		gfx_fill_rectangle(0,0, 800,200); //black sky w/ moon
		gfx_color(255, 255, 255);
		gfx_fill_arc(100, 50, 30, 30,0,360);
	}
	gfx_color(255,255,0); //bright yellow
        gfx_fill_arc(550, *ySun, 80, 80,0,360); //fill in beautiful sun
	*ySun=*ySun+.04;
	if (*ySun>=280){
		*ySun=0;
	}

	//Water
	gfx_color(17,167,242); 
	int i;
	gfx_fill_rectangle(0,200, 800,600);

	//Set up sand bank
  	XPoint xp = {300,450}; // initialize a point (using X11's Xpoint struct)

	// set up 2 arrays of points
 	XPoint mypts1[] = { {1,500},{1,800},{400,800} };
 	XPoint mypts2[] = { {400,800},{800,500},{800,800} };

	gfx_color(242, 220, 132);
	gfx_fill_polygon(mypts1, 3);
	gfx_fill_polygon(mypts2, 3);
	gfx_fill_rectangle(0, 700, 800, 100); 

	printGrass(*gAngle, *gDir);
}

void printGrass(double *gAngle, int *gDir){
	double m=cos(*gAngle);
	double n=sin(*gAngle);
	int i;

	//Grass life
	gfx_color(43, 198, 25);
	
	int grass[23][4]={{20, 700, 20, 780},{30, 680, 30, 760},{25, 690, 25, 770},{15, 676, 18, 750},{35, 705, 35, 770},{26, 680, 26, 750},{15, 700, 17, 760},{38, 700, 34, 760},{140, 740, 140, 780},{150, 720, 150, 760},{145, 710, 145, 770},{155, 726, 158, 750},{165, 715, 165, 770},{156, 720, 156, 750},{170, 720, 167, 790},{158, 740, 154, 780},{720, 700, 720, 780},{730, 680, 730, 760},{725, 690, 725, 770},{735, 705, 735, 770},{726, 680, 726, 750},{715, 700, 717, 760},{738, 700, 734, 760}};

	for (i=0;i<=22;i++){
		gfx_line(grass[i][0]+(grass[i][3]-grass[i][1])*cos(*gAngle), grass[i][1]-(grass[i][3]-grass[i][1])*sin(*gAngle), grass[i][2], grass[i][3]);
	}

	if (*gAngle>=5*M_PI/6 || (*gDir==1 && *gAngle>=M_PI/6)){
		*gAngle-=.003;
		*gDir=1; //moving left
	}	
	else if (*gAngle<=M_PI/6 || (*gDir==0 && *gAngle<=5*M_PI/6)){
		*gAngle+=.003;
		*gDir=0; //moving right
	}
}	

//Create the duck's head
void createDuckHead(double *x1, double *y1, double *beakMovement){
	*x1+=.2;
	if (*x1>=750){
		*x1=-50;
	}
	//Move the beak
	*beakMovement=*beakMovement+.3; 
        //Y2 goes back to original position after the line is completely horizontal so beak won't over extend
        if (*beakMovement>=50){
              	*beakMovement=22;
       	}
	gfx_color(255, 160, 36); //Beak's color
        gfx_line((int)*x1+15, (int)*y1-8, (int)*x1+46, (int)*y1-50+*beakMovement); //top beak of the bird
        gfx_line((int)*x1+15, (int)*y1+8, (int)*x1+46, (int)*y1+50-*beakMovement); //bottom beak of the bird
	gfx_color(12, 115, 0); //Duck's head's color
        gfx_fill_circle((int)*x1, (int)*y1, 20); //Duck's head
	gfx_color(169, 116, 8);
	gfx_fill_circle((int)*x1-30, (int)*y1+30, 35); //Duck's body
	gfx_color(17,2,2);
	gfx_fill_circle((int)*x1+10, (int)*y1-5, 3); //duck's eyeball
} 

//Create person moving in the cart
void createBird(double *bX, double *bY, double *i, double *l, double velocity, double *doRotate, double *dX, double *dY, int *numCount){
	double deltat=.01;
	//Recalculate i, l by multiplying by delta t. This changes the angle of rotation. 
	if (*doRotate<10){
        	*i+=(double)(deltat*velocity); //Movement of the carts
        	*l+=(double)(deltat*velocity*1.1); //velocity of the line
		*bX =50+(double)(cos(*i)*20);
        	*bY =20+(double)(sin(*i)*10);
		*doRotate=*doRotate+.1;
	}
	else{
		*bX=*bX+.5;
		if (*bX>300 && *bX<=750 && *bY <= 200){
			*bY=*bY+.7;
		}
		if (*bX>=780){
			*doRotate=1;
			*bX=40;
			*dX=900;
			*numCount=1;
		}
		if(*bX>=500 && *bX<=780){
			*bY=*bY-.8;
		}
	}
	gfx_color(255, 1, 2);
	gfx_line((int)*bX, (int)*bY, (int)*bX-20, (int)*bY-20); //Bird's wings
        gfx_line((int)*bX, (int)*bY, (int)*bX-20, (int)*bY+20); //Bird's wings

	if (*bX >= 500 && *bX <=780){
		*dX=*bX;
		*dY=*bY;
	}
	if (*numCount==0){
		gfx_color(247, 246, 242); //picking up a dead fish on his first try
	}
	else{
		gfx_color(252, 206, 25); //now he picks up live fish
	}
	//Dead fish that the bird will pick up
	XPoint xp = {300,450}; // initialize a point (using X11's Xpoint struct)
	// set up 2 arrays of points
 	XPoint mypts1[] = { {*dX,*dY-10},{*dX,*dY+10},{*dX+10,*dY} };
	gfx_fill_polygon(mypts1, 3);
	gfx_fill_circle((int)*dX+10, (int)*dY, 8);
}

void createFish(double *fX, double *fY, double *fY2, double *sX, int *eat){
	gfx_color(100, 100, 100);
	if (*fX-(*sX+220)<=180 && *fX-(*sX+200)>0){
		*fY+=3;
		if (*eat==1){		
			*fY2+=1;
		}
		else if (*eat==0){
			*fY2+=3;
		}
	}
	/*if (*sX>=450 && *fX>=600){ //minnows swim down while the whale is moving off screen
		*fY=570;
		*fY2=570;
		if (*eat==1){		
			*fY2+=1;
		}
		else if (*eat==0){
			*fY2+=3;
		}
	}*/
	*fX-=5;
	if (*fX<=10){
		*fY=390;
		*fY2=390;
		*fX=1300;
		*eat=rand() % 2; //randomly decide if minnow should be eaten by whale
	}
	if (*fX-30>*sX+200 || *eat==0){
		gfx_line((int)*fX-30, (int)*fY2-20, (int)*fX-10, (int)*fY2-20); //minnow that gets eaten
	}
	gfx_line((int)*fX, (int)*fY, (int)*fX+20, (int)*fY);
	gfx_line((int)*fX+10, (int)*fY, (int)*fX+30, (int)*fY);
	gfx_line((int)*fX+15, (int)*fY+10, (int)*fX+35, (int)*fY+10);
	gfx_line((int)*fX-20, (int)*fY-10, (int)*fX, (int)*fY-10);
	gfx_line((int)*fX-40, (int)*fY+20, (int)*fX-20, (int)*fY+20);
	gfx_line((int)*fX-30, (int)*fY+7, (int)*fX-10, (int)*fY+7);
	gfx_line((int)*fX, (int)*fY+20, (int)*fX, (int)*fY+20);
}

void createMoreFish(double *mX, double *mY){
	gfx_color(252, 206, 25);
	//Dead bird that it will pick up eventually
	XPoint xp = {300,450}; // initialize a point (using X11's Xpoint struct)
	// set up 2 arrays of points
 	XPoint mypts1[] = { {*mX,*mY-10},{*mX,*mY+10},{*mX+10,*mY} };
	XPoint mypts2[] = { {*mX+2,*mY+40},{*mX+2,*mY+20},{*mX+12,*mY+30} };
	XPoint mypts3[] = { {*mX-8,*mY+60},{*mX-8,*mY+80},{*mX,*mY+70} };
	gfx_fill_polygon(mypts1, 3);
	gfx_fill_circle((int)*mX+10, (int)*mY, 8);
	gfx_fill_polygon(mypts2, 3);
	gfx_fill_circle((int)*mX+12, (int)*mY+30, 8);
	gfx_fill_polygon(mypts3, 3);
	gfx_fill_circle((int)*mX, (int)*mY+70, 8);
	if (*mX<=790){
		*mX=*mX+.5;
	}
	else{
		*mX=0;
	}
}

void createLobster(double *lX, double *lY){
	if (*lX<=280){
		*lX=*lX+.05;
		*lY=*lY+.03;
	}
	if (*lX<=500 && *lX>=280){
		*lX=*lX+.05;
	}
	if (*lX>=500){
		*lX=*lX+.05;
		*lY=*lY-.03;
	}
	if (*lX>=795){
		*lX=0;
	}
	gfx_color(255, 4, 4);
	//Eye
	gfx_fill_circle((int)*lX, (int)*lY, 8);
	gfx_fill_circle((int)*lX+2, (int)*lY-10, 6);
	gfx_fill_circle((int)*lX-2, (int)*lY-10, 6);
	//Crab hook
	gfx_line((int)*lX+8, (int)*lY-2, (int)*lX+14, (int)*lY-10);
	gfx_line((int)*lX+14, (int)*lY-10, (int)*lX+18, (int)*lY-20);
	gfx_line((int)*lX+14, (int)*lY-10, (int)*lX+11, (int)*lY-18);
	gfx_line((int)*lX-8, (int)*lY-2, (int)*lX-14, (int)*lY-10);
	gfx_line((int)*lX-14, (int)*lY-10, (int)*lX-18, (int)*lY-20);
	gfx_line((int)*lX-14, (int)*lY-10, (int)*lX-11, (int)*lY-18);
	//Leg additions
	gfx_line((int)*lX+5, (int)*lY+2, (int)*lX+16, (int)*lY+1);
	gfx_line((int)*lX+5, (int)*lY+3, (int)*lX+16, (int)*lY+3);
	gfx_line((int)*lX+5, (int)*lY+4, (int)*lX+16, (int)*lY+5);
	gfx_line((int)*lX-5, (int)*lY+2, (int)*lX-16, (int)*lY+1);
	gfx_line((int)*lX-5, (int)*lY+3, (int)*lX-16, (int)*lY+3);
	gfx_line((int)*lX-5, (int)*lY+4, (int)*lX-16, (int)*lY+5);
	//Pupil of the eye
	gfx_color(0,0,0); 
	gfx_fill_circle((int)*lX+2, (int)*lY-10, 2);
	gfx_fill_circle((int)*lX-2, (int)*lY-10, 2);
	//Lips of lobster
	gfx_line((int)*lX-3, (int)*lY+2, (int)*lX+3, (int)*lY+2);
}

void createWhale(double *sX, double *sY){
	XPoint xp = {300,450}; // initialize a point (using X11's Xpoint struct)
	XPoint mypts1[] = { {*sX+210,*sY},{*sX+230,*sY},{*sX+230,*sY+90} };


	gfx_color(65, 100, 146); //blue whale
        gfx_ellipse((int)*sX, (int)*sY, 220, 76); //body
//	gfx_fill_arc((int)*sX, (int)*sY, 220, 76, 0, 360);
	gfx_color(17,167,242); //water color to avoid extra oval line over mouth
	gfx_fill_polygon(mypts1, 3); //cover up line to show true mouth
	gfx_color(65, 100, 146);
	gfx_line((int)(*sX+100),(int)(*sY),(int)(*sX+220), (int)(*sY)+2); //mouth
	gfx_line((int)(*sX+100),(int)(*sY),(int)(*sX+215), (int)(*sY)+20); //mouth
        gfx_circle((int)(*sX+135), (int)(*sY-30), 4); //eye
        gfx_line((int)(*sX-220), (int)*sY, (int)(*sX-220-50*cos(M_PI/3)), (int)(*sY+50*sin(M_PI/3))); //next three tail
        gfx_line((int)(*sX-220-50*cos(M_PI/3)), (int)(*sY+50*sin(M_PI/3)), (int)(*sX-220-50*cos(M_PI/3)), (int)(*sY-50*sin(M_PI/3)));
	gfx_line((int)(*sX-220-50*cos(M_PI/3)), (int)(*sY-50*sin(M_PI/3)), (int)(*sX-220), (int)*sY);
	if ((*sX-230)<=798){
		*sX+=.5; //whale speed
	}
	else{
		*sX=-400;
	}
}
