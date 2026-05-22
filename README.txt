PONG OYUNU - SFML

Dosyalar:
- main.cpp
- CMakeLists.txt
- README.txt

Calistirmak icin:
1) SFML kurulu olmali.
2) Proje klasorune arial.ttf font dosyasi koyulmalı.
3) VS Code terminalinde derleme komutu:

g++ main.cpp -IC:\SFML\include -LC:\SFML\lib -lsfml-graphics -lsfml-window -lsfml-system -o pong.exe

4) C:\SFML\bin icindeki sfml-graphics, sfml-window ve sfml-system DLL dosyalarini proje klasorune kopyala.
5) Calistir:

pong.exe

Kontroller:
Sol oyuncu: W / S
Sag oyuncu: Yukari ok / Asagi ok
R: Oyunu yeniden baslat

Oyun kurali:
5 puana ulasan oyuncu oyunu kazanir.
