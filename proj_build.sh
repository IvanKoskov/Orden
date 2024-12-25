#!/bin/bash

# Project builder

# Navigate to the preprocess directory
cd preprocess || exit 1  # Ensure we exit if this directory doesn't exist

# Compile the preprocessor
g++ -std=c++17 orden_procs.cpp -o preprocessor

# Move the preprocessor binary to /usr/local/bin to make it globally executable
sudo mv preprocessor /usr/local/bin/ 

echo "Compiled the preprocessor!"

# Return to the root directory
cd ..

# Navigate to the project_manager directory
cd project_manager || exit 1  # Ensure we exit if this directory doesn't exist

# Compile the template creator
g++ -std=c++17 template.cpp -o template

# Move the template creator binary to /usr/local/bin
sudo mv template /usr/local/bin/ 

echo "Compiled the template creator!"

# Return to the root directory
cd ..


