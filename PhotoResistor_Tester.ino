#define top_left_photo A1 //pin assignments
#define bottom_left_photo A2
#define top_right_photo A3
#define bottom_right_photo A4

void setup() {
  // put your setup code here, to run once:
  pinMode(top_left_photo, INPUT);
  pinMode(bottom_left_photo, INPUT);
  pinMode(top_right_photo, INPUT);
  pinMode(bottom_right_photo, INPUT);

  Serial.begin(9600); //starts the serial monitor at 9600 baud.
 
}

void loop() {
  // put your main code here, to run repeatedly:
  
  int top_left_data = analogRead(top_left_photo); //read the data of the photoresitor
  int bottom_left_data = analogRead(bottom_left_photo);
  int top_right_data = analogRead(top_right_photo);
  int bottom_right_data = analogRead(bottom_right_photo);

  Serial.print("top_left_photo:"); //print the values to the serial monitor. 
  Serial.print(top_left_data);
  Serial.print(",");               //Formated to use the serial plotter.
  Serial.print("bottom_left_photo:");
  Serial.print(bottom_left_data);
  Serial.print(",");
  Serial.print("top_right_photo:");
  Serial.print(top_right_data);
  Serial.print(",");
  Serial.print("bottom_right_photo:");
  Serial.println(bottom_right_data);
}
