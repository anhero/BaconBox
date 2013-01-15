#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=MinGW_TDM-Windows
CND_DLIB_EXT=dll
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/1336121725/InputDevice.o \
	${OBJECTDIR}/_ext/955905393/SDLInputManager.o \
	${OBJECTDIR}/_ext/357189265/PointerButtonSignalData.o \
	${OBJECTDIR}/_ext/2054729558/Serializable.o \
	${OBJECTDIR}/_ext/1774422509/KeyboardState.o \
	${OBJECTDIR}/_ext/1343313265/AudioEngine.o \
	${OBJECTDIR}/_ext/1343313265/NullAudio.o \
	${OBJECTDIR}/_ext/1343313265/Sound.o \
	${OBJECTDIR}/_ext/1741434337/SDLKeyboard.o \
	${OBJECTDIR}/_ext/562173845/NullGamePad.o \
	${OBJECTDIR}/_ext/357189265/NullPointer.o \
	${OBJECTDIR}/_ext/357189265/CursorState.o \
	${OBJECTDIR}/_ext/1492834325/Compression.o \
	${OBJECTDIR}/_ext/562173845/GamePad.o \
	${OBJECTDIR}/_ext/1343313265/MusicParameters.o \
	${OBJECTDIR}/_ext/1820289179/SDLMixerBackgroundMusic.o \
	${OBJECTDIR}/_ext/1336121725/InputManager.o \
	${OBJECTDIR}/_ext/401156515/AccelerometerState.o \
	${OBJECTDIR}/_ext/1343313265/MusicInfo.o \
	${OBJECTDIR}/_ext/1013356456/Console.o \
	${OBJECTDIR}/_ext/401156515/Accelerometer.o \
	${OBJECTDIR}/_ext/1343313265/BackgroundMusic.o \
	${OBJECTDIR}/_ext/1820289179/SDLMixerEngine.o \
	${OBJECTDIR}/_ext/1774422509/KeyboardSignalData.o \
	${OBJECTDIR}/_ext/1336121725/InputState.o \
	${OBJECTDIR}/_ext/1086840298/JsonBoxSerializer.o \
	${OBJECTDIR}/_ext/1343313265/MusicEngine.o \
	${OBJECTDIR}/_ext/1619289542/IDManager.o \
	${OBJECTDIR}/_ext/1343313265/SoundParameters.o \
	${OBJECTDIR}/_ext/1492834325/Base64.o \
	${OBJECTDIR}/_ext/1774422509/NullKeyboard.o \
	${OBJECTDIR}/_ext/1343313265/SoundInfo.o \
	${OBJECTDIR}/_ext/1492834325/Random.o \
	${OBJECTDIR}/_ext/100836037/Color.o \
	${OBJECTDIR}/_ext/1492834325/CallHelper.o \
	${OBJECTDIR}/_ext/1357070339/CameraDriverRenderer.o \
	${OBJECTDIR}/_ext/1774422509/KeyMaskSignalData.o \
	${OBJECTDIR}/_ext/1492834325/BitHelper.o \
	${OBJECTDIR}/_ext/401156515/NullAccelerometer.o \
	${OBJECTDIR}/_ext/1492834325/UTFConvert.o \
	${OBJECTDIR}/_ext/1343313265/SoundEngine.o \
	${OBJECTDIR}/_ext/357189265/PointerState.o \
	${OBJECTDIR}/_ext/1492834325/StringHelper.o \
	${OBJECTDIR}/_ext/1774422509/Key.o \
	${OBJECTDIR}/_ext/1492834325/Parser.o \
	${OBJECTDIR}/_ext/1771812190/OpenGLDriver.o \
	${OBJECTDIR}/_ext/777764764/NullGraphicDriver.o \
	${OBJECTDIR}/_ext/1013356456/VertexArray.o \
	${OBJECTDIR}/_ext/1343313265/SoundFX.o \
	${OBJECTDIR}/_ext/562173845/GamePadSignalData.o \
	${OBJECTDIR}/_ext/2054729558/Object.o \
	${OBJECTDIR}/_ext/401156515/AccelerometerSignalData.o \
	${OBJECTDIR}/_ext/1013356456/AxisAlignedBoundingBox.o \
	${OBJECTDIR}/_ext/1492834325/ResourcePathHandler.o \
	${OBJECTDIR}/_ext/1766768538/SignalAnalyzer.o \
	${OBJECTDIR}/_ext/562173845/GamePadThumbstickSignalData.o \
	${OBJECTDIR}/_ext/1619289542/Entity.o \
	${OBJECTDIR}/_ext/1820289179/SDLMixerSoundFX.o \
	${OBJECTDIR}/_ext/1492834325/ShapeFactory.o \
	${OBJECTDIR}/_ext/357189265/Pointer.o \
	${OBJECTDIR}/_ext/1066446308/MovieClipEntity.o \
	${OBJECTDIR}/_ext/1766768538/SignalData.o \
	${OBJECTDIR}/_ext/562173845/GamePadButtonSignalData.o \
	${OBJECTDIR}/_ext/1492834325/Timer.o \
	${OBJECTDIR}/_ext/1313538916/MainWindow.o \
	${OBJECTDIR}/_ext/1619289542/State.o \
	${OBJECTDIR}/_ext/1357070339/Mesh.o \
	${OBJECTDIR}/_ext/1816095337/WindowsTimeHelper.o \
	${OBJECTDIR}/_ext/777764764/GraphicDriver.o \
	${OBJECTDIR}/_ext/2054729558/Value.o \
	${OBJECTDIR}/_ext/1492834325/TimerManager.o \
	${OBJECTDIR}/_ext/2054729558/Array.o \
	${OBJECTDIR}/_ext/1492834325/Stopwatch.o \
	${OBJECTDIR}/_ext/1013356456/StandardVertexArray.o \
	${OBJECTDIR}/_ext/1085075230/TinyXMLSerializer.o \
	${OBJECTDIR}/_ext/1336121725/InputSignalData.o \
	${OBJECTDIR}/_ext/1774422509/Keyboard.o \
	${OBJECTDIR}/_ext/1621708528/SDLMainWindow.o \
	${OBJECTDIR}/_ext/700401247/Font.o \
	${OBJECTDIR}/_ext/588717407/SDLGamePad.o \
	${OBJECTDIR}/_ext/2054729558/DefaultSerializer.o \
	${OBJECTDIR}/_ext/1313538916/NullMainWindow.o \
	${OBJECTDIR}/_ext/1120482205/SDLPointer.o \
	${OBJECTDIR}/_ext/357189265/PointerSignalData.o \
	${OBJECTDIR}/_ext/1013356456/Vector2.o \
	${OBJECTDIR}/_ext/1619289542/Component.o \
	${OBJECTDIR}/_ext/700401247/GlyphInformation.o \
	${OBJECTDIR}/_ext/935822010/FontImplementation.o \
	${OBJECTDIR}/_ext/1357070339/Transform.o \
	${OBJECTDIR}/_ext/1343313265/NullAudioEngine.o \
	${OBJECTDIR}/_ext/1774422509/KeySignalData.o \
	${OBJECTDIR}/_ext/1013356456/ResourceManager.o \
	${OBJECTDIR}/_ext/2054729558/Serializer.o \
	${OBJECTDIR}/_ext/100836037/TextureInformation.o \
	${OBJECTDIR}/_ext/562173845/GamePadState.o \
	${OBJECTDIR}/_ext/100836037/Camera.o \
	${OBJECTDIR}/_ext/1492834325/MathHelper.o \
	${OBJECTDIR}/_ext/1492834325/TimeHelper.o \
	${OBJECTDIR}/_ext/1188383521/OpenGLMeshRenderer.o \
	${OBJECTDIR}/_ext/1766768538/SignalAnalyzerManager.o \
	${OBJECTDIR}/_ext/100836037/PixMap.o \
	${OBJECTDIR}/_ext/1619289542/Engine.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libnetbeans.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libnetbeans.a: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libnetbeans.a
	${AR} -rv ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libnetbeans.a ${OBJECTFILES} 
	$(RANLIB) ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libnetbeans.a

${OBJECTDIR}/_ext/1336121725/InputDevice.o: ../../BaconBox/Input/InputDevice.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1336121725
	${RM} $@.d
	$(COMPILE.cc) -g -DSDL -DTINYXML_USE_STL -DTIXML_USE_STL -I../../ -I../../libraries/MINGW32_NT-6.1/i686/include -I../../BaconBox -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1336121725/InputDevice.o ../../BaconBox/Input/InputDevice.cpp

${OBJECTDIR}/_ext/955905393/SDLInputManager.o: ../../BaconBox/Input/SDL/SDLInputManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/955905393
	${RM} $@.d
	$(COMPILE.cc) -g -DSDL -DTINYXML_USE_STL -DTIXML_USE_STL -I../../ -I../../libraries/MINGW32_NT-6.1/i686/include -I../../BaconBox -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/955905393/SDLInputManager.o ../../BaconBox/Input/SDL/SDLInputManager.cpp

${OBJECTDIR}/_ext/357189265/PointerButtonSignalData.o: ../../BaconBox/Input/Pointer/PointerButtonSignalData.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/357189265
	${RM} $@.d
	$(COMPILE.cc) -g -DSDL -DTINYXML_USE_STL -DTIXML_USE_STL -I../../ -I../../libraries/MINGW32_NT-6.1/i686/include -I../../BaconBox -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/357189265/PointerButtonSignalData.o ../../BaconBox/Input/Pointer/PointerButtonSignalData.cpp

${OBJECTDIR}/_ext/2054729558/Serializable.o: ../../BaconBox/Helper/Serialization/Serializable.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2054729558
	${RM} $@.d
	$(COMPILE.cc) -g -DSDL -DTINYXML_USE_STL -DTIXML_USE_STL -I../../ -I../../libraries/MINGW32_NT-6.1/i686/include -I../../BaconBox -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/2054729558/Serializable.o ../../BaconBox/Helper/Serialization/Serializable.cpp

${OBJECTDIR}/_ext/1774422509/KeyboardState.o: ../../BaconBox/Input/Keyboard/KeyboardState.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1774422509
	${RM} $@.d
	$(COMPILE.cc) -g -DSDL -DTINYXML_USE_STL -DTIXML_USE_STL -I../../ -I../../libraries/MINGW32_NT-6.1/i686/include -I../../BaconBox -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1774422509/KeyboardState.o ../../BaconBox/Input/Keyboard/KeyboardState.cpp

${OBJECTDIR}/_ext/1343313265/AudioEngine.o: ../../BaconBox/Audio/AudioEngine.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1343313265
	${RM} $@.d
	$(COMPILE.cc) -g -DSDL -DTINYXML_USE_STL -DTIXML_USE_STL -I../../ -I../../libraries/MINGW32_NT-6.1/i686/include -I../../BaconBox -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1343313265/AudioEngine.o ../../BaconBox/Audio/AudioEngine.cpp

${OBJECTDIR}/_ext/1343313265/NullAudio.o: ../../BaconBox/Audio/NullAudio.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1343313265
	${RM} $@.d
	$(COMPILE.cc) -g -DSDL -DTINYXML_USE_STL -DTIXML_USE_STL -I../../ -I../../libraries/MINGW32_NT-6.1/i686/include -I../../BaconBox -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1343313265/NullAudio.o ../../BaconBox/Audio/NullAudio.cpp

${OBJECTDIR}/_ext/1343313265/Sound.o: ../../BaconBox/Audio/Sound.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1343313265
	${RM} $@.d
	$(COMPILE.cc) -g -DSDL -DTINYXML_USE_STL -DTIXML_USE_STL -I../../ -I../../libraries/MINGW32_NT-6.1/i686/include -I../../BaconBox -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1343313265/Sound.o ../../BaconBox/Audio/Sound.cpp

${OBJECTDIR}/_ext/1741434337/SDLKeyboard.o: ../../BaconBox/Input/Keyboard/SDL/SDLKeyboard.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1741434337
	${RM} $@.d
	$(COMPILE.cc) -g -DSDL -DTINYXML_USE_STL -DTIXML_USE_STL -I../../ -I../../libraries/MINGW32_NT-6.1/i686/include -I../../BaconBox -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1741434337/SDLKeyboard.o ../../BaconBox/Input/Keyboard/SDL/SDLKeyboard.cpp

${OBJECTDIR}/_ext/562173845/NullGamePad.o: ../../BaconBox/Input/GamePad/NullGamePad.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/562173845
	${RM} $@.d
	$(COMPILE.cc) -g -DSDL -DTINYXML_USE_STL -DTIXML_USE_STL -I../../ -I../../libraries/MINGW32_NT-6.1/i686/include -I../../BaconBox -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/562173845/NullGamePad.o ../../BaconBox/Input/GamePad/NullGamePad.cpp

${OBJECTDIR}/_ext/357189265/NullPointer.o: ../../BaconBox/Input/Pointer/NullPointer.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/357189265
	${RM} $@.d
	$(COMPILE.cc) -g -DSDL -DTINYXML_USE_STL -DTIXML_USE_STL -I../../ -I../../libraries/MINGW32_NT-6.1/i686/include -I../../BaconBox -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/357189265/NullPointer.o ../../BaconBox/Input/Pointer/NullPointer.cpp

${OBJECTDIR}/_ext/357189265/CursorState.o: ../../BaconBox/Input/Pointer/CursorState.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/357189265
	${RM} $@.d
	$(COMPILE.cc) -g -DSDL -DTINYXML_USE_STL -DTIXML_USE_STL -I../../ -I../../libraries/MINGW32_NT-6.1/i686/include -I../../BaconBox -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/357189265/CursorState.o ../../BaconBox/Input/Pointer/CursorState.cpp

${OBJECTDIR}/_ext/1492834325/Compression.o: ../../BaconBox/Helper/Compression.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1492834325
	${RM} $@.d
	$(COMPILE.cc) -g -DSDL -DTINYXML_USE_STL -DTIXML_USE_STL -I../../ -I../../libraries/MINGW32_NT-6.1/i686/include -I../../BaconBox -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1492834325/Compression.o ../../BaconBox/Helper/Compression.cpp

${OBJECTDIR}/_ext/562173845/GamePad.o: ../../BaconBox/Input/GamePad/GamePad.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/562173845
	${RM} $@.d
	$(COMPILE.cc) -g -DSDL -DTINYXML_USE_STL -DTIXML_USE_STL -I../../ -I../../libraries/MINGW32_NT-6.1/i686/include -I../../BaconBox -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/562173845/GamePad.o ../../BaconBox/Input/GamePad/GamePad.cpp

${OBJECTDIR}/_ext/1343313265/MusicParameters.o: ../../BaconBox/Audio/MusicParameters.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1343313265
	${RM} $@.d
	$(COMPILE.cc) -g -DSDL -DTINYXML_USE_STL -DTIXML_USE_STL -I../../ -I../../libraries/MINGW32_NT-6.1/i686/include -I../../BaconBox -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1343313265/MusicParameters.o ../../BaconBox/Audio/MusicParameters.cpp

${OBJECTDIR}/_ext/1820289179/SDLMixerBackgroundMusic.o: ../../BaconBox/Audio/SDL/SDLMixerBackgroundMusic.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1820289179
	${RM} $@.d
	$(COMPILE.cc) -g -DSDL -DTINYXML_USE_STL -DTIXML_USE_STL -I../../ -I../../libraries/MINGW32_NT-6.1/i686/include -I../../BaconBox -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1820289179/SDLMixerBackgroundMusic.o ../../BaconBox/Audio/SDL/SDLMixerBackgroundMusic.cpp

${OBJECTDIR}/_ext/1336121725/InputManager.o: ../../BaconBox/Input/InputManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1336121725
	${RM} $@.d
	$(COMPILE.cc) -g -DSDL -DTINYXML_USE_STL -DTIXML_USE_STL -I../../ -I../../libraries/MINGW32_NT-6.1/i686/include -I../../BaconBox -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1336121725/InputManager.o ../../BaconBox/Input/InputManager.cpp

${OBJECTDIR}/_ext/401156515/AccelerometerState.o: ../../BaconBox/Input/Accelerometer/AccelerometerState.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/401156515
	${RM} $@.d
	$(COMPILE.cc) -g -DSDL -DTINYXML_USE_STL -DTIXML_USE_STL -I../../ -I../../libraries/MINGW32_NT-6.1/i686/include -I../../BaconBox -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/401156515/AccelerometerState.o ../../BaconBox/Input/Accelerometer/AccelerometerState.cpp

${OBJECTDIR}/_ext/1343313265/MusicInfo.o: ../../BaconBox/Audio/MusicInfo.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1343313265
	${RM} $@.d
	$(COMPILE.cc) -g -DSDL -DTINYXML_USE_STL -DTIXML_USE_STL -I../../ -I../../libraries/MINGW32_NT-6.1/i686/include -I../../BaconBox -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1343313265/MusicInfo.o ../../BaconBox/Audio/MusicInfo.cpp

${OBJECTDIR}/_ext/1013356456/Console.o: ../../BaconBox/Console.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1013356456
	${RM} $@.d
	$(COMPILE.cc) -g -DSDL -DTINYXML_USE_STL -DTIXML_USE_STL -I../../ -I../../libraries/MINGW32_NT-6.1/i686/include -I../../BaconBox -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1013356456/Console.o ../../BaconBox/Console.cpp

${OBJECTDIR}/_ext/401156515/Accelerometer.o: ../../BaconBox/Input/Accelerometer/Accelerometer.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/401156515
	${RM} $@.d
	$(COMPILE.cc) -g -DSDL -DTINYXML_USE_STL -DTIXML_USE_STL -I../../ -I../../libraries/MINGW32_NT-6.1/i686/include -I../../BaconBox -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/401156515/Accelerometer.o ../../BaconBox/Input/Accelerometer/Accelerometer.cpp

${OBJECTDIR}/_ext/1343313265/BackgroundMusic.o: ../../BaconBox/Audio/BackgroundMusic.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1343313265
	${RM} $@.d
	$(COMPILE.cc) -g -DSDL -DTINYXML_USE_STL -DTIXML_USE_STL -I../../ -I../../libraries/MINGW32_NT-6.1/i686/include -I../../BaconBox -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1343313265/BackgroundMusic.o ../../BaconBox/Audio/BackgroundMusic.cpp

${OBJECTDIR}/_ext/1820289179/SDLMixerEngine.o: ../../BaconBox/Audio/SDL/SDLMixerEngine.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1820289179
	${RM} $@.d
	$(COMPILE.cc) -g -DSDL -DTINYXML_USE_STL -DTIXML_USE_STL -I../../ -I../../libraries/MINGW32_NT-6.1/i686/include -I../../BaconBox -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1820289179/SDLMixerEngine.o ../../BaconBox/Audio/SDL/SDLMixerEngine.cpp

${OBJECTDIR}/_ext/1774422509/KeyboardSignalData.o: ../../BaconBox/Input/Keyboard/KeyboardSignalData.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1774422509
	${RM} $@.d
	$(COMPILE.cc) -g -DSDL -DTINYXML_USE_STL -DTIXML_USE_STL -I../../ -I../../libraries/MINGW32_NT-6.1/i686/include -I../../BaconBox -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1774422509/KeyboardSignalData.o ../../BaconBox/Input/Keyboard/KeyboardSignalData.cpp

${OBJECTDIR}/_ext/1336121725/InputState.o: ../../BaconBox/Input/InputState.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1336121725
	${RM} $@.d
	$(COMPILE.cc) -g -DSDL -DTINYXML_USE_STL -DTIXML_USE_STL -I../../ -I../../libraries/MINGW32_NT-6.1/i686/include -I../../BaconBox -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1336121725/InputState.o ../../BaconBox/Input/InputState.cpp

${OBJECTDIR}/_ext/1086840298/JsonBoxSerializer.o: ../../BaconBox/Helper/Serialization/JsonBox/JsonBoxSerializer.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1086840298
	${RM} $@.d
	$(COMPILE.cc) -g -DSDL -DTINYXML_USE_STL -DTIXML_USE_STL -I../../ -I../../libraries/MINGW32_NT-6.1/i686/include -I../../BaconBox -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1086840298/JsonBoxSerializer.o ../../BaconBox/Helper/Serialization/JsonBox/JsonBoxSerializer.cpp

${OBJECTDIR}/_ext/1343313265/MusicEngine.o: ../../BaconBox/Audio/MusicEngine.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1343313265
	${RM} $@.d
	$(COMPILE.cc) -g -DSDL -DTINYXML_USE_STL -DTIXML_USE_STL -I../../ -I../../libraries/MINGW32_NT-6.1/i686/include -I../../BaconBox -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1343313265/MusicEngine.o ../../BaconBox/Audio/MusicEngine.cpp

${OBJECTDIR}/_ext/1619289542/IDManager.o: ../../BaconBox/Core/IDManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1619289542
	${RM} $@.d
	$(COMPILE.cc) -g -DSDL -DTINYXML_USE_STL -DTIXML_USE_STL -I../../ -I../../libraries/MINGW32_NT-6.1/i686/include -I../../BaconBox -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1619289542/IDManager.o ../../BaconBox/Core/IDManager.cpp

${OBJECTDIR}/_ext/1343313265/SoundParameters.o: ../../BaconBox/Audio/SoundParameters.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1343313265
	${RM} $@.d
	$(COMPILE.cc) -g -DSDL -DTINYXML_USE_STL -DTIXML_USE_STL -I../../ -I../../libraries/MINGW32_NT-6.1/i686/include -I../../BaconBox -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1343313265/SoundParameters.o ../../BaconBox/Audio/SoundParameters.cpp

${OBJECTDIR}/_ext/1492834325/Base64.o: ../../BaconBox/Helper/Base64.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1492834325
	${RM} $@.d
	$(COMPILE.cc) -g -DSDL -DTINYXML_USE_STL -DTIXML_USE_STL -I../../ -I../../libraries/MINGW32_NT-6.1/i686/include -I../../BaconBox -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1492834325/Base64.o ../../BaconBox/Helper/Base64.cpp

${OBJECTDIR}/_ext/1774422509/NullKeyboard.o: ../../BaconBox/Input/Keyboard/NullKeyboard.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1774422509
	${RM} $@.d
	$(COMPILE.cc) -g -DSDL -DTINYXML_USE_STL -DTIXML_USE_STL -I../../ -I../../libraries/MINGW32_NT-6.1/i686/include -I../../BaconBox -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1774422509/NullKeyboard.o ../../BaconBox/Input/Keyboard/NullKeyboard.cpp

${OBJECTDIR}/_ext/1343313265/SoundInfo.o: ../../BaconBox/Audio/SoundInfo.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1343313265
	${RM} $@.d
	$(COMPILE.cc) -g -DSDL -DTINYXML_USE_STL -DTIXML_USE_STL -I../../ -I../../libraries/MINGW32_NT-6.1/i686/include -I../../BaconBox -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1343313265/SoundInfo.o ../../BaconBox/Audio/SoundInfo.cpp

${OBJECTDIR}/_ext/1492834325/Random.o: ../../BaconBox/Helper/Random.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1492834325
	${RM} $@.d
	$(COMPILE.cc) -g -DSDL -DTINYXML_USE_STL -DTIXML_USE_STL -I../../ -I../../libraries/MINGW32_NT-6.1/i686/include -I../../BaconBox -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1492834325/Random.o ../../BaconBox/Helper/Random.cpp

${OBJECTDIR}/_ext/100836037/Color.o: ../../BaconBox/Display/Color.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/100836037
	${RM} $@.d
	$(COMPILE.cc) -g -DSDL -DTINYXML_USE_STL -DTIXML_USE_STL -I../../ -I../../libraries/MINGW32_NT-6.1/i686/include -I../../BaconBox -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/100836037/Color.o ../../BaconBox/Display/Color.cpp

${OBJECTDIR}/_ext/1492834325/CallHelper.o: ../../BaconBox/Helper/CallHelper.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1492834325
	${RM} $@.d
	$(COMPILE.cc) -g -DSDL -DTINYXML_USE_STL -DTIXML_USE_STL -I../../ -I../../libraries/MINGW32_NT-6.1/i686/include -I../../BaconBox -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1492834325/CallHelper.o ../../BaconBox/Helper/CallHelper.cpp

${OBJECTDIR}/_ext/1357070339/CameraDriverRenderer.o: ../../BaconBox/Components/CameraDriverRenderer.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1357070339
	${RM} $@.d
	$(COMPILE.cc) -g -DSDL -DTINYXML_USE_STL -DTIXML_USE_STL -I../../ -I../../libraries/MINGW32_NT-6.1/i686/include -I../../BaconBox -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1357070339/CameraDriverRenderer.o ../../BaconBox/Components/CameraDriverRenderer.cpp

${OBJECTDIR}/_ext/1774422509/KeyMaskSignalData.o: ../../BaconBox/Input/Keyboard/KeyMaskSignalData.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1774422509
	${RM} $@.d
	$(COMPILE.cc) -g -DSDL -DTINYXML_USE_STL -DTIXML_USE_STL -I../../ -I../../libraries/MINGW32_NT-6.1/i686/include -I../../BaconBox -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1774422509/KeyMaskSignalData.o ../../BaconBox/Input/Keyboard/KeyMaskSignalData.cpp

${OBJECTDIR}/_ext/1492834325/BitHelper.o: ../../BaconBox/Helper/BitHelper.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1492834325
	${RM} $@.d
	$(COMPILE.cc) -g -DSDL -DTINYXML_USE_STL -DTIXML_USE_STL -I../../ -I../../libraries/MINGW32_NT-6.1/i686/include -I../../BaconBox -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1492834325/BitHelper.o ../../BaconBox/Helper/BitHelper.cpp

${OBJECTDIR}/_ext/401156515/NullAccelerometer.o: ../../BaconBox/Input/Accelerometer/NullAccelerometer.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/401156515
	${RM} $@.d
	$(COMPILE.cc) -g -DSDL -DTINYXML_USE_STL -DTIXML_USE_STL -I../../ -I../../libraries/MINGW32_NT-6.1/i686/include -I../../BaconBox -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/401156515/NullAccelerometer.o ../../BaconBox/Input/Accelerometer/NullAccelerometer.cpp

${OBJECTDIR}/_ext/1492834325/UTFConvert.o: ../../BaconBox/Helper/UTFConvert.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1492834325
	${RM} $@.d
	$(COMPILE.cc) -g -DSDL -DTINYXML_USE_STL -DTIXML_USE_STL -I../../ -I../../libraries/MINGW32_NT-6.1/i686/include -I../../BaconBox -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1492834325/UTFConvert.o ../../BaconBox/Helper/UTFConvert.cpp

${OBJECTDIR}/_ext/1343313265/SoundEngine.o: ../../BaconBox/Audio/SoundEngine.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1343313265
	${RM} $@.d
	$(COMPILE.cc) -g -DSDL -DTINYXML_USE_STL -DTIXML_USE_STL -I../../ -I../../libraries/MINGW32_NT-6.1/i686/include -I../../BaconBox -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1343313265/SoundEngine.o ../../BaconBox/Audio/SoundEngine.cpp

${OBJECTDIR}/_ext/357189265/PointerState.o: ../../BaconBox/Input/Pointer/PointerState.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/357189265
	${RM} $@.d
	$(COMPILE.cc) -g -DSDL -DTINYXML_USE_STL -DTIXML_USE_STL -I../../ -I../../libraries/MINGW32_NT-6.1/i686/include -I../../BaconBox -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/357189265/PointerState.o ../../BaconBox/Input/Pointer/PointerState.cpp

${OBJECTDIR}/_ext/1492834325/StringHelper.o: ../../BaconBox/Helper/StringHelper.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1492834325
	${RM} $@.d
	$(COMPILE.cc) -g -DSDL -DTINYXML_USE_STL -DTIXML_USE_STL -I../../ -I../../libraries/MINGW32_NT-6.1/i686/include -I../../BaconBox -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1492834325/StringHelper.o ../../BaconBox/Helper/StringHelper.cpp

${OBJECTDIR}/_ext/1774422509/Key.o: ../../BaconBox/Input/Keyboard/Key.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1774422509
	${RM} $@.d
	$(COMPILE.cc) -g -DSDL -DTINYXML_USE_STL -DTIXML_USE_STL -I../../ -I../../libraries/MINGW32_NT-6.1/i686/include -I../../BaconBox -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1774422509/Key.o ../../BaconBox/Input/Keyboard/Key.cpp

${OBJECTDIR}/_ext/1492834325/Parser.o: ../../BaconBox/Helper/Parser.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1492834325
	${RM} $@.d
	$(COMPILE.cc) -g -DSDL -DTINYXML_USE_STL -DTIXML_USE_STL -I../../ -I../../libraries/MINGW32_NT-6.1/i686/include -I../../BaconBox -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1492834325/Parser.o ../../BaconBox/Helper/Parser.cpp

${OBJECTDIR}/_ext/1771812190/OpenGLDriver.o: ../../BaconBox/Display/Driver/OpenGL/OpenGLDriver.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1771812190
	${RM} $@.d
	$(COMPILE.cc) -g -DSDL -DTINYXML_USE_STL -DTIXML_USE_STL -I../../ -I../../libraries/MINGW32_NT-6.1/i686/include -I../../BaconBox -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1771812190/OpenGLDriver.o ../../BaconBox/Display/Driver/OpenGL/OpenGLDriver.cpp

${OBJECTDIR}/_ext/777764764/NullGraphicDriver.o: ../../BaconBox/Display/Driver/NullGraphicDriver.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/777764764
	${RM} $@.d
	$(COMPILE.cc) -g -DSDL -DTINYXML_USE_STL -DTIXML_USE_STL -I../../ -I../../libraries/MINGW32_NT-6.1/i686/include -I../../BaconBox -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/777764764/NullGraphicDriver.o ../../BaconBox/Display/Driver/NullGraphicDriver.cpp

${OBJECTDIR}/_ext/1013356456/VertexArray.o: ../../BaconBox/VertexArray.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1013356456
	${RM} $@.d
	$(COMPILE.cc) -g -DSDL -DTINYXML_USE_STL -DTIXML_USE_STL -I../../ -I../../libraries/MINGW32_NT-6.1/i686/include -I../../BaconBox -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1013356456/VertexArray.o ../../BaconBox/VertexArray.cpp

${OBJECTDIR}/_ext/1343313265/SoundFX.o: ../../BaconBox/Audio/SoundFX.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1343313265
	${RM} $@.d
	$(COMPILE.cc) -g -DSDL -DTINYXML_USE_STL -DTIXML_USE_STL -I../../ -I../../libraries/MINGW32_NT-6.1/i686/include -I../../BaconBox -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1343313265/SoundFX.o ../../BaconBox/Audio/SoundFX.cpp

${OBJECTDIR}/_ext/562173845/GamePadSignalData.o: ../../BaconBox/Input/GamePad/GamePadSignalData.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/562173845
	${RM} $@.d
	$(COMPILE.cc) -g -DSDL -DTINYXML_USE_STL -DTIXML_USE_STL -I../../ -I../../libraries/MINGW32_NT-6.1/i686/include -I../../BaconBox -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/562173845/GamePadSignalData.o ../../BaconBox/Input/GamePad/GamePadSignalData.cpp

${OBJECTDIR}/_ext/2054729558/Object.o: ../../BaconBox/Helper/Serialization/Object.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2054729558
	${RM} $@.d
	$(COMPILE.cc) -g -DSDL -DTINYXML_USE_STL -DTIXML_USE_STL -I../../ -I../../libraries/MINGW32_NT-6.1/i686/include -I../../BaconBox -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/2054729558/Object.o ../../BaconBox/Helper/Serialization/Object.cpp

${OBJECTDIR}/_ext/401156515/AccelerometerSignalData.o: ../../BaconBox/Input/Accelerometer/AccelerometerSignalData.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/401156515
	${RM} $@.d
	$(COMPILE.cc) -g -DSDL -DTINYXML_USE_STL -DTIXML_USE_STL -I../../ -I../../libraries/MINGW32_NT-6.1/i686/include -I../../BaconBox -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/401156515/AccelerometerSignalData.o ../../BaconBox/Input/Accelerometer/AccelerometerSignalData.cpp

${OBJECTDIR}/_ext/1013356456/AxisAlignedBoundingBox.o: ../../BaconBox/AxisAlignedBoundingBox.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1013356456
	${RM} $@.d
	$(COMPILE.cc) -g -DSDL -DTINYXML_USE_STL -DTIXML_USE_STL -I../../ -I../../libraries/MINGW32_NT-6.1/i686/include -I../../BaconBox -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1013356456/AxisAlignedBoundingBox.o ../../BaconBox/AxisAlignedBoundingBox.cpp

${OBJECTDIR}/_ext/1492834325/ResourcePathHandler.o: ../../BaconBox/Helper/ResourcePathHandler.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1492834325
	${RM} $@.d
	$(COMPILE.cc) -g -DSDL -DTINYXML_USE_STL -DTIXML_USE_STL -I../../ -I../../libraries/MINGW32_NT-6.1/i686/include -I../../BaconBox -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1492834325/ResourcePathHandler.o ../../BaconBox/Helper/ResourcePathHandler.cpp

${OBJECTDIR}/_ext/1766768538/SignalAnalyzer.o: ../../BaconBox/SignalSlots/SignalAnalyzer.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1766768538
	${RM} $@.d
	$(COMPILE.cc) -g -DSDL -DTINYXML_USE_STL -DTIXML_USE_STL -I../../ -I../../libraries/MINGW32_NT-6.1/i686/include -I../../BaconBox -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1766768538/SignalAnalyzer.o ../../BaconBox/SignalSlots/SignalAnalyzer.cpp

${OBJECTDIR}/_ext/562173845/GamePadThumbstickSignalData.o: ../../BaconBox/Input/GamePad/GamePadThumbstickSignalData.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/562173845
	${RM} $@.d
	$(COMPILE.cc) -g -DSDL -DTINYXML_USE_STL -DTIXML_USE_STL -I../../ -I../../libraries/MINGW32_NT-6.1/i686/include -I../../BaconBox -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/562173845/GamePadThumbstickSignalData.o ../../BaconBox/Input/GamePad/GamePadThumbstickSignalData.cpp

${OBJECTDIR}/_ext/1619289542/Entity.o: ../../BaconBox/Core/Entity.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1619289542
	${RM} $@.d
	$(COMPILE.cc) -g -DSDL -DTINYXML_USE_STL -DTIXML_USE_STL -I../../ -I../../libraries/MINGW32_NT-6.1/i686/include -I../../BaconBox -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1619289542/Entity.o ../../BaconBox/Core/Entity.cpp

${OBJECTDIR}/_ext/1820289179/SDLMixerSoundFX.o: ../../BaconBox/Audio/SDL/SDLMixerSoundFX.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1820289179
	${RM} $@.d
	$(COMPILE.cc) -g -DSDL -DTINYXML_USE_STL -DTIXML_USE_STL -I../../ -I../../libraries/MINGW32_NT-6.1/i686/include -I../../BaconBox -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1820289179/SDLMixerSoundFX.o ../../BaconBox/Audio/SDL/SDLMixerSoundFX.cpp

${OBJECTDIR}/_ext/1492834325/ShapeFactory.o: ../../BaconBox/Helper/ShapeFactory.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1492834325
	${RM} $@.d
	$(COMPILE.cc) -g -DSDL -DTINYXML_USE_STL -DTIXML_USE_STL -I../../ -I../../libraries/MINGW32_NT-6.1/i686/include -I../../BaconBox -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1492834325/ShapeFactory.o ../../BaconBox/Helper/ShapeFactory.cpp

${OBJECTDIR}/_ext/357189265/Pointer.o: ../../BaconBox/Input/Pointer/Pointer.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/357189265
	${RM} $@.d
	$(COMPILE.cc) -g -DSDL -DTINYXML_USE_STL -DTIXML_USE_STL -I../../ -I../../libraries/MINGW32_NT-6.1/i686/include -I../../BaconBox -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/357189265/Pointer.o ../../BaconBox/Input/Pointer/Pointer.cpp

${OBJECTDIR}/_ext/1066446308/MovieClipEntity.o: ../../BaconBox/MovieClipEntity/MovieClipEntity.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1066446308
	${RM} $@.d
	$(COMPILE.cc) -g -DSDL -DTINYXML_USE_STL -DTIXML_USE_STL -I../../ -I../../libraries/MINGW32_NT-6.1/i686/include -I../../BaconBox -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1066446308/MovieClipEntity.o ../../BaconBox/MovieClipEntity/MovieClipEntity.cpp

${OBJECTDIR}/_ext/1766768538/SignalData.o: ../../BaconBox/SignalSlots/SignalData.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1766768538
	${RM} $@.d
	$(COMPILE.cc) -g -DSDL -DTINYXML_USE_STL -DTIXML_USE_STL -I../../ -I../../libraries/MINGW32_NT-6.1/i686/include -I../../BaconBox -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1766768538/SignalData.o ../../BaconBox/SignalSlots/SignalData.cpp

${OBJECTDIR}/_ext/562173845/GamePadButtonSignalData.o: ../../BaconBox/Input/GamePad/GamePadButtonSignalData.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/562173845
	${RM} $@.d
	$(COMPILE.cc) -g -DSDL -DTINYXML_USE_STL -DTIXML_USE_STL -I../../ -I../../libraries/MINGW32_NT-6.1/i686/include -I../../BaconBox -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/562173845/GamePadButtonSignalData.o ../../BaconBox/Input/GamePad/GamePadButtonSignalData.cpp

${OBJECTDIR}/_ext/1492834325/Timer.o: ../../BaconBox/Helper/Timer.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1492834325
	${RM} $@.d
	$(COMPILE.cc) -g -DSDL -DTINYXML_USE_STL -DTIXML_USE_STL -I../../ -I../../libraries/MINGW32_NT-6.1/i686/include -I../../BaconBox -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1492834325/Timer.o ../../BaconBox/Helper/Timer.cpp

${OBJECTDIR}/_ext/1313538916/MainWindow.o: ../../BaconBox/Display/Window/MainWindow.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1313538916
	${RM} $@.d
	$(COMPILE.cc) -g -DSDL -DTINYXML_USE_STL -DTIXML_USE_STL -I../../ -I../../libraries/MINGW32_NT-6.1/i686/include -I../../BaconBox -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1313538916/MainWindow.o ../../BaconBox/Display/Window/MainWindow.cpp

${OBJECTDIR}/_ext/1619289542/State.o: ../../BaconBox/Core/State.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1619289542
	${RM} $@.d
	$(COMPILE.cc) -g -DSDL -DTINYXML_USE_STL -DTIXML_USE_STL -I../../ -I../../libraries/MINGW32_NT-6.1/i686/include -I../../BaconBox -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1619289542/State.o ../../BaconBox/Core/State.cpp

${OBJECTDIR}/_ext/1357070339/Mesh.o: ../../BaconBox/Components/Mesh.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1357070339
	${RM} $@.d
	$(COMPILE.cc) -g -DSDL -DTINYXML_USE_STL -DTIXML_USE_STL -I../../ -I../../libraries/MINGW32_NT-6.1/i686/include -I../../BaconBox -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1357070339/Mesh.o ../../BaconBox/Components/Mesh.cpp

${OBJECTDIR}/_ext/1816095337/WindowsTimeHelper.o: ../../BaconBox/Helper/Windows/WindowsTimeHelper.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1816095337
	${RM} $@.d
	$(COMPILE.cc) -g -DSDL -DTINYXML_USE_STL -DTIXML_USE_STL -I../../ -I../../libraries/MINGW32_NT-6.1/i686/include -I../../BaconBox -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1816095337/WindowsTimeHelper.o ../../BaconBox/Helper/Windows/WindowsTimeHelper.cpp

${OBJECTDIR}/_ext/777764764/GraphicDriver.o: ../../BaconBox/Display/Driver/GraphicDriver.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/777764764
	${RM} $@.d
	$(COMPILE.cc) -g -DSDL -DTINYXML_USE_STL -DTIXML_USE_STL -I../../ -I../../libraries/MINGW32_NT-6.1/i686/include -I../../BaconBox -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/777764764/GraphicDriver.o ../../BaconBox/Display/Driver/GraphicDriver.cpp

${OBJECTDIR}/_ext/2054729558/Value.o: ../../BaconBox/Helper/Serialization/Value.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2054729558
	${RM} $@.d
	$(COMPILE.cc) -g -DSDL -DTINYXML_USE_STL -DTIXML_USE_STL -I../../ -I../../libraries/MINGW32_NT-6.1/i686/include -I../../BaconBox -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/2054729558/Value.o ../../BaconBox/Helper/Serialization/Value.cpp

${OBJECTDIR}/_ext/1492834325/TimerManager.o: ../../BaconBox/Helper/TimerManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1492834325
	${RM} $@.d
	$(COMPILE.cc) -g -DSDL -DTINYXML_USE_STL -DTIXML_USE_STL -I../../ -I../../libraries/MINGW32_NT-6.1/i686/include -I../../BaconBox -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1492834325/TimerManager.o ../../BaconBox/Helper/TimerManager.cpp

${OBJECTDIR}/_ext/2054729558/Array.o: ../../BaconBox/Helper/Serialization/Array.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2054729558
	${RM} $@.d
	$(COMPILE.cc) -g -DSDL -DTINYXML_USE_STL -DTIXML_USE_STL -I../../ -I../../libraries/MINGW32_NT-6.1/i686/include -I../../BaconBox -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/2054729558/Array.o ../../BaconBox/Helper/Serialization/Array.cpp

${OBJECTDIR}/_ext/1492834325/Stopwatch.o: ../../BaconBox/Helper/Stopwatch.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1492834325
	${RM} $@.d
	$(COMPILE.cc) -g -DSDL -DTINYXML_USE_STL -DTIXML_USE_STL -I../../ -I../../libraries/MINGW32_NT-6.1/i686/include -I../../BaconBox -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1492834325/Stopwatch.o ../../BaconBox/Helper/Stopwatch.cpp

${OBJECTDIR}/_ext/1013356456/StandardVertexArray.o: ../../BaconBox/StandardVertexArray.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1013356456
	${RM} $@.d
	$(COMPILE.cc) -g -DSDL -DTINYXML_USE_STL -DTIXML_USE_STL -I../../ -I../../libraries/MINGW32_NT-6.1/i686/include -I../../BaconBox -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1013356456/StandardVertexArray.o ../../BaconBox/StandardVertexArray.cpp

${OBJECTDIR}/_ext/1085075230/TinyXMLSerializer.o: ../../BaconBox/Helper/Serialization/TinyXML/TinyXMLSerializer.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1085075230
	${RM} $@.d
	$(COMPILE.cc) -g -DSDL -DTINYXML_USE_STL -DTIXML_USE_STL -I../../ -I../../libraries/MINGW32_NT-6.1/i686/include -I../../BaconBox -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1085075230/TinyXMLSerializer.o ../../BaconBox/Helper/Serialization/TinyXML/TinyXMLSerializer.cpp

${OBJECTDIR}/_ext/1336121725/InputSignalData.o: ../../BaconBox/Input/InputSignalData.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1336121725
	${RM} $@.d
	$(COMPILE.cc) -g -DSDL -DTINYXML_USE_STL -DTIXML_USE_STL -I../../ -I../../libraries/MINGW32_NT-6.1/i686/include -I../../BaconBox -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1336121725/InputSignalData.o ../../BaconBox/Input/InputSignalData.cpp

${OBJECTDIR}/_ext/1774422509/Keyboard.o: ../../BaconBox/Input/Keyboard/Keyboard.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1774422509
	${RM} $@.d
	$(COMPILE.cc) -g -DSDL -DTINYXML_USE_STL -DTIXML_USE_STL -I../../ -I../../libraries/MINGW32_NT-6.1/i686/include -I../../BaconBox -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1774422509/Keyboard.o ../../BaconBox/Input/Keyboard/Keyboard.cpp

${OBJECTDIR}/_ext/1621708528/SDLMainWindow.o: ../../BaconBox/Display/Window/SDL/SDLMainWindow.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1621708528
	${RM} $@.d
	$(COMPILE.cc) -g -DSDL -DTINYXML_USE_STL -DTIXML_USE_STL -I../../ -I../../libraries/MINGW32_NT-6.1/i686/include -I../../BaconBox -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1621708528/SDLMainWindow.o ../../BaconBox/Display/Window/SDL/SDLMainWindow.cpp

${OBJECTDIR}/_ext/700401247/Font.o: ../../BaconBox/Display/Text/Font.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/700401247
	${RM} $@.d
	$(COMPILE.cc) -g -DSDL -DTINYXML_USE_STL -DTIXML_USE_STL -I../../ -I../../libraries/MINGW32_NT-6.1/i686/include -I../../BaconBox -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/700401247/Font.o ../../BaconBox/Display/Text/Font.cpp

${OBJECTDIR}/_ext/588717407/SDLGamePad.o: ../../BaconBox/Input/GamePad/SDL/SDLGamePad.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/588717407
	${RM} $@.d
	$(COMPILE.cc) -g -DSDL -DTINYXML_USE_STL -DTIXML_USE_STL -I../../ -I../../libraries/MINGW32_NT-6.1/i686/include -I../../BaconBox -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/588717407/SDLGamePad.o ../../BaconBox/Input/GamePad/SDL/SDLGamePad.cpp

${OBJECTDIR}/_ext/2054729558/DefaultSerializer.o: ../../BaconBox/Helper/Serialization/DefaultSerializer.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2054729558
	${RM} $@.d
	$(COMPILE.cc) -g -DSDL -DTINYXML_USE_STL -DTIXML_USE_STL -I../../ -I../../libraries/MINGW32_NT-6.1/i686/include -I../../BaconBox -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/2054729558/DefaultSerializer.o ../../BaconBox/Helper/Serialization/DefaultSerializer.cpp

${OBJECTDIR}/_ext/1313538916/NullMainWindow.o: ../../BaconBox/Display/Window/NullMainWindow.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1313538916
	${RM} $@.d
	$(COMPILE.cc) -g -DSDL -DTINYXML_USE_STL -DTIXML_USE_STL -I../../ -I../../libraries/MINGW32_NT-6.1/i686/include -I../../BaconBox -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1313538916/NullMainWindow.o ../../BaconBox/Display/Window/NullMainWindow.cpp

${OBJECTDIR}/_ext/1120482205/SDLPointer.o: ../../BaconBox/Input/Pointer/SDL/SDLPointer.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1120482205
	${RM} $@.d
	$(COMPILE.cc) -g -DSDL -DTINYXML_USE_STL -DTIXML_USE_STL -I../../ -I../../libraries/MINGW32_NT-6.1/i686/include -I../../BaconBox -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1120482205/SDLPointer.o ../../BaconBox/Input/Pointer/SDL/SDLPointer.cpp

${OBJECTDIR}/_ext/357189265/PointerSignalData.o: ../../BaconBox/Input/Pointer/PointerSignalData.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/357189265
	${RM} $@.d
	$(COMPILE.cc) -g -DSDL -DTINYXML_USE_STL -DTIXML_USE_STL -I../../ -I../../libraries/MINGW32_NT-6.1/i686/include -I../../BaconBox -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/357189265/PointerSignalData.o ../../BaconBox/Input/Pointer/PointerSignalData.cpp

${OBJECTDIR}/_ext/1013356456/Vector2.o: ../../BaconBox/Vector2.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1013356456
	${RM} $@.d
	$(COMPILE.cc) -g -DSDL -DTINYXML_USE_STL -DTIXML_USE_STL -I../../ -I../../libraries/MINGW32_NT-6.1/i686/include -I../../BaconBox -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1013356456/Vector2.o ../../BaconBox/Vector2.cpp

${OBJECTDIR}/_ext/1619289542/Component.o: ../../BaconBox/Core/Component.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1619289542
	${RM} $@.d
	$(COMPILE.cc) -g -DSDL -DTINYXML_USE_STL -DTIXML_USE_STL -I../../ -I../../libraries/MINGW32_NT-6.1/i686/include -I../../BaconBox -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1619289542/Component.o ../../BaconBox/Core/Component.cpp

${OBJECTDIR}/_ext/700401247/GlyphInformation.o: ../../BaconBox/Display/Text/GlyphInformation.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/700401247
	${RM} $@.d
	$(COMPILE.cc) -g -DSDL -DTINYXML_USE_STL -DTIXML_USE_STL -I../../ -I../../libraries/MINGW32_NT-6.1/i686/include -I../../BaconBox -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/700401247/GlyphInformation.o ../../BaconBox/Display/Text/GlyphInformation.cpp

${OBJECTDIR}/_ext/935822010/FontImplementation.o: ../../BaconBox/Display/Text/FreetypeImplementation/FontImplementation.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/935822010
	${RM} $@.d
	$(COMPILE.cc) -g -DSDL -DTINYXML_USE_STL -DTIXML_USE_STL -I../../ -I../../libraries/MINGW32_NT-6.1/i686/include -I../../BaconBox -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/935822010/FontImplementation.o ../../BaconBox/Display/Text/FreetypeImplementation/FontImplementation.cpp

${OBJECTDIR}/_ext/1357070339/Transform.o: ../../BaconBox/Components/Transform.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1357070339
	${RM} $@.d
	$(COMPILE.cc) -g -DSDL -DTINYXML_USE_STL -DTIXML_USE_STL -I../../ -I../../libraries/MINGW32_NT-6.1/i686/include -I../../BaconBox -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1357070339/Transform.o ../../BaconBox/Components/Transform.cpp

${OBJECTDIR}/_ext/1343313265/NullAudioEngine.o: ../../BaconBox/Audio/NullAudioEngine.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1343313265
	${RM} $@.d
	$(COMPILE.cc) -g -DSDL -DTINYXML_USE_STL -DTIXML_USE_STL -I../../ -I../../libraries/MINGW32_NT-6.1/i686/include -I../../BaconBox -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1343313265/NullAudioEngine.o ../../BaconBox/Audio/NullAudioEngine.cpp

${OBJECTDIR}/_ext/1774422509/KeySignalData.o: ../../BaconBox/Input/Keyboard/KeySignalData.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1774422509
	${RM} $@.d
	$(COMPILE.cc) -g -DSDL -DTINYXML_USE_STL -DTIXML_USE_STL -I../../ -I../../libraries/MINGW32_NT-6.1/i686/include -I../../BaconBox -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1774422509/KeySignalData.o ../../BaconBox/Input/Keyboard/KeySignalData.cpp

${OBJECTDIR}/_ext/1013356456/ResourceManager.o: ../../BaconBox/ResourceManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1013356456
	${RM} $@.d
	$(COMPILE.cc) -g -DSDL -DTINYXML_USE_STL -DTIXML_USE_STL -I../../ -I../../libraries/MINGW32_NT-6.1/i686/include -I../../BaconBox -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1013356456/ResourceManager.o ../../BaconBox/ResourceManager.cpp

${OBJECTDIR}/_ext/2054729558/Serializer.o: ../../BaconBox/Helper/Serialization/Serializer.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2054729558
	${RM} $@.d
	$(COMPILE.cc) -g -DSDL -DTINYXML_USE_STL -DTIXML_USE_STL -I../../ -I../../libraries/MINGW32_NT-6.1/i686/include -I../../BaconBox -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/2054729558/Serializer.o ../../BaconBox/Helper/Serialization/Serializer.cpp

${OBJECTDIR}/_ext/100836037/TextureInformation.o: ../../BaconBox/Display/TextureInformation.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/100836037
	${RM} $@.d
	$(COMPILE.cc) -g -DSDL -DTINYXML_USE_STL -DTIXML_USE_STL -I../../ -I../../libraries/MINGW32_NT-6.1/i686/include -I../../BaconBox -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/100836037/TextureInformation.o ../../BaconBox/Display/TextureInformation.cpp

${OBJECTDIR}/_ext/562173845/GamePadState.o: ../../BaconBox/Input/GamePad/GamePadState.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/562173845
	${RM} $@.d
	$(COMPILE.cc) -g -DSDL -DTINYXML_USE_STL -DTIXML_USE_STL -I../../ -I../../libraries/MINGW32_NT-6.1/i686/include -I../../BaconBox -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/562173845/GamePadState.o ../../BaconBox/Input/GamePad/GamePadState.cpp

${OBJECTDIR}/_ext/100836037/Camera.o: ../../BaconBox/Display/Camera.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/100836037
	${RM} $@.d
	$(COMPILE.cc) -g -DSDL -DTINYXML_USE_STL -DTIXML_USE_STL -I../../ -I../../libraries/MINGW32_NT-6.1/i686/include -I../../BaconBox -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/100836037/Camera.o ../../BaconBox/Display/Camera.cpp

${OBJECTDIR}/_ext/1492834325/MathHelper.o: ../../BaconBox/Helper/MathHelper.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1492834325
	${RM} $@.d
	$(COMPILE.cc) -g -DSDL -DTINYXML_USE_STL -DTIXML_USE_STL -I../../ -I../../libraries/MINGW32_NT-6.1/i686/include -I../../BaconBox -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1492834325/MathHelper.o ../../BaconBox/Helper/MathHelper.cpp

${OBJECTDIR}/_ext/1492834325/TimeHelper.o: ../../BaconBox/Helper/TimeHelper.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1492834325
	${RM} $@.d
	$(COMPILE.cc) -g -DSDL -DTINYXML_USE_STL -DTIXML_USE_STL -I../../ -I../../libraries/MINGW32_NT-6.1/i686/include -I../../BaconBox -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1492834325/TimeHelper.o ../../BaconBox/Helper/TimeHelper.cpp

${OBJECTDIR}/_ext/1188383521/OpenGLMeshRenderer.o: ../../BaconBox/Components/OpenGL/OpenGLMeshRenderer.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1188383521
	${RM} $@.d
	$(COMPILE.cc) -g -DSDL -DTINYXML_USE_STL -DTIXML_USE_STL -I../../ -I../../libraries/MINGW32_NT-6.1/i686/include -I../../BaconBox -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1188383521/OpenGLMeshRenderer.o ../../BaconBox/Components/OpenGL/OpenGLMeshRenderer.cpp

${OBJECTDIR}/_ext/1766768538/SignalAnalyzerManager.o: ../../BaconBox/SignalSlots/SignalAnalyzerManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1766768538
	${RM} $@.d
	$(COMPILE.cc) -g -DSDL -DTINYXML_USE_STL -DTIXML_USE_STL -I../../ -I../../libraries/MINGW32_NT-6.1/i686/include -I../../BaconBox -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1766768538/SignalAnalyzerManager.o ../../BaconBox/SignalSlots/SignalAnalyzerManager.cpp

${OBJECTDIR}/_ext/100836037/PixMap.o: ../../BaconBox/Display/PixMap.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/100836037
	${RM} $@.d
	$(COMPILE.cc) -g -DSDL -DTINYXML_USE_STL -DTIXML_USE_STL -I../../ -I../../libraries/MINGW32_NT-6.1/i686/include -I../../BaconBox -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/100836037/PixMap.o ../../BaconBox/Display/PixMap.cpp

${OBJECTDIR}/_ext/1619289542/Engine.o: ../../BaconBox/Core/Engine.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1619289542
	${RM} $@.d
	$(COMPILE.cc) -g -DSDL -DTINYXML_USE_STL -DTIXML_USE_STL -I../../ -I../../libraries/MINGW32_NT-6.1/i686/include -I../../BaconBox -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1619289542/Engine.o ../../BaconBox/Core/Engine.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libnetbeans.a

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
