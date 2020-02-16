from tkinter import *
import serial
import time
import sys


voltaje2 = 0
voltaje1 = 0
#----------------------------------------------------------------
puerto = 'COM3'
ser = serial.Serial(port = puerto, baudrate = 300,
                    parity = serial.PARITY_EVEN,
                    stopbits = serial.STOPBITS_ONE,
                    bytesize = serial.EIGHTBITS, timeout = 1)
#-----------------------------------------------------------------
color_fondo = '#DCDCDC'
numero = 0
x = 0
Y = 0
Z = 0

#------------------------------------------------------------
def rep1():
    entrada_var = entrada.get()
    try:
        numero = int(entrada_var)
        if numero < 256 and numero >= 0:
            numero = numero.to_bytes(1,'little')
            ser.write(numero)
            ser.flushOutput()
            ventana.update()
            time.sleep(0.9)
        else:
            print('el numero debe estar entre 0-255')
    except TypeError:
        print('debe ser un numero')

#------------------ventana-------------------
ventana = Tk()
ventana.title("LAB3")
ventana.geometry("250x250")
ventana.resizable(width=FALSE, height=FALSE)
ventana.config(bg=color_fondo)
#ventana.iconbitmap('hola.ico')

#------------------labels-------------------
entrada = Entry(ventana,width = 5)
entrada.place(x=67, y=53)
nombre1 = Label(ventana, text="Incrementar/decrementar contador",background = color_fondo, font=('Times', 12)).place(x=25,y=10)
V1 = Label(ventana, text="Sensor 1", background = color_fondo, font =('Times', 8)).place(x=40,y=140)
valor_V1 = Label(ventana, text=str(voltaje1), background = color_fondo, font =('Times', 12))
valor_V1.place(x=40,y=170)
V2 = Label(ventana, text="Sensor 2", background = color_fondo, font =('Times', 8)).place(x=170,y=140)
valor_V2 = Label(ventana, text=str(voltaje2), background = color_fondo, font =('Times', 12))
valor_V2.place(x=170,y=170)
V11 = Label(ventana, text = "V", background = color_fondo, font = ('Times', 12)).place(x=80, y=170)
V21 = Label(ventana, text = "V", background = color_fondo, font = ('Times', 12)).place(x=205, y=170)
#-----------------Botones---------------------

repro1 = Button(ventana, command=rep1, text = "Enviar", height= 1, width = 10, bg = 'lightgreen').place(x=120,y=50)


while True:

    dato = ser.read()
    try:
        if dato == '':
            pass
        else:
            dato1 = ser.read()
            dato2 = ser.read()
            ser.flushInput()
            time.sleep(0.3)                                     
    except:
        print('.')
    print (dato1)
    valor1 = ord(dato1)
    valor2 = ord(dato2)
    voltaje1 = float(valor1 * 5 / 255)
    voltaje2 = float(valor2*5/255)
    valor_V1.config(text = str(voltaje1)[0:4])
    valor_V2.config(text = str(voltaje2)[0:4])
    ventana.update_idletasks()
    ventana.update()
    time.sleep(0.09)

    
ventana.mainloop()    

