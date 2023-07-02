const dns = require('dns/promises');
const axios = require('axios');

dns.setServers([
    '1.1.1.1',
    '8.8.8.8',
]);

function isPrivateIP(ip) {
    var s = ip.split('.').map(x => parseInt(x, 10));
    return s[0] === 10 ||                               // 10.0.0.0/8
        (s[0] === 172 && s[1] >= 16 && s[1] < 32) ||    // 172.16.0.0/12
        (s[0] === 192 && s[1] === 168) ||               // 192.168.0.0/16
        s[0] === 127 ||                                 // 127.0.0.0/8
        ip === '0.0.0.0';                               // 0.0.0.0/32
}

async function isSafeHost(host) {
    if (!/^[A-Za-z0-9.]+$/.test(host)) {
        return false;
    }
    try {
        const address = await dns.resolve4(host);
        return address.every(addr => !isPrivateIP(addr));
    } catch {
        return false;
    }
}

async function buildUrl(scheme, host, port, path, bypassDns=false) {
    // Watchdog proxy endpoint allowlist
    if (scheme === 'http' && host === 'cproxy' &&
        port === '8080' && path === '/api/ping') {
        return 'http://cproxy:8080/api/ping';
    }
    
    if ((scheme !== 'http' && scheme !== 'https') ||
        typeof host !== 'string' ||
        typeof port !== 'string' ||
        typeof path !== 'string' ||
        (!bypassDns && !await isSafeHost(host))) {
        return;
    }

    let url = `${scheme}://${host}`;

    if (port === '') {
        port = scheme === 'http' ? '80' : '443';
    }
    const intPort = parseInt(port, 10);
    if (intPort === NaN || intPort < 0 || intPort >= 0x10000) {
        return;
    }
    url += `:${intPort}`;

    if (!path.startsWith('/')) {
        path = '/' + path;
    }
    url += path;
    
    return url
}

async function get(url) {
    try {
        const aborter = new AbortController();
        setTimeout(() => aborter.abort(), 5000);

        const res = await axios.get(url, {
            maxRedirects: 0,
            signal: aborter.signal,
            validateStatus: _ => true
        });

        return (
            ({ status, statusText, headers, data }) => ({ status, statusText, headers: headers.toJSON(), data, url })
        )(res);
    } catch {
        return;
    }
}

function sendResponse(res, { status, statusText, headers, data }) {
    res.statusMessage = statusText;
    res.status(status);
    res.header(headers);
    res.send(data);
}

module.exports = {
    buildUrl,
    get,
    sendResponse,
};
