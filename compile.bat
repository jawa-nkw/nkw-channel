@echo off
cd "E:\Users\Korisnik\Documents\Wii\HBDev\NKW"
del build /f /q
make && C:/wiiload.exe NKW.dol
pause
compile
