#!/bin/bash

maps=(	"maps/error_test/extra_RGB1.cub"
		"maps/error_test/extra_RGB2.cub"
		"maps/error_test/extra_RGB3.cub"
		"maps/error_test/extra_sprite1.cub"
		"maps/error_test/extra_sprite2.cub"
		"maps/error_test/sprite_wrong1.cub"
		"maps/error_test/wrongmap1.cub"
		"maps/error_test/wrongmap2.cub"
)

output_file="result.txt"

> "$output_file"

for map in "${maps[@]}"; do
	echo "Running test for $map..." | tee -a "$output_file"
	./cub3D "$map" >> "$output_file" 2>&1
	echo "" >> "$output_file"
done