# Hardware Setup Guide

## Required Hardware

### ESP32 Development Board
- ESP32-DevKitC V4 (recommended)
- ESP32-WROOM-32 (compatible)
- ESP32-WROVER (compatible)
- Any ESP32 board with at least 4MB flash

### I2S Audio Module
Option 1: MAX98357A (Recommended)
- 3.2W Class D Amplifier
- I2S Digital Input
- Built-in speaker terminals
- Price: ~$5-10

Option 2: UDA1334A
- Stereo DAC breakout
- 3.3V operation
- Line out or headphone jack
- Price: ~$5-8

### Speaker
- 4-8 Ohm impedance
- 3W power rating
- Small form factor (2-3 inches recommended)

### Additional Components
- Micro USB cable
- Power supply (5V/1A minimum)
- Breadboard and jumper wires for prototyping
- Optional: Push button for additional controls
- Optional: LEDs for status indicators

## Wiring Diagram

### MAX98357A Connection

```
ESP32          MAX98357A
-----          ---------
GPIO 15   ->   LRC (Word Select)
GPIO 32   ->   DIN (Data In)
GPIO 14   ->   BCLK (Bit Clock)
3.3V      ->   VIN
GND       ->   GND
          
Speaker connects to + and - terminals on MAX98357A
```

### Pin Layout

```
                    ESP32
                  ┌─────┐
                  │     │
          3.3V ───┤1   2├─── GND
       GPIO 15 ───┤3   4├─── GPIO 2 (LED)
       GPIO 32 ───┤5   6├─── GPIO 0 (Button)
       GPIO 14 ───┤7   8├───
                  │ ... │
                  └─────┘
```

## Assembly Steps

### 1. Breadboard Setup (Prototyping)

1. Place ESP32 on breadboard
2. Place MAX98357A on breadboard
3. Connect power rails:
   - ESP32 3.3V to breadboard power rail
   - ESP32 GND to breadboard ground rail
   - MAX98357A VIN to power rail
   - MAX98357A GND to ground rail

4. Connect I2S signals:
   - GPIO 15 to MAX98357A LRC
   - GPIO 32 to MAX98357A DIN
   - GPIO 14 to MAX98357A BCLK

5. Connect speaker to MAX98357A terminals

### 2. Permanent Installation

For a more permanent setup:

1. Use a perfboard or custom PCB
2. Solder header pins to ESP32 (if not pre-installed)
3. Solder MAX98357A module
4. Wire connections following the breadboard layout
5. Add a case for protection

### 3. Optional Enhancements

**External Button:**
- Connect one side to GPIO 0
- Connect other side to GND
- Internal pullup resistor is enabled in software

**Status LED:**
- Connect LED anode to GPIO 2 through 220Ω resistor
- Connect LED cathode to GND

**Power Options:**
- USB power bank for portability
- Wall adapter (5V/1A minimum)
- Battery pack with voltage regulator

## Hardware Testing

### 1. Power Test
- Connect USB cable
- Check for power LED on ESP32
- Verify 3.3V on power rail with multimeter

### 2. Audio Test
- Upload test sketch
- Listen for startup confirmation tone
- Verify speaker is working

### 3. WiFi Test
- Check serial output for WiFi connection
- Verify LED illuminates when connected

## Troubleshooting

### No Sound
- Check all I2S connections
- Verify speaker polarity (shouldn't matter but try reversing)
- Test with headphones if available
- Check MAX98357A GAIN setting (default is usually fine)

### Distorted Audio
- Check power supply current capacity
- Add decoupling capacitor (100µF) near MAX98357A
- Reduce volume in code if needed

### ESP32 Won't Boot
- Check for short circuits
- Verify power supply voltage (5V ±10%)
- Try different USB cable
- Press EN button to reset

### WiFi Issues
- Ensure antenna area is clear (top of ESP32 module)
- Keep away from metal enclosures
- Check 2.4GHz WiFi signal strength

## Safety Notes

⚠️ **Important Safety Information:**

- Never exceed 5V on ESP32 power input
- Ensure proper polarity on power connections
- Don't connect speaker directly to ESP32 pins
- Use proper gauge wire for power connections
- Add heatsink to MAX98357A if it gets hot
- Keep away from water and moisture
- Use proper enclosure for finished product

## Bill of Materials (BOM)

| Item | Quantity | Approx. Cost |
|------|----------|-------------|
| ESP32 DevKit | 1 | $5-10 |
| MAX98357A Module | 1 | $5-10 |
| Speaker (4Ω 3W) | 1 | $2-5 |
| Micro USB Cable | 1 | $2-5 |
| Breadboard | 1 | $3-5 |
| Jumper Wires | 10 | $2-5 |
| **Total** | | **$19-40** |

## Next Steps

After hardware setup:
1. Follow software installation guide in README.md
2. Configure WiFi settings
3. Upload firmware
4. Test all functions
5. Enjoy your Yoass assistant!
