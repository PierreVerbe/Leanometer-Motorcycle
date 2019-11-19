const int lRed = 9;
const int lOrange = 8;
const int green = 7;
const int rOrange = 6;
const int rRed = 4;

void setup(){
  pinMode(lRed, OUTPUT);
  pinMode(lOrange, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(rOrange, OUTPUT);
  pinMode(rRed, OUTPUT);

   digitalWrite(lRed, HIGH);
   digitalWrite(lOrange, HIGH);
   digitalWrite(green, HIGH);
   digitalWrite(rOrange, HIGH);
   digitalWrite(rRed, HIGH);
   delay(5000);
   
   digitalWrite(lRed, LOW);
   digitalWrite(lOrange, LOW);
   digitalWrite(green, LOW);
   digitalWrite(rOrange, LOW);
   digitalWrite(rRed, LOW);
  
}
void loop(){
  digitalWrite(rRed, LOW); 
  digitalWrite(lRed, HIGH); 
  delay(500);
  
  digitalWrite(lRed, LOW);
  digitalWrite(lOrange, HIGH); 
  delay(500); // attendre 2 seconde

  digitalWrite(lOrange, LOW);
  digitalWrite(green, HIGH); 
  delay(500); // attendre 2 seconde

  digitalWrite(green, LOW);
  digitalWrite(rOrange, HIGH); 
  delay(500); // attendre 2 seconde

  digitalWrite(rOrange, LOW);
  digitalWrite(rRed, HIGH); 
  delay(500); // attendre 2 seconde
}
