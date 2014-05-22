#include "BaconBox/SignalSlots/SignalAnalyzer.h"

using namespace BaconBox;

SignalAnalyzer::SignalAnalyzer() : sigly::HasSlots<SIGLY_DEFAULT_MT_POLICY>() {
}

SignalAnalyzer::~SignalAnalyzer() {
}
