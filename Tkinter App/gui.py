# Required libaries.
# This is for the gui.
import tkinter as tk
# This is for the timer.
from datetime import datetime

# Sets the Timer up.
counter = 66600
running = False

# Defines the timer.
def counter_label(label):
    def count():
        if running:
            global counter

            # To manage the intinal delay.
            if counter==66600:
                display="Starting..."
            else: 
                tt = datetime.fromtimestamp(counter)
                string = tt.strftime("%H:%M:%S")
                display=string

            label['text']=display

            label.after(1000, count)
            counter += 1

    # This starts the timer.
    count()

# Start function of timer.
def Start(label):
    global running
    running=True
    counter_label(label)
    start['state']='disabled'
    stop['state']='normal'      
    reset['state']='normal'

# Stop function of the timer.
def Stop():
    global running
    start['state']='normal'
    stop['state'] ='disabled'
    reset['state']='normal'
    running = False

# Reset function of the timer.
def Reset(label):
    global counter
    # Sets the timer to 0.
    counter=10800

    # If reset is pressed after pressing stop.
    if running==False:
        reset['state']='disabled'
        # This displays CBR when the timer is not in use.
        label['text']='CBR'

    # If reset is pressed while stopwatch is running.
    else:
        label['text']='Starting...'

# Declares the gui.
gui = tk.Tk()
# Changes what the gui is called.
gui.title('Car Go Brrrr v1.9')
# Sets Windows size.
gui.geometry("1920x1080")
# Collumns 
gui.columnconfigure(0, weight=1)
gui.rowconfigure(0, weight=1)

# This gets grid() to work.
for i in range(20):
    tk.Frame(gui, width=20, height=20).grid(row=0, column=i)

for j in range(20):
    tk.Frame(gui, width=50, height=50).grid(column=0, row=j)

# Pitstop Button
pitButton= tk.StringVar()
pitButton = tk.Button(gui, text="Call Pitstop")
pitButton.grid(column=18, row=17)
pitButton.config(width=11, height=5)

# Defines the Exit telemetry button.
def clickExitButton():
    exit()

# Exit button code.
exButton = tk.StringVar()
exButton = tk.Button(gui, text="Exit Telemetry", command=clickExitButton)
exButton.grid(column=18, row=18)
exButton.config(width=11, height=1)

# Timer label text.
label = tk.StringVar()
label = tk.Label(text="CBR", fg="black", font="Verdana 30 bold")
label.grid(column=18, row=0)

# Start button.
start = tk.StringVar()
start = tk.Button(text="Start Timer", command=lambda:Start(label))
start.config(width=11, height=1)
start.grid(column=18, row=16)

# Stop button.
stop = tk.StringVar()
stop = tk.Button(text="Stop Timer", state='disabled', command=Stop)
stop.config(width=11, height=1)
stop.grid(column=18, row=15)

# Reset button.
reset = tk.StringVar()
reset = tk.Button(text="Reset Timer", state='disabled', command=lambda:Reset(label))
reset.config(width=11, height=1)
reset.grid(column=18, row=14)

# Never ever ever remove this, this is essential for the gui to work.   
gui.mainloop()
