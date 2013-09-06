////////////////////////////////////////////////////////////////////////
//
// Assignment 1 support functions (cs411 f13)
//
// Compile: gcc as1.cpp -framework OpenGL -framework GLUT -o as1
//
////////////////////////////////////////////////////////////////////////

#if defined(__APPLE__) && defined(__MACH__)
#  include <GLUT/glut.h>
#else 
#  include <GL/glut.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define FRAGMENTS 100

typedef enum {NOOBJ, RECTOBJ, CIRC, PLINE, PGON} objType;

typedef struct{
  float x,y;      // x and y coordinates of the point
} Point;

typedef struct{
  int   type;     // object type
  float tx,ty;    // translation
  float rotAng;   // rotation
  float sx,sy;    // scale
  float r,g,b;    // color
  float fillFlag; // fill flag
  int   ptsNum;   // number of coordinates in the vertex array
  float param;    // shape parameter (e.g. radius of circle)
  Point pts[100]; // array of vertices
} Obj;

// Global Variables
Obj objLst[100];           // object list
int objsNum;               // the total number of objects
float xMin,xMax,yMin,yMax; // specification of the current viewing window


int readObjLst(char *fn, Obj *objLst)
{
  FILE* fin;
  char c,c1,c2;
  int i;
  Obj *o;

  int objsNum=0;

  // set default values
  Obj curDefault= {NOOBJ, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0, 0.0};

  // open input file
  if(! (fin=fopen(fn,"r")) ){
    printf("\nCan't open file %s\n\7",fn);
    return 0;
  }

  // read objects
  while(fscanf(fin,"%c%c",&c1,&c2)!=EOF) {

    // remove white space
    while(c1== ' ' || c1 =='\n'){
      c1=c2;
      if(fscanf(fin,"%c",&c2)==EOF) return(objsNum);
    }
    switch(c1){

    // add object
    case 'a':
      o = &objLst[objsNum];
      *o = curDefault;

      switch(c2){
      case 'l': // polyline
      case 'p': // polygon
      	o->type=PLINE;
      	if(c2=='p') o->type=PGON;
      	fscanf(fin,"%d",&o->ptsNum);
      	for(i=0;i<o->ptsNum;i++)fscanf(fin,"%f%f",&o->pts[i].x,&o->pts[i].y);
      	objsNum++; 
      break;
      case 'r': // RECTOBJangle
      	o->type=RECTOBJ;
      	fscanf(fin,"%f%f%f%f",&o->pts[0].x,&o->pts[0].y,&o->pts[1].x,&o->pts[1].y);
      	o->ptsNum=2;
      	objsNum++; 
      break;
      case 'c': // circle
      	o->type=CIRC;
      	fscanf(fin,"%f%f%f",&o->pts[0].x,&o->pts[0].y,&o->param); 
      	o->ptsNum=1;
      	objsNum++; 
      break;
      default:
        printf("Warning: unknown object type (%c)\n\7",c2);
      }
      break;

    // set property
    case 's':
      o = &curDefault;

      switch(c2){
      case 't': fscanf(fin,"%f%f",&o->tx,&o->ty);       break; // translation
      case 'r': fscanf(fin,"%f",&o->rotAng);            break; // rotation
      case 's': fscanf(fin,"%f%f",&o->sx,&o->sy);       break; // scale
      case 'c': fscanf(fin,"%f%f%f",&o->r,&o->g,&o->b); break; // color
      case 'f': fscanf(fin,"%f",&o->fillFlag);          break; // fill
      default:
        printf("Warning: unknown object property (%c)\n\7",c2);
      }
      break;

    }

    // remove trailing characters to end of line
    while(fread(&c,1,1,fin)) if (c== '\n') break;
  }

  // return number of objects read
  fclose(fin);
  return(objsNum);
}


void processObjs(int objsNum, Obj *objLst)
{
  int i;
  Obj *o;
  Point aux;

  for (i = 0; i < objsNum; i++){
    o = &objLst[i];

    switch(o->type){
      case RECTOBJ:

        // o->pts[2]->x = o->pts[1]->x;
        // o->pts[2]->y = o->pts[0]->y;

        // o->pts[3]->x = o->pts[0]->x;
        // o->pts[3]->y = o->pts[1]->y;

        o->pts[2].x = o->pts[1].x;
        o->pts[2].y = o->pts[0].y;

        o->pts[3].x = o->pts[0].x;
        o->pts[3].y = o->pts[1].y;

        aux.x = o->pts[2].x;
        aux.y = o->pts[2].y;

        o->pts[2].x = o->pts[1].x;
        o->pts[2].y = o->pts[1].y;

        o->pts[1].x = aux.x;
        o->pts[1].y = aux.y;

        o->ptsNum=4;
      break;

      case CIRC:

      break;

    }
  }

}


void dumpObjLst(int objsNum, Obj *objLst)
{
  int i,j;
  Obj *o;

  // print the opbect type and its points
  for(i=0;i<objsNum;i++){
    o = &objLst[i];

    printf("*** %d:", o->type);
    for(j=0;j<o->ptsNum;j++) printf(" (%3.1f,%3.1f)",o->pts[j].x, o->pts[j].y);
    printf("\n");
  }
}


void reshape (int w, int h)
{
 
  glViewport (0, 0, w, h);
}



void init(void) 
{
  glClearColor (0.0, 0.0, 0.0, 0.0);
  glShadeModel (GL_FLAT);

  xMin = yMin = -10.0;
  xMax = yMax =  10.0;

  glOrtho(-10.0, 10.0, -10.0, 10.0, -10.0, 10.0);
}

void drawCircle(float cx, float cy, float r, float flag) 
{ 
  int i;
  float x, y, theta;

  if (flag) glBegin(GL_POLYGON);
  else glBegin(GL_LINE_LOOP); 

  for(i = 0; i < FRAGMENTS; i++) { 
    theta = 2.0f * M_PI * float(i) / float(FRAGMENTS);  // get the current angle 

    x = r * cosf(theta);  // calculate the x component 
    y = r * sinf(theta);  // calculate the y component 

    glVertex3f(x + cx, y + cy, 0.0);
  } 

  glEnd(); 
}

void display(void)
{
  int i, j;
  Obj *o;

  glClear (GL_COLOR_BUFFER_BIT);

  for (i=0; i<objsNum; i++) 
  {
    o = &objLst[i];
    glColor3f(o->r, o->g, o->b);
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    glTranslatef(o->tx, o->ty, 0.0);
    glRotatef(o->rotAng, 0.0, 0.0, 1.0);
    glScalef(o->sx, o->sy, 1.0);
    switch(o->type){
      case RECTOBJ:
        if (o->fillFlag) glBegin(GL_POLYGON);
        else glBegin(GL_LINE_LOOP);

        for (j = 0; j < o->ptsNum; j++) glVertex3f ((float)o->pts[j].x, (float)o->pts[j].y, 0.0);

      break;
      case PLINE:
        glBegin(GL_LINE_STRIP);
        for (j = 0; j < o->ptsNum; j++) glVertex3f ((float)o->pts[j].x, (float)o->pts[j].y, 0.0);
      break;

      case PGON:
        glBegin(GL_POLYGON);
        for (j = 0; j < o->ptsNum; j++) glVertex3f ((float)o->pts[j].x, (float)o->pts[j].y, 0.0);
      break;
      case CIRC:
        drawCircle(o->pts[0].y, o->pts[0].y, o->param, o->fillFlag);
      break;
    }
    glEnd();
    glPopMatrix();
  }

  glFlush();
}


void help()
{
  printf("Keys:\n");
  printf("-----\n");
  printf("  h   = keys help\n");
  printf("  i/o = zoom in/out\n");
}


void keyboard(unsigned char key, int x, int y)
{
  
}



int main(int argc, char *argv[])
{

  // check transferred arguments
  if(argc<2){
    printf("\nUsage draw2d <drawFile>\n\n");
    exit(0);
  }

  // load, dump, and process the object file
  objsNum=readObjLst(argv[1],objLst);
  dumpObjLst(objsNum, objLst);
  processObjs(objsNum, objLst);

  glutInit(&argc, argv);
  glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize (500, 500); 
  glutInitWindowPosition (100, 100);
  glutCreateWindow (argv[0]);
  printf("Using OpenGL version %s\n", glGetString(GL_VERSION));

  init ();
  glClear (GL_COLOR_BUFFER_BIT);
  glutDisplayFunc(display); 
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);

  glutMainLoop();
  return 0;
}


////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////
