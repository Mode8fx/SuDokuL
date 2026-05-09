#include "sound_logic.h"

static vector<Sint8> randomMusicHistory;
static Sint16 randomMusicHistoryIndex = -1;
static vector<Sint8> randomMusicBag;

static inline Sint8 normalizedMusicIndex(Sint8 index) {
	if (index < 1) {
		return 1;
	}
	if (index > MUSIC_TRACK_COUNT) {
		return MUSIC_TRACK_COUNT;
	}
	return index;
}

static inline Sint8 normalizedMusicMode(Sint8 mode) {
	if (mode < MUSIC_MODE_LOOP || mode > MUSIC_MODE_RANDOM) {
		return MUSIC_MODE_LOOP;
	}
	return mode;
}

static inline bool musicModeLoops(Sint8 mode) {
	return normalizedMusicMode(mode) == MUSIC_MODE_LOOP;
}

static Mix_Music *musicAtIndex(Sint8 index) {
	switch (index) {
		case 1:
			return bgm_1;
		case 2:
			return bgm_2;
		case 3:
			return bgm_3;
		case 4:
			return bgm_4;
		case 5:
			return bgm_5;
		case 6:
			return bgm_6;
		case 7:
			return bgm_7;
		case 8:
			return bgm_8;
		default:
			return NULL;
	}
}
void fillRandomMusicBag(bool excludeCurrentTrack) {
	randomMusicBag.clear();
	for (Sint8 trackIndex = 1; trackIndex <= MUSIC_TRACK_COUNT; ++trackIndex) {
		if (!excludeCurrentTrack || trackIndex != soundSettings.musicIndex) {
			randomMusicBag.push_back(trackIndex);
		}
	}
	for (Sint32 index = (Sint32)randomMusicBag.size() - 1; index > 0; --index) {
		Sint32 swapIndex = rand() % (index + 1);
		std::swap(randomMusicBag[index], randomMusicBag[swapIndex]);
	}
}

static void resetRandomMusicSequence() {
	soundSettings.musicIndex = normalizedMusicIndex(soundSettings.musicIndex);
	randomMusicHistory.clear();
	randomMusicHistory.push_back(soundSettings.musicIndex);
	randomMusicHistoryIndex = 0;
	fillRandomMusicBag(true);
}

void clearRandomMusicSequence() {
	randomMusicHistory.clear();
	randomMusicHistoryIndex = -1;
	randomMusicBag.clear();
}

static void ensureRandomMusicSequence() {
	if (randomMusicHistory.empty() || randomMusicHistoryIndex < 0 || randomMusicHistory[randomMusicHistoryIndex] != soundSettings.musicIndex) {
		resetRandomMusicSequence();
	}
}

static Sint8 nextRandomMusicIndex() {
	ensureRandomMusicSequence();
	if ((randomMusicHistoryIndex + 1) < (Sint16)randomMusicHistory.size()) {
		++randomMusicHistoryIndex;
		return randomMusicHistory[randomMusicHistoryIndex];
	}
	if (randomMusicBag.empty()) {
		fillRandomMusicBag(false);
	}
	Sint8 nextIndex = randomMusicBag.back();
	randomMusicBag.pop_back();
	randomMusicHistory.push_back(nextIndex);
	++randomMusicHistoryIndex;
	return nextIndex;
}

static Sint8 previousRandomMusicIndex() {
	ensureRandomMusicSequence();
	if (randomMusicHistoryIndex > 0) {
		--randomMusicHistoryIndex;
	}
	return randomMusicHistory[randomMusicHistoryIndex];
}

static void playMusicAtIndexInternal(Sint8 index, bool resetRandomSequence) {
	soundSettings.musicIndex = normalizedMusicIndex(index);
	if (addon144Settings.musicMode == MUSIC_MODE_RANDOM && resetRandomSequence) {
		resetRandomMusicSequence();
	}
	Mix_Music *bgm = musicAtIndex(soundSettings.musicIndex);
	Mix_HaltMusic();
	if (bgm != NULL) {
		playMusic(bgm);
	}
}

void normalizeMusicSettings() {
	soundSettings.musicIndex = normalizedMusicIndex(soundSettings.musicIndex);
	addon144Settings.musicMode = normalizedMusicMode(addon144Settings.musicMode);
	if (addon144Settings.musicMode == MUSIC_MODE_RANDOM) {
		resetRandomMusicSequence();
	} else {
		clearRandomMusicSequence();
	}
}

void setMusicMode(Sint8 mode) {
	Sint8 previousMode = normalizedMusicMode(addon144Settings.musicMode);
	Sint8 nextMode = normalizedMusicMode(mode);
	if (nextMode == previousMode) {
		return;
	}
	addon144Settings.musicMode = nextMode;
	if (nextMode == MUSIC_MODE_RANDOM) {
		srand(SDL_GetTicks());
		resetRandomMusicSequence();
	} else {
		clearRandomMusicSequence();
	}
	if (musicModeLoops(previousMode) != musicModeLoops(nextMode) && Mix_PlayingMusic()) {
		playMusicAtIndexInternal(soundSettings.musicIndex, false);
	}
}

void cycleMusicMode(Sint8 direction) {
	Sint8 nextMode = addon144Settings.musicMode + direction;
	if (nextMode < MUSIC_MODE_LOOP) {
		nextMode = MUSIC_MODE_RANDOM;
	} else if (nextMode > MUSIC_MODE_RANDOM) {
		nextMode = MUSIC_MODE_LOOP;
	}
	setMusicMode(nextMode);
}

void playMusicAtIndex(Sint8 index) {
	playMusicAtIndexInternal(index, true);
}

void advanceMusicTrack(bool forward) {
	if (addon144Settings.musicMode == MUSIC_MODE_RANDOM) {
		playMusicAtIndexInternal((forward ? nextRandomMusicIndex() : previousRandomMusicIndex()), false);
		return;
	}
	Sint8 nextIndex = soundSettings.musicIndex + (forward ? 1 : -1);
	if (nextIndex < 1) {
		nextIndex = MUSIC_TRACK_COUNT;
	} else if (nextIndex > MUSIC_TRACK_COUNT) {
		nextIndex = 1;
	}
	playMusicAtIndexInternal(nextIndex, false);
}

bool updateMusicPlayback() {
	if (musicModeLoops(addon144Settings.musicMode) || Mix_PlayingMusic()) {
		return false;
	}
	Sint8 previousIndex = soundSettings.musicIndex;
	if (addon144Settings.musicMode == MUSIC_MODE_RANDOM) {
		playMusicAtIndexInternal(nextRandomMusicIndex(), false);
	} else {
		Sint8 nextIndex = soundSettings.musicIndex + 1;
		if (nextIndex > MUSIC_TRACK_COUNT) {
			nextIndex = 1;
		}
		playMusicAtIndexInternal(nextIndex, false);
	}
	return soundSettings.musicIndex != previousIndex;
}

void stopMusic(Mix_Music *bgm) {
	Mix_HaltMusic();
	Mix_FreeMusic(bgm);
}

void playMusic(Mix_Music *bgm) {
	Mix_PlayMusic(bgm, musicModeLoops(addon144Settings.musicMode) ? -1 : 0);
}