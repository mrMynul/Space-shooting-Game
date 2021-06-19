#include<windows.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <glut.h>
#include <math.h>
#include<string.h>

#define PI 3.14159
#define GAME_SCREEN 0
#define MENU_SCREEN 4
#define MAX_STONES  100
#define MAX_HART  30
#define MAX_STONE_TYPES 5
#define stoneRotationSpeed 20
#define SPACESHIP_SPEED 20
float stoneTranslationSpeed=0.2;
float temp_stoneTranslationSpeed=0.0;
float	testx=0;
float	testy=0;

GLint m_viewport[4];

int x,y;
int i;
int randomStoneIndices[100];
int index;
int Score=0;
int alienLife=100;
int GameLvl= 1;
float mouseX ,mouseY ;
float LaserAngle=0 ,stoneAngle =0,lineWidth = 1;
float xOne=0,yOne=0;
float xHart[MAX_HART] ,yHart[MAX_HART];
float xEnemy[MAX_STONES] ,yEnemy[MAX_STONES];
float xHealthBarStart = 1200;
GLint stoneAlive[MAX_STONES];
GLint hartAlive[MAX_HART];

bool mButtonPressed= false,startGame=false,gameOver=false;
bool startScreen = true ,nextScreen=false,previousScreen=false;
bool gameQuit = false,instructionsGame = false, optionsGame = false;


char highScore[100],ch;
void enemySpaceship();
void display();
void createHart();
void EnemyStoneGenerate();
void hartGenerate();
void enemySpaceship_1();
void enemySpaceship_2();
void enemySpaceship_3();
void enemySpaceship_4();
void rgbColor(double r,double g,double b){

    r=r/255;
    g=g/255;
    b=b/255;
    glColor3f(r,g,b);
}
void displayRasterText(float x ,float y ,float z ,char *stringToDisplay) {
	int length;
	glRasterPos3f(x, y, z);
		length = strlen(stringToDisplay);

	for(int i=0 ;i<length ;i++){
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24 ,stringToDisplay[i]);
	}
}
void SetDisplayMode(int modeToDisplay) {
		switch(modeToDisplay){

        case GAME_SCREEN: glClearColor(0, 1, 1, 0);break;
		case MENU_SCREEN : glClearColor(1,0,1,0);break;
	}
}
void initializeEnemyArray() {


	for(int i = 0;i < MAX_STONES ;i++) {
		randomStoneIndices[i]=rand()%MAX_STONE_TYPES;
		stoneAlive[i]=true;
	}

	xEnemy[0] = -(200*MAX_STONES)-600;

	for(int i = 0;i<MAX_STONES ;i++) {
		yEnemy[i]=rand()%600;
		if(int(yEnemy[i])%2)
			yEnemy[i]*=-1;
		xEnemy[i+1] = xEnemy[i] + 200;
	}
}

void initializeHartArray() {


	for(int i = 0;i < MAX_HART ;i++) {

		hartAlive[i]=true;
	}

	xHart[0] = -(200*MAX_STONES)-600;

	for(int i = 0;i<MAX_HART ;i++) {
		yHart[i]=rand()%600;
		if(int(yHart[i])%2)
			yHart[i]*=-1;
		xHart[i+1] = xHart[i] + 600;
	}
}


void DrawenemySpaceship(int StoneIndex)
{
	glPushMatrix();
	glLoadIdentity();
	switch(StoneIndex)
	{
	case 0:


		glLoadIdentity();
		glTranslated(xEnemy[index] , yEnemy[index] ,0);
		glRotatef(90 ,0, 0, 1);
		enemySpaceship();

		break;

	case 1:
		glColor3f(1.0f, 0.8f, 0.8f);
		glLoadIdentity();
		glTranslated(xEnemy[index] , yEnemy[index] ,0);
		glRotatef(90 ,0, 0, 1);
		enemySpaceship_3();

		break;

	case 2:


		glLoadIdentity();
		glTranslated(xEnemy[index] , yEnemy[index] ,0);
		glRotatef(90 ,0, 0, 1);
		enemySpaceship_2();


		break;

	/*case 3:
		glColor3f(0.8f, 0.8f, 0.1f);
		glLoadIdentity();
		glTranslated(xEnemy[index] , yEnemy[index] ,0);
		glRotatef(90 ,0, 0, 1);
		enemySpaceship_4();


		glLoadIdentity();

		break;*/
	case 4:
		glColor3f(0.26f, 0.26f, 0.26f);
		glLoadIdentity();
		glTranslated(xEnemy[index] , yEnemy[index] ,0);
		glRotatef(90 ,0, 0, 1);
		enemySpaceship_1();

		break;
	}
	glPopMatrix();
}

void DrawHart(int HartIndex){
    glPushMatrix();
    glLoadIdentity();
        glTranslated(xHart[HartIndex] , yHart[HartIndex] ,0);
        createHart();
    glPopMatrix();

}

bool checkIfSpaceShipIsSafe() {
		for(int i =0 ;i<MAX_STONES ;i++) {
		if(stoneAlive[i]&((xOne >= (xEnemy[i]/2 -70) && xOne <= (xEnemy[i]/2 + 70) && yOne >= (yEnemy[i]/2 -18 ) && yOne <= (yEnemy[i]/2 + 53)) || (yOne <= (yEnemy[i]/2 - 20) && yOne >= (yEnemy[i]/2 - 90) && xOne >= (xEnemy[i]/2 - 40) && xOne <= (xEnemy[i]/2 + 40))))
		{
			stoneAlive[i]=0;
			return false;
		}
	}
	return true;
}

void enemySpaceship_1(){

    glColor3f(0,0,1);
    glBegin(GL_POLYGON);
        glVertex2f(-30, 10);
        glVertex2f(30, 10);
        glVertex2f(20, 0);
        glVertex2f(-20, 0);
    glEnd();

    glColor3f(1,0,0);
    glBegin(GL_POLYGON);
        glVertex2f(-20, 0);
        glVertex2f(20, 0);
        glVertex2f(0, -25);
    glEnd();

    glColor3f(1,0,1);
    glBegin(GL_POLYGON);
        glVertex2f(10, 20);
        glVertex2f(20, 20);
        glVertex2f(20, 10);
        glVertex2f(10, 10);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(-20, 20);
        glVertex2f(-10, 20);
        glVertex2f(-10, 10);
        glVertex2f(-20, 10);
    glEnd();

    glColor3f(1,1,1);
    glBegin(GL_POLYGON);
        glVertex2f(15, 30);
        glVertex2f(25, 20);
        glVertex2f(5, 20);

    glEnd();
    glBegin(GL_POLYGON);
        glVertex2f(-15, 30);
        glVertex2f(-5, 20);
        glVertex2f(-25, 20);
    glEnd();

}

void enemySpaceship_2(){

    glColor3f(0,0,1);
    glBegin(GL_POLYGON);
        glVertex2f(2, -8);
        glVertex2f(2, -12);
        glVertex2f(-2, -12);
        glVertex2f(-2, -8);
    glEnd();

    glColor3f(0,0,1);
    glBegin(GL_POLYGON);
        glVertex2f(2, -12);
        glVertex2f(5, -16);
        glVertex2f(2, -20);
        glVertex2f(-2, -20);
        glVertex2f(-5, -16);
        glVertex2f(-2, -12);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(2, -20);
        glVertex2f(2, -28);
        glVertex2f(-2, -28);
        glVertex2f(-2, -20);
    glEnd();

    glColor3f(0,0,1);
    glBegin(GL_POLYGON);
        glVertex2f(30, 0);
        glVertex2f(0, -9);
        glVertex2f(-30, 0);
    glEnd();

    glColor3f(0,1,0);
    glBegin(GL_POLYGON);
        glVertex2f(30, 0);
        glVertex2f(7, -16);
        glVertex2f(2, -10);
        glVertex2f(2, -8);
    glEnd();

    glColor3f(0,1,0);
    glBegin(GL_POLYGON);
        glVertex2f(-30, 0);
        glVertex2f(-7, -16);
        glVertex2f(-2, -10);
        glVertex2f(-2, -8);
    glEnd();

    glColor3f(1,0,0);
    glBegin(GL_POLYGON);
        glVertex2f(3, 25);
        glVertex2f(9, 11);
        glVertex2f(3, 5);
        glVertex2f(-3, 5);
        glVertex2f(-9, 11);
        glVertex2f(-3, 25);
    glEnd();

    glColor3f(1,0,0);
    glBegin(GL_POLYGON);
        glVertex2f(3, 5);
        glVertex2f(3, 0);
        glVertex2f(-3, 0);
        glVertex2f(-3, 5);
    glEnd();

    glColor3f(1,1,1);
    glBegin(GL_POLYGON);
        glVertex2f(9, 11);
        glVertex2f(30, 0);
        glVertex2f(3, 0);
        glVertex2f(3, 5);
    glEnd();

    glColor3f(1,1,1);
    glBegin(GL_POLYGON);
        glVertex2f(-9, 11);
        glVertex2f(-30, 0);
        glVertex2f(-3, 0);
        glVertex2f(-3, 5);
    glEnd();

    glColor3f(0,0.8,0.8);
    glBegin(GL_POLYGON);
        glVertex2f(9, 11);
        glVertex2f(30, 11);
        glVertex2f(30, 0);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(-9, 11);
        glVertex2f(-30, 11);
        glVertex2f(-30, 0);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(30, 11);
        glVertex2f(35, 16);
        glVertex2f(60, 16);
        glVertex2f(30, 0);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(-30, 11);
        glVertex2f(-35, 16);
        glVertex2f(-60, 16);
        glVertex2f(-30, 0);
    glEnd();

}


void enemySpaceship_3(){


}

void enemySpaceship_4(){

    glColor3f(1,0,0);
    glBegin(GL_POLYGON);
        glVertex2f(0, -15);
        glVertex2f(8, -22.5);
        glVertex2f(0, -30);
        glVertex2f(-8, -22.5);
    glEnd();

    glColor3f(0,1,0);
    glBegin(GL_POLYGON);
        glVertex2f(18, 30);
        glVertex2f(50, 0);
        glVertex2f(30, 0);
    glEnd();
    glBegin(GL_POLYGON);
        glVertex2f(50, 0);
        glVertex2f(10, -40);
        glVertex2f(30, 0);
    glEnd();
    glBegin(GL_POLYGON);
        glVertex2f(-18, 30);
        glVertex2f(-50, 0);
        glVertex2f(-30, 0);
    glEnd();
    glBegin(GL_POLYGON);
        glVertex2f(-50, 0);
        glVertex2f(-10, -40);
        glVertex2f(-30, 0);
    glEnd();

    glColor3f(0,0.8,0.8);
    glBegin(GL_POLYGON);
        glVertex2f(30, 0);
        glVertex2f(30, -3);
        glVertex2f(8, -22.5);
        glVertex2f(5, -19.5);
    glEnd();

    glColor3f(0,0.8,0.8);
    glBegin(GL_POLYGON);
        glVertex2f(15, 30);
        glVertex2f(18, 30);
        glVertex2f(8, -22.5);
        glVertex2f(5, -19.5);
    glEnd();

    glColor3f(0,0.8,0.8);
    glBegin(GL_POLYGON);
        glVertex2f(-30, 0);
        glVertex2f(-30, -3);
        glVertex2f(-8, -22.5);
        glVertex2f(-5, -19.5);
    glEnd();

    glColor3f(0,0.8,0.8);
    glBegin(GL_POLYGON);
        glVertex2f(-15, 30);
        glVertex2f(-18, 30);
        glVertex2f(-8, -22.5);
        glVertex2f(-5, -19.5);
    glEnd();

}

void createHart(){
    glColor3f(1,0,0);
    glBegin(GL_POLYGON);
        glVertex2f(0, 5);
        glVertex2f(15, 15);
        glVertex2f(30, 0);
        glVertex2f(0, -30);
        glVertex2f(-30 ,0);
        glVertex2f(-15, 15);
    glEnd();
}

//mynul start

void DrawLazerBeam1(float a, float b) {

	float xMid = -(55+50)/2.0;
	float yMid = (25+35)/2.0;

	float mouseXEnd = -((- mouseX) + a);
	float mouseYEnd = -((- mouseY) + b);
	glLineWidth(5);

	glColor3f(1, 0, 0);
	glBegin(GL_LINES);
		glVertex3f(xMid ,yMid,0);
		glVertex3f(mouseXEnd ,mouseYEnd,0);
	glEnd();
	glLineWidth(1);
}
void DrawLazerBeam2(float a, float b) {

	float xMid = -(55+50)/2.0;
	float yMid = (25+35)/2.0;

	float mouseXEnd = -((- mouseX) + a);
	float mouseYEnd = -((- mouseY) + b);
	glLineWidth(5);

	glColor3f(1, 0, 0);
	glBegin(GL_LINES);
		glVertex3f(xMid ,yMid,0);
		glVertex3f(mouseXEnd ,mouseYEnd,0);
	glEnd();
	glLineWidth(1);
}


void spaceship(){
glPushMatrix();

    glPushMatrix();
    glRotatef(90 ,0, 0, 1);
    glTranslatef(0,300,0.0f);
    glScalef(500,500,1);
    glColor3d(1,1,1);
    glBegin(GL_POLYGON);
        glVertex3f(0.0, -0.514f, 0.0f);
        glVertex3f(-.05, -0.65f, 0.0f);
        glVertex3f(.05f, -0.65f, 0.0f);
    glEnd();
        glColor3d(1,0,0);
    glBegin(GL_POLYGON);
        glVertex3f(-.05, -0.65f, 0.0f);
        glVertex3f(-.08, -0.68f, 0.0f);
        glVertex3f(.08f, -0.68f, 0.0f);
        glVertex3f(.05f, -0.65f, 0.0f);
    glEnd();
        glColor3d(0,1,0);
        glBegin(GL_POLYGON);
        glVertex3f(-.08, -0.68f, 0.0f);
        glVertex3f(-.08f, -0.71f, 0.0f);
        glVertex3f(.08f, -0.71f, 0.0f);
        glVertex3f(.08f, -0.68f, 0.0f);
    glEnd();
        glColor3d(0,0.54,0.585);
    glBegin(GL_POLYGON);
        glVertex3f(-.07f, -0.71f, 0.0f);
        glVertex3f(-.07, -0.73f, 0.0f);
        glVertex3f(-.03f, -0.73f, 0.0f);
        glVertex3f(-.03f, -0.71f, 0.0f);
    glEnd();
        glColor3d(0,0.54,0.585);
    glBegin(GL_POLYGON);
        glVertex3f(.07f, -0.71f, 0.0f);
        glVertex3f(.07f, -0.73f, 0.0f);
        glVertex3f(.03f, -0.73f, 0.0f);
        glVertex3f(.03f, -0.71f, 0.0f);
    glEnd();
        glColor3d(0.88,0.72,0.3);
    glBegin(GL_POLYGON);
        glVertex3f(.05f, -0.8f, 0.0f);
        glVertex3f(.07f, -0.73f, 0.0f);
        glVertex3f(.03f, -0.73f, 0.0f);
    glEnd();
        glColor3d(0.88,0.72,0.3);
    glBegin(GL_POLYGON);
        glVertex3f(-.05f, -0.8f, 0.0f);
        glVertex3f(-.07f, -0.73f, 0.0f);
        glVertex3f(-.03f, -0.73f, 0.0f);
    glEnd();
        glColor3d(0.54,0.0,0.0);
    glBegin(GL_POLYGON);
        glVertex3f(-0.01f, -0.58f, 0.0f);
        glVertex3f(-0.01f, -0.64f, 0.0f);
        glVertex3f(0.01f, -0.64f, 0.0f);
        glVertex3f(0.01f, -0.58f, 0.0f);
    glEnd();
    glPopMatrix();
    if(mButtonPressed){

     glPushMatrix();
     glTranslatef(86,-78,0.0f);
     DrawLazerBeam1(86,-78);
     glPopMatrix();
      glPushMatrix();
     glTranslatef(86,15,0.0f);
     DrawLazerBeam2(86,15);
     glPopMatrix();

    }

    glPushMatrix();
    glTranslatef(-25,-15,0.0f);
    glRotatef(180,1, 0, 0);
    glRotatef(180,0, 1, 0);
//    DrawSpaceShipLazer();

    glPopMatrix();

     glPushMatrix();
    glTranslatef(80,15,0.0f);

//    DrawSpaceShipLazer();

    glPopMatrix();
glPopMatrix();

}




void SpaceshipCreate(){
	glPushMatrix();
	glTranslated(xOne,yOne,0);
	if(!checkIfSpaceShipIsSafe() && alienLife ){
		alienLife-=10;
		xHealthBarStart -= 230;
	}

	spaceship();
	glPushMatrix();
	glTranslated(4,19,0);

	glPopMatrix();

	glEnd();
	glPopMatrix();
}
void DisplayHealthBar() {

	glColor3f(1 ,0 ,0);
	glBegin(GL_POLYGON);
		glVertex2f(-xHealthBarStart ,700);
		glVertex2f(1200 ,700);
		glVertex2f(1200 ,670);
		glVertex2f(-xHealthBarStart, 670);
	glEnd();
	char temp[40];
	glColor3f(0 ,0 ,1);
	sprintf(temp,"SCORE = %d",Score);
	displayRasterText(-1100 ,600 ,0.4 ,temp);
	sprintf(temp,"  LIFE = %d",alienLife);
	displayRasterText(800 ,600 ,0.4 ,temp);
	sprintf(temp,"  LEVEL : %d",GameLvl);
	displayRasterText(-100 ,600 ,0.4 ,temp);
	glColor3f(1 ,0 ,0);
}
void startScreenDisplay()
{
	glLineWidth(50);
	SetDisplayMode(MENU_SCREEN);


	rgbColor(218, 219, 227);
	glBegin(GL_LINE_LOOP);
		glVertex3f(-750 ,-500 ,0.5);
		glVertex3f(-750 ,550 ,0.5);
		glVertex3f(750 ,550 ,0.5);
		glVertex3f(750 ,-500, 0.5);
	glEnd();

	glLineWidth(1);

	glColor3f(1, 1, 1);
	glBegin(GL_POLYGON);
		glVertex3f(-200 ,300 ,0.5);
		glVertex3f(-200 ,400 ,0.5);
		glVertex3f(200 ,400 ,0.5);
		glVertex3f(200 ,300, 0.5);
	glEnd();

	glBegin(GL_POLYGON);
		glVertex3f(-200, 50 ,0.5);
		glVertex3f(-200 ,150 ,0.5);
		glVertex3f(200 ,150 ,0.5);
		glVertex3f(200 ,50, 0.5);
	glEnd();

	glBegin(GL_POLYGON);
		glVertex3f(-200 ,-200 ,0.5);
		glVertex3f(-200 ,-100 ,0.5);
		glVertex3f(200, -100 ,0.5);
		glVertex3f(200, -200 ,0.5);
	glEnd();

	if(mouseX>=-100 && mouseX<=100 && mouseY>=150 && mouseY<=200){
		rgbColor(118, 73, 254);
		if(mButtonPressed){
			startGame = true ;
			gameOver = false;
			mButtonPressed = false;
		}
	} else
		rgbColor(0, 0, 0);

	displayRasterText(-100 ,340 ,0.4 ,"Start Game");

	if(mouseX>=-100 && mouseX<=100 && mouseY>=30 && mouseY<=80) {
		rgbColor(118, 73, 254);
		if(mButtonPressed){
			instructionsGame = true ;
			mButtonPressed = false;
		}
	} else
		glColor3f(0 , 0, 0);
	displayRasterText(-120 ,80 ,0.4 ,"Instructions");

	if(mouseX>=-100 && mouseX<=100 && mouseY>=-90 && mouseY<=-40){
		rgbColor(118, 73, 254);
		if(mButtonPressed){
			gameQuit = true ;
			mButtonPressed = false;
		}
	}
	else
		rgbColor(0, 0, 0);
	displayRasterText(-100 ,-170 ,0.4 ,"    Quit");

}
void GameScreenDisplay()
{
	SetDisplayMode(GAME_SCREEN);
	DisplayHealthBar();
	glScalef(2, 2 ,0);
	if(alienLife){
		SpaceshipCreate();
	}
	else {
		gameOver=true;
		instructionsGame = false;
		startScreen = false;
	}
    hartGenerate();
	EnemyStoneGenerate();

}
void readFromFile() {

	FILE *fp = fopen("HighScoreFile.txt" ,"r");
	int i=0;
	if(fp!= NULL){
		while(fread(&ch,sizeof(char),1 ,fp)){
			highScore[i++] = ch;
		}
		highScore[i] = '\0';
	}
	fclose(fp);
}
void writeIntoFile() {
	FILE *fp = fopen("HighScoreFile.txt" ,"w");
	int i=0;
	char temp[40];
	if(fp!= NULL){
		int n= Score;
		while(n){
			ch = (n%10)+ '0';
			n/=10;
			temp[i++] = ch;
		}
		temp[i] = '\0';
		//strrev(temp);
		puts(temp);
		if(temp[0] == '\0')
			temp[i++] = '0' ,temp[i++] = '\0';
		fwrite(temp ,sizeof(char)*i ,i ,fp);
	}
 fclose(fp);
}

//mynul end



//ishmam start

void GameOverScreen()
{
	SetDisplayMode(MENU_SCREEN);
	rgbColor(218, 219, 227);
	glLineWidth(50);
	glBegin(GL_LINE_LOOP);               //Border
		glVertex3f(-650 ,-500 ,0.5);
		glVertex3f(-650 ,520 ,0.5);
		glVertex3f(650 ,520 ,0.5);
		glVertex3f(650 ,-500, 0.5);
	glEnd();

	glLineWidth(1);

	rgbColor(102, 117, 127);
	glBegin(GL_POLYGON);				//GAME OVER
		glVertex3f(-550 ,810,0.5);
		glVertex3f(-550 ,610 ,0.5);
		glVertex3f(550 ,610 ,0.5);
		glVertex3f(550 ,810, 0.5);
	glEnd();

	glColor3f(1, 1, 0);
	glBegin(GL_POLYGON);				//RESTART POLYGON
		glVertex3f(-200, 50 ,0.5);
		glVertex3f(-200 ,150 ,0.5);
		glVertex3f(200 ,150 ,0.5);
		glVertex3f(200 ,50, 0.5);
	glEnd();

	glBegin(GL_POLYGON);				//QUIT POLYGON
		glVertex3f(-200 ,-200 ,0.5);
		glVertex3f(-200 ,-100 ,0.5);
		glVertex3f(200, -100 ,0.5);
		glVertex3f(200, -200 ,0.5);
	glEnd();


	displayRasterText(-300 ,640 ,0.4 ,"!! G A M E    O V E R ! ! ");
	glColor3f(0 , 0, 0);
	char temp[40];

	sprintf(temp,"Score : %d",Score);
	displayRasterText(-100 ,340 ,0.4 ,temp);
	readFromFile();
	char temp2[40];
	if(atoi(highScore) < Score){
		writeIntoFile();
		sprintf(temp2 ,"Highest Score :%d" ,Score);
	} else
		sprintf(temp2 ,"Highest Score :%s" ,highScore);

	displayRasterText(-250 ,400 ,0.4 ,temp2);

	if(mouseX>=-100 && mouseX<=100 && mouseY>=25 && mouseY<=75){
		glColor3f(0 ,0 ,1);
		if(mButtonPressed){
			startGame = true ;
			gameOver=false;
			mButtonPressed = false;
			initializeEnemyArray();
			alienLife=100;
			xHealthBarStart=1200;
			stoneTranslationSpeed=0.2;
			Score=0;
			GameLvl=1;
			GameScreenDisplay();
		}
	} else
		glColor3f(0 , 0, 0);
        displayRasterText(-70 ,80 ,0.4 ,"Restart");

	if(mouseX>=-100 && mouseX<=100 && mouseY>=-100 && mouseY<=-50){
		glColor3f(0 ,0 ,1);
		if(mButtonPressed){
			exit(0);
			mButtonPressed = false;
		}
	}
	else
		glColor3f(0 , 0, 0);
	displayRasterText(-100 ,-170 ,0.4 ,"    Quit");

}
void EnemyStoneGenerate(){

		if(xEnemy[0]>=1200){
			GameLvl++;
			stoneTranslationSpeed+=0.5;
			Score+=50;
			initializeEnemyArray();
			GameScreenDisplay();
		}

	for(int i=0; i<MAX_STONES ;i++){
		index = i;

		if(mouseX <= (xEnemy[i]/2+20) && mouseX >=(xEnemy[i]/2-20) && mouseY >= (yEnemy[i]/2-20) && mouseY <= (yEnemy[i]/2+20) && mButtonPressed){
			if(stoneAlive[i]){   // IF ALIVE KILL STONE
				stoneAlive[i]=0;
				Score++;
				if(Score%1==0) {
					stoneTranslationSpeed+=0.001;			//<--------------Rate of increase of game speed
				}
			}
		}
		xEnemy[i] += stoneTranslationSpeed;
		if(stoneAlive[i] )             //stone alive
			DrawenemySpaceship(randomStoneIndices[i]);
	}
	stoneAngle+=stoneRotationSpeed;
	if(stoneAngle > 360) stoneAngle = 0;

}

void hartGenerate(){

		if(xHart[0]>=1200){

			initializeHartArray();
		}

	for(int i=0; i<MAX_HART ;i++){
		index = i;

		if(mouseX <= (xHart[i]/2+20) && mouseX >=(xHart[i]/2-20) && mouseY >= (yHart[i]/2-20) && mouseY <= (yHart[i]/2+20) && mButtonPressed){
			printf("enter hartGenerate coluction detaction\n");
			if(hartAlive[i]){
                printf("enter hartGenerate coluction detaction ifif \n");
				hartAlive[i]=0;
				Score++;
				alienLife+=20;

			}
		}
		xHart[i] += stoneTranslationSpeed;
		if(hartAlive[i] )             //stone alive
			DrawHart(i);
	}
}

void backButton() {
	if(mouseX <= -450 && mouseX >= -500 && mouseY >= -275 && mouseY <= -250){
			glColor3f(0, 0, 1);
			if(mButtonPressed){
				mButtonPressed = false;
				instructionsGame = false;
				startScreenDisplay();
			}
	}
	else glColor3f(0, 0, 0);
	displayRasterText(-1000 ,-550 ,0, "Back");
}
void InstructionsScreenDisplay()
{
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	SetDisplayMode(MENU_SCREEN);
	//colorBackground();
	glColor3f(0, 0, 0);
	displayRasterText(-900 ,400 ,0.4 ,"Key 'w' to move up.");
	displayRasterText(-900 ,300 ,0.4 ,"Key 's' to move down.");
	displayRasterText(-900 ,200 ,0.4 ,"Key 'd' to move right.");
	displayRasterText(-900 ,100 ,0.4 ,"Key 'a' to move left.");
	displayRasterText(-900 ,0.0 ,0.4 ,"Left mouse click to shoot laser");
	//displayRasterText(-900 ,-100 ,0.4 ,"The packet can be placed only when 's' is pressed before.");
	displayRasterText(-900 ,-200 ,0.4 ,"You Get 1 point for shooting each objet and 50 points for completing each lvl ");
	displayRasterText(-900, -270,0.4,"The Objective is to score maximum points");
	backButton();
	if(previousScreen)
		nextScreen = false ,previousScreen = false; //as set by backButton()

}

void enemySpaceship(){

    glColor3f(0,0,1);
    glBegin(GL_POLYGON);
        glVertex2f(-30, 10);
        glVertex2f(30, 10);
        glVertex2f(20, 0);
        glVertex2f(-20, 0);
    glEnd();
    glColor3d(1,0,0);
    glBegin(GL_POLYGON);
        glVertex2f(-20, 0);
        glVertex2f(20, 0);
        glVertex2f(0, -25);
    glEnd();
    glColor3f(1,0,1);
    glBegin(GL_POLYGON);
        glVertex2f(10, 20);
        glVertex2f(20, 20);
        glVertex2f(20, 10);
        glVertex2f(10, 10);
    glEnd();
    glBegin(GL_POLYGON);
        glVertex2f(-20, 20);
        glVertex2f(-10, 20);
        glVertex2f(-10, 10);
        glVertex2f(-20, 10);
    glEnd();
    glColor3f(1,1,1);
    glBegin(GL_POLYGON);
        glVertex2f(15, 30);
        glVertex2f(25, 20);
        glVertex2f(5, 20);

    glEnd();
    glBegin(GL_POLYGON);
        glVertex2f(-15, 30);
        glVertex2f(-5, 20);
        glVertex2f(-25, 20);
    glEnd();

}

void display() {

	glClear(GL_COLOR_BUFFER_BIT);
	glViewport(0,0,1200,700);

	if(startGame && !gameOver)//startGame =false  gameOver=true 0 && 0
		GameScreenDisplay();

	else if(instructionsGame)
		InstructionsScreenDisplay();

	else if(gameOver)
		GameOverScreen();

	//Make spaceship bigger
	else if(startScreen){

			startScreenDisplay();


			if(gameQuit || startGame || optionsGame || instructionsGame){
				//startScreen = false;

				if(startGame){
					SetDisplayMode(GAME_SCREEN);
					startScreen = false;

				} else if(gameQuit)
					exit(0);

				} else if(instructionsGame) {
					SetDisplayMode(GAME_SCREEN);
					InstructionsScreenDisplay();
				}
		}

	glScalef(1/2 ,1/2 ,0);
	glFlush();
	glLoadIdentity();
	glutSwapBuffers();
}
void somethingMovedRecalculateLaserAngle() {

	float mouseXForTan = (-50 - mouseX) + xOne;
	float mouseYForTan = (35 - mouseY) + yOne;
	float LaserAngleInRadian = atan(mouseYForTan/mouseXForTan);
	LaserAngle = (180/PI) * LaserAngleInRadian;
}
void keys(unsigned char key, int x, int y)
{



	if(key == 'd') xOne+=SPACESHIP_SPEED;
	if(key == 'a') xOne-=SPACESHIP_SPEED;
	if(key == 'w') {yOne+=SPACESHIP_SPEED;}
	if(key == 's') {yOne-=SPACESHIP_SPEED;}
	if(key == 'd' || key == 'a' || key == 'w' || key == 's')
		somethingMovedRecalculateLaserAngle();

	display();

}
void myinit()
{
	glClearColor(0.5,0.5,0.5,0);
	glColor3f(1.0,0.0,0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

    gluOrtho2D(-1200,1200,-700,700);                   //<-----CHANGE THIS TO GET EXTRA SPACE

	glMatrixMode(GL_MODELVIEW);
}
void passiveMotionFunc(int x,int y) {

	//when mouse not clicked
	mouseX = float(x)/(m_viewport[2]/1200.0)-600.0;  //converting screen resolution to ortho 2d spec
	mouseY = -(float(y)/(m_viewport[3]/700.0)-350.0);
	testx=float(x);
	testy=float(y);

	//Do calculations to find value of LaserAngle
	somethingMovedRecalculateLaserAngle();
	display();
}
 void mouseClick(int buttonPressed ,int state ,int x, int y) {

	if(buttonPressed == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		mButtonPressed = true;
	else
		mButtonPressed = false;
	display();
}

 void idleCallBack() {			//when no mouse or keybord pressed
	 display();
 }
 int main(int argc, char** argv) {

	 FILE *fp = fopen("HighScoreFile.txt" ,"r") ;      //check if HighScoreFile.txt exist if not create
	 if(fp!=NULL)
		fclose(fp);
	 else
		 writeIntoFile();

	glutInit(&argc, argv);
	glutInitWindowSize(1200,700);
	glutInitWindowPosition(90 ,0);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);

	glutCreateWindow("THE SPACESHIP SHOOTING GAME");
	glutDisplayFunc(display);
	glutKeyboardFunc(keys);
	glutPassiveMotionFunc(passiveMotionFunc);
	glBlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA);
	glutIdleFunc(idleCallBack);
	glutMouseFunc(mouseClick);
	glGetIntegerv(GL_VIEWPORT ,m_viewport);
	myinit();
	SetDisplayMode(GAME_SCREEN);
	initializeEnemyArray();
	initializeHartArray();
	glutMainLoop();
	return 0;
 }
