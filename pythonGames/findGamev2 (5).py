# Add your Python code here. E.g.
from microbit import *
import speech

import music

def screenShow(count, min, max):
    x = 0
    if(count >= max):
        x = 25
    elif(count <= min):
        x = 0
    else:
        x = round(((count-min)/(max-min))*25)
    imgString = ""
    for jj in range(24, -1, -1):
        if(x <= jj):
            imgString = imgString + "0"
        else:
            imgString = imgString + "9"
        if (jj != 0):
            if (jj % 5 == 0):
                imgString = imgString + ":"
    return imgString

# music.set_built_in_speaker_enabled(True) - doesn't impact...
music.play(music.ENTERTAINER)
countingDown = False
display.show(Image.HAPPY)
speech.say("Press button Ay to plant the bomb")
while True:
    if button_a.is_pressed():
        countingDown = True
        speech.say("The bomb has been planted")
        for ii in range(110, 0, -1):
            if(ii < 10):
                display.show(ii)
            else:
                zz = ii
                if(ii % 2 == 0):
                    zz = ii + 4
                display.show(Image(screenShow(zz,11,110)))
            music.pitch(587, 500)
            if button_b.is_pressed():
                countingDown = False
                display.show(Image.HAPPY)
                music.play(music.POWER_UP)
                speech.say("Well done!")
                speech.say("You diffused the bomb!")
                display.show(Image(screenShow(ii,11,110)))
                break
            sleep(500)
        if(countingDown):
            music.pitch(200, 5000, wait=False)
            speech.say("Oh No the bomb exploded")
            display.scroll("BOOM!")
            speech.say("BOOM")
            display.show(Image.SAD)



#    if button_a.is_pressed():
#        display.show(Image.HAPPY)
#    if button_b.is_pressed():
#        display.show(Image.SAD)
#basic.forever(on_forever)