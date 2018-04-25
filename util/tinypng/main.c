#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// #define TINYPNG_IMPLEMENTATION
#include "tinypng.h"

// #include <dirent.h> // for using directories
// void testfs()
// {
// 	DIR *d;
// 	struct dirent *dir;
// 	d = opendir("./imgs/sprites");
// 	if (d)
// 	{
// 		while ((dir = readdir(d)) != NULL)
// 		{
// 			printf("%s\n", dir->d_name);
// 		}
// 		closedir(d);
// 	}
// }


int main(int argc, char **argv)
{
	// testfs();

	const char *png_names[] = {
		// "imgs/1x1.png",
		// "imgs/4x4.png",
		// "imgs/debug_tile.png",
		// "imgs/default.png",
		// "imgs/house_blue.png",
		// "imgs/house_red.png",
		// "imgs/house_yellow.png",
		// "imgs/squinkle.png",

		"imgs/sprites/redbird-downflap.png",
		"imgs/sprites/pipe-red.png",
		"imgs/sprites/background-day.png",
		"imgs/sprites/8.png",
		"imgs/sprites/redbird-midflap.png",
		"imgs/sprites/bluebird-midflap.png",
		"imgs/sprites/9.png",
		"imgs/sprites/yellowbird-upflap.png",
		"imgs/sprites/bluebird-upflap.png",
		"imgs/sprites/background-night.png",
		"imgs/sprites/redbird-upflap.png",
		"imgs/sprites/yellowbird-midflap.png",
		"imgs/sprites/yellowbird-downflap.png",
		"imgs/sprites/pipe-green.png",
		"imgs/sprites/bluebird-downflap.png",
		"imgs/sprites/base.png",
		"imgs/sprites/gameover.png",
		"imgs/sprites/4.png",
		"imgs/sprites/5.png",
		"imgs/sprites/7.png",
		"imgs/sprites/6.png",
		"imgs/sprites/2.png",
		"imgs/sprites/message.png",
		"imgs/sprites/3.png",
		"imgs/sprites/1.png",
		"imgs/sprites/0.png",
	};


	int png_count = sizeof(png_names) / sizeof(png_names[0]);

	tpImage pngs[png_count];
	for (int i = 0; i < png_count; ++i)
		pngs[i] = tpLoadPNG(png_names[i]);

	// // test save all imgs in dest dir
	// for (int i = 0; i < png_count; i++)
	// {
	// 	char dest[4096];
	// 	sprintf(dest, "%s/%s", "bin", png_names[i]);
	// 	fprintf(stderr, "dest: %s\n", dest);
	// 	tpSavePNG(dest, &pngs[i]);
	// }

	int atlasSize = 1024; //64;

	tpAtlasImage *atlas_img_infos = (tpAtlasImage *)malloc(sizeof(tpAtlasImage) * png_count);
	tpImage atlas_img = tpMakeAtlas(atlasSize, atlasSize, pngs, png_count, atlas_img_infos);
	if (!atlas_img.pix)
	{
		printf("tpMakeAtlas failed: %s", g_tpErrorReason);
		return -1;
	}

	tpDefaultSaveAtlas("bin/atlas.png", "bin/atlas.txt", &atlas_img, atlas_img_infos, png_count, png_names);

	return 0;
}
