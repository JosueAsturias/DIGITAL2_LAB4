s = serial('COM3', 'BaudRate', 300); 
fopen(s);
while 1
    datos = fgets(s);
    valor1 = uint8(datos(1));
    valor2 = uint8(datos(2));
    %clear datos;
    voltaje1 = double(valor1);
    voltaje1 = (5.0/255)*voltaje1;
    voltaje1 = round(voltaje1,2)
   % set(handles.Label_V1, 'String', voltaje1);
    voltaje2 = double(valor2);
    voltaje2 = (5.0/255)*voltaje2;
    voltaje2 = round(voltaje2,2)
   % set(handles.Label_V2, 'String', voltaje2);
    
end
