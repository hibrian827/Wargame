FROM node:16-alpine@sha256:4d68856f48be7c73cd83ba8af3b6bae98f4679e14d1ff49e164625ae8831533a

ENV USER cproxy
ENV PORT 8080
ENV NODE_ENV production

# Change tmp permissions
RUN chmod 1733 /tmp /var/tmp /dev/shm

# Add user
RUN adduser -D -g "" $USER

# Add files
COPY --chown=root:root cproxy /cproxy
COPY --chown=root:$USER flag_forge /flag_forge
RUN chmod 440 /flag_forge

WORKDIR /cproxy
RUN npm install

# Run server
CMD until nc -z -w1 db 3306;    \
        do sleep 1;             \
    done;                       \
    exec npm start
USER $USER
EXPOSE $PORT
