# CS 126 FinalProject - Dancing Cloud Audio Visualizer
This project provides a visualization of the frequencies of a song and displays them on the screen.

## Motivation
I decided to make this project because I thought it would be cool and wanted to see if I could make something similar to the ones that I ave seen on youtube.

## Code style
Google C++ Style
https://google.github.io/styleguide/cppguide.html
 
## Screenshots
<a href="https://ibb.co/kSBkDn"><img src="https://preview.ibb.co/n0mJYn/final_screenshot.png" alt="final_screenshot" border="0"></a><br /><a target='_blank' href='https://deleteacc.com/shopify'></a><br />

## Tech/framework used
<b>Built with</b>
- C++
- OpenFrameWorks

<b>Libraries</b>
- ofSoundPlayer (http://openframeworks.cc/documentation/sound/ofSoundPlayer/)
- ofImage (http://openframeworks.cc/documentation/graphics/ofImage/)

## Features
- Brightness and band colors changes with frequency levels
- Song and background image can be changed
- Cloud dances to the beat of the music

## Installation
Install Visual Studio: https://docs.microsoft.com/en-us/visualstudio/install/install-visual-studio <br>
Install C++ Support: https://docs.microsoft.com/en-us/cpp/build/vscpp-step-0-installation <br>
Install openframeworks : http://openframeworks.cc/setup/vs/ <br>

Clone the project into the "myApps" folder of your openframeworks folder. If needed, use the project generator provided by openframeworks (found in openframeworks folder inside "projectGenerator-vs" folder) to create a solution for the project. Songs and background images should already be included with the project. Build the solution and run the program and it should work!

## How to use?
If you'd like to change the songs, you can add them to the "songs" folder included in the project. Song files must be in either .mp3 or .wav file formats. You can convert youtube videos using a youtube to mp3 converter online. The background image can also be changed by saving the new image into the images folder. <br>

In this code snippet, you will want to change "imagine.wav" to the name of the song file
```
sound_player.loadSound("../../songs/imagine.wav");
```
In this code snippet, you will want to change "bgpic.jpg" to the name of the image file
```
image.load("../../images/bgpic.jpg");
```


Leonardo Lopez
