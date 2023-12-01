#include "cub3d.h"

void v(void)
{
  system("leaks cub3D");
}
int main()
{
  atexit(v);
  mlx_texture_t *m = mlx_load_png("textures/flag.png");
  mlx_texture_t *mm = mlx_load_png("textures/flag.png");
  mlx_texture_t *mmm = mlx_load_png("textures/flag.png");
  mlx_texture_t *mmmm = mlx_load_png("textures/flag.png");
	// uint8_t i=0;
  // while (i < (m->height*m->width))
  // {
  //   free(m->pixels[i++]);
  // }
  // mlx_delete_texture(m);
  mlx_delete_texture(mm);
  mlx_delete_texture(mmm);
  mlx_delete_texture(mmmm);
  (void)m;
}