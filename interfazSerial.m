s = serial('COM3', 'BaudRate', 300);
fopen(s);

while 1
    data = fgets(s);
end
