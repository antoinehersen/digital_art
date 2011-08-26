
// Dancing squidAmoeba by Antoine Hersen is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.

void setup() {
  size(1000, 800, P2D);
  colorMode(HSB, 1.0);
  background(0.6);
  nb_x = 12;
  nb_y= 6;
  mobi = new Amoeba[nb_x][nb_y];
  init_amoebas();
}

Amoeba[][] mobi;
int nb_x, nb_y;

void init_amoebas() {
  for (int y=0; y < nb_y; y++) {

    for (int x=0; x < nb_x; x++) {
      mobi[x][y] = new Amoeba();
    }
  }
}

class Amoeba {
  color yellowish;
  float amoeba_size, tail_size;
  float sub_body_size, sub_body_rot, tail_rot;
  float tail_tail;
  float eye_rot;
  float noise_seed;

  Amoeba() {
    yellowish = color(50.0/360 + random(-0.05, 0.15), 
    1.0 - random(0.3), 1.0 - random(0.2));

    amoeba_size = random(0.8, 1.2);
    sub_body_size = random(0.8, 1.2);
    sub_body_rot = random(-1, 1);
    tail_rot = random(-1, 1);
    tail_size = random(0.9, 1.1);
    tail_tail = random(-120, 120);
    eye_rot = random(0.0, 6.0);
    noise_seed = random(200);
  }
  
  void move() {
    //tail_rot += noise( noise_seed + 0.3* millis()) - 0.5 ;
  }
  
  void draw() {
    pushMatrix();

    fill( yellowish);
    noStroke();
    scale( amoeba_size);
    float head_rot =  3*(noise( 9*noise_seed  + 0.0005* millis()) - 0.5) ;
    rotate(head_rot);
    ellipse(0, 0, 100, 120);
        rotate(-head_rot);

    translate(-10, 50);
    rotate(sub_body_rot+ 1.3*(noise( 7*noise_seed  + 0.0005* millis()) - 0.5) );

    scale(sub_body_size);
    ellipse(0, 0, 80, 100);
    rotate(tail_rot + 1.2*(noise( noise_seed + 0.0005* millis()) - 0.5) );
    scale(tail_size);
    beginShape();
    curveVertex(0, 0); // the first control point
    curveVertex(-5, 0); // is also the start point of curve

    curveVertex(0, 100);
    curveVertex(tail_tail+ 400*(noise( 3*noise_seed + 0.001* millis()) - 0.5) , 170);
    curveVertex(15, 100);

    curveVertex(20, 0);
    curveVertex(20, 0);
    endShape();

    fill(color(0.0, 0.0, 1.0));
    ellipse(0, 0, 50, 50);
    fill(color(0.0, 1.0, 0.0));
    ellipse(0, 0, 40, 40);
    rotate(eye_rot+ 4*(noise( noise_seed + 0.001* millis()) - 0.5));
    translate(13, 0);
    fill(color(0.0, 0.0, 1.0));
    ellipse(0, 0, 8, 8);

    popMatrix();
  }
}

void mousePressed() {
  init_amoebas();

}

void draw() {
  pushMatrix();
  //  translate(300, 300);
    background(0.8);
  scale(0.5);
  translate(-60, -200);

  for (int y=0; y < nb_y; y++) {
    translate(0, 260);
    pushMatrix();

    for (int x=0; x < nb_x; x++) {
      translate(160, 0);
      mobi[x][y].draw();
      mobi[x][y].move();
    }
    popMatrix();
  }
  popMatrix();
  save("squid.png");

}

