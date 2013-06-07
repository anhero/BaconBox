#include "BaconBox/SignalSlots/SignalAnalyzer.h"

using namespace BaconBox;

SignalAnalyzer::SignalAnalyzer() : sigly::HasSlots<sigly::SingleThreaded>() {
}

SignalAnalyzer::~SignalAnalyzer() {
}
