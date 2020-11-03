import tkinter as tk

# Sets what the gui is called.
gui = tk.Tk(className= 'Telemetry')
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
exButton.place(x=1820, y=890)
exButton.config(width=11, height=1)








# Never ever ever remove this, this is essential for the gui to work.   
gui.mainloop()
