# A short story of mine --- why I write such a useless soft #

"You are reinventing wheels!"

Some people maybe leave such a conclusion and turn to their desktop search software like google desktop on Windows or tracker on GNOME.

For these people, I will be glad to supply some explanation, if they have patient to sit down and give me some time. Background will be stated and I'll explain why not desktop search.

## Background ##

Firstly, this soft is for my personal use and open to public only hope to help somebody --- both for those who want to use my soft, or read/use source code. If you think it is not suitable for you, just close this web page with a happy smile --- I really do not want to write a program and make you feel disgusted. However, if you are kind enough and ready to ask some background of this software, I will tell you more about it.

I have many document --- like papers, software/library manual, etc.--- in my filesystem under a hierarchical directory. It was fine when they are not so much. But as I downloaded more document, it became a mass. For example, Two directories named "lib" and "p2p", used to store document of libraries, and document about peer-to-peer network, respectively. Then where should I put the document of libjingle? It is of course a library, but it also refers to peer-to-peer. Another directory named "soft" used to store software manuals, consequently, something about bittorrent or amule will be homeless.

Of course, these problem can be resolved by a well-designed tree-based directory with some rules to disambiguate. However, I'm a lazy one(remember what Larry Wall said ?). And really do not want to waste too much time to sort them. The ideal software to deal with such problem may be an intelligent one --- you only feed it with lots of document and it will find things for you when you need it. Anyway, it seems a long time to get such an implementation. So a compromised way is tag files when you create them and search these tags. Very simple way, and was widly used on web.

I have this idea and decide to write one by myself when I found no software under GNU/Linux (There's only GNU/Linux on my computer) to meet my needs --- I may be really lazy. I even haven't searched it for too much time. So, tagal was out (with many bugs, maybe).

## Why not desktop search ##

google desktop search is great, and so is tracker. However, as I mentioned, they can not meet my demand, and I also really cannot bear the hard disk noise when they manage indeces. They can not automatically add suitable tags to papers. And I don't think it will happen in recent years, only if a big step was made in nature language process field. Tagging files manually is an easy and efficient way to manage them.

## About reinventing wheels ##

"Reinventing wheels" becomes an evil. For those who do not want to write program, it is an excuse; And for those who dislike some software, it is a weapon.

It is hard to say what is reinventing. Every program, like human, is different. Moreover, it is a good practice for a newbie to reinvent some wheels.

## Hope it can help you ##

Whatever, use it if you like. Send me mail if a bug found. Close this page if you think it's useless.