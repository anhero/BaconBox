SWIG:=swig
HEADERS_PATH:=../../../libraries/Darwin/x86_64/include


all: BaconBoxLua.cpp


BaconBoxLua.cpp: BaconBox.i
	$(SWIG) -lua -c++ -module BaconBox -outdir . -ignoremissing  -DVMATH_NAMESPACE="vmath" -DBB_OPENGL -DBB_LUA -I../../.. -I$(HEADERS_PATH)  -o BaconBoxLua.cpp BaconBox.i
	$(SWIG) -lua -external-runtime
clean:
	rm -rf BaconBoxLua.cpp