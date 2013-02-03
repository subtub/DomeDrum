/**
 * DomeDrum Constants
 */
 
// Hardware
#define TEENSY_PIN_LED 11
#define TEENSY_PIN_BUTTON 10
#define TEENSY_PIN_FSR_START 12 // We uset pin 12 to 22 
#define CAP_SENSE_SENSOR_PIN 6
#define CAP_SENSE_SEND_PIN 4
#define FSR_TOTAL 9

// MIDI
#define MIDI_CHANNEL 1
#define MIDI_NOTE_START 48 // C4
#define CAP_SENSE_MIDI_NOTE 60
#define CAP_SENSE_MIDI_CHANNEL 1

// Software
// TODO: rename to FSR
#define VELOCITY_DEF_THRESHOLD 15 // der standart thresholöd [0..127]
#define CAPSENSE_BUFFER_SIZE 30
#define CAP_SENSE_THRESH 170
#define CAP_SENSE_AVG_THRESH 80



