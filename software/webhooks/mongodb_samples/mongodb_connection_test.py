import pymongo
import os
from dotenv import load_dotenv

load_dotenv()

MONGODB_PASS = os.getenv("MONGODB_PASS")

connection_string = f"mongodb+srv://bruggerem:{MONGODB_PASS}@cluster0.aserqws.mongodb.net/?retryWrites=true&w=majority"

# Create a MongoDB client
client = pymongo.MongoClient(connection_string)

# Test the connection
try:
    db = client.test

    # Print the list of databases
    print(client.list_database_names())
    
    print(db)
    print("Connection Successful")
except Exception as e:
    print("Connection Failed")
    print(e)
