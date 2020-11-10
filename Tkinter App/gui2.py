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
    stop['state'] = 'disabled'
    reset['state']='normal'
    running = False

# Reset function of the timer.
def Reset(label):
    global counter
    counter=66600

    # If reset is pressed after pressing stop.
    if running==False:
        reset['state']='disabled'
        label['text']='CBR'

    # If reset is pressed while stopwatch is running.
    else:
        label['text']='Starting...'

# Sets what the gui is called.
gui = tk.Tk(className= 'CBR (Car Go BRRR...) v1.07')
# Sets Windows size.
gui.geometry("1920x1080")
# Collumns 
gui.columnconfigure(0, weight=1)
gui.rowconfigure(0, weight=1)

# Pitstop Button
pitButton= tk.StringVar()
pitButton = tk.Button(gui, text="Call Pitstop")
pitButton.grid(column=2, row=1)
pitButton.config(width=11, height=5)

# Defines the Exit telemetry button.
def clickExitButton():
    exit()

# Exit button code.
exButton = tk.StringVar()
exButton = tk.Button(gui, text="Exit Telemetry", command=clickExitButton)
exButton.grid(column=2, row=2)
exButton.config(width=11, height=1)

# Timer label text.
label = tk.StringVar()
label = tk.Label(text="CBR", fg="black", font="Verdana 30 bold")
label.grid(column=5, row=10)

# Start button.
start = tk.StringVar()
start = tk.Button(text="Start", command=lambda:Start(label))
start.config(width=11, height=1)
start.grid(column=2, row=2)

# Stop button.
stop = tk.StringVar()
stop = tk.Button(text="Stop", state='disabled', command=lambda:Reset(label))
stop.config(width=11, height=1)
stop.grid(column=2, row=5)

# Reset button.
reset = tk.StringVar()
reset = tk.Button(text="Reset", state='disabled', command=lambda:Reset(label))

# Never ever ever remove this, this is essential for the gui to work.   
gui.mainloop()
