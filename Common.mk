# Version of echoprint, as a list. Is expanded out
# for various version numbers.
EP_VERSION ?= 4 1 2
VERSION := $(word 1, $(EP_VERSION)).$(word 2, $(EP_VERSION)).$(word 3, $(EP_VERSION))
MACRO_VERSION := $(word 1, $(EP_VERSION))$(word 2, $(EP_VERSION))$(word 3, $(EP_VERSION))
VERSION_MAJ := $(word 1, $(EP_VERSION))
VERSION_COMPAT := $(word 1, $(EP_VERSION)).$(word 2, $(EP_VERSION))
UNAME := $(shell uname -s)
CXX=g++
CC=gcc
#OPTFLAGS=-g -O0
OPTFLAGS=-O3 -DBOOST_UBLAS_NDEBUG -DNDEBUG
BOOST_CFLAGS=-I/usr/local/include/boost-1_35
TAGLIB_CFLAGS=`taglib-config --cflags`
VERSION_CFLAGS=-D ECHOPRINT_VERSION=$(MACRO_VERSION) $(TEST_CFLAGS)
TAGLIB_LIBS=`taglib-config --libs`
CXXFLAGS=-Wall $(BOOST_CFLAGS) $(TAGLIB_CFLAGS) -fPIC $(OPTFLAGS) $(VERSION_CFLAGS)
CFLAGS=-Wall -fPIC $(OPTFLAGS) $(VERSION_CFLAGS)
LDFLAGS=$(TAGLIB_LIBS) -lz -lpthread -lfftw3 $(OPTFLAGS)
LIBNAME=libcodegen.so
SONAME=$(LIBNAME).$(VERSION_MAJ)

MODULES_LIB = \
    $(SRC)/AudioBufferInput.o \
    $(SRC)/AudioStreamInput.o \
    $(SRC)/Base64.o \
    $(SRC)/Codegen.o \
    $(SRC)/Fingerprint.o \
    $(SRC)/MatrixUtility.o \
    $(SRC)/SubbandAnalysis.o \
		$(SRC)/StockwellTransform.o \
		$(SRC)/gft.o \
    $(SRC)/Whitening.o
MODULES = $(MODULES_LIB) $(SRC)/Metadata.o

