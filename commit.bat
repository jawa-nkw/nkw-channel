@echo off
set /p m="Message: "
git init
git add .
git commit -m "%m%"
git branch -M main
git remote add origin https://github.com/jawa-nkw/nkw-channel.git
git push -u origin main
pause
commit