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
  // free(m->pixels);
  // free(mm->pixels);
  // free(mmm->pixels);
  // free(mmmm->pixels);
  free(m);
  free(mm);
  free(mmm);
  free(mmmm);
  (void)m;
}