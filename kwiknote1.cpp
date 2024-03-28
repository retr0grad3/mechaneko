void runGame(){
    setTime(01,01,00,9,9,1999);
    digitalWrite(servoPower, HIGH);

    while(second() < timelimit && year() == 1999){
        if(digitalRead(joystickFwd) == LOW){
            digitalWrite(motor3Out1, HIGH); // MOTOR 1 FORWARD ON
            digitalWrite(motor3Out2, LOW); // REVERSE OFF
            digitalWrite(motor3Speed, 255); // SPEED MAX
            digitalWrite(motor4Out1, LOW); // MOTOR 2 FORWARD OFF (must be opposite)
            digitalWrite(motor4Out2, HIGH); // REVERSE OFF
            digitalWrite(motor4Speed, 255); // SPEED MAX
            Serial.println("DOWN");

        } else if(digitalRead(joystickBck) == LOW){
            digitalWrite(motor3Out1, LOW); // MOTOR 1 FORWARD OFF
            digitalWrite(motor3Out2, HIGH); // REVERSE ON
            digitalWrite(motor3Speed, 255); // SPEED MAX
            digitalWrite(motor4Out1, HIGH); // MOTOR 2 FORWARD ON
            digitalWrite(motor4Out2, LOW); // REVERSE OFF
            digitalWrite(motor4Speed, 255); // SPEED MAX
            Serial.println("UP");

        } else if(digitalRead(joystickLeft) == LOW){
            digitalWrite(motor2Out1, LOW); // MOTOR 1 FORWARD OFF
            digitalWrite(motor2Out2, HIGH); // REVERSE ON
            digitalWrite(motor2Speed, 255); // SPEED MAX
            Serial.println("LEFT");

        } else if(digitalRead(joystickRight) == LOW){
            digitalWrite(motor2Out1, HIGH); // MOTOR 1 FORWARD OFF
            digitalWrite(motor2Out2, LOW); // REVERSE ON
            digitalWrite(motor2Speed, 255); // SPEED MAX
            Serial.println("RIGHT");

        } else if(digitalRead(joystickFwd) == LOW && digitalRead(joystickLeft) == LOW){
            digitalWrite(motor3Out1, HIGH); // MOTOR 1 FORWARD ON
            digitalWrite(motor3Out2, LOW); // REVERSE OFF
            digitalWrite(motor3Speed, 255); // SPEED MAX
            digitalWrite(motor4Out1, LOW); // MOTOR 2 FORWARD OFF (must be opposite)
            digitalWrite(motor4Out2, HIGH); // REVERSE OFF
            digitalWrite(motor4Speed, 255); // SPEED MAX

            digitalWrite(motor2Out1, LOW); // MOTOR 1 FORWARD OFF
            digitalWrite(motor2Out2, HIGH); // REVERSE ON
            digitalWrite(motor2Speed, 255); // SPEED MAX
            Serial.println("UP LEFT");

        } else if(digitalRead(joystickFwd) == LOW && digitalRead(joystickRight) == LOW){
            digitalWrite(motor3Out1, HIGH); // MOTOR 1 FORWARD ON
            digitalWrite(motor3Out2, LOW); // REVERSE OFF
            digitalWrite(motor3Speed, 255); // SPEED MAX
            digitalWrite(motor4Out1, LOW); // MOTOR 2 FORWARD OFF (must be opposite)
            digitalWrite(motor4Out2, HIGH); // REVERSE OFF
            digitalWrite(motor4Speed, 255); // SPEED MAX

            digitalWrite(motor2Out1, HIGH); // MOTOR 1 FORWARD OFF
            digitalWrite(motor2Out2, LOW); // REVERSE ON
            digitalWrite(motor2Speed, 255); // SPEED MAX
            Serial.println("UP RIGHT");

        } else if(digitalRead(joystickBck) == LOW && digitalRead(joystickLeft) == LOW){
            digitalWrite(motor3Out1, LOW); // MOTOR 1 FORWARD OFF
            digitalWrite(motor3Out2, HIGH); // REVERSE ON
            digitalWrite(motor3Speed, 255); // SPEED MAX
            digitalWrite(motor4Out1, HIGH); // MOTOR 2 FORWARD ON
            digitalWrite(motor4Out2, LOW); // REVERSE OFF
            digitalWrite(motor4Speed, 255); // SPEED MAX

            digitalWrite(motor2Out1, LOW); // MOTOR 1 FORWARD OFF
            digitalWrite(motor2Out2, HIGH); // REVERSE ON
            digitalWrite(motor2Speed, 255); // SPEED MAX
            Serial.println("UP LEFT");

        } else if(digitalRead(joystickBck) == LOW && digitalRead(joystickRight) == LOW){
            digitalWrite(motor3Out1, LOW); // MOTOR 1 FORWARD OFF
            digitalWrite(motor3Out2, HIGH); // REVERSE ON
            digitalWrite(motor3Speed, 255); // SPEED MAX
            digitalWrite(motor4Out1, HIGH); // MOTOR 2 FORWARD ON
            digitalWrite(motor4Out2, LOW); // REVERSE OFF
            digitalWrite(motor4Speed, 255); // SPEED MAX

            digitalWrite(motor2Out1, HIGH); // MOTOR 1 FORWARD OFF
            digitalWrite(motor2Out2, LOW); // REVERSE ON
            digitalWrite(motor2Speed, 255); // SPEED MAX
            Serial.println("UP RIGHT");

        } else {
            digitalWrite(motor2Out1, LOW); // MOTOR 1/X FORWARD OFF
            digitalWrite(motor2Out2, LOW); // REVERSE OFF
            digitalWrite(motor2Speed, 0); // SPEED MIN

            digitalWrite(motor3Out1, LOW); // MOTOR 2/Y FORWARD OFF
            digitalWrite(motor3Out2, LOW); // REVERSE OFF
            digitalWrite(motor3Speed, 0); // SPEED MIN

            digitalWrite(motor4Out1, LOW); // MOTOR 2/Y FORWARD OFF
            digitalWrite(motor4Out2, LOW); // REVERSE OFF
            digitalWrite(motor4Speed, 0); // SPEED MIN

            Serial.println("CENTER");
            delay(100);

        }
    }
}