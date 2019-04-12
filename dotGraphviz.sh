#!/bin/bash

#cd ./doc/sfml

#dot -Tsvg -o class.svg class.dot

cd ./doc

dot -Tsvg -o tinysfml.svg tinysfml.dot
dot -Tsvg -o tinybgfx.svg tinybgfx.dot
dot -Tsvg -o tinybgfx_helloworld.svg tinybgfx_helloworld.dot