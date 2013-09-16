/*luminaria
  =========
  A battery operated luminaria powered by the ATTiny25

  This work is licensed by Peter Riddell under a Creative
  Commons Attribution-ShareAlike 3.0 Unported License:
  http://creativecommons.org/licenses/by-sa/3.0/
  */

#define FLICKER_LED_PIN 0

// the start of the flicker (low)
static int flicker_low_min = 200;
static int flicker_low_max = 240;
 
// the end value of the flicker (high)
static int flicker_high_min = 230;
static int flicker_high_max = 256;
 
// delay between each low-high-low cycle
// low->high |flicker_hold| high->low
static int flicker_hold_min = 40; // milliseconds
static int flicker_hold_max = 80; // milliseconds
 
// delay after each low-high-low cycle
// low->high->low |flicker_pause| low->high...
static int flicker_pause_min = 100; // milliseconds
static int flicker_pause_max = 200;  // milliseconds
 
// delay low to high and high to low cycle
static int flicker_speed_min = 900; // microseconds
static int flicker_speed_max = 1000; // microseconds
 
// define ouput pin for LED and set pullup resistors on unused
// pins to reduce power consumption
void setup() {
  pinMode(FLICKER_LED_PIN, OUTPUT);
  pinMode(1,INPUT_PULLUP); // unused pin set to high
  pinMode(2,INPUT_PULLUP); // unused pin set to high
  pinMode(3,INPUT_PULLUP); // unused pin set to high
  pinMode(4,INPUT_PULLUP); // unused pin set to high
}
 
int flicker_random_low_start = 0;
int flicker_random_low_end = 0;
int flicker_random_high = 0;
int flicker_random_speed_start = 0;
int flicker_random_speed_end = 0;
 
void loop() {
   
  // random time for low
  flicker_random_low_start = random(flicker_low_min, flicker_low_max);
  flicker_random_low_end = random(flicker_low_min, flicker_low_max);
   
  // random time for high
  flicker_random_high = random(flicker_high_min, flicker_high_max);
   
  // random time for speed
  flicker_random_speed_start = random(flicker_speed_min, flicker_speed_max);
  flicker_random_speed_end = random(flicker_speed_min, flicker_speed_max);
   
  // low -> high
  for (int i = flicker_random_low_start; i<flicker_random_high; i++) {
    analogWrite(FLICKER_LED_PIN, i);
    delayMicroseconds(flicker_random_speed_start);
  }
   
  // hold
  delay(random(flicker_hold_min, flicker_hold_max));
   
  // high -> low
  for (int i = flicker_random_high; i>=flicker_random_low_end; i--) {
    analogWrite(FLICKER_LED_PIN, i);
    delayMicroseconds(flicker_random_speed_end);
  }
   
  // pause
  delay(random(flicker_pause_min, flicker_pause_max));
}
