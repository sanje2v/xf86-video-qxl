#!/bin/bash
CURRENT_DIR_NAME=${PWD##*/}

docker build --build-arg HOST_UID=$(id -u) --build-arg HOST_NAME=$(whoami) -f Dockerfile -t $CURRENT_DIR_NAME . && \
mkdir -p ./install && \
docker run --rm -it \
           -v $(pwd):/home/$(whoami)/$CURRENT_DIR_NAME:rw \
           -v $HOME/.ssh:/home/$(whoami)/.ssh:ro \
           --user $(whoami) \
           --workdir /home/$(whoami)/$CURRENT_DIR_NAME \
           --entrypoint /bin/bash \
           --name $CURRENT_DIR_NAME $CURRENT_DIR_NAME
