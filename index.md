# INTRODUCTION

I have always wanted to learn how to play drums. With everything I have learned in MUMT306, I figured that I can finally make it possible without taking too much space and making too much noises. I decided to make a portable electronic drum kit. <br /><br />
I'm hoping this drum kit can help make it eaiser for beginner drummers to learn. That's how this design of light-up piezo drum comes into my mind. It is based on an arduino piezo drum, plus the functionality that if the user plays a midifile, and a drum key is triggered in the file, the corresponding part in the drum kit will light up, and the user will be able to follow along playing the drum part with the music.<br /><br />

# DESIGN & METHOD 
## Hardware
![drumkit](media/arduino_piezo_drum_kit.jpeg)
I'm using an Arduino Uno board to implement the hardware side. It mainly consists of two parts - the piezo drum kit and the lights. For each drum piece, I need a piezoelectric sensor connecting to an analog pin for reading. Since there are only six analog pins in an Arduino Uno board, I can only include six pieces for my drum kit, so I took off some toms and only left a floor tom in my kit. As show in the image above, from left to right, I have crash cymbal, hi-hat, snare drum, bass drum, floor tom and ride cymbal. <br /><br /> 
The connection of LED lights is more straightforward. One side is to the digital pin and the other is to the ground. Each light is placed right at the edge of each drum pad. And that completes my circuit. <br /><br />
## Software

# DEMO 1

# IMPROVEMENT

# DEMO 2

# DISCUSSION
When a piezo sensor gets hit, in order to get a value read, 
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

### Jekyll Themes

Your Pages site will use the layout and styles from the Jekyll theme you have selected in your [repository settings](https://github.com/yolanmz/light-up-piezo-drum/settings). The name of this theme is saved in the Jekyll `_config.yml` configuration file.

### Support or Contact

Having trouble with Pages? Check out our [documentation](https://docs.github.com/categories/github-pages-basics/) or [contact support](https://github.com/contact) and we’ll help you sort it out.
