# Add your Python code here. E.g.
from microbit import *
import speech

import music

# music.set_built_in_speaker_enabled(True) - doesn't impact...
music.play(music.ENTERTAINER)
countingDown = False
display.show(Image.HAPPY)

while True:
    if button_a.is_pressed():
        countingDown = True
        speech.say("The bomb has been planted")
        for ii in range(110, 0, -1):
            if(ii < 10):
                display.show(ii)
            else:
                length = int((110-ii) / 4)
                imgString = ""
                if(length < 1):
                    length = 1
                for jj in range(1, length, 1):
                    if(jj == length - 1):
                        if(ii % 2 == 0):
                            imgString = imgString + "0"
                        else:
                            imgString = imgString + "9"
                    else:
                        imgString = imgString + str(0)
                    if (jj % 5 == 0):
                        imgString = imgString + ":"
                for jj in range(length, 26, 1):
                    imgString = imgString + str(9)
                    if (jj % 5 == 0):
                        if(jj < 25):
                            imgString = imgString + ":"
                display.show(Image(imgString))
            music.pitch(587, 500)
            if button_b.is_pressed():
                countingDown = False
                display.show(Image.HAPPY)
                music.play(music.POWER_UP)
                break
            sleep(500)
        if(countingDown):
            music.pitch(200, 5000, wait=False)
            speech.say("Oh No")
            display.scroll("BOOM!")
            display.show(Image.SAD)


# 0def on_forever():
#    if button_a.is_pressed():
#        display.show(Image.HAPPY)
#    if button_b.is_pressed():
#        display.show(Image.SAD)
#basic.forever(on_forever)