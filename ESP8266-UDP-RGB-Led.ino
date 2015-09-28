#include <Adafruit_NeoPixel.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

//ルータのSSIDとパスワード
//TODO: Cogle の場合 ココを APモードでREST APIとかで設定後にリセット
const char* ssid     = "aterm-a9d21b-gw";
const char* password = "755335947c1f9";

//NeoPixel RGB LEDの設定
#define PIN            5
#define NUMPIXELS      1
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

//UDP ポート等
const int PACKET_SIZE = 12;
char packetBuffer[PACKET_SIZE] = "000,000,000";
const int localPort = 2390;
WiFiUDP Udp;

void setup() {
  Serial.begin(115200);
  delay(10);

  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  
  Serial.println("WiFi connected");  
  Serial.print("IP address: "); 
  Serial.println(WiFi.localIP());

  //mac からの ncコマンド 例
  Serial.print("echo '100,100,100' | nc -u "); 
  Serial.print(WiFi.localIP());
  Serial.print(" "); 
  Serial.println(localPort);
    
  Udp.begin(localPort);

  //LEDを初期化
  pixels.begin();
  //LEDの色を消灯
  ledOn(0,0,0);
}

void ledOn(int r,int g,int b){
  pixels.setPixelColor(0,pixels.Color(r,g,b)); 
  pixels.show();  
}

void loop() {
  uint8_t r=0,g=0,b=0;
  
  //UDPからのパケット待ち
  int packetSize = Udp.parsePacket();
  if (packetSize)
  {
    //UDPからパケットを読み込む
    int len = Udp.read(packetBuffer, PACKET_SIZE);
    Serial.println("read packet");
    String buf = String( packetBuffer );
    
    //000,000,000 のフォーマットから数値を取り出す
    r = (buf.substring(0,3).toInt());
    g = (buf.substring(4,7).toInt());
    b = (buf.substring(8,12).toInt());
    
    Serial.print("r:");Serial.println(r,DEC);
    Serial.print("g:");Serial.println(g,DEC);
    Serial.print("b:");Serial.println(b,DEC);
    
    //LEDの色を変更
    ledOn(r,g,b);
  }
}

