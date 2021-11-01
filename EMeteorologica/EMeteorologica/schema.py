import graphene

import mediciones.schema


class Query(mediciones.schema.Query, graphene.ObjectType):
    pass

class Mutation(mediciones.schema.Mutation, graphene.ObjectType):
    pass

schema = graphene.Schema(query=Query, mutation=Mutation)
