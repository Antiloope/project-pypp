import kivy
kivy.require('1.0.6') # replace with your current kivy version !

from kivy.app import App
from kivy.uix.widget import Widget
from kivy.clock import Clock
from kivy.properties import (
    StringProperty, ListProperty
)
import sysv_ipc
import numpy as np
import struct

#from type_definitions import *
SIZEOF_FLOAT = 8

received_message = "Hello world"

mq = sysv_ipc.MessageQueue(1234, sysv_ipc.IPC_CREAT)

class PongGame(Widget):
    text = StringProperty("Hi")
    points = ListProperty()
    def update(self, dt):
        pass

    def getMessage(self, dt):
        try:
            message, mtype = mq.receive(block=False)
            print("*** New message received ***")
            #print(f"Raw message: {message}")

            if len(self.points) > 700:
                self.points = [
                    message[i//2] + 300 if i % 2 != 0 else i * 5
                    for i in range(len(message) * 2)
                ]
            elif len(self.points) == 0:
                self.points = [
                    message[i//2] + 300 if i % 2 != 0 else i * 5
                    for i in range(len(message) * 2)
                ]
            else:
                l = len(self.points)
                self.points = self.points + [
                    message[i//2] + 300 if i % 2 != 0 else (l + i) * 5
                    for i in range(len(message) * 2)
                ]
            print(self.points)

        except sysv_ipc.ExistentialError:
            print("ERROR: message queue creation failed")
        except sysv_ipc.BusyError:
            pass



class MyApp(App):

    def build(self):
        game = PongGame()
        #Clock.schedule_interval(game.update, 1.0/60.0)
        Clock.schedule_interval(game.getMessage, 1.0/60.0)
        return game

if __name__ == '__main__':
    MyApp().run()

