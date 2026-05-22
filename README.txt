PONG OYUNU - C++ / SFML

Bu proje, iki oyunculu klasik Pong oyunudur.
Oyun C++ dili ve SFML kütüphanesi kullanılarak geliştirilmiştir.

Proje Dosyaları:
- main.cpp
- CMakeLists.txt
- README.txt
- arial.ttf
- SFML DLL dosyaları

Oyunun Amacı:
İki oyuncu kendi paddle çubuklarını kontrol ederek topu karşı tarafa göndermeye çalışır.
Topu kaçıran oyuncunun rakibi puan kazanır.
5 puana ulaşan oyuncu oyunu kazanır.

Kontroller:
Sol oyuncu:
W = Yukarı
S = Aşağı

Sağ oyuncu:
Yukarı ok = Yukarı
Aşağı ok = Aşağı

R = Oyunu yeniden başlat

Çalıştırmak İçin:
Terminale şu komut yazılır:

.\pong.exe

Derleme Komutu:
C:\mingw64\bin\g++.exe main.cpp -std=c++17 -IC:\SFML-3.1.0-windows-gcc-14.2.0-mingw-64-bit\SFML-3.1.0\include -LC:\SFML-3.1.0-windows-gcc-14.2.0-mingw-64-bit\SFML-3.1.0\lib -lsfml-graphics -lsfml-window -lsfml-system -o pong.exe

Not:
Oyunun çalışması için arial.ttf ve gerekli SFML DLL dosyaları proje klasöründe bulunmalıdır.