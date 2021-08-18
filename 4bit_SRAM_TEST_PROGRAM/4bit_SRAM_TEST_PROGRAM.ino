//
// 1024*4bit(2114) SRAM TEST PROGRAM
//
// [Base Program]https://github.com/kanpapa/arduino/blob/master/HM6264TEST/HM6264TEST.ino
//


const unsigned ADDR_BIT_MAX=9; //アドレス幅 配列は0～9を指定
const unsigned IO_BIT_MAX=3;   //データ幅   配列は0～3を指定

//                  4bit SRAM
unsigned IO0=14;   // I/O1
unsigned IO1=15;   // I/O2
unsigned IO2=16;   // I/O3
unsigned IO3=17;   // I/O4

unsigned AD0=2;    // A0
unsigned AD1=3;    // A1
unsigned AD2=4;    // A2
unsigned AD3=5;    // A3
unsigned AD4=6;    // A4
unsigned AD5=7;    // A5
unsigned AD6=8;    // A6
unsigned AD7=9;    // A7
unsigned AD8=10;   // A8
unsigned AD9=11;   // A9

unsigned WE=12;     // ~WE
unsigned OE=13;     // ~OE(ピンが無いときは接続しない)
                    // ~CS1 = LOW
                    // CS2 = HIGH

unsigned DATA[]={IO0,IO1,IO2,IO3};
unsigned ADDR[]={AD0,AD1,AD2,AD3, AD4,AD5,AD6,AD7, AD8,AD9};

void setAddress(unsigned addr) {
  if (addr & 0x200) digitalWrite(AD9, HIGH); else digitalWrite(AD9, LOW);
  if (addr & 0x100) digitalWrite(AD8, HIGH); else digitalWrite(AD8, LOW);
  if (addr & 0x80) digitalWrite(AD7, HIGH); else digitalWrite(AD7, LOW);
  if (addr & 0x40) digitalWrite(AD6, HIGH); else digitalWrite(AD6, LOW);
  if (addr & 0x20) digitalWrite(AD5, HIGH); else digitalWrite(AD5, LOW);
  if (addr & 0x10) digitalWrite(AD4, HIGH); else digitalWrite(AD4, LOW);
  if (addr & 0x08) digitalWrite(AD3, HIGH); else digitalWrite(AD3, LOW);
  if (addr & 0x04) digitalWrite(AD2, HIGH); else digitalWrite(AD2, LOW);
  if (addr & 0x02) digitalWrite(AD1, HIGH); else digitalWrite(AD1, LOW);
  if (addr & 0x01) digitalWrite(AD0, HIGH); else digitalWrite(AD0, LOW);
  return;
}

void memWrite(unsigned addr, unsigned data) {

  digitalWrite(OE, HIGH);  // OE = High
  setAddress(addr);
  for (int i=0; i <= IO_BIT_MAX; i++) pinMode(DATA[i], OUTPUT);

  if (data & 0x08) digitalWrite(IO3, HIGH); else digitalWrite(IO3, LOW);
  if (data & 0x04) digitalWrite(IO2, HIGH); else digitalWrite(IO2, LOW);
  if (data & 0x02) digitalWrite(IO1, HIGH); else digitalWrite(IO1, LOW);
  if (data & 0x01) digitalWrite(IO0, HIGH); else digitalWrite(IO0, LOW);
  delayMicroseconds(1); // Wait 1micro sec

  digitalWrite(WE, LOW);  // WE = Low
  delayMicroseconds(1); // Wait 1micro sec

  digitalWrite(WE, HIGH);  // WE = High
  return;
}

unsigned memRead(unsigned addr) {

  digitalWrite(OE, HIGH);  // OE = High

  unsigned result = 0;
  setAddress(addr);
  for (int i=0; i <= IO_BIT_MAX; i++) pinMode(DATA[i], INPUT);

  digitalWrite(OE, LOW);  // OE = Low

  delayMicroseconds(1); // Wait 1micro sec
  for (int i = IO_BIT_MAX; i >= 0; i--) {
    result += result;
    if (digitalRead(DATA[i]) == HIGH) result |= 1;
  }

  digitalWrite(OE, HIGH);  // OE = High
  return result;
}

void setup() {
  // Initalize serial --------------------------------------------------------------------
  Serial.begin(9600);
  while (!Serial) {
    ;
  }

  //アナログ入力ピンのADC値を乱数の種として乱数列を初期化
  //https://www.arduino.cc/reference/en/language/functions/random-numbers/randomseed/
  //http://www.musashinodenpa.com/arduino/ref/index.php?f=0&pos=2867
  randomSeed(analogRead(4));
    
  // set PINMMODE
  pinMode(OE, OUTPUT);
  digitalWrite(OE, HIGH);

  pinMode(WE, OUTPUT);
  digitalWrite(WE, HIGH);

  for (int i=0; i<=ADDR_BIT_MAX; i++) pinMode(ADDR[i], OUTPUT); // address
  for (int i=0; i<=IO_BIT_MAX; i++) pinMode(DATA[i], INPUT);   // data

  Serial.println("4bit SRAM TEST PROGRAM");
  delay(10000);
  Serial.println("START!!");
  
  // memory check
  float tmpAdIdx = ADDR_BIT_MAX + 1;
  double MAX_ADDR = pow(2, tmpAdIdx) - 1;

  float tmpIOIdx = IO_BIT_MAX + 1;
  double MAX_DATA = pow(2, tmpIOIdx) - 1;


  for (unsigned testadrs = 0x000; testadrs <= MAX_ADDR ; testadrs++){
    // display address
    Serial.print(testadrs, HEX);
    Serial.print(":");

    // display memory
    Serial.print(memRead(testadrs), HEX);
    
    // random write memory
    Serial.print("  Write data: ");
    unsigned rnddata = random(MAX_DATA);
    Serial.print(rnddata, HEX);
    memWrite(testadrs, rnddata);

    // display memory
    Serial.print("  Read data: ");
    unsigned readdata = memRead(testadrs);
    Serial.print(readdata, HEX);
    //Serial.println(readdata, HEX);
    
    // match?
    if (rnddata == readdata) {
      Serial.println("  OK");
    } else {
      Serial.println("  ERROR!!");
    }
  }
}

void loop() {
}
