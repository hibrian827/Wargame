const express = require('express');
const session = require('express-session');
const NodeCache = require('node-cache');
const crypto = require('crypto');
const path = require('path');
const fs = require('fs/promises');
const net = require('./net');
const db = require('./db');
require('express-async-errors');

const SESSION_SECRET = crypto.randomBytes(32).toString('hex');

const app = express();
const port = process.env.PORT || 8080;
const cache = new NodeCache({ stdTTL: 60, checkperiod: 120 });

app.use(session({
	secret: SESSION_SECRET,
	resave: true,
	saveUninitialized: true
}));
app.use(express.urlencoded());

const requireAuth = async (req, res, next) => {
    if (req.session.uid !== undefined) {
        next();
    } else {
        res.redirect('/auth');
    }
};

const requireLocal = async (req, res, next) => {
    if (req.socket.remoteAddress === '127.0.0.1') {
        next();
    } else {
        res.sendStatus(403);
    }
}

const hashKey = (key) => {
    return crypto.createHash('sha256').update(key).digest('hex');
};

app.get('/', requireAuth, async (req, res) => {
    return res.sendFile(path.join(__dirname + '/static/index.html'));
});

app.get('/auth', async (req, res) => {
    return res.sendFile(path.join(__dirname + '/static/auth.html'));
});

app.post('/auth', async (req, res) => {
    const {id, pw} = req.body;
    const isRegister = 'register' in req.body;

    if (isRegister) {
        if (await db.doRegister(id, pw)) {
            return res.redirect('/auth');
        } else {
            return res.sendStatus(409);
        }
    } else {
        const uid = await db.doLogin(id, pw);
        if (uid !== undefined) {
            req.session.uid = uid;
            return res.redirect('/');
        } else {
            return res.sendStatus(401);
        }
    }
});

app.post('/logout', async (req, res) => {
    req.session.destroy(_ => { res.redirect('/auth'); });
});

app.get('/proxy', requireAuth, async (req, res, next) => {
    const {scheme, host, port, path} = req.query;
    
    const url = await net.buildUrl(scheme, host, port, path, bypassDns=true);
    const cacheKey = url ? hashKey(url) : undefined;
    const cachedRes = url ? cache.get(cacheKey) : undefined;

    if (cachedRes === undefined) {
        req.cacheKey = cacheKey;
        next();
    } else {
        net.sendResponse(res, cachedRes);
    }
}, async (req, res) => {
    const param = {};
    for (c of ['scheme', 'host', 'port', 'path']) {
        param[c] = req.param(c);
    }
    const {scheme, host, port, path} = param;

    const url = await net.buildUrl(scheme, host, port, path);
    if (url === undefined) {
        return res.sendStatus(404);
    }

    const proxyRes = await net.get(url);
    if (proxyRes === undefined) {
        return res.sendStatus(404);
    }

    net.sendResponse(res, proxyRes);
    delete proxyRes.headers['set-cookie'];
    await db.insertResponse(req.session.uid, proxyRes);
    cache.set(req.cacheKey, proxyRes);
});

app.get('/api/history', requireAuth, async (req, res) => {
    const result = await db.getResponseMulti(req.session.uid);
    const filtered = result.map(({ rid, res: { status, url } }) => ({ rid, res: { status, url } }));
    return res.send(filtered);
});

app.get('/api/history/:rid(\\d+)', requireAuth, async (req, res) => {
    const rid = parseInt(req.params.rid, 10);
    const result = await db.getResponse(req.session.uid, rid);
    if (result === undefined) {
        return res.sendStatus(404);
    } else {
        return res.send(result);
    }
});

app.get('/api/ping', async (req, res) => {
    return res.send('pong');
});

app.get('/api/local/flag', requireLocal, async (req, res) => {
    return res.send(await fs.readFile('/flag_forge', { encoding: 'ascii' }));
});

app.listen(port, '0.0.0.0', () => {
  console.log(`CProxy is live on port ${port}!`)
});
