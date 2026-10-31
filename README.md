# Nature-Inspired Fog Harvesting Prototype using ESP32 🪲💧
A functional hardware prototype replicating the moisture-harvesting capabilities of the Namib Desert *Stenocara* beetle, built for my Semester 1 "Nature Inspired Engineering" course. 

![Prototype Photo](Image1.jpg)(Image2.jpg)

**[Watch the working prototype and data logging video here](LINK_TO_YOUR_LINKEDIN_OR_YOUTUBE_VIDEO)**

## Tech Stack (ECE Integration)
*   **Microcontroller:** ESP32 (C++)
*   **Sensors:** DHT22 (Temperature/Humidity), Analog Water-Level Sensor
*   **Modules:** 0.96" I2C OLED Display, SPI MicroSD Card Module
*   **Core Concepts:** Biomimicry (Hydrophilic/Hydrophobic coatings), Analog-to-Digital Conversion (ADC), I2C & SPI Communication, Local Data Logging.

## Circuit Diagram
![Circuit Diagram](CircuitDiagram.jpg)

## How It Works
The acrylic panel is coated with a grid of hydrophilic bumps (PVA) and hydrophobic channels. Dense moisture nucleates on the bumps, grows, and rolls down the channels into a collection jar. The ESP32 processes the raw analog water-level data and ambient humidity, displays it live on the OLED screen.
