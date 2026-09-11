/*
  Two-Relay Serial Control
  -------------------------
  Reads commands from the Serial Monitor and switches two relays ON/OFF.

  Commands (type in Serial Monitor, line ending = "Newline"):
    1 ON   -> turn relay 1 ON
    1 OFF  -> turn relay 1 OFF
    2 ON   -> turn relay 2 ON
    2 OFF  -> turn relay 2 OFF
    ALL ON  -> turn both relays ON
    ALL OFF -> turn both relays OFF
    STATUS  -> print current relay states

  Note: Most relay modules are ACTIVE LOW (LOW = relay energized/ON).
  Set ACTIVE_LOW to false below if your module is active-high.
*/

const int RELAY1_PIN = D1;
const int RELAY2_PIN = D2;
const bool ACTIVE_LOW = true;   // change to false if your relay board is active-high

bool relay1State = false;  // false = OFF, true = ON
bool relay2State = false;

void handleCommand(String cmd);
void setRelay(int relayNumber, bool turnOn);
void printStatus();

void setup() {
  Serial.begin(115200);
  delay(10);
  
  pinMode(RELAY1_PIN, OUTPUT);
  pinMode(RELAY2_PIN, OUTPUT);

  setRelay(1, false);
  setRelay(2, false);

  Serial.println(F("Relay control ready."));
  Serial.println(F("Commands: 1 ON | 1 OFF | 2 ON | 2 OFF | ALL ON | ALL OFF | STATUS"));
}

void loop() {
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    command.trim();
    command.toUpperCase();
    handleCommand(command);
  }
}

void handleCommand(String cmd) {
  if (cmd == "1 ON") {
    setRelay(1, true);
  } else if (cmd == "1 OFF") {
    setRelay(1, false);
  } else if (cmd == "2 ON") {
    setRelay(2, true);
  } else if (cmd == "2 OFF") {
    setRelay(2, false);
  } else if (cmd == "ALL ON") {
    setRelay(1, true);
    setRelay(2, true);
  } else if (cmd == "ALL OFF") {
    setRelay(1, false);
    setRelay(2, false);
  } else if (cmd == "STATUS") {
    printStatus();
  } else if (cmd.length() > 0) {
    Serial.print(F("Unknown command: "));
    Serial.println(cmd);
  }
}

void setRelay(int relayNumber, bool turnOn) {
  int pin = (relayNumber == 1) ? RELAY1_PIN : RELAY2_PIN;

  // Active-low modules need LOW to energize, active-high need HIGH
  int outputLevel;
  if (ACTIVE_LOW) {
    outputLevel = turnOn ? LOW : HIGH;
  } else {
    outputLevel = turnOn ? HIGH : LOW;
  }
  digitalWrite(pin, outputLevel);

  if (relayNumber == 1) {
    relay1State = turnOn;
  } else {
    relay2State = turnOn;
  }

  Serial.print(F("Relay "));
  Serial.print(relayNumber);
  Serial.println(turnOn ? F(": ON") : F(": OFF"));
}

void printStatus() {
  Serial.print(F("Relay 1: "));
  Serial.println(relay1State ? F("ON") : F("OFF"));
  Serial.print(F("Relay 2: "));
  Serial.println(relay2State ? F("ON") : F("OFF"));
}
