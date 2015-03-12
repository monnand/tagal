# Add tags to file in a convenient way #

When you want to add tags to file(s), you maybe do not like to open main window of tagal and add tags/files by clicking add tags/files button. It should be a more natural way to add tags --- say, open file browser, right click on a certain file, then input tags for that file. And the main window of tagal only used to search tags --- of course, you still can add files/tags under that window if you like.

Now, this can be done by a little configuration --- again, it is very simple.

# Nautilus Actions #

[nautilus-actions](http://freshmeat.net/projects/nautilus-actions/) is a very wonderful software if you use nautilus. As said in its description:
_Nautilus Actions is an extension for Nautilus, the GNOME file manager, which allows you to configure programs to be launched on files selected in the Nautilus interface. Each time you right-click on one or several selected files in Nautilus, Nautilus Actions will parse its configuration files to see if a program has been set for this selection. If one has been set, it will add an item to the menu that allows you to execute the program on the selected files._

So we need some help from nautilus actions. Download and install it, or if you are using ubuntu, just type:
```
sudo apt-get install nautilus-actions
```

# Config nautilus-actions for tagal #

First download two config files: [tagal\_edit\_tags.schemas](http://tagal.googlecode.com/files/tagal_edit_tags.schemas) and [tagal.schemas](http://tagal.googlecode.com/files/tagal.schemas). Then, import them to nautilus-actions:

**Open nautilus-actions, here's the main window. And click "Import/Export" button**

![http://tagal.googlecode.com/files/main_wnd.jpg](http://tagal.googlecode.com/files/main_wnd.jpg)

**Input the path of [tagal\_edit\_tags.schemas](http://tagal.googlecode.com/files/tagal_edit_tags.schemas) in your host to import this config file. Then click "OK"**

![http://tagal.googlecode.com/files/import_wnd.jpg](http://tagal.googlecode.com/files/import_wnd.jpg)

**Import [tagal.schemas](http://tagal.googlecode.com/files/tagal.schemas) in the same way**

**Finally, when you right-click some file(s), here is the menu you would see.**

![http://tagal.googlecode.com/files/right.click.jpg](http://tagal.googlecode.com/files/right.click.jpg)

**Click "Edit Tags" on that menu, you would see:**

![http://tagal.googlecode.com/files/add-tags-main-wnd.jpg](http://tagal.googlecode.com/files/add-tags-main-wnd.jpg)

# About portability #
I'm very sorry to say: this method can not be done without nautilus and nautilus-actions. I'll try to add KDE support as soon as possible. Or, if you have any suggestions, send me mail (monnand at gmail dot com)