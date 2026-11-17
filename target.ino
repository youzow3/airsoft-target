int ledPin = 4;
int vibPin = 3;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);
  pinMode(vibPin, INPUT);
}

void loop() {
  int state = digitalRead(vibPin);
  if (state == HIGH)
    digitalWrite(ledPin, HIGH);
  else
    digitalWrite(ledPin, LOW);

  delay(10);
}
