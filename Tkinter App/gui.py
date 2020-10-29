import tkinter as tk


gui = tk.Tk(className= 'Telemetry')
# Sets Windows size
gui.geometry("1920x1080")

pitButton = tk.Button(text="Call Pitstop")
pitButton.place(x=1820, y=920)
pitButton.config(width=10, height=5)



gui.mainloop()
