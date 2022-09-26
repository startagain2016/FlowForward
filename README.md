# FlowForward 流量转发工具

<br>

<div align=center>
  
![image](https://user-images.githubusercontent.com/52789403/192257366-d0efd52d-9bc1-466e-a9ee-6c4a72b896fb.png)

</div>

<br>

FlowForward 是一款基于命令行实现的功能强大的TCP流量转发工具，用于在后渗透中的横向越权时使用，该工具可定向转发数据包，打破内外网屏障，实现对内网特定主机发起攻击或中转数据包到外网，工具只有19KB绝对小巧且无任何特征，是一款不错的渗透辅助工具。

工具提供三种转发模式,`正向隧道转发模式`,`反向纯流量隧道模式`,`双向隧道转发模式`，这三种模式的使用场景各不相同，下面将逐一介绍功能使用细节，命令行帮助文档如下：
```C
Shell> FlowForward.exe
  _____ _                 _____                                _
 |  ___| | _____      __ |  ___|__  _ ____      ____ _ _ __ __| |
 | |_  | |/ _   / / / | |_ / _ | '__  / / / _` | '__/ _` |
 |  _| | | (_)  V  V /  |  _| (_) | |    V  V / (_| | | | (_| |
 |_|   |_|___/ _/_/   |_|  ___/|_|    _/_/ __,_|_|  __,_|

E-Mail: me@lyshark.com

Usage:
         --ListenPort          指定转发服务器侦听端口
         --RemoteAddress       指定对端IP地址
         --RemotePort          指定对端端口号
         --LocalPort           指定本端端口号
         --ServerAddress       指定服务端IP地址
         --ServerPort          指定服务器Port端口号
         --ConnectAddress      指定连接到对端IP地址
         --ConnectPort         指定对端连接Port端口号
```

 - 正向隧道转发模式
 
当处于正向隧道模式下，用户访问本机的`8888`端口则流量将被转发到远端的`8.141.58.64:22`地址上，此时如果使用`SSH`连接本机的`8888`端口相当于连接了`8.141.58.64`的`22`号端口。
 ```C
Shell> FlowForward.exe Forward --ListenPort 8888 --RemoteAddress 8.141.58.64 --RemotePort 22
[*] 正向隧道模式
[+] 本机侦听端口: 8888
[+] 流量转发地址 8.141.58.64:22

Shell> ssh root@localhost -p 8888
root@localhost's password:
 ```
 
 

















更新文档中。。。。




























