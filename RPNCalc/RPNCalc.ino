#include <LiquidCrystal.h>

const int css = 53;

const int rs = 22, en = 23, d4 = 25, d5 = 24, d6 = 27, d7 = 26;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


#define lcdbl 8  //backlight pantalla

#define kr1 39 //     ----[1]-[2]-[3] 
#define kr2 41 //     ----[4]-[5]-[6]
#define kr3 34 //     ----[7]-[8]-[9]
#define kr4 35 //     ----[*]-[0]-[#] 
#define kc1 36 //     -----+   |   |
#define kc2 38 //     ---------+   | 
#define kc3 37 //     -------------+ 

#define men 40  //-[*]
#define men2 42 //--+
#define buzzer 10 //buzzer

#define gpa 3
#define gpb 2

int op=0;
int c=0;
int index=0; 
int menu=00;  //index menu
int dur=50;  //key debounce time
int tecdel=50;  //delay entre deteccion de teclas
int keyp;
int lcdbl_offtime=50000;
int before=0;
int dill=100;  //delay seleccion
int ant=0; // bufer
int dis;
int buff=0; 
int RECV_PIN = 7;
int ok;
int qq;
int pos;

unsigned long x;
unsigned long y;

String ox;
String oy;

void setup() {
Serial.begin(9600);   
pinMode(gpa, OUTPUT);
pinMode(kr1, OUTPUT);
pinMode(kr2, OUTPUT);
pinMode(kr3, OUTPUT);
pinMode(kr4, OUTPUT);
pinMode(kc1, INPUT_PULLUP);
pinMode(kc2, INPUT_PULLUP);
pinMode(kc3, INPUT_PULLUP);
pinMode(men, OUTPUT);
pinMode(men2, INPUT_PULLUP);
pinMode(buzzer, OUTPUT);
pinMode(lcdbl, OUTPUT);                         //backlight pantalla
Serial.begin(9600);                             //iniciar serial
digitalWrite(lcdbl, HIGH);  //encender backlight
digitalWrite(buzzer, LOW);
digitalWrite(men, LOW);
digitalWrite(kr1, HIGH);
digitalWrite(kr2, HIGH);
digitalWrite(kr3, HIGH);
digitalWrite(kr4, HIGH);
digitalWrite(gpa, HIGH);
digitalWrite(gpb, HIGH);
lcd.begin(16, 2);
delay(50);
lcd.print("-RPN Calculator-");
lcd.setCursor(0, 1);
lcd.print("V: 0.1 - (ALPHA)");
delay(2000);
lcd.clear();
}

void loop() {
restart:  
keyp = keyread(kr1,kr2,kr3,kr4,kc1,kc2,kc3,dur,tecdel);

if (keyp != 11 && keyp != 10 && menu==0){
 String sx = String(keyp);
 ox = ox + sx;
          lcd.setCursor(ant, 1);
          ant = ant + 1; 
          lcd.print(sx);
  x = ox.toInt(); 
}

if (digitalRead(men2) == LOW){
  y = x;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(y);
  lcd.setCursor(0, 1);
  ant = 0;
  ox = "";
  delay(100);
}

if (keyp == 10){
  lcd.clear();
  lcd.setCursor(0, 0);
  y = x + y;
  lcd.print(y);
  ox = "";
  ant=0;
   
}


Serial.print("x: ");
Serial.println(x);
Serial.print("y: "); 
Serial.println(y);
Serial.print("ox: ");
Serial.println(ox);
Serial.print("ant: "); 
Serial.println(ant);

}


void beep(int a){
  digitalWrite(buzzer, HIGH);
  delay(a);
  digitalWrite(buzzer, LOW);
}

void menuDraw(int menu){
  
}

void scrDraw(int x, int y){
  
}

int keyread(int a,int b,int c,int d,int aa,int bb,int cc,int dur,int tecdel){
int result=11;
  digitalWrite(a, LOW);
  if (digitalRead(aa)==LOW){
    result=1;
    delay(dur);
  }

  if (digitalRead(bb)==LOW){
    result=2;
    delay(dur);
  }

  if (digitalRead(cc)==LOW){
    result=3;
    delay(dur);
  }

  digitalWrite(a, HIGH);
  delay(tecdel);
  digitalWrite(b, LOW);


  if (digitalRead(aa)==LOW){
    result=4;
    delay(dur);
  }

  if (digitalRead(bb)==LOW){
    result=5;
    delay(dur);
  }

  if (digitalRead(cc)==LOW){
    result=6;
    delay(dur);
  }

  digitalWrite(b, HIGH);
  delay(tecdel);
  digitalWrite(c, LOW);

if (digitalRead(aa)==LOW){
 result=7;
  delay(dur);
  }

if (digitalRead(bb)==LOW){
result=8;
  delay(dur);
}

if (digitalRead(cc)==LOW){
result=9;
  delay(dur);
}

digitalWrite(c, HIGH);
delay(tecdel);
digitalWrite(d, LOW);


if (digitalRead(bb)==LOW){
result=0;
  delay(dur);
}

if (digitalRead(cc)==LOW){
result=10;
  delay(dur);
}

digitalWrite(d, HIGH);

  return result;
}
