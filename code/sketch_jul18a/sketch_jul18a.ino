

int ledPin = 2;  // LED connected to digital pin 13
int inPin = 3;    // pushbutton connected to digital pin 7
int val = 0;      // variable to store the read value

// Initialize I2C bus: Problem is I am using the i2c buss to drive display
Wire.begin(0x38);             // join i2c bus with address 38h
Wire.onReceive(receiveEvent); // register event


void setup() {
  pinMode(ledPin, OUTPUT);  // sets the digital pin 13 as output
  pinMode(inPin, INPUT);    // sets the digital pin 7 as input
}

void loop() {
  val = digitalRead(inPin);   // read the input pin
  digitalWrite(ledPin, val);  // sets the LED to the button's value
}
