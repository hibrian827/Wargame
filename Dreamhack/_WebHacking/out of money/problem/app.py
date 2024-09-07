from flask import Flask, session, redirect, url_for, request, render_template
from threading import Thread
from util import get_price, deposit, liquidate

app = Flask(__name__)
app.secret_key = "[REDACTED]"


@app.route("/", methods=["GET", "POST"])
def main():
    if request.method == "POST" and request.form["name"] != "":
        session["name"] = request.form["name"]

        session["DHH"] = 0.0
        session["DHC"] = 0.0
        session["DHD"] = 0.0

        session["debt_DHH"] = 0.0

        session["col_DHC"] = 0.0
        session["depo_DHC"] = 0.0
        session["depo_DHD"] = 0.0
        session["debt_DHD"] = 0.0

        return redirect(url_for("main"))

    if "name" in session:
        return render_template("lobby.html", session=session)
    else:
        return render_template("login.html")


@app.route("/santa", methods=["GET", "POST"])
def santa():
    return render_template("santa.html", session=session, message="")


@app.route("/santa/lend", methods=["POST"])
def santa_lend():
    value = float(request.form["value"])

    if session["debt_DHH"] + value >= 10000.0:
        return render_template("santa.html", session=session, message="그만 빌려욧!")
    if session["DHH"] + value < 0.0:
        return render_template("santa.html", session=session, message="더 갚으시게요...?")

    session["DHH"] += value
    session["debt_DHH"] += value
    return render_template("santa.html", session=session, message="대출완료!")


@app.route("/santa/flag", methods=["GET"])
def santa_flag():
    if session["DHH"] >= 1000.0:
        if session["debt_DHH"] == 0.0:
            return render_template("flag.html")
        else:
            return render_template("santa.html", session=session, message="빚을 먼저 값으세욧!")
    return render_template("santa.html", session=session, message="드핵코인이 없어욧!")


@app.route("/santa/change", methods=["POST"])
def santa_change():
    frm = int(request.form["from"])
    to = int(request.form["to"])
    value = float(request.form["value"])

    if value < 0:
        return render_template("santa.html", session=session, message="어디서 음수만큼 바꾸려고!")

    tbl = ["DHH", "DHC", "DHD"]
    if frm in [0, 1, 2] and to in [0, 1, 2]:
        frm = tbl[frm]
        to = tbl[to]

        if session[frm] < value:
            return render_template(
                "santa.html", session=session, message="가지고 있는 코인이 그만큼 없어욧!"
            )

        if frm != to:
            frm_price = get_price(frm)
            to_price = get_price(to)

            to_balance = value * frm_price / to_price

            session[frm] -= value
            session[to] += to_balance
        return render_template("santa.html", session=session, message="교환 완료!")
    return render_template("santa.html", session=session, message="다른건 교환 못합니다!")


@app.route("/dream", methods=["GET"])
def dream():
    return render_template("dream.html", session=session, message="")


@app.route("/dream/collateral", methods=["POST"])
def dream_col():
    value = float(request.form["value"])

    if value < 0:
        if session["debt_DHD"] == 0.0:
            session["DHC"] += session["col_DHC"]
            session["col_DHC"] = 0.0
            return render_template("dream.html", session=session, message="담보 반환 완료!")
        else:
            return render_template("dream.html", session=session, message="빚을 먼저 값으세욧!")
    if session["DHC"] - value < 0.0:
        return render_template(
            "dream.html", session=session, message="가지고 있는 드냥코인이 부족합니다!"
        )

    session["DHC"] -= value
    session["col_DHC"] += value
    return render_template("dream.html", session=session, message="담보 확인!")


@app.route("/dream/deposit", methods=["POST"])
def dream_deposit():
    type = int(request.form["type"])
    value = float(request.form["value"])

    if type not in [0, 1]:
        return render_template(
            "dream.html", session=session, message="드핵코인, 드냥코인만 예금할 수 있습니다!"
        )

    tbl = ["DHC", "DHD"]
    type = tbl[type]
    if session[type] - value < 0:
        return render_template(
            "dream.html", session=session, message="가지고 있는 코인이 부족합니다!"
        )
    if session["depo_" + type] + value < 0:
        return render_template(
            "dream.html", session=session, message="에금한 코인보다 더 뺄수는 없습니다!"
        )
    session[type] -= value
    session["depo_" + type] += value
    deposit(type, value)
    return render_template("dream.html", session=session, message="예금완료")


@app.route("/dream/lend", methods=["POST"])
def dream_loan():
    value = float(request.form["value"])

    dhc_price = get_price("DHC")
    dhd_price = get_price("DHD")

    max_lend = session["col_DHC"] * dhc_price / dhd_price * 0.8

    print(max_lend)

    if session["DHD"] + value < 0.0:
        return render_template("dream.html", session=session, message="더 갚으시게요...?")
    if max_lend < value:
        return render_template(
            "dream.html", session=session, message="그만큼 빌리기에는 담보가 부족합니다!"
        )

    session["DHD"] += value
    session["debt_DHD"] += value

    return render_template("dream.html", session=session, message="대출 완료!")


@app.route("/logout")
def logout():
    session.pop("name", None)
    return redirect(url_for("main"))


import time


def loop_liquid():
    while True:
        time.sleep(2)
        liquidate()


if __name__ == "__main__":
    t1 = Thread(target=loop_liquid, daemon=True)
    t1.start()
    app.run(host="0.0.0.0")
