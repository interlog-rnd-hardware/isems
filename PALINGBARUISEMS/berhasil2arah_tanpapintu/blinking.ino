void blinking()
{
  digitalWrite(led_g, HIGH);
  delay(1000);
  digitalWrite(led_g, LOW);
  delay(50);
  digitalWrite(led_b,HIGH);
  delay(1000);
  digitalWrite(led_b,LOW);
  delay(50);
  digitalWrite(led_r,HIGH);
  delay(1000);
  digitalWrite(led_r,LOW);
  delay(50);
  digitalWrite(buzzer,HIGH);
  delay(1000);
  digitalWrite(buzzer,LOW);
  delay(100);
}
