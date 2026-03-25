#!/bin/bash

# --- Clean old files and create empty ones ---
echo "Creating data files..."
touch audio-data.txt FFT-result.txt

# --- Compile and run create-audio-file ---
CFILE="create-audio-file.c"
EXE="${CFILE%.c}"
echo "Compiling $CFILE..."
rm -f "$EXE"          # remove old executable if it exists
gcc "$CFILE" -o "$EXE"
if [ $? -eq 0 ]; then
    echo "Running $EXE..."
    ./"$EXE"
else
    echo "Compilation failed for $CFILE"
    exit 1
fi

# --- Compile and run FFT-testing ---
CFILE="FFT-testing.c"
EXE="${CFILE%.c}"
echo "Compiling $CFILE..."
rm -f "$EXE"
gcc "$CFILE" -o "$EXE" -lm
if [ $? -eq 0 ]; then
    echo "Running $EXE..."
    ./"$EXE"
else
    echo "Compilation failed for $CFILE"
    exit 1
fi

# --- Clean temporary executables if needed ---
echo "Cleaning temporary executables..."
rm -f FFT-testing create-audio-file


# --- Run Python script in virtual environment ---
echo "Activating Python virtual environment..."
source python/myenv/bin/activate
python3 python/fft.py
deactivate

rm -f audio-data.txt FFT-result.txt

echo "Done!"