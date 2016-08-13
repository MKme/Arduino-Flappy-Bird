#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include "pitches.h"

#define melodyPin 8
int melody[] = {
	NOTE_E7, NOTE_E7, 0, NOTE_E7, 
	0, NOTE_C7, NOTE_E7, 0,
	NOTE_G7, 0, 0,  0,
	NOTE_G6, 0, 0, 0, 

	NOTE_C7, 0, 0, NOTE_G6, 
	0, 0, NOTE_E6, 0, 
	0, NOTE_A6, 0, NOTE_B6, 
	0, NOTE_AS6, NOTE_A6, 0, 

	NOTE_G6, NOTE_E7, NOTE_G7, 
	NOTE_A7, 0, NOTE_F7, NOTE_G7, 
	0, NOTE_E7, 0,NOTE_C7, 
	NOTE_D7, NOTE_B6, 0, 0,

	NOTE_C7, 0, 0, NOTE_G6, 
	0, 0, NOTE_E6, 0, 
	0, NOTE_A6, 0, NOTE_B6, 
	0, NOTE_AS6, NOTE_A6, 0, 

	NOTE_G6, NOTE_E7, NOTE_G7, 
	NOTE_A7, 0, NOTE_F7, NOTE_G7, 
	0, NOTE_E7, 0,NOTE_C7, 
	NOTE_D7, NOTE_B6, 0, 0
};

//Mario main them tempo
int tempo[] = {
	12, 12, 12, 12, 
	12, 12, 12, 12,
	12, 12, 12, 12,
	12, 12, 12, 12, 

	12, 12, 12, 12,
	12, 12, 12, 12, 
	12, 12, 12, 12, 
	12, 12, 12, 12, 

	9, 9, 9,
	12, 12, 12, 12,
	12, 12, 12, 12,
	12, 12, 12, 12,

	12, 12, 12, 12,
	12, 12, 12, 12,
	12, 12, 12, 12,
	12, 12, 12, 12,

	9, 9, 9,
	12, 12, 12, 12,
	12, 12, 12, 12,
	12, 12, 12, 12,
};

// pin 7 - Serial clock out (SCLK)
// pin 6 - Serial data out (DIN)
// pin 5 - Data/Command select (D/C)
// pin 4 - LCD chip select (CS)
// pin 3 - LCD reset (RST)
  
Adafruit_PCD8544 display = Adafruit_PCD8544(7, 6, 5, 4, 3);

static unsigned char PROGMEM splash[] = {
B00000000,B10000000,B00000011,B11000111,B10000000,B00000000,B00000011,B11100000,B00000011,B11100111,
B11000000,B00000000,B00000111,B11100000,B00000111,B11111111,B11100000,B00000000,B00000111,B11100000,
B00000111,B11111111,B11100000,B00000000,B00000100,B01100000,B00000111,B11111111,B11100000,B00000000,
B00000100,B01100000,B00000111,B11111111,B11110000,B00000000,B00000110,B01100000,B00000111,B11111111,
B11110000,B00000000,B11111110,B01100000,B11001111,B11111111,B11110000,B00000000,B11111110,B00111111,
B11111111,B11111111,B11110011,B11000000,B11000110,B00111000,B00011111,B11111111,B11111111,B11000000,
B11000110,B00110000,B00001100,B00011000,B00110011,B00100000,B11001110,B00110001,B10001100,B00011000,
B00110011,B00110000,B10000110,B00111110,B00001100,B10011001,B00110001,B00110000,B10000110,B00111000,
B00001100,B10011001,B00111000,B00110000,B11001111,B00110001,B10001100,B10011001,B00111000,B00110000,
B11001111,B00110001,B10001100,B10011001,B00111000,B00110000,B11001111,B00110000,B00001100,B00011000,
B00111000,B01110000,B11001111,B00110000,B00001100,B00011000,B00111100,B01110000,B11001111,B00111111,
B11111100,B11111001,B11111110,B01110000,B11001111,B00111111,B11111100,B11111001,B11111110,B01110000,
B11001111,B11111111,B11111100,B11111001,B11111110,B01100000,B11001111,B11011100,B00001111,B11111111,
B11111100,B11100000,B01001111,B00000000,B01111111,B11101111,B11011101,B00000000,B01111100,B00000000,
B00000001,B11000011,B10011110,B00000000,B00111000,B00000000,B00000000,B00000000,B00000000,B00000000,
B00001000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B11000000,B00000000,B00000111,
B11100000,B00000000,B00000001,B11100011,B10000000,B00000111,B11110000,B00000000,B00000001,B11100111,
B10000000,B00001111,B11111000,B00000000,B00000011,B11110111,B11000000,B00001111,B11111000,B00000000,
B00000011,B01110111,B11001111,B11111111,B11111000,B00000000,B00000010,B01111011,B11111111,B11111111,
B11111000,B00000000,B00000010,B01111111,B11110001,B00011111,B11111000,B00000000,B00000010,B01111111,
B11110000,B00011111,B10001000,B00000000,B00000010,B00111110,B01110000,B01111111,B10001000,B00000000,
B00000011,B00001110,B00110000,B11111111,B10001000,B00000000,B00000001,B00000111,B11110000,B11111000,
B00001000,B00000000,B00000001,B00100110,B00110000,B11110000,B00001000,B00000000,B00000001,B00100010,
B00110000,B11110001,B00001000,B00000000,B00000001,B00100010,B00110000,B11110011,B10001000,B00000000,
B00000001,B00100010,B00111000,B11110011,B10001000,B00000000,B00000001,B00100010,B00111000,B11110011,
B00001000,B00000000,B00000001,B00100110,B00111111,B11110000,B00001000,B00000000,B00000001,B00000110,
B00111111,B11111000,B00001000,B00000000,B00000001,B11111110,B01111111,B11111111,B11110000,B00000000,
B00000000,B00000011,B11111111,B11111111,B11100000,B00000000,B00000000,B00000011,B11111111,B11100000,
B00000000,B00000000,B00000000,B00000000,B11001111,B11100000,B00000000,B00000000};  

static unsigned char PROGMEM bullet[] = {
B00000000,
B01011011,
B10111111,
B11111011,
B11111111,
B11111111,
B01111011,
B00000000};

static unsigned char PROGMEM bird[6][8] = {
{ B11000000, 
  B10100000,
  B10011100,
  B10001010,
  B10000111,
  B11000110,
  B01000100,
  B00111000
  },
  
{ B00000000, 
  B00000000,
  B11111100,
  B10001010,
  B11100111,
  B10000110,
  B11000100,
  B00111000
  },
  
{ B00000000, 
  B00000000,
  B00111100,
  B01001010,
  B10010111,
  B10100110,
  B11000100,
  B00111000
  },
  
{ B00011111, 
  B00101011,
  B00100111,
  B01010001,
  B10001010,
  B11001010,
  B01101100,
  B00011000
  },
  
{ B00110000, 
  B01101000,
  B01000110,
  B10001001,
  B11110011,
  B01000101,
  B00110111,
  B00001111,
  },
  
{ B00011111, 
  B00010101,
  B00100101,
  B00100001,
  B00100011,
  B00011101,
  B00001110,
  B00000100
  }
};

unsigned long clock = 0;
unsigned long timerDelay = 0;
unsigned long fallTimer = 0;

int score = 0;

int highScore = 0;

int buttonState = 0;
boolean buttonActive = true;
int boost = 0;
int height = 10;
int fallSpeed = 0;
 
int flap[] = {0,2,3,3,2,1,1};

int sewer1 = 84;
int sewer2 = 126;
int sewerSpeed = 2;

int gap1 = 7;
int gap2 = 14;

int hills[84]; 
int hillSlope = 1;
int hillTop = 26;
int shade = 0;

int song = 0;

void sing(int s){ // ---------------------------------------------------------------------------------------- THEME SONG      

	song = s;

	int size = sizeof(melody) / sizeof(int);
	for (int thisNote = 0; thisNote < size; thisNote++) {
		int noteDuration = 1000/tempo[thisNote];
		buzz(melodyPin, melody[thisNote],noteDuration);
		int pauseBetweenNotes = noteDuration * .4;
		delay(pauseBetweenNotes);
		buttonState = digitalRead(2);
		buzz(melodyPin, 0,noteDuration);
		display.clearDisplay();     
		background();
		display.fillRect(24, 30, 29, 14, WHITE);
		display.drawBitmap(17, 0, splash, 48, 48, 1);
		display.display();
		buttonState = digitalRead(2);
		if(buttonState == LOW){break;}
	}
}

void buzz(int targetPin, long frequency, long length) {
	long delayValue = 1000000/frequency/2; 
	long numCycles = frequency * length/ 1000; 
	for (long i=0; i < numCycles; i++){ 
		digitalWrite(targetPin,HIGH); 
		delayMicroseconds(delayValue);
		digitalWrite(targetPin,LOW);
		delayMicroseconds(delayValue);
	}
}

void background(){ // ----------------------------------------------------------------------------------------- BACKGROUND
  
	display.fillRect(0, 46, 83, 2, BLACK); 

	if(hills[83] < hillTop){hillSlope = 0; hillTop = random(20, 40);}
	if(hills[83] > 45){hillSlope = 1;}
	if(hillSlope == 1){hills[83] = hills[83] - 1;}
	if(hillSlope == 0){hills[83] = hills[83] + 1;}

	//if (hills[83] % 2 == 0){shade = 1;}
	//else {shade = 0;}

	for (int i = 0; i < 83; i = i++) {                            
		hills[i] = hills[i+1]; 
		display.drawPixel(i+1, hills[i], BLACK);
		display.drawFastVLine(i+1, hills[i], 3, BLACK);
		//display.drawLine(i+1, hills[i], (i+1) * 2, hills[i] + ((i+1) * 2), BLACK);}
			
			if (i % 2 == 0){
			  display.drawLine(i+1, hills[i], (i+1) * 2, hills[i] + ((i+1) * 2), BLACK);}
			  //display.drawFastVLine(i+1, hills[i], -(hills[i]), BLACK); }  
	}
}  


int bullet1 = 3;
int bullet2 = 36;
int bulletTravel1 = 150;
int bulletTravel2 = 250;



void bullets() { // ---------------------------------------------------------------------------------------------- BULLETS

	if (bulletTravel1 < 0){
		bulletTravel1 = 150;
		bullet1 = random(1, 6);
	}
	if (bulletTravel2 < 0){
		bulletTravel2 = 150;
		bullet2 = random(35, 39);
	}

	bulletTravel1 = bulletTravel1 - 4;
	bulletTravel2 = bulletTravel2 - 4;

	if (bulletTravel1 >= 84 && bulletTravel1 <= 88){for(int i = 300; i < 450; i++){tone(8, i, 100);}}
	if (bulletTravel2 >= 84 && bulletTravel2 <= 88){for(int i = 300; i < 450; i++){tone(8, i, 100);}}

	display.drawBitmap(bulletTravel1, bullet1, bullet, 8, 8, 1);
	display.drawBitmap(bulletTravel2, bullet2, bullet, 8, 8, 1);
}

void sewers() { // ---------------------------------------------------------------------------------------------- SEWERS

	if (sewer1 < 0){
		sewer1 = 84;
		gap1 = random(5, 20);
	}
	if (sewer2 < 0){
		sewer2 = 84;
		gap2 = random(5, 20);
	}

	if(score == 4){sewerSpeed = 3;}

	sewer1 = sewer1 - sewerSpeed;
	sewer2 = sewer2 - sewerSpeed;

	display.fillRect(sewer1 - 1, 0, 8, gap1 - 4, WHITE);         // Top Tube
	display.fillRect(sewer1 - 2, gap1 - 4, 10, 4, WHITE);        // Top Cap

	display.fillRect(sewer1 - 2, gap1 + 20, 10, 4, WHITE);       // Bottom Cap
	display.fillRect(sewer1 - 1, gap1 + 24, 8, 20, WHITE);       // Bottom Tube

	display.fillRect(sewer2 - 1, 0, 8, gap2 - 4, WHITE);         // Top Tube
	display.fillRect(sewer2 - 2, gap2 - 4, 10, 4, WHITE);        // Top Cap

	display.fillRect(sewer2 - 2, gap2 + 20, 10, 4, WHITE);       // Bottom Cap
	display.fillRect(sewer2 - 1, gap2 + 24, 8, 20, WHITE);       // Bottom Tube  

	display.drawRect(sewer1 - 1, 0, 8, gap1 - 4, BLACK);         // Top Tube
	display.drawRect(sewer1 - 2, gap1 - 4, 10, 4, BLACK);        // Top Cap

	display.drawRect(sewer1 - 2, gap1 + 20, 10, 4, BLACK);       // Bottom Cap
	display.drawRect(sewer1 - 1, gap1 + 24, 8, 20, BLACK);       // Bottom Tube

	display.drawRect(sewer2 - 1, 0, 8, gap2 - 4, BLACK);         // Top Tube
	display.drawRect(sewer2 - 2, gap2 - 4, 10, 4, BLACK);        // Top Cap

	display.drawRect(sewer2 - 2, gap2 + 20, 10, 4, BLACK);       // Bottom Cap
	display.drawRect(sewer2 - 1, gap2 + 24, 8, 20, BLACK);       // Bottom Tube  
}
  
void scores() { // --------------------------------------------------------------------------------------------- SCORES
	if(sewer1 <= 11 && sewer1 >= 9 || sewer2 <= 11 && sewer2 >= 9){
		score++;
		for(int i = 1500; i > 1000; i--){tone(8, i, 50);}
	}
	display.setCursor(71,0);
	display.fillRect(70, 0, 9, 9, WHITE); 
	display.println(score);
  }

void collision() { // ------------------------------------------------------------------------------------------ COLLISION
	if(height + 1 < gap1 && sewer1 <= 26 && sewer1 >= 14){died();}
	if(height + 8 > gap1+20 && sewer1 <= 26 && sewer1 >= 14){died();}
	if(height + 1 < gap2 && sewer2 <= 26 && sewer2 >= 14){died();}
	if(height + 8 > gap2+20 && sewer2 <= 26 && sewer2 >= 14){died();}

	if(height < bullet1 + 6 && bulletTravel1 <= 26 && bulletTravel1 >= 14){died();}
	if(height > bullet2 && bulletTravel2 <= 26 && bulletTravel2 >= 14){died();}

	if(height + 8 > 39){died();}
  }

void died() { // ----------------------------------------------------------------------------------------------- DIED

	buttonActive = false;
	tone(8, 500, 100);
	delay(200);
	tone(8, 500, 100);
	delay(100);
	tone(8, 300, 500);
  
	if(score > highScore){highScore = score;}
	while(height < 39){
		clock = millis();
		fallSpeed = ((clock - fallTimer) / 200) + 1; 
		height = height + fallSpeed;
		display.clearDisplay();   
		background();
		sewers(); 
		bullets();  
		display.fillCircle(23, height + 4, 3, WHITE);    
		if (fallSpeed > 2){display.drawBitmap(18, height, bird[5], 8, 8, 1);}
		else if (fallSpeed > 1){display.drawBitmap(18, height, bird[4], 8, 8, 1);}
		else {display.drawBitmap(18, height, bird[1], 8, 8, 1);}       
		scores();
		display.display();
		delay(100);  
	}
	display.fillRect(13, 7, 56, 32, WHITE);
	display.drawRect(14, 8, 54, 30, BLACK); 
	display.setCursor(25,11);
	display.println("SCORE");
	display.setCursor(27,21);
	display.setTextSize(2);
	display.println(score);
	display.setTextSize(1);
	display.display();
	buttonState = digitalRead(2);
	while(buttonState == HIGH){
		buttonState = digitalRead(2);
		delay(40);
	}
	score = 0;
	buttonActive = true;
	sewer1 = 84;
	sewer2 = 126;
	sewerSpeed = 2;
	bulletTravel1 = 150;
	bulletTravel2 = 250;
	bullet1 = random(1, 4);
	bullet2 = random(35, 39);
	boost = 0;
	height = 10;
	fallSpeed = 0;
	clock = millis();
	fallTimer = clock;
}

void gamePlay(){// -------------------------------------------------------------------------------------------- GAMEPLAY

	int flapHeight[] = {height,height,height - 5,height - 7,height - 9,height - 7,height - 6};
	buttonState = digitalRead(2);

	if(buttonState == LOW && buttonActive == true){
		for(int i = 900; i < 1400; i++){tone(8, i, 20);}
		for(int x = 0; x < 7; x = x++){ 
			display.clearDisplay();
			background();
			sewers();
			bullets();
			display.fillCircle(23, (flapHeight[x] - boost) + 4, 3, WHITE);
			display.drawBitmap(18, flapHeight[x] - boost, bird[flap[x]], 8, 8, 1);
			scores();
			display.display();
			buttonState = digitalRead(2);
			delay(50);
			buttonState = digitalRead(2);
			delay(50);
			buttonState = digitalRead(2);
			height = flapHeight[x] - boost;
			collision();
			if (x > 2) {
				if(buttonState == LOW && buttonActive == true){x = 0;boost = boost + 7;for(int i = 900; i < 1400; i++){tone(8, i, 20);}}
			}
		}
		height = flapHeight[5] - boost;
		clock = millis();
		fallTimer = clock;
		boost = 0;
	}

	else{ 
		fallSpeed = ((clock - fallTimer) / 400) + 1;
		if (fallSpeed > 3) {fallSpeed = 3;}
		height = height + fallSpeed;

		if (height > 39){height = 39;}
		display.clearDisplay();

		background();
		sewers();
		bullets();

		display.fillCircle(23, height + 4, 3, WHITE);

		if (fallSpeed > 2){display.drawBitmap(18, height, bird[5], 8, 8, 1);}
		else if (fallSpeed > 1){display.drawBitmap(18, height, bird[4], 8, 8, 1);}
		else {display.drawBitmap(18, height, bird[1], 8, 8, 1);}
		   
		scores();

		display.display();
		delay(100);
		collision();
	}    
}
// ----------------------------------------- SETUP ----------------------------------------- 

void setup() {    
	display.clearDisplay();
	pinMode(2, INPUT_PULLUP);
	pinMode(8, OUTPUT);
analogWrite(11,220);// PWM of LCD backlight but ebay unit is backwards- 
  //must go high + cycle to dim 
  //Very Dim=230
	display.begin();
	display.setContrast(40);
	display.setTextSize(1);

	for (int i = 0; i < 83; i = i++) {hills[i] = 47;}
	hills[83] = 47;

	while(hills[0] > 30){background();}

	buttonState = digitalRead(2); 
	while(buttonState == HIGH){
	sing(1);   
	}
}

// --------------------------------------- MAIN LOOP --------------------------------------- 

void loop() {
	clock = millis();
	gamePlay();
}
