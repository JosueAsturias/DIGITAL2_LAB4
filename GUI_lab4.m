
function varargout = GUI_lab4(varargin)
% GUI_LAB4 MATLAB code for GUI_lab4.fig
%      GUI_LAB4, by itself, creates a new GUI_LAB4 or raises the existing
%      singleton*.
%
%      H = GUI_LAB4 returns the handle to a new GUI_LAB4 or the handle to
%      the existing singleton*.
%
%      GUI_LAB4('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in GUI_LAB4.M with the given input arguments.
%
%      GUI_LAB4('Property','Value',...) creates a new GUI_LAB4 or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before GUI_lab4_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to GUI_lab4_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help GUI_lab4

% Last Modified by GUIDE v2.5 17-Feb-2020 11:49:00

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @GUI_lab4_OpeningFcn, ...
                   'gui_OutputFcn',  @GUI_lab4_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT


% --- Executes just before GUI_lab4 is made visible.
function GUI_lab4_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to GUI_lab4 (see VARARGIN)
% Choose default command line output for GUI_lab4
handles.output = hObject;
% Update handles structure
guidata(hObject, handles);

% UIWAIT makes GUI_lab4 wait for user response (see UIRESUME)
% uiwait(handles.figure1);

% --- Outputs from this function are returned to the command line.
function varargout = GUI_lab4_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;



function numero_env_Callback(hObject, eventdata, handles)
% hObject    handle to numero_env (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of numero_env as text
%        str2double(get(hObject,'String')) returns contents of numero_env as a double


% --- Executes during object creation, after setting all properties.
function numero_env_CreateFcn(hObject, eventdata, handles)
% hObject    handle to numero_env (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in check_conectar.
function check_conectar_Callback(hObject, eventdata, handles)
% hObject    handle to check_conectar (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global s
global estado
estado = get(handles.check_conectar, 'Value');
if estado == 1
   delete(instrfind);
   s = serial('COM3', 'BaudRate', 300); 
   fopen(s);
%    handles.t = timer('TimerFcn', @(~,~)funcTiempo, 'Period', 10, 'ExecutionMode', 'FixedRate');
%    start(handles.t);
end
if estado == 0
   delete(instrfind);
   clear s
end



% function funcTiempo(handles, s)    
% global s
%         datos = fgets(s);
%         valor1 = uint8(datos(1));
%         valor2 = uint8(datos(2));
%         clear datos;
%         voltaje1 = double(valor1);
%         voltaje1 = (5.0/255)*voltaje1;
%         voltaje1 = round(voltaje1,2);
%         set(handles.Label_V1, 'String', voltaje1);
%         voltaje2 = double(valor2);
%         voltaje2 = (5.0/255)*voltaje2;
%         voltaje2 = round(voltaje2,2);
%         set(handles.Label_V2, 'String', voltaje2);
%     

% --- Executes on button press in pushbutton_enviar.
function pushbutton_enviar_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton_enviar (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global s
numero = str2double(get(handles.numero_env, 'String'));

if get(handles.check_conectar, 'Value') == 1
    fprintf(s, '%c', numero);
end


% --- Executes on button press in boton_refresh.
function boton_refresh_Callback(hObject, eventdata, handles)
% hObject    handle to boton_refresh (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global s;
delete(instrfind);
s = serial('COM3', 'BaudRate', 300); 
fopen(s);
datos = fgets(s);
if length(datos) >=2 
    valor1 = uint8(datos(1));
    valor2 = uint8(datos(2));
    clear datos
    voltaje1 = double(valor1);
    voltaje1 = (5.0/255)*voltaje1;
    voltaje1 = round(voltaje1,2);
    set(handles.Label_V1, 'String', voltaje1);
    voltaje2 = double(valor2);
    voltaje2 = (5.0/255)*voltaje2;
    voltaje2 = round(voltaje2,2);
    set(handles.Label_V2, 'String', voltaje2);
end




    
