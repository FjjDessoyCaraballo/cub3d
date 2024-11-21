#!/bin/bash

maps=(	"error_maps/extra_RGB1.cub"
		"error_maps/extra_RGB2.cub"
		"error_maps/extra_RGB3.cub"
		"error_maps/extra_RGB4.cub"
		"error_maps/extra_RGB5.cub"
		"error_maps/extra_RGB6.cub"
		"error_maps/extra_RGB7.cub"
		"error_maps/extra_sprite1.cub"
		"error_maps/extra_sprite2.cub"
		"error_maps/extra_sprite3.cub"
		"error_maps/extra_sprite4.cub"
		"error_maps/wrongmap1.cub"
		"error_maps/wrongmap2.cub"
		"error_maps/wrongmap3.cub"
		"error_maps/wrongmap4.cub"
		"error_maps/wrongmap5.cub"
		"error_maps/missing_RGB1.cub"
		"error_maps/missing_RGB2.cub"
		"error_maps/missing_RGB3.cub"
		"error_maps/wrong_RGB1.cub"
		"error_maps/wrong_RGB2.cub"
		"error_maps/wrong_RGB3.cub"
		"error_maps/wrong_RGB4.cub"
		"error_maps/wrong_RGB5.cub"
		"error_maps/wrong_RGB6.cub"
		"error_maps/wrong_RGB7.cub"
		"error_maps/wrong_RGB8.cub"
		"error_maps/wrong_RGB9.cub"
		"error_maps/no_permission1.cub"
		"error_maps/no_permission2.cub"
		"error_maps/no_permission3.cub"
		"error_maps/no_permission4.cub"
		"error_maps/extra_player1.cub"
		"error_maps/extra_player2.cub"
		"error_maps/extra_player3.cub"
		"error_maps/extra_player4.cub"
		"error_maps/extra_player5.cub"
		"error_maps/extra_player6.cub"
		"error_maps/extra_player7.cub"
		"error_maps/extra_player8.cub"
		"error_maps/not_walled1.cub"
		"error_maps/not_walled2.cub"
		"error_maps/not_walled3.cub"
		"error_maps/not_walled4.cub"
		"error_maps/not_walled5.cub"
		"error_maps/island1.cub"
		"error_maps/island2.cub"
		"error_maps/wrong_name.cbu"
		"error_maps/file.cbuwrong"
		"error_maps/dir_test.cub"
		"error_maps/gap1.cub"
		"error_maps/wrong_sprite1.cub"
		"error_maps/wrong_sprite2.cub"
		"error_maps/wrong_sprite3.cub"
		"error_maps/wrong_sprite4.cub"
		"error_maps/wrong_sprite5.cub"
		"error_maps/wrong_sprite6.cub"
		"error_maps/wrong_sprite7.cub"
		"error_maps/wrong_sprite8.cub"
		"error_maps/wrong_sprite9.cub"
		"error_maps/wrong_sprite10.cub"
		"error_maps/wrong_sprite11.cub"
		"error_maps/wrong_sprite12.cub"
		"error_maps/wrong_sprite13.cub"
		"error_maps/wrong_sprite14.cub"
		"error_maps/wrong_place1.cub"
		"error_maps/wrong_place2.cub"
)

# log directory
log_dir="logs"

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
