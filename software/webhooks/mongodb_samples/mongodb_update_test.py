import pymongo
from dataclasses import dataclass, field, asdict
from typing import List, Dict, Any
import random
import os
from dotenv import load_dotenv

load_dotenv()


@dataclass
class Planet:
    name: str
    orderFromSun: int
    hasRings: bool
    mainAtmosphere: List[str] = field(default_factory=list)
    surfaceTemperatureC: Dict[str, Any] = field(default_factory=dict)


MONGODB_PASS = os.getenv("MONGODB_PASS")

connection_string = f"mongodb+srv://bruggerem:{MONGODB_PASS}@cluster0.aserqws.mongodb.net/?retryWrites=true&w=majority"

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
