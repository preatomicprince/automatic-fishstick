iso: iso.c
	gcc -o iso iso.c sprite.c sprite.h settings.h colider.c colider.h entity.h entity.c input.h input.c debug.h debug.c player.h player.c -lm -lSDL2 -lSDL2_image
