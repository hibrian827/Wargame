FROM tiangolo/uwsgi-nginx-flask:python3.8

# ENV
ENV port 80
ENV API_KEY API_KEY

# SET USER
RUN useradd -d /home/user/ -m -s /bin/bash user

# SET packages
RUN apt-get update -y
RUN apt-get install -y python-pip

# SET challenges
ADD ./deploy/app /app
WORKDIR /app
RUN pip install -r requirements.txt
ADD ./deploy/nginx/ /etc/nginx/conf.d/
EXPOSE $port