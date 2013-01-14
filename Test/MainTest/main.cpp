#include <iostream>

#include <BaconBox/Core/Engine.h>
#include <BaconBox/Core/State.h>
#include <BaconBox/Helper/Serialization/DefaultSerializer.h>
#include <BaconBox/Helper/Serialization/JsonSerializer.h>
#include <BaconBox/Helper/Random.h>
int main(int argc, char *argv[]) {
	// Initialize BaconBox
	BaconBox::Engine::application(argc, argv, "test");
	
	// We set the number of updates per second to be executed.
	BaconBox::Engine::setUpdatesPerSecond(48);
	
	// We set the minimum number of frames per second that are
	// tolerated before sacrificing on the number of updates per second.
	BaconBox::Engine::setMinFps(5);
	
	// We initialize the engine with a screen resolution.
	BaconBox::Engine::initializeEngine(800, 600);
	
	BaconBox::State * state = new BaconBox::State();
	
	BaconBox::Engine::addState(state);
	
	BaconBox::DefaultSerializer::setDefaultSerializer(new BaconBox::JsonSerializer(false));
	
	// Then start everything.
	BaconBox::Engine::showMainWindow();
	
	return 0;
}