all: check

	@echo "-------- SWIG wrappers --------"
	"$(FLASCC)/usr/bin/swig" -as3 -c++ -module EntityWrapper -outdir . -includeall -ignoremissing -o Entity_wrapper.c entity.i

	@echo "-------- Compile the SWIG wrapper to ABC --------"
	$(AS3COMPILERARGS) -abcfuture -AS3 -import $(call nativepath,$(FLASCC)/usr/lib/builtin.abc) -import $(call nativepath,$(FLASCC)/usr/lib/playerglobal.abc) EntityWrapper.as 
	# rename the output so the compiler doesn't accidentally use both this .as file along with the .abc file we just produced
	mv EntityWrapper.as EntityWrapper.as3



	@echo "-------- BaconBox --------"
	"$(FLASCC)/usr/bin/g++" $(BASE_CFLAGS) -DBB_FLASH_PLATEFORM EntityWrapper.abc Entity_wrapper.c ../../Core/IDManager.cpp ../../Core/Component.cpp ../../Core/Entity.cpp ../../MovieClipEntity/MovieClipEntity.cpp ../../MovieClipEntity/Flash/MovieClipHolder.cpp main.cpp -emit-swc=temp -o temp.swc -lFlash++ -lAS3++

	@echo "-------- Compile EntityMovieClip --------"
	"$(FLEX)/bin/compc" -include-libraries=temp.swc -include-classes=EntityHolderMovieClip -source-path . -debug=true -o BaconBox.swc

FLASCC:=X
FLEX:=X
AS3COMPILER:=asc2.jar
BASE_CFLAGS:=-Werror -Wno-write-strings -Wno-trigraphs

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

check:
	@if [ -d $(FLASCC)/usr/bin ] ; then true ; \
	else echo "Couldn't locate FLASCC sdk directory, please invoke make with \"make FLASCC=/path/to/FLASCC/sdk ...\"" ; exit 1 ; \
	fi

	@if [ -d "$(FLEX)/bin" ] ; then true ; \
	else echo "Couldn't locate Flex sdk directory, please invoke make with \"make FLEX=/path/to/flex  ...\"" ; exit 1 ; \
	fi

clean:
	rm -f *_wrapper.c *.swf *.swc *.as3 *.abc



