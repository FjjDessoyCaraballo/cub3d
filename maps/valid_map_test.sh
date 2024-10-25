#!/bin/bash

maps=(	"valid/map1.cub"
		"valid/map2.cub"
		"valid/map3.cub"
		"valid/map4.cub"
		"valid/no_zero1.cub"
		"valid/no_zero2.cub"
		"valid/no_zero3.cub"
		"valid/no_zero4.cub"
		"valid/map_simple1.cub"
		"valid/map_simple2.cub"
		"valid/map_simple3.cub"
		"valid/map_simple4.cub"
)

# log directory
log_dir="logs_valid"

mkdir -p "$log_dir"

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