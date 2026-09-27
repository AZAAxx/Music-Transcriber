# Music Transcriber

## Overview

**Music Transcriber** is an embedded music-analysis application for the **DE1-SoC**, running C software on a **Nios V RISC-V processor** connected to FPGA-based peripherals.

The system captures audio, performs frequency-domain analysis using an FFT, identifies the dominant musical note, stores detected notes as a score, and renders the resulting sheet music on the VGA display.

### Key Features

- **Real-time audio acquisition** through the DE1-SoC audio peripheral
- **8 kHz audio sampling** and buffered signal processing
- **Hann-windowed FFT-based frequency analysis**
- Iterative **radix-2 FFT** implementation with bit-reversal ordering
- Automatic mapping of detected frequencies to musical notes from **C0–B8**
- Dynamic **sheet-music rendering** on the 320×240 VGA display
- Support for:
  - Whole, half, quarter, eighth, and sixteenth notes
  - Sharps
  - Treble clef
  - Ledger lines
  - 4/4 time signature
  - Adjustable tempo
- **Audio playback** of generated scores
- PS/2 keyboard interface for a command-line-style interface
- In-memory score database supporting creation, lookup, deletion, and listing
- Double-buffered VGA rendering with vertical synchronization
- Separate CPUlator-based testing for FFT, database, keyboard, score, and audio functionality

---

## System Architecture

The application is structured around the **Nios V processor** executing C software while communicating with FPGA peripherals through memory-mapped I/O.

```text
                 DE1-SoC FPGA / Nios V System
                           │
                           ▼
                    ┌─────────────┐
                    │   Nios V    │
                    │ RISC-V CPU  │
                    └──────┬──────┘
                           │
          ┌────────────────┼────────────────┐
          │                │                │
          ▼                ▼                ▼
      Audio I/O         PS/2 I/O        VGA Pixel
      0xFF203040        0xFF200100       0xFF203020
          │                │                │
          ▼                ▼                ▼
     Audio samples     Keyboard input    Display output
          │                │
          ▼                ▼
    ┌────────────┐   ┌─────────────┐
    │ FFT Engine │   │   Terminal  │
    │   (C)      │   │   / Input   │
    └─────┬──────┘   └───────┬─────┘
          │                  │
          ▼                  ▼
    Frequency → Note      Score DB
          │                  │
          └────────┬─────────┘
                   ▼
              ┌───────────┐
              │   Score   │
              │ Renderer  │
              └─────┬─────┘
                    │
                    ▼
                 VGA Sheet
                   Music
```

### 1. Application Entry

`main.c` starts the application by calling `terminal()`.

The terminal initializes the VGA and PS/2 interfaces and provides the primary user interface.

### 2. Command Interface

The user interacts with the system through the PS/2 keyboard.

Supported commands include:

```text
new <name>
open <name>
delete <name>
list
help
clear
```

Opening a score transfers execution into the score interface.

### 3. Score Management

Scores are represented using linked data structures:

```text
ScoreList
   │
   ├── Score
   │     ├── name
   │     ├── tempo
   │     └── Note → Note → Note → ...
   │
   └── Score
         └── ...
```

Each `Note` contains:

- Pitch
- Octave
- Duration
- Sharp flag
- Pointer to the next note

New scores are initialized with a default tempo of **120 BPM**.

### 4. Audio Transcription Pipeline

When audio analysis is enabled, the application continuously collects samples from the audio FIFO.

The processing pipeline is:

```text
Audio FIFO
    │
    ▼
Sample Buffer
    │
    ▼
Hann Window
    │
    ▼
Zero Padding
to next power of 2
    │
    ▼
Efficient FFT
    │
    ▼
Magnitude / Power Spectrum
    │
    ▼
Dominant Frequency Bin
    │
    ▼
Frequency → Closest Musical Note
    │
    ▼
Note Structure
    │
    ▼
Score Linked List
```

The FFT uses an **8 kHz sampling frequency**. Input data is converted into complex-valued samples, zero-padded to a power-of-two length, and processed using an iterative FFT.

The dominant frequency is calculated from the largest spectral bin below the Nyquist frequency:

```text
f = k × Fs / N
```

The resulting frequency is compared against the predefined frequency table and mapped to the closest note.

### 5. Score Rendering

`score.c` converts the internal linked-list representation into graphical sheet music.

The VGA renderer draws:

- Staff lines
- Treble clef
- Time signature
- Bar lines
- Notes
- Note stems
- Flags
- Sharps
- Ledger lines
- Score title
- BPM information

The display uses **double buffering and vertical synchronization** to reduce visible rendering artifacts.

### 6. Score Playback

Stored notes can also be played back through the audio output.

The playback system converts each note into its corresponding frequency and generates a square-wave-like audio signal by alternating the output sign.

Note duration is calculated from the score tempo.

---

## Repository File System

```text
Music-Transcriber/
│
├── README.md
│
├── source/
│   ├── main.c
│   ├── terminal.c
│   ├── terminal.h
│   │
│   ├── database.c
│   ├── database.h
│   ├── score.c
│   ├── score.h
│   │
│   ├── fft.c
│   ├── fft.h
│   ├── tunes.h
│   ├── assets.h
│   ├── address-map.h
│   ├── Makefile
│   │
│   ├── hal/
│   │   ├── AUDIO.c
│   │   ├── AUDIO.h
│   │   ├── PS2.c
│   │   ├── PS2.h
│   │   ├── VGA.c
│   │   └── VGA.h
│   │
│   └── Adafruit/
│
├── do_one_file/
│   ├── main.c
│   ├── Makefile
│   ├── address-map.h
│   └── gmake.bat
│
└── CPUlator-testing/
    ├── fft-testing/
    ├── database-testing/
    │
    ├── ps2-keyboard-testing.c
    ├── score-fft-testing.c
    ├── score_playback_testing.c
    ├── terminal-testing.c
    └── ...

```

### Major Source Modules

| Module | Purpose |
|---|---|
| `main.c` | Application entry point |
| `terminal.c` | User command interface |
| `database.c` | Score and note data management |
| `fft.c` | Audio signal processing and note detection |
| `score.c` | Score rendering, transcription control, and playback |
| `AUDIO.c` | Audio FIFO access, sampling, and playback |
| `PS2.c` | PS/2 keyboard decoding |
| `VGA.c` | Pixel rendering and sheet-music graphics |
| `tunes.h` | Musical assets / predefined tune data |
| `assets.h` | Bitmap graphics for musical symbols |
| `address-map.h` | DE1-SoC peripheral memory map |
| `Makefile` | Nios V/RISC-V compilation and FPGA programming |

---

## Peripherals and Interfacing

The application communicates with DE1-SoC peripherals using **memory-mapped I/O**.

### Audio

The audio HAL:

- Resets the audio FIFOs
- Checks FIFO availability
- Reads left/right audio samples
- Buffers samples for FFT processing
- Writes generated samples for score playback

The transcription path uses an **8 kHz sampling rate**.

### PS/2 Keyboard

The PS/2 driver:

1. Reads raw PS/2 scan codes
2. Handles make/break codes
3. Tracks Shift state
4. Converts scan codes to ASCII
5. Builds command strings

This provides the terminal interface used to create and manage scores.

### VGA

The VGA subsystem operates at:

```text
Resolution: 320 × 240 pixels
Color: 16-bit pixel values
```

It implements low-level primitives such as:

```text
plot_pixel()
draw_line()
background()
```

Higher-level drawing functions construct musical notation from these primitives.

The system uses two frame buffers and swaps them on vertical synchronization:

```text
Back Buffer
    │
    ▼
Render Frame
    │
    ▼
  VSync
    │
    ▼
Swap Buffers
```

### FPGA Switches and Keys

Switches control score interaction and audio-analysis operation, while push-buttons are used for score redraw, playback, and returning to the terminal.

---

## Testing and Verification

Testing is separated from the main embedded application under `CPUlator-testing/`.

### FFT Verification

`FFT-testing.c` provides an isolated environment for validating:

- Input formatting
- Zero padding
- FFT computation
- Frequency-bin generation
- Dominant-frequency detection
- Frequency-to-note conversion

The repository also contains WAV test files and a Python FFT implementation for comparison and visualization.

The FFT implementation also contains both:

- A recursive reference FFT
- An iterative `efficient_fft()` implementation

This allows the optimized implementation to be compared against a simpler reference implementation.

### Database Verification

`database-testing.c` tests the score database operations:

```text
exists()
find()
add()
delete()
get_scores()
```

Tests cover:

- Empty database behavior
- Adding scores
- Searching for scores
- Detecting duplicate names
- Deleting scores
- Managing multiple scores

### Keyboard Verification

`ps2-keyboard-testing.c` isolates PS/2 functionality, including keyboard input and scan-code decoding.

### Graphics and Musical-Notation Testing

Separate test programs exercise notation rendering, including:

```text
sharps.c
flats.c
sharps-and-flats.c
no-accidentals.c
```

These help verify correct placement and rendering of accidentals and notes.

### Overall Verification Strategy

The project follows a layered verification approach:

```text
Individual Algorithm Tests
        │
        ├── FFT
        ├── Database
        ├── PS/2
        └── Graphics
                │
                ▼
       Subsystem Integration
                │
                ├── FFT + Audio
                ├── FFT + Score
                └── Score + Playback
                │
                ▼
        Full DE1-SoC System
                │
                ▼
     Real-Time Music Transcription
```

This strategy validates computational algorithms independently before integrating them with the Nios V processor and FPGA peripherals.
