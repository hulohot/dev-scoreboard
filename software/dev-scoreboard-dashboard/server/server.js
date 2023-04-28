const express = require('express');
const cors = require('cors');
const MongoClient = require('mongodb').MongoClient;
require('dotenv').config();

const app = express();

app.use(cors());

const port = process.env.PORT || 5000;

MongoClient.connect(process.env.MONGO_URI, { useUnifiedTopology: true })
  .then(client => {
    console.log('Connected to MongoDB database');
    const db = client.db('dashboard-db');
    const collection = db.collection('dashboard-data');

    // Define API routes here
    app.get('/api/dashboard-data', (req, res) => {
      collection.find().toArray()
        .then(data => {
          res.json(data);
        })
        .catch(error => {
          console.log(error);
          res.status(500).send('Internal server error');
        });
    });

    app.listen(port, () => {
      console.log(`Server running on port ${port}`);
    });
  })
  .catch(error => {
    console.log(error);
  });
