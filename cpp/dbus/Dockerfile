# Base image
FROM ubuntu:latest

# Install dependencies for D-Bus
RUN apt-get update && apt-get install -y \
  cmake \
  g++ \
  vim \
  libglib2.0-dev \
  dbus \
  dbus-x11

# Set working directory
WORKDIR /app

ENV DISPLAY=:0
RUN dbus-uuidgen > /etc/machine-id

# Copy directories
COPY Makefile /app/Makefile
COPY notifier /app/notifier
COPY rxtx /app/rxtx
COPY server /app/server

# Compile all the apps
RUN make all

RUN echo '#!/bin/sh' > /app/entrypoint.sh && \
    echo 'exec tail -f /dev/null' >> /app/entrypoint.sh && \
    chmod +x /app/entrypoint.sh

# Set the entrypoint to let us exec into the container
# NOTE: You need to run this in the shell
# export $(dbus-launch)
# echo "export DBUS_SESSION_BUS_PID=$DBUS_SESSION_BUS_PID"
# echo "export DBUS_SESSION_BUS_ADDRESS=$DBUS_SESSION_BUS_ADDRESS"
# and then run the output of the echos in the other shells that you want to connect to the dbus
ENTRYPOINT [ "/app/entrypoint.sh" ]