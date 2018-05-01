Problem: Couldn't commit because file sizes of commits were too large
Solution: Created a gitignore file
----------------------------------------------------------------------------------------------------------
Problem: Initialization of point offsets were causing weird errors with point movement, they would move linearly or blink
Solution: Used openframeworks ofRandom method
----------------------------------------------------------------------------------------------------------
Problem: The ide wouldnt allow me to create a vector of a structure that i made (Color) in the cpp file
Solution: Created it in the header file
----------------------------------------------------------------------------------------------------------
Problem: Colors of points would change rapidly instead of just when they were disconnected
Solution: Created a vecotr of booleans to keep track of the connection of each point and changed color depending on those values
----------------------------------------------------------------------------------------------------------
Problem: Struggled to use ofSoundStream and get frequencies for the stream. I wanted to use this to capture the systemss audio instead of capturing the audio of a single song in a file.
Solution: Completely switched to ofSoundPlayer and decided to just work with one song for the meantime
----------------------------------------------------------------------------------------------------------
Problem: Changes to pt_velocity were not  causing changes to the points speed
Solution: Created aa speed multiplier variable and multiplied it with the offsets when updating
----------------------------------------------------------------------------------------------------------
