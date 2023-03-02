import pymongo
from dataclasses import dataclass, field, asdict
from typing import List, Dict, Any
import random


@dataclass
class Planet:
    name: str
    orderFromSun: int
    hasRings: bool
    mainAtmosphere: List[str] = field(default_factory=list)
    surfaceTemperatureC: Dict[str, Any] = field(default_factory=dict)


connection_string = "mongodb+srv://bruggerem:test12345@cluster0.aserqws.mongodb.net/?retryWrites=true&w=majority"

# Create a MongoDB client
client = pymongo.MongoClient(connection_string)

# Select the database and collection you want to insert the document into
db = client["sample_guides"]
collection = db["planets"]

# Geneate a random number between -300 and -100
random_temp = random.randint(-300, -100)

# define the filter and update values
filter = {"name": "Bthan"}
update = {"$set": {"surfaceTemperatureC.min": random_temp}}

# update the document
result = collection.update_one(filter, update)

# print the number of documents updated
print(result.modified_count)
