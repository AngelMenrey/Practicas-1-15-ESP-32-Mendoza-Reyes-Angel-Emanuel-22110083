int led=13;
int push_button=14; 
void setup(){
  Serial.begin(115200);
  pinMode(led, OUTPUT);
  pinMode(push_button,INPUT);
}
void loop(){
 int state= digitalRead(push_button);
 if(state==HIGH)
 {
   digitalWrite(led,HIGH);
   Serial.println("led is on");
   delay(10);
 }
 else
 {
   digitalWrite(led, LOW);
   Serial.println("led is off");
   delay(10);
 }
}