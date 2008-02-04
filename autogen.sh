#gettextize --force --copy
libtoolize --force --copy
aclocal 
autoheader
automake --add-missing --force-missing --gnu
autoconf
