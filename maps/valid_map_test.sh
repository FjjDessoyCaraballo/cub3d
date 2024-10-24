#!/bin/bash

maps=(	"valid_maps/map1.cub"
		"valid_maps/map2.cub"
		"valid_maps/map3.cub"
		"valid_maps/map4.cub"
		"valid_maps/no_zero1.cub"
		"valid_maps/no_zero2.cub"
		"valid_maps/no_zero3.cub"
		"valid_maps/no_zero4.cub"
		"valid_maps/map_simple1.cub"
		"valid_maps/map_simple2.cub"
		"valid_maps/map_simple3.cub"
		"valid_maps/map_simple4.cub"
)

# log directory
log_dir="logs"

mkdir -p "$log_valid_dir"

# timestamp
timestamp=$(date +"%d%m%y_%H.%M")

# output file
output_file="${log_dir}/log_${timestamp}.txt"

> "$output_file"

for map in "${maps[@]}"; do
	echo "Running test for $map..." | tee -a "$output_file"
	echo "###########################################################################" | tee -a "$output_file"
	
	output=$(../cub3D "$map" >> "$output_file" 2>&1)

	first_line=$(echo "$output" | head -n 1)

	echo "$output" >> "$output_file"

	echo "" >> "$output_file"
done