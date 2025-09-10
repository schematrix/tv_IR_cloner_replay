
/*
/ ___| / ___| | | | ____|  \/  |  / \|_   _|  _ \|_ _\ \/ /
\___ \| |   | |_| |  _| | |\/| | / _ \ | | | |_) || | \  / 
 ___) | |___|  _  | |___| |  | |/ ___ \| | |  _ < | | /  \ 
|____/ \____|_| |_|_____|_|  |_/_/   \_\_| |_| \_\___/_/\_\
*/     

#include <IRremote.h>

const int SEND_PIN = 3; // IR LED burada
IRsend irsend(SEND_PIN);

const uint8_t REPEAT_COUNT = 3;
const uint8_t CARRIER_KHZ  = 38; // 36 veya 40 deneyebilirsin

// 0 (üstte denediğin 22'lik dizi)
const unsigned int RAW_0[] = {
  900,850,900,850,1800,850,850,900,900,850,900,1750,1800,850,900,1700,900,850,1800,850,950
}; // 22 eleman

// ON/OFF (ESC)
const unsigned int RAW_ONOFF[] = {
  900,850,1800,850,900,850,900,850,900,900,900,1700,1800,850,950,1700,900,850,1800,850,900
}; // 22

// 1
const unsigned int RAW_1[] = {
  950,850,900,850,1800,850,900,850,900,850,900,1750,1800,800,950,850,900,850,900,850,900,1750,900
}; // 24

// 2
const unsigned int RAW_2[] = {
  900,850,1800,850,900,850,900,850,900,850,900,1750,1800,850,900,850,900,850,900,1750,1800
}; // 22

// 3
const unsigned int RAW_3[] = {
  900,850,850,900,1800,850,900,850,900,850,900,1750,1800,850,900,850,900,850,900,1750,900,850,900
}; // 24

// 4
const unsigned int RAW_4[] = {
  900,850,1800,850,900,850,900,850,900,850,900,1750,1800,850,900,850,900,1700,1800,850,950
}; // 22

// 5
const unsigned int RAW_5[] = {
  900,850,900,850,1800,850,900,850,900,850,950,1700,1800,850,900,850,900,1750,1800,1700,950
}; // 22

// 6
const unsigned int RAW_6[] = {
  900,850,1800,850,900,850,900,850,900,850,950,1700,1800,850,900,850,900,1750,900,850,1800
}; // 22

// 7
const unsigned int RAW_7[] = {
  900,850,900,850,1800,850,900,850,900,850,900,1750,1800,850,900,850,950,1700,900,850,900,850,900
}; // 24

// 8
const unsigned int RAW_8[] = {
  900,850,1800,850,900,850,900,850,900,850,900,1750,1800,850,900,1700,1800,850,950,800,950
}; // 22

// 9
const unsigned int RAW_9[] = {
  900,850,900,850,1800,850,900,850,900,850,950,1700,1800,850,900,1750,1800,800,950,1700,900
}; // 22

// Yardımcı: ham sinyali N kez gönder
void sendRawRepeat(const unsigned int *raw, uint8_t len, uint8_t repeats = REPEAT_COUNT, uint8_t khz = CARRIER_KHZ) {
  for (uint8_t i = 0; i < repeats; i++) {
    irsend.sendRaw(raw, len, khz);
    delay(40); // tekrar arası
  }
}

void setup() {
  Serial.begin(9600);
  Serial.println("IR verici hazir. ESC = ON/OFF, 0-9 = sayi tuslari.");
}

void loop() {
  if (Serial.available() > 0) {
    int ch = Serial.read();

    switch (ch) {
      case 27: // ESC -> ON/OFF
        Serial.println("ON/OFF gonderiliyor");
        sendRawRepeat(RAW_ONOFF, sizeof(RAW_ONOFF) / sizeof(RAW_ONOFF[0]));
        break;

      case '0':
        Serial.println("0 gonderiliyor");
        sendRawRepeat(RAW_0, sizeof(RAW_0) / sizeof(RAW_0[0]));
        break;

      case '1':
        Serial.println("1 gonderiliyor");
        sendRawRepeat(RAW_1, sizeof(RAW_1) / sizeof(RAW_1[0]));
        break;

      case '2':
        Serial.println("2 gonderiliyor");
        sendRawRepeat(RAW_2, sizeof(RAW_2) / sizeof(RAW_2[0]));
        break;

      case '3':
        Serial.println("3 gonderiliyor");
        sendRawRepeat(RAW_3, sizeof(RAW_3) / sizeof(RAW_3[0]));
        break;

      case '4':
        Serial.println("4 gonderiliyor");
        sendRawRepeat(RAW_4, sizeof(RAW_4) / sizeof(RAW_4[0]));
        break;

      case '5':
        Serial.println("5 gonderiliyor");
        sendRawRepeat(RAW_5, sizeof(RAW_5) / sizeof(RAW_5[0]));
        break;

      case '6':
        Serial.println("6 gonderiliyor");
        sendRawRepeat(RAW_6, sizeof(RAW_6) / sizeof(RAW_6[0]));
        break;

      case '7':
        Serial.println("7 gonderiliyor");
        sendRawRepeat(RAW_7, sizeof(RAW_7) / sizeof(RAW_7[0]));
        break;

      case '8':
        Serial.println("8 gonderiliyor");
        sendRawRepeat(RAW_8, sizeof(RAW_8) / sizeof(RAW_8[0]));
        break;

      case '9':
        Serial.println("9 gonderiliyor");
        sendRawRepeat(RAW_9, sizeof(RAW_9) / sizeof(RAW_9[0]));
        break;

      case '\r':
      case '\n':
      case ' ':
        // yok say
        break;

      default:
        Serial.print("Taninmayan giris: ");
        Serial.println(ch);
        break;
    }
  }
}

/*
ON OFF
unsigned int raw[22] = {900,850,1800,850,900,850,900,850,900,900,900,1700,1800,850,950,1700,900,850,1800,850,900,};
irsend.sendRaw(raw,22,38);

1
unsigned int raw[24] = {950,850,900,850,1800,850,900,850,900,850,900,1750,1800,800,950,850,900,850,900,850,900,1750,900,};
irsend.sendRaw(raw,24,38);

2
unsigned int raw[22] = {900,850,1800,850,900,850,900,850,900,850,900,1750,1800,850,900,850,900,850,900,1750,1800,};
irsend.sendRaw(raw,22,38);

3
unsigned int raw[24] = {900,850,850,900,1800,850,900,850,900,850,900,1750,1800,850,900,850,900,850,900,1750,900,850,900,};
irsend.sendRaw(raw,24,38);

4
unsigned int raw[22] = {900,850,1800,850,900,850,900,850,900,850,900,1750,1800,850,900,850,900,1700,1800,850,950,};
irsend.sendRaw(raw,22,38);

5
unsigned int raw[22] = {900,850,900,850,1800,850,900,850,900,850,950,1700,1800,850,900,850,900,1750,1800,1700,950,};
irsend.sendRaw(raw,22,38);

6
unsigned int raw[22] = {900,850,1800,850,900,850,900,850,900,850,950,1700,1800,850,900,850,900,1750,900,850,1800,};
irsend.sendRaw(raw,22,38);

7
unsigned int raw[24] = {900,850,900,850,1800,850,900,850,900,850,900,1750,1800,850,900,850,950,1700,900,850,900,850,900,};
irsend.sendRaw(raw,24,38);

8
unsigned int raw[22] = {900,850,1800,850,900,850,900,850,900,850,900,1750,1800,850,900,1700,1800,850,950,800,950,};
irsend.sendRaw(raw,22,38);

9
unsigned int raw[22] = {900,850,900,850,1800,850,900,850,900,850,950,1700,1800,850,900,1750,1800,800,950,1700,900,};
irsend.sendRaw(raw,22,38);

*/