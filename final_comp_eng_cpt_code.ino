//variables that correspond to motors a and b
int pwma = 11;
int ai1 = 13;
int ai2 = 12;
int pwmb = 10;
int bi1 = 7;
int bi2 = 8;
//variables that correspond to ir sensor (Lside, Center, Rside)
int Lsen = 4;
int Csen = 5;
int Rsen = 6;

//variables that correspond to joystick (Xaxis, Yaxis, button)
int x_pin = A0;
int y_pin = A1;
int b_pin = 2;

void setup() {
  Serial.begin(9600);
  //motor variables are outputs
  pinMode(pwma, OUTPUT);
  pinMode(ai1, OUTPUT);
  pinMode(ai2, OUTPUT);
  pinMode(pwmb, OUTPUT);
  pinMode(bi1, OUTPUT);
  pinMode(bi2, OUTPUT);
 //IRsensor variables are inputs
  pinMode(Lsen, INPUT);
  pinMode(Csen, INPUT);
  pinMode(Rsen, INPUT);
 //joystick variables are outputs
  pinMode(x_pin, INPUT);
  pinMode(y_pin, INPUT);
  pinMode(b_pin, INPUT);
}

void loop() {
  while (Serial.available() == 0) {
// the varibles made correspond with whatever value x_pin is, y_pin is, and b_pin is. This variable gets or reads the value of the variable in the "...Read" function and sets itself equal to that.
    int x_data = analogRead(x_pin);
    int y_data = analogRead(y_pin);
    int b_data = digitalRead(b_pin);

//speed for motor A and B
    int speedm1 = pwma;
    int speedm2 = pwmb;

// if joystick button isn't pressed than it runs the joystick code in the if statement
    if (b_data == 0) {
// prints the joystick value
      Serial.print(" x data:");
      Serial.print(x_data);

      Serial.println(" y data:");
      Serial.print(y_data);

      Serial.println(" b data:");
      Serial.print(b_data);
// if the value of y is between 523-1023 it will move motors forward and the speed of both motors is set to the value of y read from the joystick
      if (y_data > 523 && y_data < 1023) {
        analogWrite(speedm1, y_data);
        analogWrite(speedm2, y_data);
        digitalWrite(ai1, HIGH);
        digitalWrite(ai2, LOW);
        digitalWrite(bi1, HIGH);
        digitalWrite(bi2, LOW);
// if the value of y is inbetween 0-517 it will move motors backwards and the speed of both motors is set to the value of y read from the joystick
      } else if (y_data < 517 && y_data > 0) {
        analogWrite(pwma, y_data);
        analogWrite(pwmb, y_data);
        digitalWrite(ai1, LOW);
        digitalWrite(ai2, HIGH);
        digitalWrite(bi1, LOW);
        digitalWrite(bi2, HIGH);
// if the value of x is between 0-515 it will move motor A forward and motor B backward turning the car left and the speed of both motors is set to the value of x read from the joystick
      } else if (x_data < 515 && x_data > 0) {
        analogWrite(pwma, x_data);
        analogWrite(pwmb, x_data);
        digitalWrite(ai1, HIGH);
        digitalWrite(ai2, LOW);
        digitalWrite(bi1, LOW);
        digitalWrite(bi2, HIGH);
// if the value of x is between 514-1023 it will move motor B forward and motor A backward turning the car right and the speed of both motors is set to the value of x read from the joystick
      } else if (x_data > 514 && x_data < 1023) {
        analogWrite(pwma, x_data);
        analogWrite(pwmb, x_data);
        digitalWrite(ai1, LOW);
        digitalWrite(ai2, HIGH);
        digitalWrite(bi1, HIGH);
        digitalWrite(bi2, LOW);
// if the value of x is in the middle meaning no one is moving the joystick the car doesn't move
      } else {
        analogWrite(pwma, LOW);
        analogWrite(pwmb, LOW);
        digitalWrite(ai1, LOW);
        digitalWrite(ai2, LOW);
        digitalWrite(bi1, LOW);
        digitalWrite(bi2, LOW);
      }
    }

// if joystick button is pressed than it runs the ir sensor code in the if statement
    else if (b_data == 1) {
      //speed of motors A and B are set to 130
      analogWrite(pwma, 130);
      analogWrite(pwmb, 130);
      // the variables below are equal to whatever value is read from it's corresponding sensor. For example lwd_val value is based of whether the Left ir sensor is on
      int lwd_val = digitalRead(Lsen);
      int cen_val = digitalRead(Csen);
      int rwd_val = digitalRead(Rsen);
//prints values of each sensor
      Serial.print("left sen: ");
      Serial.print(lwd_val);
      Serial.print("                    center sen: ");
      Serial.print(cen_val);
      Serial.print("                    right sen: ");
      Serial.println(rwd_val);
// if the center sensor is 0 but the right and left are on (car in the middle of black line) the function fwd runs
      if (cen_val == 0 && rwd_val == 1 && lwd_val == 1) {
        fwd();
// if the right sensor is 1 but the center and left are off (car on left side of the black line) the function left runs
      } else if (rwd_val == 1 && cen_val == 0 && lwd_val == 0) {
        left();
// if the left sensor is 1 but the center and right are off (car on right side of the black line) the function right runs
      } else if (lwd_val == 1 && cen_val == 0 && rwd_val == 0) {
        right();
// if the right and center sensor is 1 but the left are off (car on left side of the black line) the function hardL runs
      } else if (rwd_val == 1 && cen_val == 1 && lwd_val == 0) {
        hardL();
        // if the left and center sensor are 1(on) and right sensor is off (car on right side of the black line) the function hardR runs
      } else if (lwd_val == 1 && cen_val == 1 && rwd_val == 0) {
        hardR();
      }
// else if all sensor are on or all sensor are off car doesn't move  
      else {
        digitalWrite(ai1, LOW);
        digitalWrite(bi1, LOW);
        digitalWrite(ai2, LOW);
        digitalWrite(bi2, LOW);
      }
    }
  }
}
//Method fwd() runs when it is called and drives car forward
void fwd() {
  digitalWrite(ai1, HIGH);
  digitalWrite(bi1, HIGH);
  digitalWrite(ai2, LOW);
  digitalWrite(bi2, LOW);
}
//Method right() runs when it is called and drives car rightward
void right() {
  digitalWrite(bi1, HIGH);
  digitalWrite(ai1, LOW);
  digitalWrite(ai2, LOW);
  digitalWrite(bi2, LOW);
}
//Method left() runs when it is called and drives car leftward
void left() {
  digitalWrite(ai1, HIGH);
  digitalWrite(bi1, LOW);
  digitalWrite(ai2, LOW);
  digitalWrite(bi2, LOW);
}
//Method hardR() runs when it is called and drives car rightward
void hardR() {
  digitalWrite(bi1, HIGH);
  digitalWrite(ai1, LOW);
  digitalWrite(ai2, HIGH);
  digitalWrite(bi2, LOW);
}
//Method hardL() runs when it is called and drives car leftward
void hardL() {
  digitalWrite(ai1, HIGH);
  digitalWrite(bi1, LOW);
  digitalWrite(ai2, LOW);
  digitalWrite(bi2, HIGH);
}
