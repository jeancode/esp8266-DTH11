# esp8266-DTH11

## Intrucciones

###### 1.- Instalar python_
>descargar he instalar python
>https://www.python.org/downloads/

###### 2.- Abrir cmd_
>precionar inicio +r o buscar cmd y abrir

###### 3.- Escribir: 
> pip install platformio -U

###### 4.- Entrar a la carpeta_
> Entrar a la carpeta del proyecto justo donde se encuentra platformio.ini

###### 6.- Editar el codigo ./src/main.cpp_
>Editar el espesificar el puerto de salida ademas de  el nombre y password de tu red en la linea 59 y el puerto del sensor en la linea 57

###### 7.- Compilar y subir a la nodencu conectada junto con el sensor en el pin D0 que se espesifica en el codigo y escribir:
> platformio run -t upload && platformio device monitor

###### 8.- Entrar al Navegador
> ver el puerto ip de salida quese mostrara en la consola despues de compilarse y subirse el codigo entrar desde cualquier navegador dentro de la misma red local


![Foto](foto.jpg)
![Captura1](Captura1.PNG)
![Captura1](Captura2.PNG)
