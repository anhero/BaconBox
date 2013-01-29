FLASCC:=X
FLEX:=X
SWIG:=X
BUILD_PATH=$(PROJECT_ROOT)/build
CXX="$(FLASCC)/usr/bin/g++"

AS3COMPILER:=asc2.jar
BASE_CFLAGS=-Werror -Wno-write-strings -Wno-trigraphs
DEFINE_FLAG=-DTIXML_USE_STL -DTINYXML_USE_STL
PROJECT_ROOT=../../..
CUSTOM_LIB_PATH=$(wildcard $(PROJECT_ROOT)/libraries/FreeBSD/i686 $(PROJECT_ROOT)/libraries/FreeBSD/x86_64)
LINK_FLAG=-lpng -lz -lAS3++ -lJsonBox -ltinyxml -lfreetype



ifdef lua
partialSwig=1
LINK_FLAG += -llua
DEFINE_FLAG+= -DBB_LUA
LUA_SWIG_WRAPPER = BaconBoxLua
LUA_SWIG_INTERFACE=../Swig/BaconBox.i
LUA_SWIG_SOURCES= BaconBox/Special/Flash/$(addsuffix .o,$(LUA_SWIG_WRAPPER))
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
BaconBox/Audio/AudioEngine.o \
BaconBox/Audio/BackgroundMusic.o \
BaconBox/Audio/MusicEngine.o \
BaconBox/Audio/MusicInfo.o \
BaconBox/Audio/MusicParameters.o \
BaconBox/Audio/NullAudio.o \
BaconBox/Audio/NullAudioEngine.o \
BaconBox/Audio/Sound.o \
BaconBox/Audio/SoundFX.o \
BaconBox/Audio/SoundEngine.o \
BaconBox/Audio/SoundInfo.o \
BaconBox/Audio/SoundParameters.o

COMPONENTS_SOURCES = \
BaconBox/Components/CameraDriverRenderer.o \
BaconBox/Components/Mesh.o \
BaconBox/Components/Transform.o \
BaconBox/Components/Flash/MovieClipHolder.o

CORE_SOURCES= \
BaconBox/Core/Component.o \
BaconBox/Core/Engine.o \
BaconBox/Core/Entity.o \
BaconBox/Core/IDManager.o \
BaconBox/Core/State.o

DISPLAY_SOURCES= \
BaconBox/Display/Camera.o \
BaconBox/Display/Color.o \
BaconBox/Display/PixMap.o \
BaconBox/Display/TextureInformation.o \
BaconBox/Display/Driver/GraphicDriver.o \
BaconBox/Display/Driver/NullGraphicDriver.o \
BaconBox/Display/Text/Font.o \
BaconBox/Display/Text/GlyphInformation.o \
BaconBox/Display/Text/FreetypeImplementation/FontImplementation.o \
BaconBox/Display/Window/MainWindow.o \
BaconBox/Display/Window/NullMainWindow.o \
BaconBox/Display/Window/Flash/FlashMainWindow.o


HELPER_SOURCES= \
BaconBox/Helper/Base64.o \
BaconBox/Helper/BitHelper.o \
BaconBox/Helper/CallHelper.o \
BaconBox/Helper/Compression.o \
BaconBox/Helper/MathHelper.o \
BaconBox/Helper/Parser.o \
BaconBox/Helper/Random.o \
BaconBox/Helper/ResourcePathHandler.o \
BaconBox/Helper/ShapeFactory.o \
BaconBox/Helper/Stopwatch.o \
BaconBox/Helper/StringHelper.o \
BaconBox/Helper/TimeHelper.o \
BaconBox/Helper/Timer.o \
BaconBox/Helper/TimerManager.o \
BaconBox/Helper/UTFConvert.o \
BaconBox/Helper/libc/LibcTimeHelper.o \
BaconBox/Helper/Serialization/Array.o \
BaconBox/Helper/Serialization/DefaultSerializer.o \
BaconBox/Helper/Serialization/Object.o \
BaconBox/Helper/Serialization/Serializable.o \
BaconBox/Helper/Serialization/Serializer.o \
BaconBox/Helper/Serialization/Value.o \
BaconBox/Helper/Serialization/JsonBox/JsonBoxSerializer.o \
BaconBox/Helper/Serialization/TinyXML/TinyXMLSerializer.o \
BaconBox/Helper/Flash/FlashHelper.o

INPUT_SOURCES= \
BaconBox/Input/InputDevice.o \
BaconBox/Input/InputManager.o \
BaconBox/Input/InputSignalData.o \
BaconBox/Input/InputState.o \
BaconBox/Input/Accelerometer/Accelerometer.o \
BaconBox/Input/Accelerometer/AccelerometerSignalData.o \
BaconBox/Input/Accelerometer/AccelerometerState.o \
BaconBox/Input/Accelerometer/NullAccelerometer.o \
BaconBox/Input/GamePad/GamePad.o \
BaconBox/Input/GamePad/GamePadButtonSignalData.o \
BaconBox/Input/GamePad/GamePadSignalData.o \
BaconBox/Input/GamePad/GamePadState.o \
BaconBox/Input/GamePad/GamePadThumbstickSignalData.o \
BaconBox/Input/GamePad/NullGamePad.o \
BaconBox/Input/Keyboard/Key.o \
BaconBox/Input/Keyboard/Keyboard.o \
BaconBox/Input/Keyboard/KeyboardSignalData.o \
BaconBox/Input/Keyboard/KeyboardState.o \
BaconBox/Input/Keyboard/KeyMaskSignalData.o \
BaconBox/Input/Keyboard/KeySignalData.o \
BaconBox/Input/Keyboard/NullKeyboard.o \
BaconBox/Input/Pointer/CursorState.o \
BaconBox/Input/Pointer/NullPointer.o \
BaconBox/Input/Pointer/Pointer.o \
BaconBox/Input/Pointer/PointerButtonSignalData.o \
BaconBox/Input/Pointer/PointerSignalData.o \
BaconBox/Input/Pointer/PointerState.o

MOVIECLIP_SOURCES= \
BaconBox/MovieClipEntity/MovieClipEntity.o

SIGNALSLOTS_SOURCES= \
BaconBox/SignalSlots/SignalAnalyzer.o \
BaconBox/SignalSlots/SignalAnalyzerManager.o \
BaconBox/SignalSlots/SignalData.o

FLASCC_SOURCES = \
BaconBox/Special/Flash/$(addsuffix .o,$(SWIG_OUTPUT)) \
BaconBox/Special/Flash/main.o

SCRIPT_SOURCES = \
BaconBox/Script/Lua/LuaManager.o


ALL_SOURCES= \
$(AUDIO_SOURCES) \
$(COMPONENTS_SOURCES) \
$(CORE_SOURCES) \
$(DISPLAY_SOURCES) \
$(HELPER_SOURCES) \
$(INPUT_SOURCES) \
$(MOVIECLIP_SOURCES) \
$(SIGNALSLOTS_SOURCES) \
BaconBox/AxisAlignedBoundingBox.o \
BaconBox/Console.o \
BaconBox/ResourceManager.o \
BaconBox/StandardVertexArray.o \
BaconBox/Vector2.o \
BaconBox/EntityFactory.o \
BaconBox/VertexArray.o

FLASCC_FILE_PATH=BaconBox/Special/Flash

ifdef lua
ALL_SOURCES+= $(SCRIPT_SOURCES) $(LUA_SWIG_SOURCES)
endif


all: check $(BUILD_PATH)/BaconBox.swc


swf: check $(BUILD_PATH)/BaconBox.swf


.PHONY : clean all swf partialSwig




$(BUILD_PATH)/BaconBox.swf: $(addsuffix .abc,$(SWIG_OUTPUT)) EntityHolderMovieClip.abc $(addprefix $(PROJECT_ROOT)/,$(ALL_SOURCES)) $(addprefix $(PROJECT_ROOT)/,$(FLASCC_SOURCES))

	@echo "-------- BaconBox.swf--------"
	"$(FLASCC)/usr/bin/g++" $(BASE_CFLAGS) $(DEFINE_FLAG) -I$(PROJECT_ROOT) -I$(CUSTOM_LIB_PATH)/include $(addsuffix .abc,$(SWIG_OUTPUT)) EntityHolderMovieClip.abc \
	$(addprefix $(PROJECT_ROOT)/, $(ALL_SOURCES)) $(addprefix $(PROJECT_ROOT)/, $(FLASCC_SOURCES)) -emit-swf -o $(BUILD_PATH)/BaconBox.swf \
	-L$(CUSTOM_LIB_PATH)/lib $(LINK_FLAG)

$(BUILD_PATH)/BaconBox.swc: $(addsuffix .abc,$(SWIG_OUTPUT)) EntityHolderMovieClip.abc $(addprefix $(PROJECT_ROOT)/,$(ALL_SOURCES)) $(addprefix $(PROJECT_ROOT)/,$(FLASCC_SOURCES))
	@echo "-------- BaconBox.swc --------"
	"$(FLASCC)/usr/bin/g++" $(BASE_CFLAGS) $(DEFINE_FLAG) -I$(PROJECT_ROOT) -I$(CUSTOM_LIB_PATH)/include $(addsuffix .abc,$(SWIG_OUTPUT)) EntityHolderMovieClip.abc \
	$(addprefix $(PROJECT_ROOT)/, $(ALL_SOURCES)) $(addprefix $(PROJECT_ROOT)/, $(FLASCC_SOURCES)) -emit-swc=BaconBox -o $(BUILD_PATH)/BaconBox.swc \
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


$(addsuffix .as3,$(SWIG_OUTPUT)) $(addsuffix .cpp,$(SWIG_OUTPUT)): $(BUILD_PATH)/build $(SWIG_INTERFACE)
	@echo "-------- SWIG wrappers --------"
	"$(FLASCC)/usr/bin/swig" -as3 -c++ -module $(SWIG_MODULE) -outdir . -ignoremissing $(DEFINE_FLAG) -DBB_FLASH_PLATEFORM -package BaconBox -I$(PROJECT_ROOT) -o $(addsuffix .cpp,$(SWIG_OUTPUT)) $(SWIG_INTERFACE)
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
	$(SWIG)/swig -lua -c++ -module BaconBox -outdir . -ignoremissing $(DEFINE_FLAG) -DBB_FLASH_PLATEFORM -DBB_LUA -I$(PROJECT_ROOT) -o $(addsuffix .cpp,$(LUA_SWIG_WRAPPER)) $(LUA_SWIG_INTERFACE)


EntityHolderMovieClip.abc: $(addsuffix .abc,$(SWIG_OUTPUT)) EntityHolderMovieClip.as
	@echo "-------- Compile the EntityHolderMovieClip to ABC --------"
	$(AS3COMPILERARGS) -abcfuture -AS3 -import $(call nativepath,$(FLASCC)/usr/lib/builtin.abc) -import $(call nativepath,$(FLASCC)/usr/lib/playerglobal.abc) -import $(call nativepath,./$(addsuffix .abc,$(SWIG_OUTPUT))) EntityHolderMovieClip.as 


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
	rm -rf BaconBoxAS3.cpp BaconBox.cpp BaconBoxLua.cpp *.swf *.swc *.as3 *.abc *.o $(BUILD_PATH) $(addprefix $(PROJECT_ROOT)/,$(ALL_SOURCES)) $(addprefix $(PROJECT_ROOT)/,$(FLASCC_SOURCES))



