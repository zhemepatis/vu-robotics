#define GAS_SENSOR_PIN 0

#define MOTOR_PIN 2
#define BUZZER_PIN 4
#define BTN_PIN 7

#define DEBOUNCE_DELAY 20 // ms

#define GAS_THRESHOLD 100 // ?

long lastDebounceTime = 0;
int lastBtnState = HIGH;
int btnState = HIGH;

bool ventilationIsOn = false;

void setup()
{
	Serial.begin(9600);
  	
  	pinMode(MOTOR_PIN, OUTPUT);
  	pinMode(BUZZER_PIN, OUTPUT);
  	pinMode(BTN_PIN, INPUT_PULLUP);	
}

void loop()
{
  	int btnInput = digitalRead(BTN_PIN);
	int gasInput = analogRead(GAS_SENSOR_PIN);
  	
  	if (btnInput != lastBtnState)
    {
        lastDebounceTime = millis();
    }

    if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY && btnInput != btnState)
    {
        btnState = btnInput;
        
        if (btnState == LOW)
        {
            deactivateAlarm();
        }
    }

    if (!ventilationIsOn && gasInput >= GAS_THRESHOLD)
    {
    	activateVentilation();
     	activateAlarm();
    }
    else if (ventilationIsOn && gasInput < GAS_THRESHOLD)
    {
        deactivateVentilation();
    }

    lastBtnState = btnInput;
}

void activateVentilation()
{
	digitalWrite(MOTOR_PIN, HIGH);
    ventilationIsOn = true;
}

void activateAlarm()
{
	tone(BUZZER_PIN, 330);
}

void deactivateVentilation()
{
	digitalWrite(MOTOR_PIN, LOW);
    ventilationIsOn = false;
}

void deactivateAlarm()
{
	noTone(BUZZER_PIN);
}