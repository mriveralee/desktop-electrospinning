# Research Code for Desktop Electrospinning

This is the research repository for  
"Desktop Electrospinning: A Single Extruder 3D Printer for Producing Rigid Plastic and Electrospun Textiles". It contains the 3D printer firmware and control electronics set-up for the printer characterized in the publication  that can perform rigid plastic FDM 3D printer as well as melt electrospinning. [More information about the work can be found here](https://mikeriv.com/research/desktop-electrospinning/).

The [publication is also freely available here](https://mikeriv.com/assets/research/desktop-electrospinning/chi19-desktop-electrospinning.pdf).



## 3D Printer Firmware and Control Electronics Set-up
This 3D printer uses a modified version of the Repeiter Firmware (v0.92) that includes add-ons for controlling high voltage via an infared signal. It also include firmware for two slave arduino nanos. One acts as an IR sender when receiving a signal from the 3D printer; the other triggers a mechanical servo to open/close a connection to the high voltage ground on the 3D printer's build plate as well as toggle a solid-state relay that is connected to the high voltage power supply's AC-to-DC power adapter as seen in the image below:

![3D printer and melt electrospinning setup](https://mikeriv.com/assets/research/desktop-electrospinning/img/high-res/printing_types_01.png)

The necessary electrical connections are shown in the circuit schematics below.

### IR Servo Switch Schematic
![alt text][irservo_schematic]

### 3D Printer Slave IR Sender
![alt text][irsender_schematic]
Note: [RAMPS 1.4/Arduino Mega Pin out diagram can be found here](http://makerdev.com/blog/wp-content/uploads/2014/02/ramps_fanboard_annotations.jpg).


## Citation
```Michael L. Rivera and Scott E. Hudson. 2019. Desktop Electrospinning: A Single Extruder 3D Printer for Producing Rigid Plastic and Electrospun Textiles. In CHI Conference on Human Factors in Computing Systems Proceedings (CHI 2019), May 4–9, 2019, Glasgow, Scotland UK. ACM, New York, NY, USA, 12 pages. https://doi.org/10.1145/3290605.3300434```

# License
```MIT License

Copyright (c) 2018 Michael Rivera

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```


[irservo_schematic]: https://github.com/mriveralee/desktop-electrospinning/ESInfaredControlledServo/ESInfaredControlledServo_schematic.png "Infared Controlled Servo Circuit Schematic"

[irsender_schematic]: https://github.com/mriveralee/desktop-electrospinning/ESPrinterSlaveInfaredSender/ESPrinterSlaveInfaredSender_schematic.png "3D Printer Slave Infared Sender Circuit Schematic"

