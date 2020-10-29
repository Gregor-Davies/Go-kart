import tkinter as tk

# Sets what the gui is called.
gui = tk.Tk(className= 'Telemetry')
# Sets Windows size.
gui.geometry("1920x1080")

# Pitstop Button
pitButton = tk.Button(text="Call Pitstop")
pitButton.place(x=1820, y=920)
pitButton.config(width=11, height=5)

# Defines the Exit telemetry button.
def clickExitButton():
    exit()

# Exit button code.
exButton = tk.Button(text="Exit Telemetry", command=clickExitButton)
exButton.place(x=1820, y=890)
exButton.config(width=11, height=1)








# Never ever ever remove this, this is essential for the gui to work.   
gui.mainloop()
