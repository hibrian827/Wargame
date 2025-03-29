FROM ubuntu:22.04@sha256:965fbcae990b0467ed5657caceaec165018ef44a4d2d46c7cdea80a9dff0d1ea

ENV USER=dreamhack
ENV PORT=14448

RUN apt update
RUN apt-get install -y socat python3 python3-pip && \ 
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*
    
RUN pip install pycryptodome

RUN adduser $USER -u 1337


COPY ./deploy/flag /flag
COPY ./deploy/prob.py /prob.py
COPY ./deploy/cipher.py /cipher.py

RUN chmod 755 /flag /prob.py

EXPOSE $PORT

CMD socat TCP-LISTEN:14448,reuseaddr,fork EXEC:/prob.py
