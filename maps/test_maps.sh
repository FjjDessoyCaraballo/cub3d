#!/bin/bash

maps=(	"error_test/extra_RGB1.cub"
		"error_test/extra_RGB2.cub"
		"error_test/extra_RGB3.cub"
		"error_test/extra_sprite1.cub"
		"error_test/extra_sprite2.cub"
		"error_test/sprite_wrong1.cub"
		"error_test/wrongmap1.cub"
		"error_test/wrongmap2.cub"
)

output_file="result.txt"

> "$output_file"

for map in "${maps[@]}"; do
	echo "Running test for $map..." | tee -a "$output_file"
	
	output=$(../cub3D "$map" >> "$output_file" 2>&1)

	first_line=$(echo "$output" | head -n 1)

	if [[ "$first_line" == "Error\n" ]]; then
		echo "Skipping output for $map (Error succesful reached)" | tee -a $"output_file"
	else
		echo "$output" >> "$output_file"
	fi

	echo "" >> "$output_file"
done