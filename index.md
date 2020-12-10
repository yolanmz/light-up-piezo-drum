# INTRODUCTION

I have always wanted to learn how to play drums. With everything I have learned in MUMT306, I figured that I can finally make it possible without taking too much space and making too much noises. I decided to make a portable electronic drum kit. <br /><br />
I'm hoping this drum kit can help make it eaiser for beginner drummers to learn. That's how this design of light-up piezo drum comes into my mind. It is based on an arduino piezo drum, plus the functionality that if the user plays a midi file, and a drum key is triggered in the file, the corresponding pad in the drum kit will light up, and the user will be able to follow along playing the drum part with the music.<br /><br />

# DESIGN & METHOD 
## Hardware
![drumkit](media/arduino_piezo_drum_kit.jpeg)
I'm using an Arduino Uno board to implement the hardware side. It mainly consists of two parts - the piezo drum kit and the lights. For each drum piece, I need a piezoelectric sensor connecting to an analog pin for reading. Since there are only six analog pins in an Arduino Uno board, I can only include six pieces for my drum kit, so I took off some toms and only left a floor tom in my kit. As show in the image above, from left to right, I have crash cymbal, hi-hat, snare drum, bass drum, floor tom and ride cymbal. <br /><br /> 
The connection of LED lights is more straightforward. One side is to the digital pin and the other is to the ground. Each light is placed right at the edge of each drum pad. And that completes my circuit. <br /><br />
## Software
I'm using RtMidi in C++ to read the midi file. 
# DEMO 1
Here is a [video](https://youtu.be/JguaIu-2GNw) testing the piezo drum itself.<br />
Here is a [video](https://youtu.be/OgUzo6It5Sk) playing the drums while a midi file is played.

# IMPROVEMENT
A problem I found when testing the device is that the lights flash out so fast, and it is very hard for people to catch a good number of notes.
# DEMO 2
Here is a [video](https://youtu.be/Vw5fl9Twc7Q) playing the drums while playing the midi file at half speed.


# DISCUSSION
When a piezo sensor gets hit, in order to get a value read, 

# CONCLUSION

# RESOURCES

### Markdown

Markdown is a lightweight and easy-to-use syntax for styling your writing. It includes conventions for

```markdown
Syntax highlighted code block

# Header 1
## Header 2
### Header 3

- Bulleted
- List

1. Numbered
2. List

**Bold** and _Italic_ and `Code` text

[Link](url) and ![Image](src)
```

For more details see [GitHub Flavored Markdown](https://guides.github.com/features/mastering-markdown/).

