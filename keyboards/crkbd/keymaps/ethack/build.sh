#!/bin/bash

pushd "$(dirname "$BASH_SOURCE[0]")" > /dev/null

cd ../../../../
util/docker_build.sh crkbd:ethack

popd > /dev/null
