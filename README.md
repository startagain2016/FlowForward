# FlowForward 流量转发工具

<br>

<div align=center>
  
![image](https://user-images.githubusercontent.com/52789403/192257366-d0efd52d-9bc1-466e-a9ee-6c4a72b896fb.png)

</div>

<br>

FlowForward 是一款基于命令行实现的功能强大的TCP流量转发工具，用于在后渗透中横向越权时使用，该工具可定向转发数据包，打破内外网屏障，实现对内网特定主机发起攻击或中转数据包到外网，工具只有19KB绝对小巧且无任何特征，是一款不错的渗透辅助工具。

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
 
  - 反向纯流量隧道模式

当处于反向纯流量隧道模式下用户需要做两件事，服务端需要在本机运行，客户端需要在内网中的一台主机上运行。

服务端运行侦听命令，执行后本地将侦听`9999`端口等待客户端连接。
```C
Shell> FlowForward.exe ReverseServer --ListenPort 9999 --LocalPort 8888

[*] 反向纯流量隧道模式 (服务端)
[+] 侦听端口: 9999
[+] 本机连接地址: localhost:8888
```
客户端运行反弹命令，其中`ServerAddress:ServerPort`用于指定服务端地址以及端口号，其中`ConnectAddress:ConnectPort`则是内网中其他主机的IP地址。
```C
Shell> FlowForward.exe ReverseClient --ServerAddress 127.0.0.1 --ServerPort 9999 \
--ConnectAddress 8.141.58.64 --ConnectPort 22

[*] 反向纯流量隧道模式 (客户端)
[+] 服务端地址 127.0.0.1:9999
[+] 连接内网地址 8.141.58.64:22
```
如果你有幸获得了内网一台主机的控制权，而你想攻击其他主机，当你建立了如上隧道，攻击本机的`127.0.0.1:8888`则相当于在攻击内网中的`8.141.58.64:22`这个地址，其实是在变相的攻击，如上客户端执行后，服务端连接本地`8888`端口，则实际连接到了`8.141.58.64:22`端口上。
```C
Shell> ssh root@localhost -p 8888
root@localhost's password:
```

 - 双向隧道转发模式

当处于双向隧道转发模式下用户需要做两件事，服务端需要在本机运行，客户端需要在内网中的一台主机上运行。

不同于`反向纯流量隧道模式`此模式主要用于连接带有页面的服务，例如连接远程的`3389`远程桌面，这类流量需要更加精细的控制，所以需要使用本隧道完成。

服务端侦听地址
```C
Shell> FlowForward.exe TwoForwardServer --ListenPort 9999 --LocalPort 8888

[*] 双向隧道转发模式 (服务端)
[+] 侦听端口: 9999
[+] 本机连接地址: localhost:8888
```

客户端执行如下命令,主动连接服务端`127.0.0.1:9999`端口，连接成功后转发`8.141.58.64:3389`的流量到服务端。
```C
Shell> FlowForward.exe TwoForwardClient --ServerAddress 127.0.0.1 --ServerPort 9999 \
--ConnectAddress 8.141.58.64 --ConnectPort 3389

[*] 双向隧道转发模式 (客户端)
[+] 服务端地址 127.0.0.1:9999
[+] 连接内网地址 8.141.58.64:3389
```
此时通过远程协助连接本机的`localhost:8888`端口则相当于连接了内网主机`8.141.58.64:3389`端口，实现直接访问。
