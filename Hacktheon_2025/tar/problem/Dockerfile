FROM python:3.11-slim AS jail

FROM disconnect3d/nsjail

COPY --from=jail / /jail/

COPY flag /jail/flag
COPY tar.py  /jail/tar.py
COPY run_py.sh /jail/run_py.sh
RUN chmod +x /jail/run_py.sh

COPY start.sh /start.sh
RUN chmod +x /start.sh

CMD [ "/start.sh" ]