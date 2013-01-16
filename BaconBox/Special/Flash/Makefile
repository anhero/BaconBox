FLASCC:=X
FLEX:=X
BUILD_PATH=$(PROJECT_ROOT)/build
CXX="$(FLASCC)/usr/bin/g++"
AS3COMPILER:=asc2.jar
BASE_CFLAGS=-Werror -Wno-write-strings -Wno-trigraphs -DTIXML_USE_STL -DTINYXML_USE_STL
PROJECT_ROOT=../../..
CUSTOM_LIB_PATH=$(wildcard $(PROJECT_ROOT)/libraries/FreeBSD/i686 $(PROJECT_ROOT)/libraries/FreeBSD/x86_64)
LINK_FLAG=-lpng -lz -lFlash++ -lAS3++ -lJsonBox -ltinyxml -lfreetype

#VPATH = $PROJECT_ROOT
vpath %.c $(PROJECT_ROOT)
vpath %.cpp $(PROJECT_ROOT)

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
BaconBox/Components/Transform.o 

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
BaconBox/Display/Window/NullMainWindow.o

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
BaconBox/Helper/Serialization/TinyXML/TinyXMLSerializer.o

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
BaconBox/MovieClipEntity/MovieClipEntity.o \
BaconBox/MovieClipEntity/Flash/MovieClipHolder.o

SIGNALSLOTS_SOURCES= \
BaconBox/SignalSlots/SignalAnalyzer.o \
BaconBox/SignalSlots/SignalAnalyzerManager.o \
BaconBox/SignalSlots/SignalData.o

FLASCC_SOURCES = \
BaconBox/Special/Flash/Entity_wrapper.o \
BaconBox/Special/Flash/main.o


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
BaconBox/VertexArray.o

FLASCC_FILE_PATH=BaconBox/Special/Flash

all: check $(BUILD_PATH)/BaconBox.swc

$(BUILD_PATH)/temp.swc: EntityWrapper.abc $(addprefix $(BUILD_PATH)/,$(ALL_SOURCES)) $(addprefix $(BUILD_PATH)/,$(FLASCC_SOURCES)) #Entity_wrapper.o main.o

	@echo "-------- BaconBox --------"
	"$(FLASCC)/usr/bin/g++" $(BASE_CFLAGS) -I$(PROJECT_ROOT) -I$(CUSTOM_LIB_PATH)/include -DBB_FLASH_PLATEFORM EntityWrapper.abc \
	$(addprefix $(BUILD_PATH)/, $(ALL_SOURCES)) $(addprefix $(BUILD_PATH)/, $(FLASCC_SOURCES)) -emit-swc=temp -o $(BUILD_PATH)/temp.swc \
	-L$(CUSTOM_LIB_PATH)/lib $(LINK_FLAG)

$(BUILD_PATH)/BaconBox.swc: $(BUILD_PATH)/temp.swc EntityHolderMovieClip.as
	@echo "-------- Compile EntityMovieClip --------"
	"$(FLEX)/bin/compc" -include-libraries=$(BUILD_PATH)/temp.swc -include-classes=EntityHolderMovieClip -source-path . -debug=true -o $(BUILD_PATH)/BaconBox.swc

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


EntityWrapper.as3 Entity_wrapper.c: $(BUILD_PATH)/build entity.i
	@echo "-------- SWIG wrappers --------"
	"$(FLASCC)/usr/bin/swig" -as3 -c++ -module EntityWrapper -outdir . -includeall -ignoremissing -o Entity_wrapper.c entity.i
	cp Entity_wrapper.c $(BUILD_PATH)/BaconBox/Special/Flash/
	mv EntityWrapper.as EntityWrapper.as3
EntityWrapper.abc: EntityWrapper.as3
	@echo "-------- Compile the SWIG wrapper to ABC --------"
	mv EntityWrapper.as3 EntityWrapper.as
	$(AS3COMPILERARGS) -abcfuture -AS3 -import $(call nativepath,$(FLASCC)/usr/lib/builtin.abc) -import $(call nativepath,$(FLASCC)/usr/lib/playerglobal.abc) EntityWrapper.as 
	# rename the output so the compiler doesn't accidentally use both this .as file along with the .abc file we just produced
	mv EntityWrapper.as EntityWrapper.as3


#Entity_wrapper.o main.o: Entity_wrapper.c main.cpp
#	echo $@ --------------------
#	$(CXX) $< -c $(BASE_CFLAGS) -I$(PROJECT_ROOT) -I$(CUSTOM_LIB_PATH)/include -o $@


$(BUILD_PATH)/%.o: %.c
	@echo "-------- BUILD C FILE--------"
	$(CXX) $< -c $(BASE_CFLAGS) -I$(PROJECT_ROOT) -I$(CUSTOM_LIB_PATH)/include -o $@

$(BUILD_PATH)/%.o: %.cpp
	@echo "-------- BUILD CPP FILE--------"
	$(CXX) $< -c $(BASE_CFLAGS) -I$(PROJECT_ROOT) -I$(CUSTOM_LIB_PATH)/include -o $@

$(BUILD_PATH)/build: $(PROJECT_ROOT)/BaconBox
	mkdir $(BUILD_PATH)
	cp -r $(PROJECT_ROOT)/BaconBox $(BUILD_PATH)
	rm $(addsuffix .cpp, $(basename $(addprefix $(BUILD_PATH)/, $(ALL_SOURCES))))

	touch $(BUILD_PATH)/build


check:
	@if [ -d $(FLASCC)/usr/bin ] ; then true ; \
	else echo "Couldn't locate FLASCC sdk directory, please invoke make with \"make FLASCC=/path/to/FLASCC/sdk ...\"" ; exit 1 ; \
	fi

	@if [ -d "$(FLEX)/bin" ] ; then true ; \
	else echo "Couldn't locate Flex sdk directory, please invoke make with \"make FLEX=/path/to/flex  ...\"" ; exit 1 ; \
	fi

clean:
	rm -rf *_wrapper.c *.swf *.swc *.as3 *.abc *.o $(BUILD_PATH) 
#$(addprefix $(PROJECT_ROOT)/, $(BUILD_PATH), $(ALL_SOURCES))



