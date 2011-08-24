void setup() {
  size(600, 600, P2D);
  colorMode(HSB, 1.0);
  background(0.6);
}

Amoeba mobi = new Amoeba();


class Amoeba {
  void draw() {
    pushMatrix();

    fill(color(50.0/360, 0.99, 0.97));
    noStroke();
    ellipse(0, 0, 100, 120);
    translate(-10, 50);
    rotate(0.5);
    ellipse(0, 0, 80, 100);
    
    beginShape();
    curveVertex(0, 0); // the first control point
    curveVertex(-5, 0); // is also the start point of curve

    curveVertex(0, 100);
    curveVertex(20, 170);
    curveVertex(15, 100);
    
    curveVertex(20, 0);
    curveVertex(20, 0);
    endShape();
    
    fill(color(0.0, 0.0, 1.0));
    ellipse(0, 0, 50, 50);
    fill(color(0.0, 1.0, 0.0));
    ellipse(0, 0, 40, 40);
    
    translate(16,0);
    rotate(0.0);
    fill(color(0.0, 0.0, 1.0));
    ellipse(0, 0, 5, 5);

    popMatrix();
  }
}

void draw() {
  pushMatrix();
  translate(300, 300);
  mobi.draw();
  popMatrix();
}

