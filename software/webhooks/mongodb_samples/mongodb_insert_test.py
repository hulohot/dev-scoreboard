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

# Create a document to insert
planet = Planet(
    name="Bthan",
    orderFromSun=8,
    hasRings=False,
    mainAtmosphere=["O2", "N2", "CO2"],
    surfaceTemperatureC={"min": random_temp, "max": 50.0, "mean": 10.0},
)

# Convert Planet object to a dictionary
planet_dict = asdict(planet)

# Insert the document into the collection
result = collection.insert_one(planet_dict)

# Print the result of the insert
print(f"Inserted document with ID: {result.inserted_id}")
