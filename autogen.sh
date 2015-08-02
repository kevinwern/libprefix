# simple autoconfigure script

aclocal
case `uname` in Darwin*) glibtoolize --copy;; *) libtoolize ;; esac
autoheader
autoconf
automake --add-missing
