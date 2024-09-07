const mysql = require('mysql');
const util = require('util');

const conn = mysql.createConnection({
	host     : 'db',
	user     : 'cproxy',
	password : 'cproxy',
	database : 'cproxy'
});

const query = util.promisify(conn.query).bind(conn);

async function doRegister(id, pw) {
    try {
        await query("INSERT INTO users (id, pw) VALUES (?, ?)", [id, pw]);
        return true;
    } catch {
        return false;
    }
}

async function doLogin(id, pw) {
    try {
        const result = await query("SELECT * FROM users WHERE id = ? AND pw = ?", [id, pw]);
        if (result.length === 1) {
            return result[0]._id;
        }
    } catch {}
}

async function insertResponse(uid, res) {
    try {
        await query("INSERT INTO responses (uid, res) VALUES (?, ?)", [uid, JSON.stringify(res)]);
        // Keep history per user <= 10
        const old = await query("SELECT _id FROM responses WHERE uid = ? ORDER BY _id DESC LIMIT 10,1", [uid]);
        if (old.length === 1) {
            await query("DELETE FROM responses WHERE uid = ? AND _id <= ?", [uid, old[0]._id]);
        }
    } catch {}
}

async function getResponseMulti(uid) {
    try {
        const result = await query("SELECT * FROM responses WHERE uid = ? ORDER BY _id DESC LIMIT 10", [uid]);
        return result.map(e => ({ rid: e._id, res: JSON.parse(e.res) }));
    } catch {
        return [];
    }
}

async function getResponse(uid, rid) {
    try {
        const result = await query("SELECT res FROM responses WHERE _id = ? and uid = ?", [rid, uid]);
        if (result.length === 1) {
            return JSON.parse(result[0].res);
        }
    } catch {}
}

module.exports = {
    doRegister,
    doLogin,
    insertResponse,
    getResponseMulti,
    getResponse,
}
