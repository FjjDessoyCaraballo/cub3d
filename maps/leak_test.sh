#!/bin/bash

maps=(	"error_test/extra_RGB1.cub"
		"error_test/extra_RGB2.cub"
		"error_test/extra_RGB3.cub"
		"error_test/extra_RGB4.cub"
		"error_test/extra_RGB5.cub"
		"error_test/extra_sprite1.cub"
		"error_test/extra_sprite2.cub"
		"error_test/extra_sprite3.cub"
		"error_test/extra_sprite4.cub"
		"error_test/wrongmap1.cub"
		"error_test/wrongmap2.cub"
		"error_test/wrongmap3.cub"
		"error_test/wrongmap4.cub"
		"error_test/wrongmap5.cub"
		"error_test/missing_RGB1.cub"
		"error_test/missing_RGB2.cub"
		"error_test/missing_RGB3.cub"
		"error_test/wrong_RGB1.cub"
		"error_test/wrong_RGB2.cub"
		"error_test/wrong_RGB3.cub"
		"error_test/extra_player1.cub"
		"error_test/extra_player2.cub"
		"error_test/extra_player3.cub"
		"error_test/extra_player4.cub"
		"error_test/extra_player5.cub"
		"error_test/extra_player6.cub"
		"error_test/extra_player7.cub"
		"error_test/extra_player8.cub"
		"error_test/not_walled1.cub"
		"error_test/not_walled2.cub"
		"error_test/island1.cub"
		"error_test/island2.cub"
		"error_test/island3.cub"
		"error_test/island4.cub"
		"error_test/wrong_name.cbu"
		"error_test/file.cbuwrong"
		"error_test/dir_test.cub"
)

# log directory
log_dir="leak_log"

mkdir -p "$log_dir"

# timestamp
timestamp=$(date +"%d%m%y_%H.%M")

# output file
output_file="${log_dir}/leak_check_${timestamp}.txt"

> "$output_file"

for map in "${maps[@]}"; do
	echo "Running test for $map..." | tee -a "$output_file"
	echo "###########################################################################" | tee -a "$output_file"
	
	output=$(valgrind --leak-check=full ../cub3D "$map" >> "$output_file" 2>&1)

	first_line=$(echo "$output" | head -n 1)

	echo "$output" >> "$output_file"

	echo "" >> "$output_file"
done