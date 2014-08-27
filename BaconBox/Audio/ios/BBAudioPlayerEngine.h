/**
 * @file
 * @ingroup Audio
 */
#ifndef BB_AUDIO_PLAYER_ENGINE_H
#define BB_AUDIO_PLAYER_ENGINE_H

#include "BaconBox/PlatformFlagger.h"

#include <string>
#include <list>

#include "BaconBox/Audio/MusicEngine.h"

namespace BaconBox {
	class BackgroundMusic;
	struct MusicInfo;
	class BBAudioPlayerMusic;
	/**
	 * Music engine implementation for iOS.
	 * @ingroup Audio
	 */
	class BBAudioPlayerEngine : public MusicEngine {
		friend class BaseEngine;
		friend class MusicEngine;

		BB_SINGLETON_DECL(BBAudioPlayerEngine);

	public:
		/**
		 * Constructs a background music. Gets the music's data associated with
		 * the key. In AVAudioPlayerEngine's case, the music is really loaded
		 * here rather than in MusicInfo.
		 * @param key Identifier for the music data to use. The music data needs
		 * to be loaded beforehand.
		 * @param survive Used to specify if the music destroy is managed by the
		 * user or by the engine when the music is done playing. This lets the
		 * user simply call this function and play the music directly if survive
		 * is at false or keep it and re-use it if surive is at true.
		 * @return Background music generated by this function, the user will
		 * either have to destroy it manually if survive is set at true, or will
		 * be automatically destroyed once the music's state is at STOPPED. The
		 * background music returned is at the INITIAL state.
		 */
		BackgroundMusic* getBackgroundMusic(const std::string& key,
											bool survive = true);
		/**
		 * Sets the engine's global music volume.
		 * @param newMusicVolume Engine's new global music volume level.
		 * @see BaconBox::AudioEngine::musicVolume
		 */
		void setMusicVolume(int newMusicVolume);
	private:
		/**
		 * List of pointers to the musics that are to be deleted automatically
		 * once done.
		 */		
		std::list<BackgroundMusic*> managedMusics;
		/**
		 * Default constructor.
		 */
		BBAudioPlayerEngine();
		/**
		 * Destructor.
		 */
		~BBAudioPlayerEngine();
		/**
		 * Updates the necessary informations for the audio engine.
		 */
		void update();
		/**
		 * Loads a music from a path.
		 * @param filePath Path to the music file to load.
		 * @return Pointer to the loaded music's data.
		 */
		MusicInfo* loadMusic(const std::string& filePath);
		/**
		 * Loads a music from platform specific parameters.
		 * @param params Platform specific parameters to load the music. In this
		 * implementation's case, only the file path is needed.
		 * @return Pointer to the loaded music's data.
		 */
		MusicInfo* loadMusic(const MusicParameters& params);
		/**
		 * Unloads music data.
		 * @param music Music data that needs to be unloaded. Delete must not be
		 * called on it, the resource manager that calls this function takes
		 * care of that.
		 * @return True if the unloading was successful, false if not.
		 */
		bool unloadMusic(MusicInfo* music);
	};
}
#endif
