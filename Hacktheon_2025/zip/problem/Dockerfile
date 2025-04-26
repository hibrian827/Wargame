FROM ubuntu:22.04 AS base

FROM disconnect3d/nsjail

RUN --mount=type=cache,target=/var/cache/apt,sharing=locked,id=nsjail-apt-cache \
    --mount=type=cache,target=/var/lib/apt,sharing=locked,id=nsjail-apt-lib \
    apt-get update && \
    apt-get install -y --no-install-recommends dos2unix

COPY --from=base / /jail/
COPY flag /jail/
COPY zip /jail/

COPY start.sh /

RUN chmod +x /jail/zip /start.sh && \
    dos2unix /jail/flag /start.sh

EXPOSE 9999
CMD [ "/start.sh" ]
