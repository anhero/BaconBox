SWIG:=X


all: BaconBoxLua.cpp


BaconBoxLua.cpp: BaconBox.i
	$(SWIG)/swig -lua -c++ -module BaconBox -outdir . -ignoremissing -DTIXML_USE_STL -DTINYXML_USE_STL -DBB_OPENGL -DBB_LUA -I../../.. -o BaconBoxLua.cpp BaconBox.i

clean:
	rm -rf BaconBoxLua.cpp