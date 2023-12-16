Este proyecto consta de dos driver, el mpu6050 controlado por i2c y un pcf8574 tambien contraldo por i2c este a su vez controla una pantalla lcd 16x2 hitachi hd44780.
Se despliega un menu el cual es controlado por un boton, el menu esta programado en dos capas, el boton tiene dos funciones, usa el flanco de subida y detecta si ha sido
presionado por 2s, los datos que se muestran en el lcd son la aceleracion y los datos del gyroscopio, los datos sonmostrados en bruto y en sus componentes
