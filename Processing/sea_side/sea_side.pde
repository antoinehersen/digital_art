color background_color;
color rock_color;
float seed;
int perlin_octave;

import processing.opengl.*;

void setup() {
  size(1000, 700, OPENGL);
  colorMode(HSB, 360.0, 1.0, 1.0);
  background_color = color(180.0, 0.07, 0.85);
  background( background_color);
  seed = 0.0;
  rock_color = color(228, 0.79, 0.42);
  perlin_octave = 1;
  noiseDetail(perlin_octave);


  //  draw_
}

void mousePressed() {
  seed += 999;
  perlin_octave ++ ;
}

void draw_montain_line() {
  fill(rock_color);
  pushMatrix();
  translate(0, 500);
  beginShape();
  vertex(0, 0);
  int step = 1;
  for (int x = 10; x < width - step ; x+=step ) {
    float y_noise = 150* noise(0.01* x, seed);
    vertex(x, - y_noise);
  }
  vertex( width-10, 0);
  vertex( width-10, 0);
  endShape(CLOSE);

  popMatrix();
  seed += 0.001;
}

void draw_montain_curve() {
  fill(rock_color);
  pushMatrix();
  translate(0, 500);
  beginShape();
  curveVertex(0, 0);
  curveVertex(0, 0);
  int step = 5;
  for (int x = 10; x < width - step ; x+=step ) {
    float y_noise = 100* noise(0.01* x + seed);
    println(y_noise);
    curveVertex(x, - y_noise);
  }
  curveVertex( width-10, 0);
  curveVertex( width-10, 0);
  endShape();
  popMatrix();
  seed += 0.001;
  println( "narf" + seed );
}

void draw() {
  background( background_color);

  draw_montain_line();
}

