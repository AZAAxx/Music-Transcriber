// river flows in you
static Note score4_notes[] = {
    {'A', 4, 's', false, &score4_notes[1]},
    {'C', 5, 's', true, &score4_notes[2]},
    {'A', 5, 'e', false, &score4_notes[3]},
    {'G', 5, 's', true, &score4_notes[4]},
    {'A', 5, 'e', false, &score4_notes[5]},
    {'A', 4, 's', false, &score4_notes[6]},
    {'G', 5, 's', true, &score4_notes[7]},
    {'A', 5, 'e', false, &score4_notes[8]},
    {'A', 4, 's', false, &score4_notes[9]},
    {'E', 5, 's', false, &score4_notes[10]},
    {'A', 5, 'e', false, &score4_notes[11]},
    {'A', 4, 's', false, &score4_notes[12]},
    {'D', 5, 's', false, &score4_notes[13]},
    {'A', 4, 'e', false, &score4_notes[14]},
    {'B', 4, 's', false, &score4_notes[15]},
    {'C', 5, 'e', true, &score4_notes[16]},
    {'D', 5, 'e', false, &score4_notes[17]},
    {'E', 5, 'e', false, &score4_notes[18]},
    {'C', 5, 'e', true, &score4_notes[19]},
    {'B', 4, 'h', false, &score4_notes[20]},
    {'\0', 0, '\0', false, NULL}
};

// rick roll
static Note score3_notes[] = {
    {'C', 4, 's', false, &score3_notes[1]},
    {'D', 4, 's', false, &score3_notes[2]},
    {'F', 4, 's', false, &score3_notes[3]},
    {'D', 4, 's', false, &score3_notes[4]},
    {'A', 4, 'q', false, &score3_notes[5]},
    {'A', 4, 'q', false, &score3_notes[6]},
    {'G', 4, 'h', false, &score3_notes[7]},
    {'C', 4, 's', false, &score3_notes[8]},
    {'D', 4, 's', false, &score3_notes[9]},
    {'F', 4, 's', false, &score3_notes[10]},
    {'D', 4, 's', false, &score3_notes[11]},
    {'G', 4, 'q', false, &score3_notes[12]},
    {'G', 4, 'q', false, &score3_notes[13]},
    {'F', 4, 'h', false, &score3_notes[14]},
    {'\0', 0, '\0', false, NULL}
};

// mii channel theme
static Note score2_notes[] = {
    {'F', 4, 'q', true, &score2_notes[1]},
    {'A', 4, 'e', false, &score2_notes[2]},
    {'C', 5, 'q', true, &score2_notes[3]},
    {'A', 4, 'q', false, &score2_notes[4]},
    {'F', 4, 'e', true, &score2_notes[5]},
    {'D', 4, 'e', false, &score2_notes[6]},
    {'D', 4, 'e', false, &score2_notes[7]},
    {'D', 4, 'h', false, &score2_notes[8]},
    {'C', 4, 'e', true, &score2_notes[9]},
    {'D', 4, 'e', false, &score2_notes[10]},
    {'F', 4, 'e', true, &score2_notes[11]},
    {'A', 4, 'e', false, &score2_notes[12]},
    {'C', 5, 'q', true, &score2_notes[13]},
    {'A', 4, 'q', false, &score2_notes[14]},
    {'F', 4, 'e', true, &score2_notes[15]},
    {'E', 5, 'q', false, &score2_notes[16]},
    {'D', 5, 'e', true, &score2_notes[17]},
    {'D', 5, 'q', false, &score2_notes[18]},
    {'\0', 0, '\0', false, NULL}
};

// november rain
static Note score1_notes[] = {
    {'A', 4, 'q', false, &score1_notes[1]},
    {'F', 4, 'e', false, &score1_notes[2]},
    {'G', 4, 'e', false, &score1_notes[3]},
    {'A', 4, 'e', false, &score1_notes[4]},
    {'B', 4, 'q', false, &score1_notes[5]},
    {'C', 5, 'e', false, &score1_notes[6]},
    {'A', 4, 'q', false, &score1_notes[7]},
    {'E', 4, 's', false, &score1_notes[8]},
    {'G', 4, 's', false, &score1_notes[9]},
    {'A', 4, 's', false, &score1_notes[10]},
    {'B', 4, 's', false, &score1_notes[11]},
    {'C', 5, 'e', false, &score1_notes[12]},
    {'B', 4, 'e', false, &score1_notes[13]},
    {'A', 4, 'e', false, &score1_notes[14]},
    {'G', 4, 'e', false, &score1_notes[15]},
    {'A', 4, 'q', false, &score1_notes[16]},
    {'F', 4, 'e', false, &score1_notes[17]},
    {'G', 4, 'e', false, &score1_notes[18]},
    {'A', 4, 'e', false, &score1_notes[19]},
    {'G', 4, 'q', false, &score1_notes[20]},
    {'F', 4, 'e', false, &score1_notes[21]},
    {'E', 4, 's', false, &score1_notes[22]},
    {'G', 4, 'q', false, &score1_notes[23]},
    {'\0', 0, '\0', false, NULL}
};


Score score4 = {
    .name = "RiverFlows",
    .next = NULL,
    .notes = score4_notes,
    .tempo = 120
};

Score score3 = {
    .name = "Rick",
    .next = &score4,
    .notes = score3_notes,
    .tempo = 200
};

Score score2 = {
    .name = "MiiChannel",
    .next = &score3,
    .notes = score2_notes,
    .tempo = 200
};

Score score1 = {
    .name = "NovemberRain",
    .next = &score2,
    .notes = score1_notes,
    .tempo = 120
};

// ScoreList is a Linked List with Score as the node
ScoreList scoreList = {&score1};