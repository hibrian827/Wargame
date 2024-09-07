FROM python:3.10-slim-buster

ENV USER buffer_wing
ENV PORT 8000
RUN adduser --disabled-password $USER

RUN apt-get update && apt-get install -y supervisor nginx lsb-release wget curl unzip gnupg2


## chrome
RUN wget --no-verbose -O /tmp/chrome.deb https://dl.google.com/linux/chrome/deb/pool/main/g/google-chrome-stable/google-chrome-stable_114.0.5735.90-1_amd64.deb
RUN apt install -y /tmp/chrome.deb
RUN rm /tmp/chrome.deb

RUN apt-get update -y && apt-get install -y libnss3
RUN wget https://chromedriver.storage.googleapis.com/`curl -sS https://chromedriver.storage.googleapis.com/LATEST_RELEASE`/chromedriver_linux64.zip && unzip chromedriver_linux64.zip && rm chromedriver_linux64.zip


## need for php7.4
RUN wget -O /etc/apt/trusted.gpg.d/php.gpg https://packages.sury.org/php/apt.gpg
RUN echo "deb https://packages.sury.org/php/ $(lsb_release -sc) main" | tee /etc/apt/sources.list.d/php.list
RUN rm -rf /var/lib/apt/lists/*


RUN apt update && apt install -y php7.4-fpm

RUN sed -i '215s/4096/8192/' /etc/php/7.4/fpm/php.ini
RUN service php7.4-fpm restart

COPY  ./config/fpm.conf /etc/php/7.4/fpm/php-fpm.conf
COPY  ./config/supervisord.conf /etc/supervisord.conf
COPY  ./config/nginx.conf /etc/nginx/nginx.conf


WORKDIR /app


COPY --chown=$USER:$USER . /app

RUN pip3 install -r ./bot/requirements.txt
RUN chmod +x bot/bot.py

EXPOSE $PORT

COPY --chown=root entrypoint.sh /entrypoint.sh
RUN chmod +x /entrypoint.sh
ENTRYPOINT ["/entrypoint.sh"]