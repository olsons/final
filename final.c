//This program creates a visual display of an acquatic ecosystem

#include "gfx4.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

void createLayout(double *ySun, double **gAngle, int **gDir, double **wX, int **wDir);
void createDuck(double *x1, double *y1, double *beakMovement);
void createBird(double *bX, double *bY, double *i, double *l, double velocity, double *doRotate, double *dX, double *dY, int *numCount);
void createFish(double *fX, double *fY, double *fY2, double *sX, int *eat);
void createMoreFish(double *mX, double *mY);
void createLobster(double *lX, double *lY);
void printGrass(double *gAngle, int *gDir);
void printWaves(double *wX, int *wDir);
void createWhale(double *sX, double *sY);
void createSquid(double *qX, double *qY, int *direction, double *iX, double *iY, double *r);

int main()
{
	gfx_open(800, 800, "A soFISHticated Aquatic Ecosystem");

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
	double *gangle=&gAngle;
	int gDir=0; //grass direction (1 is left and 0 is right)
	int *gdir=&gDir;
	double wX=0; //wave location
	double *wx=&wX;
	int wDir=0; //wave direction (1 is left and 0 is right)
	int *wdir=&wDir;
	double sX=-230; //whale
	double sY=390;
	double qX=600; //squid
	double qY=600;
	double iX=650; //ink
	double iY=610;
	double r=5; //radius of ink
	int direction=1; //direction of the squid

        while(1){
                gfx_clear();
		createLayout(&ySun, &gangle, &gdir, &wx, &wdir); //create the layout of the structure
		createDuck(&x1, &y1, &beakMovement);
		createBird(&bX, &bY, &i, &l, velocity, &doRotate, &dX, &dY, &numCount);
		createFish(&fX, &fY, &fY2, &sX, &eat);
		createLobster(&lX, &lY);
		createMoreFish(&mX, &mY);
		createWhale(&sX, &sY);
		createSquid(&qX, &qY, &direction, &iX, &iY, &r);
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
void createLayout(double *ySun, double **gAngle, int **gDir, double **wX, int **wDir){
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
	if (*ySun<=200){
		//Clouds
		gfx_color(255, 255, 255);
		gfx_fill_arc(29, 29, 95, 40, 0, 360);
		gfx_fill_arc(70, 45, 85, 40, 0, 360);
		gfx_fill_arc(779, 29, 95, 40, 0, 360);
		gfx_fill_arc(720, 45, 85, 40, 0, 360);
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

	//set up twigs
	gfx_color(122, 69, 0); //brown twig color
	gfx_fill_rectangle(10, 710, 22, 6); 
	gfx_fill_rectangle(780, 700, 20, 3); 
	gfx_fill_rectangle(30, 750, 30, 5);

	printGrass(*gAngle, *gDir);
	printWaves(*wX, *wDir);
}

void printGrass(double *gAngle, int *gDir){
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

void printWaves(double *wX, int *wDir){
	//draw the waves
	int i;
	gfx_color(17,167,242);
	for (i=-1;i<=20;i++){
		gfx_fill_arc(40*(*wX+i), 190, 40, 20, 0, 180);
	}
	if (*wX>=.5 || (*wDir==1 && *wX>=-.5)){
		*wX-=.005;
		*wDir=1; //moving left
	}
	else if (*wX<=-.5 || (*wDir==0 && *wX<=.5)){
		*wX+=.005;
		*wDir=0; //moving right
	}
}

//Create the duck
void createDuck(double *x1, double *y1, double *beakMovement){
	*x1+=.2;
	if (*x1>=875){
		*x1=-75;
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
		if (*bX>=790){
			*doRotate=1;
			*bX=40;
			*dX=900;
			*numCount=1;
		}
		if(*bX>=500 && *bX<=790){
			*bY=*bY-.8;
		}
	}
	gfx_color(255, 1, 2);
	gfx_line((int)*bX, (int)*bY, (int)*bX-20, (int)*bY-20); //Bird's wings
        gfx_line((int)*bX, (int)*bY, (int)*bX-20, (int)*bY+20); //Bird's wings

	if (*bX >= 500 && *bX <=790){
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
	gfx_color(0, 0, 0); //dead fish eye color
	gfx_text(*dX+10, *dY+3, "X");
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
	*fX-=5;
	if (*fX<=10){
		*fY=390;
		*fY2=390;
		*fX=1300;
		*eat=rand() % 2; //randomly decide if minnow should be eaten by whale
	}
	if (*fX-30>*sX+170 || *eat==0){
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
	XPoint xp = {300,450}; // initialize a point (using X11's Xpoint struct)
	// set up 2 arrays of points, gold fish
 	XPoint mypts1[] = { {*mX,*mY-10},{*mX,*mY+10},{*mX+10,*mY} };
	XPoint mypts2[] = { {*mX+2,*mY+40},{*mX+2,*mY+20},{*mX+12,*mY+30} };
	XPoint mypts3[] = { {*mX-8,*mY+60},{*mX-8,*mY+80},{*mX,*mY+70} };
	XPoint mypts4[] = { {*mX-26,*mY+55},{*mX-26,*mY+65},{*mX-18,*mY+60} }; //baby one
	gfx_fill_polygon(mypts1, 3);
	gfx_fill_circle((int)*mX+10, (int)*mY, 8);
	gfx_fill_polygon(mypts2, 3);
	gfx_fill_circle((int)*mX+12, (int)*mY+30, 8);
	gfx_fill_polygon(mypts3, 3);
	gfx_fill_circle((int)*mX, (int)*mY+70, 8);
	if (*mX>=200){
		gfx_color(255, 240, 137);
		gfx_fill_polygon(mypts4, 3);
		gfx_fill_circle((int)*mX-18, (int)*mY+60, 6);
	}
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
	XPoint mypts1[] = { {*sX+100, *sY},{*sX+223, *sY+2},{*sX+215, *sY+20} }; //mouth
	XPoint mypts2[] = { {*sX-200, *sY},{*sX-220-75*cos(M_PI/3), *sY+75*sin(M_PI/3)},{*sX-220-75*cos(M_PI/3), *sY-75*sin(M_PI/3)} }; //tail
	gfx_color(65, 100, 146); //blue whale
	gfx_fill_arc((int)*sX-220, (int)*sY-76, 440, 152, 0, 360); //body
	gfx_fill_polygon(mypts2, 3); //tail
	gfx_color(17,167,242); //water color to avoid extra oval line over mouth
	gfx_fill_polygon(mypts1, 3); //cover up line to show true mouth
	gfx_fill_arc((int)(*sX+131), (int)(*sY-34), 8, 8, 0, 360); //eye
	if ((*sX-230)<=850){
		*sX+=.5; //whale speed
	}
	else{
		*sX=-400;
	}
}

void createSquid(double *qX, double *qY, int *direction, double *iX, double *iY, double *r){
	gfx_color(253, 6, 6);
	gfx_fill_arc((int)(*qX), (int)(*qY), 50, 90, 0, 360); //squid filled in red like fire
	gfx_line((int)*qX+22, (int)*qY+80, (int)*qX, (int)*qY+140); //squid's legs
	gfx_line((int)*qX+25, (int)*qY+80, (int)*qX+10, (int)*qY+140);
	gfx_line((int)*qX+27, (int)*qY+80, (int)*qX+20, (int)*qY+140);
	gfx_line((int)*qX+28, (int)*qY+80, (int)*qX+25, (int)*qY+140);
	gfx_line((int)*qX+29, (int)*qY+80, (int)*qX+30, (int)*qY+140);
	gfx_line((int)*qX+29, (int)*qY+80, (int)*qX+36, (int)*qY+140);
	gfx_line((int)*qX+30, (int)*qY+80, (int)*qX+45, (int)*qY+140);
	gfx_color(255, 255, 255);
	gfx_fill_arc((int)(*qX+30), (int)(*qY+45), 10, 20, 0, 360); //squid eyes
	gfx_fill_arc((int)(*qX+10), (int)(*qY+45), 10, 20, 0, 360); //squid eyes
	gfx_color(0, 0, 0);
	gfx_fill_arc((int)(*qX+30), (int)(*qY+56), 5, 5, 0, 360); //squid pupil
	gfx_fill_arc((int)(*qX+10), (int)(*qY+56), 5, 5, 0, 360); //squid pupil
	if ((*direction==-1)&&(*iY<=950)){
		gfx_fill_arc((int)(*iX), (int)(*iY), *r, *r, 0, 360); //squid inks
		*iY=*iY+.06;
		*iX=*iX+.08;
		*r=*r+.022;
	}
	else{
		*iY=610;
		*iX=650;
		*r=5;
	}
	switch(*direction){
		case 1:
			*qY=*qY-.05 ;//moving up
			break;
		case -1:
			*qY=*qY+.05; //moving down
			break;
	}
	//Squid
	if(*qY<=500){
		*direction=-1;
		*qY=501; //put it back into old range
	}
	else if(*qY>=600){
		*direction=1;
		*qY=599;
	}
}
