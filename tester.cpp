////////////////////////////////////////
// tester.cpp
////////////////////////////////////////

#include "tester.h"



#define WINDOWTITLE	"Project 4: Cloth"

////////////////////////////////////////////////////////////////////////////////

static Tester *TESTER;

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	TESTER = new Tester(argc,argv);
	glutMainLoop();
	return 0;
}

////////////////////////////////////////////////////////////////////////////////

// These are really HACKS to make glut call member functions instead of static functions
static void display()									{TESTER->Draw();}
static void idle()										{TESTER->Update();}
static void resize(int x,int y)							{TESTER->Resize(x,y);}
static void keyboard(unsigned char key,int x,int y)		{TESTER->Keyboard(key,x,y);}
static void mousebutton(int btn,int state,int x,int y)	{TESTER->MouseButton(btn,state,x,y);}
static void mousemotion(int x, int y)					{TESTER->MouseMotion(x,y);}

////////////////////////////////////////////////////////////////////////////////

Tester::Tester(int argc,char **argv) {
	WinX=640;
	WinY=480;
	LeftDown=MiddleDown=RightDown=false;
	MouseX=MouseY=0;

	// Create the window
	glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH );
	glutInitWindowSize( WinX, WinY );
	glutInitWindowPosition( 0, 0 );
	WindowHandle = glutCreateWindow( WINDOWTITLE );
	glutSetWindowTitle( WINDOWTITLE );
	glutSetWindow( WindowHandle );

	// Background color
	glClearColor( .144, .195, .212, 1. );
    
   /* GLfloat lightColor0[] = {0.9f, 0.05f, 0.05f, 1.0f}; //Color (0.8, 0.1, 0.1)
    GLfloat lightPos0[] = {40.0f, 0.0f, 80.0f, 1.0f}; //Positioned at (4, 0, 8)
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
    
    //Add positioned light
    
    GLfloat lightColor1[] = {0.1f, 0.8f, 0.1f, 1.0f}; //Color (0.1, 0.8, 0.1)
    GLfloat lightPos1[] = {40.0f, 0.0f, -20.0f, 1.0f}; //Positioned at (-4, 0, -2)
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
    glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);*/
    
    
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
   // glEnable(GL_LIGHTING);
    glShadeModel(GL_SMOOTH);
   // glEnable(GL_LIGHT0);
   // glEnable(GL_LIGHT1);


	// Callbacks
	glutDisplayFunc( display );
	glutIdleFunc( idle );
	glutKeyboardFunc( keyboard );
	glutMouseFunc( mousebutton );
	glutMotionFunc( mousemotion );
	glutPassiveMotionFunc( mousemotion );
	glutReshapeFunc( resize );



	// Initialize components
    
    wind = new Wind(40 * Vector3(1, 1, 1));
    ground = new Ground();
    
    cloth = new Cloth(7, 10, 1.5);
    cloth->SetWind(wind);
    
    Cam.SetAspect(float(WinX)/float(WinY));
}

////////////////////////////////////////////////////////////////////////////////

Tester::~Tester() {
	glFinish();
	glutDestroyWindow(WindowHandle);
}

////////////////////////////////////////////////////////////////////////////////

void Tester::Update() {
	// Update the components in the world
	Cam.Update();

    cloth->Update(0.01);

	// Tell glut to re-display the scene
	glutSetWindow(WindowHandle);
	glutPostRedisplay();
}

////////////////////////////////////////////////////////////////////////////////

void Tester::Reset() {
	Cam.Reset();
	Cam.SetAspect(float(WinX)/float(WinY));

	//Cube.Reset();
}

////////////////////////////////////////////////////////////////////////////////

void Tester::Draw() {

	// Begin drawing scene
	glViewport(0, 0, WinX, WinY);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Draw components
	Cam.Draw();		// Sets up projection & viewing matrices

    cloth->Draw();
    ground->Draw();

	// Finish drawing scene
	glFinish();
	glutSwapBuffers();
}

////////////////////////////////////////////////////////////////////////////////

void Tester::Quit() {
	glFinish();
	glutDestroyWindow(WindowHandle);
	exit(0);
}

////////////////////////////////////////////////////////////////////////////////

void Tester::Resize(int x,int y) {
	WinX = x;
	WinY = y;
	Cam.SetAspect(float(WinX)/float(WinY));
}

////////////////////////////////////////////////////////////////////////////////

void Tester::Keyboard(int key,int x,int y) {
    
    
	switch(key) {
		case 0x1b:		// Escape
			Quit();
			break;
		case 'r':
			Reset();
			break;
        case 'w':
            wind->incrementVelocity();
            break;
        case 's':
            wind->decrementVelocity();
            break;
        case 'q':
            wind->togglePower();
            break;
        case 'b':
            cloth->toggleSelector();
            break;
        case 'n':
            cloth->decrementSelector();
            break;
        case 'm':
            cloth->incrementSelector();
            break;
        case 'h':
            cloth->toggleFixed();
            break;
        case 'l':
            cloth->decrementZ();
            break;
        case 'p':
            cloth->incrementZ();
            break;
        case 'k':
            cloth->decrementY();
            break;
        case 'o':
            cloth->incrementY();
            break;
        case 'j':
            cloth->decrementX();
            break;
        case 'i':
            cloth->incrementX();
            break;
    
    }
}

////////////////////////////////////////////////////////////////////////////////

void Tester::MouseButton(int btn,int state,int x,int y) {
	if(btn==GLUT_LEFT_BUTTON) {
		LeftDown = (state==GLUT_DOWN);
	}
	else if(btn==GLUT_MIDDLE_BUTTON) {
		MiddleDown = (state==GLUT_DOWN);
	}
	else if(btn==GLUT_RIGHT_BUTTON) {
		RightDown = (state==GLUT_DOWN);
	}
}

////////////////////////////////////////////////////////////////////////////////

void Tester::MouseMotion(int nx,int ny) {
	int dx = nx - MouseX;
	int dy = -(ny - MouseY);

	MouseX = nx;
	MouseY = ny;

	// Move camera
	// NOTE: this should really be part of Camera::Update()
	if(LeftDown) {
		const float rate=1.0f;
		Cam.SetAzimuth(Cam.GetAzimuth()+dx*rate);
		Cam.SetIncline(Cam.GetIncline()-dy*rate);
	}
	if(RightDown) {
		const float rate=0.01f;
		Cam.SetDistance(Cam.GetDistance()*(1.0f-dx*rate));
	}
}

////////////////////////////////////////////////////////////////////////////////
