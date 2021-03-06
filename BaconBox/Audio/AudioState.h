/**
 * @file
 * @ingroup Audio
 */
#ifndef BB_AUDIO_STATE_H
#define BB_AUDIO_STATE_H


namespace BaconBox {
	/**
	 * Represents the state of a sound effect or a background music. When one is
	 * created and initialized, it is at INITIAL. When it is currently playing,
	 * it is at PLAYING. When paused is called on a playing sound effect or
	 * music, it set at PAUSED. When a sound is done being played, it is set at
	 * STOPPED.
	 */
	
	struct AudioState {
		enum type {
			INITIAL,
			PLAYING,
			PAUSED,
			STOPPED,
			FADING_IN,
			FADING_OUT
		};
		
	private:
	};
}

#endif
