const express = require('express');
const crypto = require('crypto');

const PORT = process.env.PORT || 3000;
const FLAG = process.env.FLAG || 'flag{fake_flag}';

const app = express();

let obj = {};
let c = 0;

app.get('/',(req, res)=>{
    res.redirect('/generate');
})

app.get('/generate',(req, res)=>{
    crypto.randomBytes(2, (err, buf)=>{
        if (err){
            res.status(500).send('Error generating random bytes');
        } 
        else {
            const random = buf.toString('hex');
            obj[random] = random;
            res.json({result: true, msg: 'Generate random bytes success'});
        }
    })
})

app.get('/guess',(req, res)=>{
    key = req.query.key;
    if(obj[key]){
        return res.json({result: true, msg: FLAG});
    }else{
        c ++;
        if(c >= 3){
            obj = {};
            c = 0;
            return res.json({result: true, msg: 'obj has been reset'});
        }
        return res.json({result: true, msg: `You have left ${3-c} chances`});
    }

})

app.listen(PORT, ()=>{
    console.log(`[+] Server is running on ${PORT}`);
})

