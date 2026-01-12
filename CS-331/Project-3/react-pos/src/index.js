import 'bootstrap/dist/css/bootstrap.min.css';

const express = require('express');
const path = require('path');
const app = express();
const port = process.env.PORT || 4000;

// serve the static frontend files
app.use(express.static(path.join(__dirname, '/html')));

// default route -> serve index.html
app.get('/', (req, res) => {
  res.sendFile(path.join(__dirname, '../html/index.html'));
});

app.listen(port, () => {
  console.log(`✅ Listening on http://localhost:${port}`);
});
