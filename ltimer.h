#ifndef LTIMER_H
#define LTIMER_H
#pragma once

#include <SDL.h>
#include <stdio.h>
class LTimer{
	public:
		LTimer();
		void start();
		void stop();
		void pause();
		void unpause();
		Uint32 getTicks();
		bool isStarted();
		bool isPaused();
	private:
		Uint32 mStartTicks;
		Uint32 mPausedTicks;
		bool mPaused;
		bool mStarted;
};
#endif