from django.db import models

# Create your models here.

class Medicion(models.Model):
    Temperatura = models.DecimalField(max_digits=5, decimal_places=2)
    Luz = models.IntegerField()
    Humedad = models.IntegerField()
    Fecha = models.DateField(auto_now_add=True)

