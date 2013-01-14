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
CC=gcc.exe
CCC=g++.exe
CXX=g++.exe
FC=gfortran
AS=as.exe

# Macros
CND_PLATFORM=MinGW-Windows
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
	${OBJECTDIR}/_ext/58131762/main.o


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
LDLIBSOPTIONS=-L../../../../libraries/MINGW32_NT-6.1/i686/lib ../../../../ide/netbeans/dist/Debug/MinGW_TDM-Windows/libnetbeans.a -lopengl32 -lglu32 -lJsonBox -lSDL2_mixer -lSDL2 -lSDL2main -lfreetype -logg -lpng -ltinyxml -lvorbis -lvorbisenc -lvorbisfile -lz -lOle32 -lImm32 -lVersion -lMSVCRT -lKernel32 -lwinmm -lGdi32 -lUUID -lOleAut32

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/maintest.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/maintest.exe: ../../../../ide/netbeans/dist/Debug/MinGW_TDM-Windows/libnetbeans.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/maintest.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	g++.exe -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/maintest ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/_ext/58131762/main.o: /C/Workspace/EntityBB/Test/MainTest/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/58131762
	${RM} $@.d
	$(COMPILE.cc) -g -DSDL -DTINYXML_USE_STL -DTIXML_USE_STL -I../../../.. -I../../../../libraries/MINGW32_NT-6.1/i686/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/58131762/main.o /C/Workspace/EntityBB/Test/MainTest/main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/maintest.exe

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
