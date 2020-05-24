#!/bin/bash

echo ClassName:
read name
touch "$name.h"
touch "$name.cpp"
echo "Created $name.h $name.cpp files"