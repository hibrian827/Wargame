dhc_balance = 1000.0
dhd_balance = 1000.0


def get_price(name):
    if name == "DHH":
        return 1.0
    if name == "DHC":
        return 1.0
    if name == "DHD":
        return dhc_balance * get_price("DHC") / dhd_balance


def deposit(name, value):
    global dhc_balance, dhd_balance
    if name == "DHC":
        dhc_balance += value
    if name == "DHD":
        dhd_balance += value


def liquidate():
    pass
    # 차익거래 후, dhc_balance * dhc_price == dhd_balance * dhd_price
    # 만들어짐
    # 나만 이득 못봐!
