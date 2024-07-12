#include <SPI.h>

// Editable variables
int scan_amount = 40;                    // Number of readings to average for distance measurement
String file_path = "/scan_001.txt";      // Path to save the file
int z_axis_height = 7;                  // Maximum height of the scanned file in cm.
int step_delay = 3000;                   // Delay for each step of the stepper motor in microseconds.
float z_layer_height = 0.5;              // Layer height in mm.
int lead_screw_rotations_per_cm = 2;     // Number of rotations needed for the lead screw to move 1 cm.
int steps_per_rotation_for_motor = 200;  // Steps that the motor needs for a full rotation.
int distance_to_center = 8;              // Distance from the sensor to the center of the object

// Pin Definitions
int button = 14;
int limit_switch = 10;
int dir_r = 2;
int step_r = 15;
int enable_r = 4;
int dir_z = 32;
int step_z = 21;
int enable_z = 22;
int sensor_pin = 27;

// Variables
bool scan = false;
bool scan_changed = false;
float distance = 0.0;
float angle = 0.0;
float x = 0.0;
float y = 0.0;
float z = 0.0;
int z_loop = 0;
int r_loop = 0;
float measured_analog = 0.0;
float analog = 0.0;
float RADIANS = 0.0;
int steps_z_height = 0;
bool homed = false;

void setup() {
  Serial.begin(115200);
  pinMode(sensor_pin, INPUT);
  pinMode(limit_switch, INPUT);
  pinMode(button, INPUT);
  pinMode(dir_z, OUTPUT);
  pinMode(step_z, OUTPUT);
  pinMode(enable_z, OUTPUT);
  pinMode(dir_r, OUTPUT);
  pinMode(step_r, OUTPUT);
  pinMode(enable_r, OUTPUT);
  digitalWrite(enable_z, HIGH); // Disable the z_axis driver
  digitalWrite(enable_r, HIGH); // Disable the turntable driver

  RADIANS = (3.141592 / 180.0) * (360 / steps_per_rotation_for_motor);
  steps_z_height = (z_layer_height * steps_per_rotation_for_motor * lead_screw_rotations_per_cm) / 10;
}

void loop() {
  // Wait till the push button is pressed
  if (digitalRead(button)) {
    if (scan && !scan_changed) {
      scan = false;
      delay(3000);
      scan_changed = true;
      Serial.println("Scan Stopped"); // Enviar señal de detener el escaneo
    }
    if (!scan && !scan_changed) {
      scan = true;
      delay(3000);
      scan_changed = true;
    }
    scan_changed = false;
  }

  // If the scanning process is ON
  if (scan) {
    // We stop when we reach the maximum height
    if (z < z_axis_height) {
      for (int loop_cont = 0; loop_cont < steps_per_rotation_for_motor; loop_cont++) {
        getDistance();
        digitalWrite(enable_r, LOW);   // Enable the turntable driver
        digitalWrite(dir_r, LOW);      // Turntable spin to right
        digitalWrite(step_r, HIGH);    // Make a step
        delayMicroseconds(step_delay);
        digitalWrite(step_r, LOW);
        delayMicroseconds(step_delay);
        angle += RADIANS; // Increase the angle by one more unit
        sendToSerial(x, y, z); // Send x, y, z to serial
      }
      angle = 0; // Reset the angle value for next rotation

      while (z_loop < steps_z_height) {
        digitalWrite(enable_z, LOW);   // Enable the z_axis driver
        digitalWrite(dir_z, HIGH);      // z_axis spin to right
        digitalWrite(step_z, HIGH);    // z_axis make a step
        delayMicroseconds(step_delay);
        digitalWrite(step_z, LOW);
        delayMicroseconds(step_delay);
        z_loop++; // Increase the loop by 1
      }
      z += z_layer_height; // Increase the made z-height by 1 unit
      z_loop = 0; // Reset the z-axis rotation variable
    } 
    else {
      // We finished the scan, stop the drivers
      digitalWrite(enable_z, HIGH);
      digitalWrite(enable_r, HIGH);
      Serial.println("Scan Complete");
      scan = false; // Stop scanning
    }
  }
}

// Function that gets the distance from sensor
void getDistance() {
  for (int aa = 0; aa < scan_amount; aa++) {
    measured_analog = analogRead(sensor_pin);
    delay(2);
    analog += measured_analog;
  }
  distance = analog / scan_amount; // Get the mean
  analog = 0; // Reset analog read total value
  measured_analog = 0; // Reset analog read value
  distance = mapFloat(distance, 0.0, 1023.0, 0.0, 3.3); // Convert analog pin reading to voltage
  distance = -5.40274 * pow(distance, 3) + 28.4823 * pow(distance, 2) - 49.7115 * distance + 31.3444; // From datasheet
  distance = distance_to_center - distance; // The distance d = distance from sensor to center - measured distance
  y = cos(angle) * distance;
  x = sin(angle) * distance;

}

// Function to send coordinates to serial
void sendToSerial(float x, float y, float z) {
  Serial.printf("%f,%f,%f\n", x, y, z);
}

// Function that maps the value in a float format
float mapFloat(float fval, float val_in_min, float val_in_max, float val_out_min, float val_out_max) {
  return (fval - val_in_min) * (val_out_max - val_out_min) / (val_in_max - val_in_min) + val_out_min;
}
