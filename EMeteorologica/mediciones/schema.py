import graphene
from graphene_django import DjangoObjectType

from .models import Medicion

class MedicionType(DjangoObjectType):
    class Meta:
        model = Medicion


class Query(graphene.ObjectType):
    mediciones = graphene.List(MedicionType)

    def resolve_mediciones(self, info, **kwargs):
        return Medicion.objects.all()
