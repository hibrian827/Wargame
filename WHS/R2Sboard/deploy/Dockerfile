FROM python:3.10-slim-buster

# ENV
ENV user user 
ENV port 8000

RUN apt-get update && apt-get install -y python3-pip wget curl unzip gnupg2

# Add Google Chrome's official GPG key and setup repository
RUN wget -q -O - https://dl-ssl.google.com/linux/linux_signing_key.pub | apt-key add - && \
    echo 'deb [arch=amd64] http://dl.google.com/linux/chrome/deb/ stable main' > /etc/apt/sources.list.d/google-chrome.list

# Install the latest stable version of Google Chrome
RUN apt-get update -y && apt-get install -y google-chrome-stable

# Fetch the latest ChromeDriver version matching the installed Google Chrome version
RUN CHROME_VERSION=$(google-chrome --version | grep -oP '\d+\.\d+\.\d+\.\d+') && \
    wget https://storage.googleapis.com/chrome-for-testing-public/${CHROME_VERSION}/linux64/chromedriver-linux64.zip && \
    unzip chromedriver-linux64.zip && \
    mv chromedriver-linux64/chromedriver /usr/local/bin/ && \
    rm -rf chromedriver-linux64.zip chromedriver-linux64


# SET challenges
RUN adduser  $user
ADD ./ /app
WORKDIR /app
RUN pip3 install -r requirements.txt

# RUN
USER $user
EXPOSE $port


ENTRYPOINT ["python3"]
CMD ["app.py"]
