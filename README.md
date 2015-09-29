# ESP8266-UDP-RGB-Led

スケッチのSSIDとパスワードを自分の環境の物に修正が必要
```
const char* ssid     = "XXXXXXX";
const char* password = "XXXXXXX";
````

mac コマンドラインからUDPパケット送信
```
echo ‘100,100,100' | nc -u 192.168.0.6 2390
```
