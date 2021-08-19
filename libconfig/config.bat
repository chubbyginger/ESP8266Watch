@echo off
copy .\packages\*.* %userprofile%\AppData\Local\Arduino15\staging\packages\
echo 现在可以去Arduino的开发板管理器中安装esp8266了（目前只支持3.0.2）
pause