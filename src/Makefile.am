# Copyright (C) 2009 2010 Giovanni [gnup] Simoni
#                           <simgignup@gmail.com>
# 
# This program is free software; you can redistribute it and/or 
# modify it under the terms of the GNU General Public License 
# as published by the Free Software Foundation; either 
# version 3 of the License, or (at your option) any later 
# version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
# 

SUBDIRS = tests
AM_CPPFLAGS = -I./ -Wall -Werror
lib_LTLIBRARIES = libgnupplus.la

include_HEADERS = gnupplus.hpp

includetreedir = $(prefix)/include/gnupplus
includetree_HEADERS = gnupplus/gnuplot.hpp \
                      gnupplus/pipe.hpp \
                      gnupplus/plots.hpp \
                      gnupplus/layout.hpp \
                      gnupplus/drawable.hpp

libgnupplus_la_SOURCES = $(include_HEADERS) \
                         $(includetreedir_HEADERS) \
                         gnuplot.cpp \
                         pipe.cpp \
                         plots.cpp \
                         layout.cpp \
                         drawable.cpp

