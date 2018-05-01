<b>Problem:</b> Couldn't commit because file sizes of commits were too large
<br>
<b>Solution:</b> Created a gitignore file


<b>Problem:</b> Initialization of point offsets were causing weird errors with point movement, they would move linearly or blink
<br>
<b>Solution:</b> Used openframeworks ofRandom method


<b>Problem:</b> The ide wouldnt allow me to create a vector of a structure that i made (Color) in the cpp file
<br>
<b>Solution:</b> Created it in the header file


<b>Problem:</b> Colors of points would change rapidly instead of just when they were disconnected
<br>
<b>Solution:</b> Created a vecotr of booleans to keep track of the connection of each point and changed color depending on those values


<b>Problem:</b> Struggled to use ofSoundStream and get frequencies for the stream. I wanted to use this to capture the systemss audio instead of capturing the audio of a single song in a file.
<br>
<b>Solution:</b> Completely switched to ofSoundPlayer and decided to just work with one song for the meantime


<b>Problem:</b> Changes to pt_velocity were not  causing changes to the points speed
<br>
<b>Solution:</b> Created aa speed multiplier variable and multiplied it with the offsets when updating
