FLASCC:=X
FLEX:=X
SWIG:=`which swig`
BUILD_PATH=$(PROJECT_ROOT)/build
CXX="$(FLASCC)/usr/bin/g++"

AS3COMPILER:=asc2.jar
BASE_CFLAGS=-Werror -Wno-write-strings -Wno-trigraphs
DEFINE_FLAG=-DBB_DEBUG -DSIGLY_DEFAULT_MT_POLICY=SingleThreaded
PROJECT_ROOT=../../..
CUSTOM_LIB_PATH=$(wildcard $(PROJECT_ROOT)/libraries/FreeBSD/i686 $(PROJECT_ROOT)/libraries/FreeBSD/x86_64)
LINK_FLAG=-lpng -lz -lAS3++ -lJsonBox
SWIG_HEADERS_PATH:=../../../libraries/Darwin/x86_64/include

COMPC=$(FLEX)/bin/compc

ifdef linkOptimize
	BASE_CFLAGS+=-O4
	LINK_FLAG+=  -flto-api=$(BUILD_PATH)/exports.txt -fllvm-opt-opt=-strip
endif


ifdef lua
partialSwig=1
LINK_FLAG += -llua
DEFINE_FLAG+= -DBB_LUA
LUA_SWIG_WRAPPER = BaconBoxLua
LUA_SWIG_INTERFACE=../Swig/BaconBox.i
LUA_SWIG_SOURCES= BaconBox/Special/Flash/$(LUA_SWIG_WRAPPER)
endif


ifdef partialSwig
SWIG_INTERFACE=BaconBoxAS3.i
SWIG_OUTPUT=BaconBoxAS3
SWIG_MODULE=BaconBoxAS3
else
SWIG_INTERFACE=../Swig/BaconBox.i
SWIG_OUTPUT=BaconBox
SWIG_MODULE=BaconBox
endif


#VPATH = $PROJECT_ROOT
#vpath %.c $(PROJECT_ROOT)
#vpath %.cpp $(PROJECT_ROOT)

AUDIO_SOURCES = \
BaconBox/Audio/AudioEngine \
BaconBox/Audio/BackgroundMusic \
BaconBox/Audio/MusicEngine\
BaconBox/Audio/MusicInfo\
BaconBox/Audio/MusicParameters \
BaconBox/Audio/NullAudio\
BaconBox/Audio/NullAudioEngine \
BaconBox/Audio/Sound \
BaconBox/Audio/SoundFX \
BaconBox/Audio/SoundEngine \
BaconBox/Audio/SoundInfo \
BaconBox/Audio/SoundParameters \
BaconBox/Audio/Flash/FlashSoundEngine \
BaconBox/Audio/Flash/FlashMusicEngine \
BaconBox/Audio/Flash/FlashBackgroundMusic \
BaconBox/Audio/Flash/FlashSoundFX


COMPONENTS_SOURCES = \
BaconBox/Components/Mesh \
BaconBox/Components/Transform \
BaconBox/Components/HasName \
BaconBox/Components/TextComponent \
BaconBox/Components/Clickable \
BaconBox/Components/UIManager \
BaconBox/Components/EntityManager \
BaconBox/Components/ComponentAddedData \
BaconBox/Components/ColorTransform \
BaconBox/Components/Timeline \
BaconBox/Components/EntityContainer \
BaconBox/Components/SymbolComponent \
BaconBox/Components/MatrixComponent \
BaconBox/Components/DefaultMatrix \
BaconBox/Components/SizeComponent \
BaconBox/Components/ParticleEmitter \
BaconBox/Components/Speed \
BaconBox/Components/AABBHitBox \
BaconBox/Components/Flash/MovieClipHolder \
BaconBox/Components/Flash/TextFieldHolder \
BaconBox/Components/Flash/FlashTimeline \
BaconBox/Components/Flash/FlashEntityContainer \
BaconBox/Components/Flash/FlashHasName \
BaconBox/Components/Flash/FlashSizeComponent \
BaconBox/Components/Flash/FlashTransform \
BaconBox/Components/Flash/FlashAABBHitBox \
BaconBox/Components/Flash/FlashColorTransform \
BaconBox/Components/Flash/FlashCameraManager \
BaconBox/Components/Flash/FlashEntityManager 



CORE_SOURCES= \
BaconBox/Core/Component \
BaconBox/Core/Engine \
BaconBox/Core/Entity \
BaconBox/Core/IDManager \
BaconBox/Core/State \
BaconBox/Core/BaseEngine \
BaconBox/Core/Flash/FlashEngine

DISPLAY_SOURCES= \
BaconBox/Display/Camera \
BaconBox/Display/Color \
BaconBox/Display/Emitter \
BaconBox/Display/ParticlePhase \
BaconBox/Display/PixMap \
BaconBox/Display/TextureInformation \
BaconBox/Display/SubTextureInfo \
BaconBox/Display/Driver/GraphicDriver \
BaconBox/Display/Driver/NullGraphicDriver \
BaconBox/Display/Text/Font \
BaconBox/Display/Text/TextEntity \
BaconBox/Display/Text/Flash/FlashFont \
BaconBox/Display/Window/MainWindow \
BaconBox/Display/Window/NullMainWindow \
BaconBox/Display/Window/Flash/FlashMainWindow


HELPER_SOURCES= \
BaconBox/Helper/Base64 \
BaconBox/Helper/BitHelper \
BaconBox/Helper/CallHelper \
BaconBox/Helper/Compression \
BaconBox/Helper/MathHelper \
BaconBox/Helper/Parser \
BaconBox/Helper/Random \
BaconBox/Helper/ResourcePathHandler \
BaconBox/Helper/ShapeFactory \
BaconBox/Helper/EmitterFactory \
BaconBox/Helper/Stopwatch \
BaconBox/Helper/StringHelper \
BaconBox/Helper/TimeHelper \
BaconBox/Helper/Timer \
BaconBox/Helper/TimerManager \
BaconBox/Helper/UTFConvert \
BaconBox/Helper/libc/LibcTimeHelper \
BaconBox/Helper/Serialization/Array \
BaconBox/Helper/Serialization/DefaultSerializer \
BaconBox/Helper/Serialization/Object \
BaconBox/Helper/Serialization/Serializable \
BaconBox/Helper/Serialization/Serializer \
BaconBox/Helper/Serialization/Value \
BaconBox/Helper/Serialization/JsonBox/JsonBoxSerializer \
BaconBox/Helper/Serialization/RapidXml/RapidXmlSerializer \
BaconBox/Helper/Lua/LuaHelper \
BaconBox/Script/Lua/LuaCallback \
BaconBox/Helper/Flash/FlashHelper

INPUT_SOURCES= \
BaconBox/Input/InputDevice \
BaconBox/Input/InputManager \
BaconBox/Input/InputSignalData \
BaconBox/Input/InputState \
BaconBox/Input/Accelerometer/Accelerometer \
BaconBox/Input/Accelerometer/AccelerometerSignalData \
BaconBox/Input/Accelerometer/AccelerometerState \
BaconBox/Input/Accelerometer/NullAccelerometer \
BaconBox/Input/GamePad/GamePad \
BaconBox/Input/GamePad/GamePadButtonSignalData \
BaconBox/Input/GamePad/GamePadSignalData \
BaconBox/Input/GamePad/GamePadState \
BaconBox/Input/GamePad/GamePadThumbstickSignalData \
BaconBox/Input/GamePad/NullGamePad \
BaconBox/Input/Keyboard/Key \
BaconBox/Input/Keyboard/Keyboard \
BaconBox/Input/Keyboard/KeyboardSignalData \
BaconBox/Input/Keyboard/KeyboardState \
BaconBox/Input/Keyboard/KeyMaskSignalData \
BaconBox/Input/Keyboard/KeySignalData \
BaconBox/Input/Keyboard/NullKeyboard \
BaconBox/Input/Pointer/CursorState \
BaconBox/Input/Pointer/NullPointer \
BaconBox/Input/Pointer/Pointer \
BaconBox/Input/Pointer/PointerButtonSignalData \
BaconBox/Input/Pointer/PointerSignalData \
BaconBox/Input/Pointer/PointerState \
BaconBox/Input/Pointer/CursorButton \
BaconBox/Input/Keyboard/Flash/FlashKeyboard \
BaconBox/Input/Pointer/Flash/FlashPointer

MOVIECLIP_SOURCES= \
BaconBox/MovieClipEntity/MovieClipEntity

SIGNALSLOTS_SOURCES= \
BaconBox/SignalSlots/SignalAnalyzer \
BaconBox/SignalSlots/SignalAnalyzerManager \
BaconBox/SignalSlots/SignalData

FLASCC_SOURCES = \
BaconBox/Special/Flash/$(addsuffix ,$(SWIG_OUTPUT)) \
BaconBox/Special/Flash/main

ALL_SOURCES= \
$(AUDIO_SOURCES) \
$(COMPONENTS_SOURCES) \
$(CORE_SOURCES) \
$(DISPLAY_SOURCES) \
$(HELPER_SOURCES) \
$(INPUT_SOURCES) \
$(MOVIECLIP_SOURCES) \
$(SIGNALSLOTS_SOURCES) \
BaconBox/AxisAlignedBoundingBox \
BaconBox/Console \
BaconBox/ResourceManager \
BaconBox/StandardVertexArray \
BaconBox/Vector2 \
BaconBox/EntityFactory \
BaconBox/Symbol \
BaconBox/Matrix \
BaconBox/ColorMatrix \
BaconBox/Platform \
BaconBox/VertexArray \
BaconBox/EmitterEntity

FLASCC_FILE_PATH=BaconBox/Special/Flash

ifdef lua
ALL_SOURCES+= BaconBox/Script/Lua/LuaManager \
$(LUA_SWIG_SOURCES) \
BaconBox/Components/Lua/LuaEntity
endif


all: check $(BUILD_PATH)/BaconBox.swc $(BUILD_PATH)/EntityWrapper.swc


swf: check $(BUILD_PATH)/BaconBox.swf


.PHONY : clean all swf partialSwig LTO



LTO: VFS.abc $(addsuffix .abc,$(SWIG_OUTPUT)) $(BUILD_PATH)/exports.txt $(BUILD_PATH)/EntityWrapper.swc
	"$(FLASCC)/usr/bin/g++" $(BASE_CFLAGS) $(DEFINE_FLAG) -I$(PROJECT_ROOT) -I$(CUSTOM_LIB_PATH)/include $(addsuffix .abc,$(SWIG_OUTPUT))  \
	VFS.abc $(addsuffix .cpp, $(addprefix $(PROJECT_ROOT)/, $(ALL_SOURCES))) $(addsuffix .cpp, $(addprefix $(PROJECT_ROOT)/, $(FLASCC_SOURCES)))  $(DEFINE_FLAG) -I$(PROJECT_ROOT) -I$(CUSTOM_LIB_PATH)/include -emit-swc=BaconBox -o $(BUILD_PATH)/BaconBox.swc \
	-L$(CUSTOM_LIB_PATH)/lib $(LINK_FLAG)

LTOSWF: $(addsuffix .abc,$(SWIG_OUTPUT)) $(BUILD_PATH)/exports.txt $(BUILD_PATH)/EntityWrapper.swc
	"$(FLASCC)/usr/bin/g++" $(BASE_CFLAGS) $(DEFINE_FLAG) -I$(PROJECT_ROOT) -I$(CUSTOM_LIB_PATH)/include $(addsuffix .abc,$(SWIG_OUTPUT))  \
	$(addsuffix .cpp, $(addprefix $(PROJECT_ROOT)/, $(ALL_SOURCES))) $(addsuffix .cpp, $(addprefix $(PROJECT_ROOT)/, $(FLASCC_SOURCES)))  $(DEFINE_FLAG) -I$(PROJECT_ROOT) -I$(CUSTOM_LIB_PATH)/include -emit-swf -o $(BUILD_PATH)/BaconBox.swf \
	-L$(CUSTOM_LIB_PATH)/lib $(LINK_FLAG)

$(BUILD_PATH)/BaconBox.swf: $(addsuffix .abc,$(SWIG_OUTPUT))  EntityHolderMovieClip.abc EntityHolderTextField.abc $(addsuffix .o,$(addprefix $(PROJECT_ROOT)/,$(ALL_SOURCES))) $(addprefix $(PROJECT_ROOT)/,$(FLASCC_SOURCES)) (BUILD_PATH)/exports.txt
	@echo "-------- BaconBox.swf--------"
	"$(FLASCC)/usr/bin/g++" $(BASE_CFLAGS) $(DEFINE_FLAG) -I$(PROJECT_ROOT) -I$(CUSTOM_LIB_PATH)/include $(addsuffix .abc,$(SWIG_OUTPUT)) EntityHolderMovieClip.abc EntityHolderTextField.abc \
	$(addsuffix .o,$(addprefix $(PROJECT_ROOT)/, $(ALL_SOURCES))) $(addprefix $(PROJECT_ROOT)/, $(FLASCC_SOURCES)) -emit-swf -o $(BUILD_PATH)/BaconBox.swf \
	-L$(CUSTOM_LIB_PATH)/lib $(LINK_FLAG)

$(BUILD_PATH)/BaconBox.swc: VFS.abc $(addsuffix .abc,$(SWIG_OUTPUT)) $(addsuffix .o,$(addprefix $(PROJECT_ROOT)/,$(ALL_SOURCES))) $(addsuffix .o,$(addprefix $(PROJECT_ROOT)/,$(FLASCC_SOURCES)))
	@echo "-------- BaconBox.swc --------"
	"$(FLASCC)/usr/bin/g++" $(BASE_CFLAGS) $(DEFINE_FLAG) -I$(PROJECT_ROOT) -I$(CUSTOM_LIB_PATH)/include $(addsuffix .abc,$(SWIG_OUTPUT)) \
	VFS.abc $(addsuffix .o,$(addprefix $(PROJECT_ROOT)/, $(ALL_SOURCES))) $(addsuffix .o,$(addprefix $(PROJECT_ROOT)/, $(FLASCC_SOURCES))) -emit-swc=BaconBox -o $(BUILD_PATH)/BaconBox.swc \
	-L$(CUSTOM_LIB_PATH)/lib $(LINK_FLAG)

$?UNAME=$(shell uname -s)
ifneq (,$(findstring CYGWIN,$(UNAME)))
	$?nativepath=$(shell cygpath -at mixed $(1))
	$?unixpath=$(shell cygpath -at unix $(1))
else
	$?nativepath=$(abspath $(1))
	$?unixpath=$(abspath $(1))
endif

ifneq (,$(findstring "asc2.jar","$(AS3COMPILER)"))
	$?AS3COMPILERARGS=java $(JVMARGS) -jar $(call nativepath,$(FLASCC)/usr/lib/$(AS3COMPILER)) -merge -md 
else
	echo "ASC is no longer supported" ; exit 1 ;
endif


$(BUILD_PATH)/exports.txt: ./exports.txt $(addsuffix .o,$(SWIG_OUTPUT)) $(PROJECT_ROOT)/BaconBox/Special/Flash/$(addsuffix .o,$(LUA_SWIG_WRAPPER))
	@echo "-------- exports.txt generation--------"
	cp ./exports.txt $(BUILD_PATH)/exports.txt
		"$(FLASCC)/usr/bin/nm" $(addsuffix .o,$(SWIG_OUTPUT)) | grep " T " | awk '{print $$3}' | sed 's/_//' >> $(BUILD_PATH)/exports.txt
	#	"$(FLASCC)/usr/bin/nm" $(addsuffix .o,$(SWIG_OUTPUT)) | grep " W " | awk '{print $$3}' | sed 's/_//' >> $(BUILD_PATH)/exports.txt
	#	"$(FLASCC)/usr/bin/nm" $(addsuffix .o,$(SWIG_OUTPUT)) | grep " U " | awk '{print $$2}' | sed 's/_//' >> $(BUILD_PATH)/exports.txt

	#	"$(FLASCC)/usr/bin/nm" $(PROJECT_ROOT)/BaconBox/Special/Flash/$(addsuffix .o,$(LUA_SWIG_WRAPPER)) | grep " T " | awk '{print $$3}' | sed 's/_//' >> $(BUILD_PATH)/exports.txt
	#	"$(FLASCC)/usr/bin/nm" $(PROJECT_ROOT)/BaconBox/Special/Flash/$(addsuffix .o,$(LUA_SWIG_WRAPPER)) | grep " W " | awk '{print $$3}' | sed 's/_//' >> $(BUILD_PATH)/exports.txt
	#	"$(FLASCC)/usr/bin/nm" $(PROJECT_ROOT)/BaconBox/Special/Flash/$(addsuffix .o,$(LUA_SWIG_WRAPPER)) | grep " U " | awk '{print $$2}' | sed 's/_//' >> $(BUILD_PATH)/exports.txt


	#	"$(FLASCC)/usr/bin/nm" $(PROJECT_ROOT)/BaconBox/Core/Component.o | grep " T " | awk '{print $$3}' | sed 's/_//' >> $(BUILD_PATH)/exports.txt
	#	"$(FLASCC)/usr/bin/nm" $(PROJECT_ROOT)/BaconBox/Core/Component.o | grep " W " | awk '{print $$3}' | sed 's/_//' >> $(BUILD_PATH)/exports.txt
	#	"$(FLASCC)/usr/bin/nm" $(PROJECT_ROOT)/BaconBox/Core/Component.o | grep " U " | awk '{print $$2}' | sed 's/_//' >> $(BUILD_PATH)/exports.txt
LSOBackingStore.as:
	chmod 766 "$(FLASCC)/usr/share/LSOBackingStore.as"
	cp "$(FLASCC)/usr/share/LSOBackingStore.as" .


VFS.abc: LSOBackingStore.as URLLoaderVFS.as
	$(AS3COMPILERARGS)	-import $(call nativepath,$(FLASCC)/usr/lib/builtin.abc) \
			-import $(call nativepath,$(FLASCC)/usr/lib/playerglobal.abc) \
			-import $(call nativepath,$(FLASCC)/usr/lib/BinaryData.abc) \
			-import $(call nativepath,$(FLASCC)/usr/lib/ISpecialFile.abc) \
			-import $(call nativepath,$(FLASCC)/usr/lib/IBackingStore.abc) \
			-import $(call nativepath,$(FLASCC)/usr/lib/IVFS.abc) \
			-import $(call nativepath,$(FLASCC)/usr/lib/InMemoryBackingStore.abc) \
			-import $(call nativepath,$(FLASCC)/usr/lib/PlayerKernel.abc) \
			URLLoaderVFS.as LSOBackingStore.as -outdir . -out VFS

$(addsuffix .as3,$(SWIG_OUTPUT)) $(addsuffix .cpp,$(SWIG_OUTPUT)): $(BUILD_PATH)/build $(SWIG_INTERFACE)
	@echo "-------- SWIG wrappers --------"
	"$(FLASCC)/usr/bin/swig" -as3 -c++ -module $(SWIG_MODULE) -outdir . -ignoremissing $(DEFINE_FLAG) -DBB_FLASH_PLATFORM -package BaconBox -I$(PROJECT_ROOT) -o $(addsuffix .cpp,$(SWIG_OUTPUT)) $(SWIG_INTERFACE)
#	cp Entity_wrapper.cpp $(BUILD_PATH)/BaconBox/Special/Flash/
	mv $(addsuffix .as,$(SWIG_OUTPUT)) $(addsuffix .as3,$(SWIG_OUTPUT))

$(addsuffix .abc,$(SWIG_OUTPUT)): $(addsuffix .as3,$(SWIG_OUTPUT))
	@echo "-------- Compile the SWIG wrapper to ABC --------"
	mv $(addsuffix .as3,$(SWIG_OUTPUT)) $(addsuffix .as,$(SWIG_OUTPUT))
	$(AS3COMPILERARGS) -abcfuture -AS3 -import $(call nativepath,$(FLASCC)/usr/lib/builtin.abc) -import $(call nativepath,$(FLASCC)/usr/lib/playerglobal.abc) $(addsuffix .as,$(SWIG_OUTPUT)) 
	# rename the output so the compiler doesn't accidentally use both this .as file along with the .abc file we just produced
	mv $(addsuffix .as,$(SWIG_OUTPUT)) $(addsuffix .as3,$(SWIG_OUTPUT))


$(PROJECT_ROOT)/BaconBox/Special/Flash/$(addsuffix .cpp,$(LUA_SWIG_WRAPPER)): $(LUA_SWIG_INTERFACE)
	@echo "-------- lua SWIG wrappers --------"
	$(SWIG) -lua -c++ -module BaconBox -outdir . -ignoremissing $(DEFINE_FLAG) -DBB_FLASH_PLATFORM -DBB_LUA -I$(PROJECT_ROOT) -I$(SWIG_HEADERS_PATH) -o $(addsuffix .cpp,$(LUA_SWIG_WRAPPER)) $(LUA_SWIG_INTERFACE)


BaconBox/EntityWrapper/EntityHolderMovieClip.abc: BaconBox/EntityWrapper/EntityHolderMovieClip.as
	@echo "-------- Compile the EntityHolderMovieClip to ABC --------"
	$(AS3COMPILERARGS) -abcfuture -AS3 -import $(call nativepath,$(FLASCC)/usr/lib/builtin.abc) -import $(call nativepath,$(FLASCC)/usr/lib/playerglobal.abc) BaconBox/EntityWrapper/EntityHolderTextField.as BaconBox/EntityWrapper/EntityHolderMovieClip.as 

BaconBox/EntityWrapper/EntityHolderTextField.abc: BaconBox/EntityWrapper/EntityHolderTextField.as
	@echo "-------- Compile the EntityHolderTextField to ABC --------"
	$(AS3COMPILERARGS) -abcfuture -AS3 -import $(call nativepath,$(FLASCC)/usr/lib/builtin.abc) -import $(call nativepath,$(FLASCC)/usr/lib/playerglobal.abc) BaconBox/EntityWrapper/EntityHolderTextField.as 



$(BUILD_PATH)/EntityWrapper.swc: BaconBox/EntityWrapper/EntityHolderMovieClip.abc
	@echo "-------- Compile EntityWrapper.swc --------"
	$(COMPC) -compiler.source-path . -include-classes BaconBox.EntityWrapper.EntityHolderTextField BaconBox.EntityWrapper.EntityHolderMovieClip -output $(BUILD_PATH)/EntityWrapper.swc

#Entity_wrapper.o main.o: Entity_wrapper.cpp main.cpp
#	echo $@ --------------------
#	$(CXX) $< -c $(BASE_CFLAGS) -I$(PROJECT_ROOT) -I$(CUSTOM_LIB_PATH)/include -o $@


$(addprefix $(PROJECT_ROOT)/,$(LUA_SWIG_SOURCES)): $(PROJECT_ROOT)/BaconBox/Special/Flash/$(addsuffix .cpp,$(LUA_SWIG_WRAPPER))


%.o: %.c 
	@echo "-------- BUILD C FILE--------"
	$(CXX) $< -c $(BASE_CFLAGS) -emit-swf $(DEFINE_FLAG) -I$(PROJECT_ROOT) -I$(CUSTOM_LIB_PATH)/include -o $@


%.o: %.cpp 
	@echo "-------- BUILD CPP FILE--------"
	$(CXX) $< -c $(BASE_CFLAGS) -emit-swf $(DEFINE_FLAG) -I$(PROJECT_ROOT) -I$(CUSTOM_LIB_PATH)/include -o $@


$(BUILD_PATH)/build:
	@echo "-------- creating build path --------"
	mkdir $(BUILD_PATH)
#	cp -r $(PROJECT_ROOT)/BaconBox $(BUILD_PATH)
#	rm $(addsuffix .cpp, $(basename $(addprefix $(BUILD_PATH)/, $(ALL_SOURCES))))

	touch $(BUILD_PATH)/build


check:
	@if [ -d $(FLASCC)/usr/bin ] ; then true ; \
	else echo "Couldn't locate FLASCC sdk directory, please invoke make with \"make FLASCC=/path/to/FLASCC/sdk ...\"" ; exit 1 ; \
	fi

	@if [ -d "$(FLEX)/bin" ] ; then true ; \
	else echo "Couldn't locate Flex sdk directory, please invoke make with \"make FLEX=/path/to/flex  ...\"" ; exit 1 ; \
	fi

clean:
	rm -rf BaconBoxAS3.cpp BaconBox.cpp BaconBoxLua.cpp *.swf *.swc *.as3 BaconBox/EntityWrapper/*.abc *.abc *.o $(BUILD_PATH) LSOBackingStore.as $(addsuffix .o,$(addprefix $(PROJECT_ROOT)/,$(ALL_SOURCES))) $(addsuffix .o,$(addprefix $(PROJECT_ROOT)/,$(FLASCC_SOURCES)))



