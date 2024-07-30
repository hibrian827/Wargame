from flask import Flask, request, render_template, redirect, url_for
import random
import threading
import time
from datetime import datetime, timedelta

app = Flask(__name__)

posts = []
search_keywords = []
search_logs = []

def reset_data():
    global posts, search_keywords, search_logs
    posts = [
        {"id": 1, "title": "Breaking News", "content": "Latest updates on current events."},
        {"id": 2, "title": "Weather Forecast", "content": "Today's weather forecast and updates."},
        {"id": 3, "title": "Sports Highlights", "content": "Summary of the latest sports events."},
        {"id": 4, "title": "Movie Reviews", "content": "Reviews of the latest movies."},
        {"id": 5, "title": "Music Charts", "content": "Top hits and music charts."},
        {"id": 6, "title": "Tech Innovations", "content": "Recent advancements in technology."},
        {"id": 7, "title": "Health Tips", "content": "Tips for maintaining good health."},
        {"id": 8, "title": "Travel Destinations", "content": "Popular travel destinations and tips."},
        {"id": 9, "title": "Financial News", "content": "Latest updates in the financial world."},
        {"id": 10, "title": "Educational Resources", "content": "Resources for enhancing your education."}
    ]
    search_keywords = [
        {"id": i+1, "keyword": kw, "count": random.randint(8, 15)}
        for i, kw in enumerate(["news", "weather", "sports", "movies", "music", "technology", "health", "travel", "finance", "education"])
    ]
    search_logs = []

reset_data()

@app.route('/')
def index():
    global posts, search_keywords
    top_keywords = sorted(search_keywords, key=lambda x: x['count'], reverse=True)[:5]
    return render_template('index.html', posts=posts, keywords=top_keywords)

@app.route('/search')
def search():
    global search_keywords, search_logs, posts
    query = request.args.get('q', '')
    if query:
        client_ip = request.remote_addr
        x_forwarded_for = request.headers.get('X-Forwarded-For')
        if x_forwarded_for:
            client_ip = x_forwarded_for.split(',')[0]

        last_log = next((log for log in search_logs if log['ip'] == client_ip and log['keyword'] == query), None)
        if not last_log or datetime.now() - last_log['timestamp'] > timedelta(minutes=10):
            keyword_entry = next((kw for kw in search_keywords if kw['keyword'] == query), None)
            if keyword_entry:
                keyword_entry['count'] += 1
            else:
                new_id = max([kw['id'] for kw in search_keywords]) + 1 if search_keywords else 1
                search_keywords.append({"id": new_id, "keyword": query, "count": 1})
            search_logs.append({"id": len(search_logs) + 1, "ip": client_ip, "keyword": query, "timestamp": datetime.now()})

    top_keywords = sorted(search_keywords, key=lambda x: x['count'], reverse=True)[:5]
    matching_posts = [post for post in posts if query.lower() in post['content'].lower()]
    return render_template('search.html', query=query, posts=matching_posts, keywords=top_keywords)

@app.route('/create_post', methods=['GET', 'POST'])
def create_post():
    global posts
    if request.method == 'POST':
        title = request.form['title']
        content = request.form['content']
        new_id = max([post['id'] for post in posts]) + 1 if posts else 1
        posts.append({"id": new_id, "title": title, "content": content})
        return redirect(url_for('index'))
    return render_template('create_post.html')

def read_search():
    from selenium import webdriver
    from selenium.webdriver.chrome.service import Service
    from selenium.webdriver.common.by import By

    driver = None
    cookie = {"name": "flag", "value": "flag{**flag**}"}
    cookie.update({"domain": "127.0.0.1"})
    try:
        service = Service(executable_path="/usr/local/bin/chromedriver")
        options = webdriver.ChromeOptions()
        for arg in [
            "headless",
            "window-size=1920x1080",
            "disable-gpu",
            "no-sandbox",
            "disable-dev-shm-usage",
        ]:
            options.add_argument(arg)
        driver = webdriver.Chrome(service=service, options=options)
        driver.implicitly_wait(3)
        driver.set_page_load_timeout(3)

        driver.get("http://127.0.0.1:8000/")
        driver.add_cookie(cookie)
        driver.get("http://127.0.0.1:8000/")

    except Exception as e:
        print(str(e))
    finally:
        if driver:
            driver.quit()
    return 'Bot checked keywords'

def start_bot():
    while True:
        read_search()
        time.sleep(10)

if __name__ == '__main__':
    bot_thread = threading.Thread(target=start_bot)
    bot_thread.start()
    app.run(host='0.0.0.0', port=8000)
