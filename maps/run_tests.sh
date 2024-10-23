#!/bin/bash

# Array of scripts to run
scripts=(
    "leak_test.sh"
    "tests.sh"
    "valid_leak_test.sh"
    "valid_map_test.sh"
)

# Loop through and run each script
for script in "${scripts[@]}"; do
    echo "Running $script..."
    ./"$script"
done


	