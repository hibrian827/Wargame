FROM ubuntu:22.04

RUN sed -i "s/[a-z\.]*\.com/mirror.kakao.com/g" /etc/apt/sources.list

RUN apt update && apt install -y curl git python3 python3-pip

RUN curl -L https://foundry.paradigm.xyz | bash
RUN /root/.foundry/bin/foundryup
ENV PATH="/root/.foundry/bin:${PATH}"

RUN git config --global user.email "user@example.com"
RUN git config --global user.name "User"

RUN forge init contract

WORKDIR /contract

RUN forge install OpenZeppelin/openzeppelin-contracts
RUN rm -rf script && rm -rf test && rm -rf src

COPY script /contract/script
COPY src /contract/src
COPY start.sh /contract/start.sh
RUN chmod +x /contract/start.sh

RUN forge build

CMD [ "/contract/start.sh" ]