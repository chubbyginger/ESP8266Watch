# 配置库
如果家里网不好，直接安装esp8266是巨慢的甚至可能根本装不上，可以用以下方法安装：

1. 从[这里](https://github.com/yangshunhuai/ESP8266Watch/releases/libconfig)下载库配置包
2. 解压缩
3. 运行config.bat
4. 在Arduino的首选项中有一个附加开发板管理器网址，把`https://arduino.esp8266.com/stable/package_esp8266com_index.json`填进去。
5. 在Arduino工具->开发板->开发板管理器中搜索esp8266，点进去，有一个选择版本的下拉菜单，进去选择3.0.2，点右边安装，因为有了预先下载的缓存，安装非常快。
