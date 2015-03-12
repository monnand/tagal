# 下载 #
下载[tagal-0.2.1.tar.bz2](http://tagal.googlecode.com/files/tagal-0.2.1.tar.bz2)

# 安装 #

在GNU/Linux下, 本软件依赖GTK+ (>=2.0), 这一般是多数发行版的标准配置, 因此不必担心. 对于ubuntu, 可以执行以下命令下载GTK+(开发版):
```
sudo apt-get install libgtk2.0-dev
```

之后, 解压[tagal-0.2.1.tar.bz2](http://tagal.googlecode.com/files/tagal-0.2.1.tar.bz2)到本地目录:
```
tar jxvf tagal-0.2.1.tar.bz2
```

按照一般的软件安装方法, 执行configure; make; make install:
```
cd tagal-0.2.1
./configure && make
sudo make install
```

好了, tagal已经安装完成, 不是很困难吧?
运行gtk-tagal就会看到如下界面:
![http://tagal.googlecode.com/files/tagal.screenshot.jpg](http://tagal.googlecode.com/files/tagal.screenshot.jpg)

如果你希望它更方便地为您服务, 请花些时间, 按照[这里](http://code.google.com/p/tagal/wiki/Config)的方法进行简单地配置.

[英文版](http://code.google.com/p/tagal/wiki/Install)