//Hardware level display helpers

void plot_pixel(int x, int y, short int color);
void background(short int color);
void draw_line(int x0, int y0, int x1, int y1, short int line_color);
void swap(int* a, int* b);
void wait_for_vsync();

// void draw(int* deltaP, int X, int Y); // not sure if i will use this rn

// void write(char s[]);

// void mouse(int X, int Y);

// void scroll();


void draw_staff(int x, int y); // x, y is starting position
void draw_brace(int x, int y);
void draw_bar_line(int x_center, int y_center);
void draw_treble_clef(int x, int y);
void draw_time_signature(int x, int y);

void draw_toolbar();


void draw_whole_note(int x_center, int y_center);
void draw_note(int x_center, int y_center);
void draw_half_note(int x_center, int y_center);
void draw_quarter_note(int x_center, int y_center);
void draw_eighth_note(int x_center, int y_center);
void draw_sixteenth_note(int x_center, int y_center);
void draw_ledger_line(int x_center, int y_center);
void draw_flag(int x, int y);