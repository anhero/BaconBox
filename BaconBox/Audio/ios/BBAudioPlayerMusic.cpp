#include "BaconBox/Audio/ios/BBAudioPlayerMusic.h"

#include "BaconBox/PlatformFlagger.h"

#include "BaconBox/Console.h"
#include <cassert>

using namespace BaconBox;

BBAudioPlayerMusic* BBAudioPlayerMusic::currentMusic = NULL;

void BBAudioPlayerMusic::play(int nbTimes) {
	play(nbTimes, 0.0);
}

void BBAudioPlayerMusic::play(int nbTimes, double fadeIn) {
	assert(bgm);
	if(nbTimes != 0) {
		if (nbTimes > 0) {
			--nbTimes;
		}
		if(fadeIn >= 0.0) {
			[bgm fadeInPlay:nbTimes :static_cast<float>(fadeIn)];
			playedOnce = true;
			currentMusic = this;
		} else {
			Console::print("Tried to play a music with an invalid fade in time : " +
				Console::toString(fadeIn) + " sec.");
		}
	}
}

void BBAudioPlayerMusic::stop() {
	stop(0.0);
}

void BBAudioPlayerMusic::stop(double fadeOut) {
	assert(bgm);
	if(fadeOut >= 0.0) {
		[bgm fadeOutStop:static_cast<float>(fadeOut)];
		currentMusic = NULL;
	} else {
		Console::print("Tried to stop a music with an invalid fade out time : " +
			  Console::toString(fadeOut) + " sec.");
	}
}

void BBAudioPlayerMusic::pause() {
	pause(0.0);
}

void BBAudioPlayerMusic::pause(double fadeOut) {
	assert(bgm);
	if(fadeOut >= 0.0) {
		[bgm fadeOutPause:static_cast<float>(fadeOut)];
	} else {
		Console::print("Tried to pause a music with an invalid fade out time : " +
			  Console::toString(fadeOut) + " sec.");
	}
}

void BBAudioPlayerMusic::resume() {
	resume(0.0);
}

void BBAudioPlayerMusic::resume(double fadeIn) {
	assert(bgm);
	if(fadeIn >= 0.0) {
		[bgm fadeInResume:static_cast<float>(fadeIn)];
		playedOnce = true;
	} else {
		Console::print("Tried to resume a music with an invalid fade in time : " +
			  Console::toString(fadeIn) + " sec.");
	}
}

bool BBAudioPlayerMusic::isLooping() {
	return [bgm isLooping];
}

void BBAudioPlayerMusic::setVolume(int newVolume) {
	this->Sound::setVolume(newVolume);
	[bgm setVolume:(static_cast<float>(getVolume()) / static_cast<float>(Sound::MAX_VOLUME))];
}

AudioState BBAudioPlayerMusic::getCurrentState() const {
	if(!playedOnce) {
		return AudioState::INITIAL;
	} else if([bgm isStopped]) {
		return AudioState::STOPPED;
	} else if([bgm isPaused]) {
		return AudioState::PAUSED;
	} else {
		return AudioState::PLAYING;
	}
}

BBAudioPlayerMusic::~BBAudioPlayerMusic() {
}

void BBAudioPlayerMusic::refreshVolume() {
	if(currentMusic) {
		[currentMusic->bgm refreshVolume];
	}
}

BBAudioPlayerMusic::BBAudioPlayerMusic(): BackgroundMusic(), bgm(NULL),
playedOnce(false) {
}

void BBAudioPlayerMusic::load(std::string const& filePath) {
	if(!bgm) {
		const char* tmp = filePath.c_str();
		bgm = [[BBAudioPlayerMusicDelegate alloc] initWithPath:[NSString stringWithUTF8String:tmp]];
	}
}
