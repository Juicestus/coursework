const fs = require('fs');
const Table = require('cli-table3');

require('dotenv').config({path:'.env'});

const express = require('express');
const session = require('express-session');
const cors = require('cors');
const passport = require('passport');

const userRoutes = require('./routes/customerRoute');       // public (customer)
const employeeRoutes = require('./routes/employeeRoute');   // cashier + manager
const managerRoutes = require('./routes/managerRoute');     // manager only

// Auth module exposes router + guards
const buildAuth = require('./routes/authRoute');
const { router: authRouter, requireRole, requireAnyRole, requireAuth } = buildAuth();

const app = express();

// --- Root ---
app.get('/', (req, res) => {
  const art = fs.readFileSync('art.txt', 'utf8');

  if (req.accepts('html')) {
    return res.type('text/plain').send(art);
  }

  return res.status(200);
});

/* -------------------- ROUTE LISTING -------------------- */
app.get('/routes', (req, res) => {
  const routes = [
    '/customer',
    '/cashier',
    '/manager',
    '/auth',
    '/dbz'
  ];

  const table = new Table({
    head: ['Method(s)', 'Path'],
    style: { head: [], border: [] },
  });

  routes.forEach(path => {
    table.push(['GET, POST, PUT, DELETE', path]);
  });

  res.type('text/plain').send('Available API Routes:\n\n' + table.toString());
});

// --- CORS ---
const ALLOWED_ORIGINS = [
  process.env.FRONTEND_ORIGIN,
  'http://localhost:4000',
  'http://127.0.0.1:4000',
].filter(Boolean);

const corsOptions = {
  origin(origin, cb) {
    if (!origin) return cb(null, true); // Postman / curl
    if (ALLOWED_ORIGINS.includes(origin)) return cb(null, true);
    return cb(new Error(`CORS: origin not allowed -> ${origin}`));
  },
  credentials: true,
  methods: ['GET', 'POST', 'PUT', 'DELETE', 'OPTIONS'],
  allowedHeaders: ['Content-Type', 'Authorization'],
};

app.use(cors(corsOptions));

/* -------------------- Body parser -------------------- */
app.use(express.json());

/* -------------------- Sessions & Passport -------------------- */
const isProd = process.env.NODE_ENV === 'production';
if (isProd) app.set('trust proxy', 1);

app.use(session({
  secret: process.env.SESSION_SECRET || 'dev-secret',
  resave: false,
  saveUninitialized: false,
  cookie: {
    httpOnly: true,
    sameSite: isProd ? 'none' : 'lax',
    secure: isProd,
  },
}));

app.use(passport.initialize());
app.use(passport.session());

/* -------------------- Auth routes -------------------- */
app.use('/auth', authRouter);

/* -------------------- Application routes -------------------- */
app.use('/customer', userRoutes);

const useAuth = true;
if (useAuth) {
  app.use('/cashier', requireAnyRole(['cashier', 'manager']), employeeRoutes);
  app.use('/manager', requireAnyRole(['manager']), managerRoutes);
} else {
  app.use('/cashier', employeeRoutes);
  app.use('/manager', managerRoutes);
}

/* -------------------- Health checks -------------------- */
app.get('/dbz', async (_, res) => {
  try {
    const { query } = require('db');
    const r = await query('SELECT NOW()');
    res.json(r.rows[0]);
  } catch (e) {
    res.status(500).json({ error: String(e.message || e) });
  }
});

/* -------------------- Global Error Handler -------------------- */
app.use((err, req, res, _next) => {
  console.error('[SERVER ERROR]', err);

  if (err.message && err.message.startsWith('CORS:')) {
    return res.status(403).json({ error: err.message });
  }

  res.status(500).json({ error: 'Internal server error' });
});

/* -------------------- Start -------------------- */
const PORT = process.env.PORT || 3000;
app.listen(PORT, () => {
  console.log(`Server running on port ${PORT}`);
  console.log('Allowed origins:', ALLOWED_ORIGINS.join(', ') || '(none)');
});