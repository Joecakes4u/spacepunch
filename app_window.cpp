
# include <iostream>
# include "app_window.h"

AppWindow::AppWindow ( const char* label, int x, int y, int w, int h )
          :GlutWindow ( label, x, y, w, h )
 {
   _markx = 0;
   _marky = 0;
   addMenuEntry ( "Restart", evOption0);

   stash.add(new Rect(-.1, .1, .2, .2, 1, .5 ,0));
   stash.add(new Rect(-.6, 0.6, 1.2, 1.2, 0, 0 ,0));
   stash.add(new Rect(-0.7, 0.7, 1.4, 1.4, 0, 0.56 , 0.72));
   started = false;
   winner = false;
   count = 0;
   accelx = .008;
   accely = .016;
   highscore = 0;
   lastscore = 0;
 }

// mouse events are in window coordinates, but your scene is in [0,1]x[0,1],
// so make here the conversion when needed
void AppWindow::windowToScene ( float& x, float &y )
 {
   x = (2.0f*(x/float(_w))) - 1.0f;
   y = 1.0f - (2.0f*(y/float(_h)));
 }

void AppWindow::idle(){
  GlutWindow::Event e;
  e.type = GlutWindow::None;
  handle(e);
}

// Called every time there is a window event
void AppWindow::handle ( const Event& e ){
    bool rd=true;

    if (e.type == None)
    {
      if (started == true)
      {
        stash.first()->x -= accelx;
        stash.first()->y += accelx;
        stash.first()->l += accely;
        stash.first()->h += accely;
      }
    }
    if ( e.type==Keyboard ) 
    {
      switch ( e.key ){
        case ' ':         
          if (stash.r[2]->contains(stash.r[0]) && !stash.r[1]->contains(stash.r[0]))
          {
            std::cout << "YOU WIN!" << std::endl;
            winner = true;
            accelx *= 1.05;
            accely *= 1.05;
            count++;
            if(count > highscore){
              highscore = count;
            }
            lastscore = count;
          } else
          {
            std::cout << "FUCK YOU" << std::endl;
            winner = false;
            accelx = 0.008;
            accely = 0.016;
            started = false;
            if(count > highscore){
              highscore = count;
            }
            count = 0;
          }
          stash.r[0]->reset();
          break;
        case 27: // Esc was pressed
          exit(1);
      }
    }

    if ( e.type==MouseDown || e.type==Motion){
      _markx=(float)e.mx;
      _marky=(float)e.my;
      windowToScene(_markx,_marky);
    }

    if (e.type == MouseDown){
      started = true;
    }

    if (e.type==Menu){ 
      std::cout<<"Menu Event: "<<e.menuev<<std::endl;
      switch(e.menuev){

      }
      rd=false; // no need to redraw
    }

    const float incx=0.02f;
    const float incy=0.02f;
    if ( e.type==SpecialKey )
      switch ( e.key ){ 
        case GLUT_KEY_LEFT:  _markx-=incx; break;
        case GLUT_KEY_RIGHT: _markx+=incx; break;
        case GLUT_KEY_UP:    _marky+=incy; break;
        case GLUT_KEY_DOWN:  _marky-=incy; break;
        default: rd=false; // no redraw
      }

    if (rd) redraw(); // ask the window to be rendered when possible
}

void AppWindow::resize ( int w, int h )
 {
   // Define that OpenGL should use the whole window for rendering
    glViewport( 0, 0, w, h );
    _w=w; _h=h;
 }

// here we will redraw the scene according to the current state of the application.
void AppWindow::draw ()
  {
    // Clear the rendering window
    glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    // Clear the trasnformation stack
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_MULTISAMPLE);
    glEnable(GL_MULTISAMPLE);

    glColor3d(0,0,0);
    glRasterPos2f(-.05,-.05);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, count/10 + 48);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, count%10 + 48);

    //Prints highest score
    glColor3f(.1,.2,.8);
    char hs[14] = "High Score: \0";
    glRasterPos2f(-.99,.9);
    for(int i = 0; i < 12; i++){
      glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, hs[i]);
    }
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, highscore/10 + 48);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, highscore%10 + 48);

    //Prints last score
    glColor3f(.8,.2,.3);
    char ls[14] = "Last Score: \0";
    glRasterPos2f(.55,.9);
    for(int i = 0; i < 12; i++){
      glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ls[i]);
    }
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, lastscore/10 + 48);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, lastscore%10 + 48);

    if(!stash.r.empty()){
      for(std::vector<Rect*>::iterator i = stash.r.begin(); i != stash.r.end(); i++){
        (*i)->draw();
      }
    }

    // Swap buffers
    glFlush();         // flush the pipeline (usually not necessary)
    glutSwapBuffers(); // we were drawing to the back buffer, now bring it to the front
}

