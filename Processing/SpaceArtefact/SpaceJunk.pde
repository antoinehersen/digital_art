/**
 * Space Artefact
 * by Antoine Hersen
 * based on  Space Junk  
 * by Ira Greenberg. 
 * 
 */
import processing.video.*;

import processing.opengl.*;

MovieMaker mm;  // Declare MovieMaker object

// Used for oveall rotation
float ang;

// Cube count-lower/raise to test P3D/OPENGL performance
int limit = 3000;

// Array for all cubes
Cube[]cubes = new Cube[limit];


boolean record = false;

void setup() {

  //  size(1024, 768 ); 
  size(1024, 768, OPENGL); 
  if (record) {
    hint(DISABLE_OPENGL_2X_SMOOTH);  
    String _time = "" + minute();
    mm = new MovieMaker(this, 1024, 768, "video" + _time + ".mov", 
    30, MovieMaker.H263, MovieMaker.HIGH);
  }

  //  size(screen.width,screen.height,OPENGL);
  //  stroke(255);
  noFill();
  background(0); 
  noStroke();

  float initial_rad = 10;
  float init_size = 20;
  // Instantiate cubes, passing in random vals for size and postion
  for (int i = 0; i< cubes.length; i++) {
    cubes[i] = new Cube(random(20), random(20), random(20), 
    random(-initial_rad, initial_rad), int(random(-initial_rad, initial_rad)), 
    int(random(-initial_rad, initial_rad)));
  }
}

void draw() {
  background(0); 
  fill(200);

  // Set up some different colored lights
  pointLight(51, 102, 255, 0, 0, 0); 
  // pointLight(200, 40, 60, -65, -60, -150);

  // Raise overall light in scene 
  ambientLight(20, 20, 20); 

  // Center geometry in display windwow.
  // you can change 3rd argument ('0')
  // to move block group closer(+)/further(-)
  translate(width/2, height/2, -200 );

  // Rotate around y and x axes
  rotateY(radians(0.8* ang));
  rotateX(radians(0.8* ang));

  // Draw cubes
  for (int i = 0; i < cubes.length; i++) {
    cubes[i].drawCube();
    // cubes[i].jiggle();
    cubes[i].expand();
  }

  if (record)
    mm.addFrame();  // Add window's pixels to movie

    //println(frameCount);
  // Used in rotate function calls above
  ang++;
}

void keyPressed() {
  if (key == ' ') {
    if (record) 
      mm.finish();  // Finish the movie if space bar is pressed!
  }
}

