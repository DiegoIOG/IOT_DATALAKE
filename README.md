# DATALAKE ARDUINO -> PYTHON -> AWS BUCKET S3

## OBJETIVO

Se realizo una conexion para enviar datos a un bucket s3 con la intencion de crear un datalake basico con la idea de poder enviar informacion de un sensor de temperatura, de la misma manera con este sensor poder detener los datos  de manera manual  , con esto se logra automatizar el envio de datos de manera automatica permitiendo obtener la informaacion de datos, en un ambito indutrial esto se puede replicar para poder responder a paros de maquinas en mantenimiento, deteccion de problemas de calidad en maquinas  o al igual que la deteccion de problemas a futuro si se integra machine learing.



##  Proceso ARDUINO(ky-015,ky-004,ky-027) -> PYTHON(.JSON) -> AWS BUCKET S3

## Arduino
KY-015 → Sensor de temperatura y humedad

KY-004 → Botón ON/OFF

KY-027 → Indicador visual



## BUCKET S3 


## Video del funcionamiento 

https://youtu.be/FRlGeq7yL4w 



## Herramientas

- Arduino 
- Python
- AWS bucket S3


# Conexiones 
- KY-015 | 7
- KY-004 | 2
-    KY-027 
- R      | 9
- G      | 10



# Formato ejemplo .JSON

{
    "timestamp": "2026-02-27T14:22:17.529128",
    "temperature": "{\"device_id\":\"sensor_01\",\"status\":\"ON\",\"temp\":29.00,\"hum\":41.90}"
  }

