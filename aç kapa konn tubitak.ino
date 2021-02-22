#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <EEPROM.h>

LiquidCrystal_I2C lcd(0x27,16,2);

int PUL=10;
int DIR=11;
int EN=12;
int k=130;
long n=1;
long z=2000;

const byte satir=4;
const byte sutun=4;

String girilen_deger="";
String girilen_deger2="";

int bol1=0;
int bol2=0;
int mert=0;
int test=0;
char tus_takimi[satir][sutun]=
{
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte satirpin[satir]={2,3,4,5};
byte sutunpin[sutun]={6,7,8,9};

Keypad tus_takimim =Keypad(makeKeymap(tus_takimi), satirpin, sutunpin, satir, sutun);

void setup() {
  pinMode (PUL, OUTPUT);
  pinMode (DIR, OUTPUT);
  pinMode (EN, OUTPUT);
  digitalWrite(EN,HIGH);

  lcd.begin();
  lcd.home();
  lcd.backlight();
  lcd.setCursor(6,0);
  lcd.print("TEM");
  lcd.setCursor(5,1);
  lcd.print("KABLO");
}

void loop() {
char tus =tus_takimim.getKey();

if (tus=='A')
{
  lcd.begin();
  lcd.home();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Tekrar sayisi =");
  bol1=1;
  bol2=0;
  girilen_deger="";
}

else if (tus=='B')
{
  lcd.begin();
  lcd.home();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("300-4000 hiz gir =");
  bol1=0;
  bol2=1;
  girilen_deger2="";
}

else if (tus=='C')
{   
    lcd.begin();
    lcd.home();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Devam et !");


    long fouroku2 = EEPROM.read(4);
    long threeoku2 = EEPROM.read(5);
    long twooku2 = EEPROM.read(6);
    long oneoku2 = EEPROM.read(7);
    girilen_deger2 = ((fouroku2 << 0) & 0xFF) + ((threeoku2 << 8) & 0xFFFF) + ((twooku2 << 16) & 0xFFFFFF) + ((oneoku2 << 24) & 0xFFFFFFFF);


    long fouroku = EEPROM.read(0);
    long threeoku = EEPROM.read(1);
    long twooku = EEPROM.read(2);
    long oneoku = EEPROM.read(3);

    girilen_deger = ((fouroku << 0) & 0xFF) + ((threeoku << 8) & 0xFFFF) + ((twooku << 16) & 0xFFFFFF) + ((oneoku << 24) & 0xFFFFFFFF);

}

else if (tus=='#')
{ 
  n=girilen_deger.toInt ();
  z=girilen_deger2.toInt ();

   if(z<300)
  {
    z=300;
  }

  if(z>4000)
  {
    z=4000;
  }

  for(int y=1; y<=n; y++)
  {
      if(mert==1)
  {
    lcd.begin();
    lcd.home();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Durduruldu !");
    long t=(n-y)+1;

    byte four = (t & 0xFF);
    byte three = ((t >> 8) & 0xFF);
    byte two = ((t >> 16) & 0xFF);
    byte one = ((t >> 24) & 0xFF);

    EEPROM.write(0, four);
    EEPROM.write(1, three);
    EEPROM.write(2, two);
    EEPROM.write(3, one);

    long fouroku = EEPROM.read(0);
    long threeoku = EEPROM.read(1);
    long twooku = EEPROM.read(2);
    long oneoku = EEPROM.read(3);

    girilen_deger = ((fouroku << 0) & 0xFF) + ((threeoku << 8) & 0xFFFF) + ((twooku << 16) & 0xFFFFFF) + ((oneoku << 24) & 0xFFFFFFFF);

    byte four2 = (z & 0xFF);
    byte three2 = ((z >> 8) & 0xFF);
    byte two2 = ((z >> 16) & 0xFF);
    byte one2 = ((z >> 24) & 0xFF);

    EEPROM.write(4, four2);
    EEPROM.write(5, three2);
    EEPROM.write(6, two2);
    EEPROM.write(7, one2);

    long fouroku2 = EEPROM.read(4);
    long threeoku2 = EEPROM.read(5);
    long twooku2 = EEPROM.read(6);
    long oneoku2 = EEPROM.read(7);
    girilen_deger2 = ((fouroku2 << 0) & 0xFF) + ((threeoku2 << 8) & 0xFFFF) + ((twooku2 << 16) & 0xFFFFFF) + ((oneoku2 << 24) & 0xFFFFFFFF);
    mert=0;
    break;
  }
    lcd.begin();
    lcd.home();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Tekrar =");
    lcd.setCursor(8,0);
    lcd.print(n);
    lcd.setCursor(0,1);
    lcd.print("Hiz =");
    lcd.setCursor(5,1);
    lcd.print(z);
    lcd.setCursor(10,1);
    long t=n-y;
    lcd.print(t);
    if(t==0){
    lcd.setCursor(10,1);
    lcd.print("Bitti !");
    }
  digitalWrite(DIR,LOW);
  for (int i=0; i<k; i++)
  {
    char tus =tus_takimim.getKey();

    digitalWrite(PUL,HIGH);
    delayMicroseconds(z);
    digitalWrite(PUL,LOW);
    delayMicroseconds(z);

        if(tus=='D'||mert==1)
    {
      lcd.begin();
      lcd.home();
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Durduruldu !");
      mert=1;
      break;
    }
  }
    delay(250);
   digitalWrite(DIR,HIGH);
   for (int i=0; i<k; i++)
   {
    char tus =tus_takimim.getKey();
      if(tus=='D'||mert==1)
    {
      lcd.begin();
      lcd.home();
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Durduruldu !");
      mert=1;
      break;
    }
     digitalWrite(PUL,HIGH);
     delayMicroseconds(z);
     digitalWrite(PUL,LOW);
     delayMicroseconds(z);
   }
     delay(250);
   }
}

if(bol1==1)
{
  if(tus=='1'||tus=='2'||tus=='3'||tus=='4'||tus=='5'||tus=='6'||tus=='7'||tus=='8'||tus=='9'||tus=='0')
  {
    lcd.begin();
    lcd.home();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Tekrar sayisi =");
    girilen_deger = girilen_deger + tus;
    lcd.setCursor(0,1);
    lcd.print(girilen_deger);
  }
  else if(tus=='*')
  {
   girilen_deger=girilen_deger.substring(0,girilen_deger.length()-1);
   lcd.begin();
   lcd.home();
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("Tekrar sayisi =");
   lcd.setCursor(0,1);
   lcd.print(girilen_deger);
  }
}
if(bol2==1)
{
    if(tus=='1'||tus=='2'||tus=='3'||tus=='4'||tus=='5'||tus=='6'||tus=='7'||tus=='8'||tus=='9'||tus=='0')
  {
    lcd.begin();
    lcd.home();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("300-4000 hiz gir =");
    girilen_deger2 = girilen_deger2 + tus;
    lcd.setCursor(0,1);
    lcd.print(girilen_deger2);
  }
    else if(tus=='*')
    {
      girilen_deger2=girilen_deger2.substring(0,girilen_deger2.length()-1);
      lcd.begin();
      lcd.home();
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("300-4000 hiz gir =");
      lcd.setCursor(0,1);
      lcd.print(girilen_deger2);
    }
}
}
