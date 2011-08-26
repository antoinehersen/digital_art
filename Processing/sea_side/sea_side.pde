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
  noStroke();
}

void mousePressed() {
  seed += 999;
  perlin_octave ++ ;
  noiseDetail(perlin_octave);
}

void draw_montain_line(float y) {
  fill(  color(228, 0.79, 1.0- 0.8 * y/height));

  beginShape();
  vertex(0, 0);
  int step = 1;
  for (int x = 0; x < width - step ; x+=step ) {
    float y_noise = 160* noise(0.01* x, y+seed);
    vertex(x, - y_noise);
  }
  vertex( width, 0);
  vertex( width, 0);
  endShape(CLOSE);

}

void draw_montain_curve() {
  fill(rock_color);
  pushMatrix();
  translate(0, 500);
  beginShape();
  curveVertex(0, 0);
  curveVertex(0, 0);
  int step = 2;
  for (int x = 10; x < width - step ; x+=step ) {
    float y_noise = 160* noise(0.01* x + seed);
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
  pushMatrix();
  int y_step = 40;
    for (int y = 100; y <= height + y_step; y += y_step) {
    translate(0, y_step);
    draw_montain_line(y);
  }
  popMatrix();
  seed += 0.01;

}

