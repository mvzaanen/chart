dnl Process this file using autoconf to create a configure script

dnl Initialization
AC_INIT(chart, 0.1)
AM_INIT_AUTOMAKE
AC_CONFIG_SRCDIR(main.cpp)
AC_CONFIG_HEADERS(config.h)
AC_REVISION($Rev$)
AC_CONFIG_FILES([Makefile])

dnl Check for programs
AC_PROG_CXX
AC_HEADER_STDC
dnl AC_CHECK_HEADERS(getopt.h)
AC_LANG(C++)

dnl Add warnings
CPPFLAGS="-Wall $CPPFLAGS"

dnl Boost
boost_include_path="/usr/include" dnl Path to the Boost include files.
AC_ARG_WITH(boost-includes,
            [  --with-boost-includes=DIR  Path to the Boost include files],
            [boost_include_path=$withval],
            )
if test -z $boost_include_path; then
	AC_MSG_ERROR([Boost support is required.  You must
specify a path to a valid installation of the Boost include files.  This
can be done using --with-boost-includes=DIR, or try 'configure --help' for
the list of possible options.])
fi

dnl Do the check
CPPFLAGS="-I$boost_include_path $CPPFLAGS"
AC_CHECK_FILE($boost_include_path/boost/regex.hpp,
              ,
              AC_MSG_ERROR([Boost regex include files not found])
             )
LIBS="-lboost_regex $LIBS"
AC_CHECK_FILE($boost_include_path/boost/program_options.hpp,
              ,
              AC_MSG_ERROR([Boost program option include files not found])
             )
LIBS="-lboost_program_options $LIBS"
AC_CHECK_FILE($boost_include_path/boost/iostreams/filtering_stream.hpp,
              ,
              AC_MSG_ERROR([Boost iostreams include files not found])
             )
LIBS="-lboost_iostreams $LIBS"
dnl End Boost
AC_OUTPUT
