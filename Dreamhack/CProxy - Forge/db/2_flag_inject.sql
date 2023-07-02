USE `cproxy`;

INSERT INTO users (_id, id, pw) VALUES (1, 'admin_inject', 'fake_pw_inject');
INSERT INTO users (_id, id, pw) VALUES (2, 'admin_watchdog', 'fake_pw_watchdog');

INSERT INTO responses (_id, uid, res) VALUES (1, 1, '{"status":200,"statusText":"OK","headers":{},"data":"DH{sample_flag_inject}","url":"flag_inject"}');
