# TV_hack 

Arduino ile TV kumandası IR sinyallerini **yakala** (RX/sniffer) ve **aynı şekilde geri gönder** (TX/cloner).  
Bu repo iki ayrı skeç içerir: **gönderici (TX)** ve **alıcı (RX)**. TX tarafında **ESC = ON/OFF**, **0–9 = rakam tuşları** olarak map’lenmiştir. RX tarafı yakalanan sinyali ham dizi (`raw[]`) ve örnek `sendRaw(...)` çağrısı olarak seri porta basar.

> **Not:** Ham veriyle birebir tekrar (replay) için **IRremote 3.9.0** gereklidir.

## Özellikler
- **Ham veri yakalama** (RX) ve **sendRaw ile gönderim** (TX)
- Seri porttan **ESC/0–9** ile anlık kontrol
- **Tekrar sayısı** (repeat) ve **taşıyıcı frekans** (kHz) ayarlanabilir
- **UNO SRAM** kısıtına uygun minimal yapı

## Donanım
- Arduino **UNO** (veya uyumlu)
- **IR alıcı**: VS1838B / TSOP1738 vb. → **D2 (RECV_PIN)**
- **IR verici LED** + **NPN transistör** (2N2222 / BC547)
  - Arduino **D3 (SEND_PIN) → 1 kΩ → Transistör Base**
  - **5V → IR LED (+) → 100–220 Ω → Transistör Kolektör**
  - **Transistör Emitter → GND**
- **Tüm GND’ler ortak** olmalı  
Varsayılan pinler: **SEND_PIN = 3**, **RECV_PIN = 2**

## Kurulum
**IRremote 3.9.0** yükleyin (4.5.x’te ham veri API’si değişmiştir):


arduino-cli lib uninstall IRremote@4.5.0      # Opsiyonel: Yeni sürümü kaldır
arduino-cli lib install "IRremote@3.9.0"      # Gerekli sürüm
arduino-cli lib list | grep IRremote          # Yalnızca 3.9.0 görünmeli


Derleme ve yükleme (Mac terminal örneği):
```bash
arduino-cli compile --fqbn arduino:avr:uno /senin/uzatın
arduino-cli upload -p /dev/tty.usbmodem11201 --fqbn arduino:avr:uno /senin/uzatın
```

Seri port bağlantısı:
```bash
# TX skeçi (9600 baud)
python3 -m serial.tools.miniterm /dev/tty.usbmodem11201 9600 --raw
# RX skeçi (57600 baud)
python3 -m serial.tools.miniterm /dev/tty.usbmodem11201 57600 --raw
```

## Kullanım
1) **Alıcı (RX) ile yakalama:**  
RX skeçini yükleyin, 57600 baud ile bağlanın. Kumandadan bir tuşa basın. Seri porttan şu iki satırı görürsünüz:
```cpp
unsigned int raw[XX] = { ... };
irsend.sendRaw(raw, XX, 38);
```
Bu satırları TX kodunda ilgili tuşa map’leyin (repo’da hazır eşlemeler mevcut).

2) **Gönderici (TX) ile geri gönderme:**  
TX skeçini yükleyin, 9600 baud ile bağlanın. RX skeçinde aldığınız verileri burada ilgili yerlere kopyalayın. Her komut varsayılan olarak 3 kez ve 38 kHz ile gönderilir.

## İpuçları
- **Frekans:** 38 kHz varsayılan. Gerekirse 36 veya 40 kHz deneyin.  
- **Tekrar sayısı:** Çoğu TV 2–3 tekrar ister → TX’te `REPEAT_COUNT` artırılabilir.  
- **Ham veri uzunluğu:** Çok kısa diziler başarısız olabilir → RX ile yeniden yakalayın.  
- **Güç:** Transistörsüz verici genellikle yetersiz menzil/sinyal üretir.  
- **UNO SRAM:** Büyük diziler RAM taşabilir → dizi sayısını/uzunluğunu azaltın veya `PROGMEM/sendRaw_P()` kullanın.  

## Teşekkür & Lisans
Ken Shirriff → IRremote kütüphanesi  
PJRC/Teensy → Dokümantasyon ve örnekler  

Email: theindustriesofengineering@gmail.com  
Instagram: https://www.instagram.com/schematrix.io/  
YouTube: https://www.youtube.com/@schematrix  
TikTok: https://www.tiktok.com/@schematrix  
Patreon: https://www.patreon.com/c/schematrix  
Buy Me a Coffee: https://buymeacoffee.com/schematrix  

Feel free to open issues or contribute to this repository!
