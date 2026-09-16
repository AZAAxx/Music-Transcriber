#ifndef __SCORE__
#define __SCORE__

#include "database.h"

void analyze_audio_continuous(struct Score * scr);
void score(Score* score);
void draw_score_helper(Note * note);

void draw_score(Score* score);
void play_score(Score* score);

#endif