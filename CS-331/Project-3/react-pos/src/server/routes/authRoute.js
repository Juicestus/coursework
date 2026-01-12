require('dotenv').config({path:'../.env'});

const express = require('express');
const passport = require('passport');
const GoogleStrategy = require('passport-google-oauth20').Strategy;
const session = require('express-session');
const cors = require('cors');
const { query } = require('../db');

/* -------------------- Environment Variables -------------------- */
const {
  GOOGLE_CLIENT_ID,
  GOOGLE_CLIENT_SECRET,
  GOOGLE_CALLBACK_URL,
  SESSION_SECRET,
  FRONTEND_ORIGIN,
  NODE_ENV,
} = process.env;
console.log("Frontend_Orgin", FRONTEND_ORIGIN);
console.log("Google Callback URL:", process.env.GOOGLE_CALLBACK_URL);


if (!GOOGLE_CLIENT_ID || !GOOGLE_CLIENT_SECRET || !GOOGLE_CALLBACK_URL) {
  console.error('[AUTH] Missing Google OAuth env vars:', {
    id: !!GOOGLE_CLIENT_ID,
    secret: !!GOOGLE_CLIENT_SECRET,
    callback: !!GOOGLE_CALLBACK_URL,
    envPath: '../.env',
  });
  throw new Error('Missing Google OAuth environment variables');
}

const isProd = NODE_ENV === 'production';

/* -------------------- Passport: Serialization -------------------- */
passport.serializeUser((user, done) => {
  done(null, { id: user.id, role: user.role, email: user.email });
});

passport.deserializeUser(async (idObj, done) => {
  try {
    const r = await query(
      'SELECT id, email, role, display_name FROM users WHERE id = $1',
      [idObj.id]
    );
    if (!r.rows.length) return done(null, false);
    done(null, r.rows[0]);
  } catch (err) {
    done(err);
  }
});

/* -------------------- Google OAuth Strategy -------------------- */
passport.use(
  new GoogleStrategy(
    {
      clientID: GOOGLE_CLIENT_ID,
      clientSecret: GOOGLE_CLIENT_SECRET,
      callbackURL: GOOGLE_CALLBACK_URL,
    },

    async (_accessToken, _refreshToken, profile, done) => {
      try {
        const email = profile.emails?.[0]?.value?.toLowerCase() || null;
        const display = profile.displayName || null;
        const providerId = profile.id;

        if (!email) {
          return done(null, false, { message: 'No email returned from Google' });
        }

        const result = await query(
          `
          INSERT INTO users (email, display_name, provider, provider_id, role)
          VALUES ($1, $2, 'google', $3,
              COALESCE((SELECT role FROM users WHERE email=$1), 'customer')
          )
          ON CONFLICT (email)
          DO UPDATE SET display_name = EXCLUDED.display_name,
                        provider_id = EXCLUDED.provider_id
          RETURNING id, email, role, display_name;
        `,
          [email, display, providerId]
        );

        return done(null, result.rows[0]);
      } catch (err) {
        return done(err);
      }
    }
  )
);

/* -------------------- Auth Router Factory -------------------- */
function buildAuth() {
  const router = express.Router();

  /* ---------- CORS ---------- */
  const ALLOWED_ORIGINS = [
    FRONTEND_ORIGIN,
    'http://localhost:4000',
    'http://127.0.0.1:4000',
  ].filter(Boolean);

  router.use(
    cors({
      origin(origin, cb) {
        if (!origin) return cb(null, true);
        if (ALLOWED_ORIGINS.includes(origin)) return cb(null, true);
        return cb(new Error(`CORS blocked origin: ${origin}`));
      },
      credentials: true,
    })
  );

  /* ---------- Sessions ---------- */
  router.use(
    session({
      secret: SESSION_SECRET || 'dev-secret',
      resave: false,
      saveUninitialized: false,
      cookie: {
        httpOnly: true,
        sameSite: isProd ? 'none' : 'lax',
        secure: isProd,
      },
    })
  );

  router.use(passport.initialize());
  router.use(passport.session());

  /* ---------- Routes ---------- */

  // Start Google login
  router.get(
    '/google',
    passport.authenticate('google', {
      scope: ['email', 'profile'],
      prompt: 'select_account',
      accessType: 'offline',
    })
  );

  // OAuth callback
  router.get(
    '/google/callback',
    passport.authenticate('google', { failureRedirect: '/auth/fail' }),
    (req, res) => {
      res.redirect(`${FRONTEND_ORIGIN || 'http://localhost:4000'}/`);
    }
  );

  router.get('/fail', (_req, res) =>
    res.status(401).json({ error: 'Login failed' })
  );

  // Get current logged-in user
  router.get('/me', (req, res) => {
    if (!req.user) return res.json({ authenticated: false });
    res.json({ authenticated: true, user: req.user });
  });

  // Logout
  router.post('/logout', (req, res) => {
    req.logout(() => {
      req.session.destroy(() => res.json({ ok: true }));
    });
  });

  /* ---------- Role Guards ---------- */
  const roleRank = { customer: 0, cashier: 1, manager: 2 };

  const requireAuth = (req, res, next) =>
    req.user ? next() : res.status(401).json({ error: 'Not authenticated' });

  const requireRole = (role) => (req, res, next) =>
    req.user?.role === role
      ? next()
      : res.status(403).json({ error: 'Forbidden' });

  const requireAnyRole = (roles) => (req, res, next) =>
    !req.user
      ? res.status(401).json({ error: 'Not authenticated' })
      : roles.includes(req.user.role)
      ? next()
      : res.status(403).json({ error: 'Forbidden' });

  const requireAtLeast = (minRole) => (req, res, next) =>
    !req.user
      ? res.status(401).json({ error: 'Not authenticated' })
      : (roleRank[req.user.role] ?? -1) >= roleRank[minRole]
      ? next()
      : res.status(403).json({ error: 'Forbidden' });

  return { router, requireAuth, requireRole, requireAnyRole, requireAtLeast };
}

module.exports = buildAuth;