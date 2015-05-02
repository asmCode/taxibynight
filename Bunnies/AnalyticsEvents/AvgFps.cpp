#include "AvgFps.h"

AvgFps::AvgFps(int fps) : AnalyticsEvent("AvgFps", (float)fps) {}