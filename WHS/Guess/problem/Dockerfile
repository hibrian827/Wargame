FROM node:20-alpine

ENV USER user
ENV PORT 3000

RUN adduser --disabled-password $USER

WORKDIR /app
COPY ./deploy/app .
RUN npm install

RUN chmod +x ./entrypoint.sh

USER $USER
EXPOSE $PORT

ENTRYPOINT ["./entrypoint.sh"]
CMD ["node", "app.js"]
