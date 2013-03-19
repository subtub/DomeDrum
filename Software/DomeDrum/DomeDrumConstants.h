/**
 * DomeDrum - DomeDrumConstants.h
 *
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/*
 * Hardware
 */
#define TEENSY_PIN_LED 11
#define TEENSY_PIN_BUTTON 10
#define TEENSY_PIN_FSR_START 12 // We used pin 12 to 22
#define CAP_SENSE_SENSOR_PIN 6
#define CAP_SENSE_SEND_PIN 4
#define FSR_TOTAL 9

/*
 * MIDI
 */
#define MIDI_CHANNEL 1
#define MIDI_NOTE_START 48 // Midi note C4
#define CAP_SENSE_MIDI_NOTE 12
#define CAP_SENSE_MIDI_CHANNEL 2

/*
 * Software
 */
#define VELOCITY_DEF_THRESHOLD 15 // Standart threshold [0..127] TODO: rename to FSR
#define CAPSENSE_BUFFER_SIZE 30
#define CAP_SENSE_THRESH 170
#define CAP_SENSE_AVG_THRESH 80
