/**
 * DomeDrum Constants
 */
 
// Hardware
#define TEENSY_PIN_LED 11
#define TEENSY_PIN_BUTTON 10
#define TEENSY_PIN_FSR_START 12 // We uset pin 12 to 22 
#define FSR_TOTAL 9

// MIDI
#define MIDI_CHANNEL 1
#define MIDI_NOTE_START 48 // C4

// Software
// TODO: rename to FSR
#define VELOCITY_DEF_THRESHOLD 15 // der standart thresholöd [0..127]
#define CAPSENSE_BUFFER_SIZE 50
