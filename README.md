# ESP32-TO-ChatGPT

ESP32 接入Chatgpt 

因为国内网络原因无法直接访问api.openai.com，所以需要自己部署函数，     教程：https://github.com/Ice-Hazymoon/openai-scf-proxy     2. https://github.com/easychen/openai-api-proxy获取url

然后要注册chatgpt账号获得密钥，这个自行解决

用platform打开上面文件，替换wife名字密码，替换自己的网站和密钥，然后就能通过串口发送问题，等待chatgpt回答

目标代码还是存在于一些问题中，当问题比较复杂是，响应时间过长会报错，希望大佬可以帮忙改一下下
的
#chatgpt #esp32
