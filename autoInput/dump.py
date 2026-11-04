import keyboard
import mouse
import random
# keyboard.add_hotkey('space', lambda: print('space was pressed!'))
# If the program finishes, the hotkey is not in effect anymore.

# Don't do this! This will use 100% of your CPU.
#while True: pass

# # Use this instead
#  

t = 0.1
s = 100
# or this
import time
while True:
    time.sleep(t)
    # keyboard.send('space')
    mouse.move(random.randint(-s, s), random.randint(-s, s), absolute=False,duration=t*0.9)
          