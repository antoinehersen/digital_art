color background_color;
color rock_color;
float seed;
int perlin_octave;


void setup() {
  size(screen.width, screen.height  );
  colorMode(HSB, 360.0, 1.0, 1.0);
  background_color = color(180.0, 0.07, 0.85);
  background( background_color);
  seed = 0.0;
  rock_color = color(228, 0.79, 0.42);
  perlin_octave = 3;
  noiseDetail(perlin_octave);
  noStroke();
  draw_mountain_range();
}

void mousePressed() {
  //  seed += 999;
  perlin_octave ++ ;
  noiseDetail(perlin_octave);
  // add_noise();
  //save("noise_sea.png");
}

void draw() {
  // add_noise();
  draw_mountain_range();
  add_noise();
}

int coord(int x, int y) {
  int x_ = x % width;
  if (x_ < 0) { 
    x_ += width;
  }

  int y_ = y % height;
  if (y_ < 0) { 
    y_ += height ;
  }
  return x_ + width* y_;
}

void add_noise() {
  loadPixels();


  for ( int x=0 ; x < width; x++) {
    for (int y=0; y< height;y++) {
      color i = pixels[coord(x, y)];
      pixels[coord(x, y)] = color(
      hue(i), // + random(-3,3),
      saturation(i) +random(-0.02, 0.02), 
      brightness(i) +random(-0.02, 0.02) 
        );
    }
  }

  updatePixels();
  // filter(BLUR, 0.4);
  //filter(DILATE);
}

void draw_montain_line(float y) {
  fill(  color(228, 0.79, 1.0- 0.8 * y/height));
  stroke(  color(228, 0.79, 1.0- 0.9 * y/height));
  beginShape();
  vertex(0, 200);
  int step = 1;
  for (int x = 0; x < width - step ; x+=step ) {
    float y_noise = 160* pow( noise(0.01* x, 0.02* y, seed), 1.2);
    vertex(x, - y_noise);
  }
  vertex( width, 200);
  endShape(CLOSE);
}


void draw_mountain_range() {
  background( background_color);
  pushMatrix();
 // translate(0, 100);

  float y_step = 2;
  for (int y = 100; y <= height + 2*y_step; y += y_step) {
    translate(0, y_step);
    draw_montain_line(y);
    y_step *= 1.3;
    //   println(y_step);
  }
  popMatrix();
  seed += 0.01;
}

