

void pulse(int f, int offTime, int onTime, int starttime) { //frequency, time
  sine1.frequency(f);
  unsigned long currentMillis = millis();
  if (currentMillis - starttime < offTime) {
    sine1.amplitude(0.0);
    digitalWrite(ledPin, LOW);
  //  Serial.println("ITS SILENT");
  } else if (currentMillis - starttime < onTime) {
    sine1.amplitude(0.2);
    digitalWrite(ledPin, HIGH);
  //  Serial.println("ITS HAPPENING");
  } else {
    sine1.amplitude(0.0);
    digitalWrite(ledPin, LOW);
  //  Serial.println("IT HAPPENED AND WE NEVER NOTICED");
  }

}



boolean thresholdReached(int sensorValue, int granularity) { //frequency, time
  int feedbackPosition = sensorValue / granularity;
  Serial.print("Value: ");
  Serial.print(sensorValue);
  Serial.print(", Granularity: " );
  Serial.print(granularity);
  Serial.print(", currentPositon: " );
  Serial.println(feedbackPosition);
  if (currentStep != feedbackPosition) {
    currentStep = feedbackPosition;
    return true;
  } else {
    return false;
  }

}
