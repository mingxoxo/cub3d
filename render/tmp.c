#include <stdio.h>
#include <math.h>
#include "mlx_opengl/mlx.h"
#include "libft/libft.h"

#define mapWidth 24
#define mapHeight 24
#define screenWidth 1280
#define screenHeight 720
int texWidth = 64;
int texHeight = 64;

enum	e_keycode
{
	KEY_ESC = 53,
	KEY_Q = 12,
	KEY_W = 13,
	KEY_A = 0,
	KEY_S = 1,
	KEY_Z = 6,
	KEY_X = 7,
	KEY_E = 14,
	KEY_R = 15,
	KEY_D = 2,
	KEY_F = 3,
	KEY_C = 8,
	KEY_V = 9,
	KEY_O = 31,
	KEY_P = 35,
	KEY_UP = 126,
	KEY_DOWN = 125,
	KEY_LEFT = 123,
	KEY_RIGHT = 124,
	KEY_LARR = 43,
	KEY_RARR = 47
};

int worldMap[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	void	*img;
	int		win_x;
	int		win_y;
	int		bit;
	int		lsize;
	int		end;
	char	*ptr;
}			t_mlx;

typedef struct s_img
{
	char	*path;
	void	*ptr;
	char	*data;
	int		w;
	int		h;
	int		bpp;
	int		lsize;
	int		end;
}			t_img;

double posX = 22, posY = 12; //플레이어의 초기 위치벡터
double dirX = -1, dirY = 0; //플레이어의 초기 방향벡터
double planeX = 0, planeY = 0.66; //플레이어의 카메라 평면

double time = 0; //현재 프레임의 시간
double oldTime = 0; //이전 프레임의 시간
t_img	img;


void	init_mlx(t_mlx *m, int width, int height)
{
	m->mlx = mlx_init();
	m->win = mlx_new_window(m->mlx, width, height, "Raycaster");
	m->img = mlx_new_image(m->mlx, width, height);
	m->win_x = width;
	m->win_y = height;
	m->bit = 0;
	m->lsize = 0;
	m->end = 0;
	m->ptr = mlx_get_data_addr(m->img, &(m->bit), &(m->lsize), &(m->end));
}

static int	create_argb(int a, int r, int g, int b)
{
	return (a << 24 | r << 16 | g << 8 | b);
}

static int	hex_to_int(char *hex)
{
	int	i;
	int	res;

	if (!hex || ft_strlen(hex) != 8)
		return (create_argb(0, 255, 255, 255));
	i = 2;
	res = 0;
	while (hex[i])
	{
		res <<= 4;
		if (ft_isdigit(hex[i]))
			res += hex[i] - '0';
		else
			res += ft_tolower(hex[i]) - 'a' + 10;
		i++;
	}
	return (res);
}

void	print_dot(t_mlx mlx, int x, int y, char *color)
{
	char	*dst;

	if (screenHeight <= y || screenWidth <= x || x < 0 || y < 0)
		return ;
	dst = mlx.ptr + (y * (mlx.lsize) + x * (mlx.bit) / 8);
	if (color == NULL)
		*(unsigned int *)dst = create_argb(0, 255, 255, 255);
	else
		*(unsigned int *)dst = hex_to_int(color);
}

void	print_dot_int(t_mlx mlx, int x, int y, unsigned int color)
{
	char	*dst;

	if (screenHeight <= y || screenWidth <= x || x < 0 || y < 0)
		return ;
	dst = mlx.ptr + (y * (mlx.lsize) + x * (mlx.bit) / 8);
	*(unsigned int *)dst = color;
}

void	verLine(t_mlx mlx, int x, int drawStart, int drawEnd, char *color)
{
	int	i;

	i = drawStart;

	while (i <= drawEnd)
	{
		print_dot(mlx, x, i, color);
		i++;
	}
}

void	fill_background(t_mlx *mlx)
{
	char	*dst;
	int		i;
	int		j;

	i = 0;
	while (i < mlx->win_y)
	{
		j = 0;
		while (j < mlx->win_x)
		{
			dst = mlx->ptr + (i * (mlx->lsize) + j * (mlx->bit) / 8);
			if (i < mlx->win_y / 2)
				*(unsigned int *)dst = create_argb(0, 0, 255, 255); // sky
			else
				*(unsigned int *)dst = create_argb(0, 153, 204, 0); // ground
			j++;
		}
		i++;
	}
}

void	render_screen(t_mlx *mlx, int width, int height)
{
	fill_background(mlx);
	for(int x = 0; x < width; x++)
	{
		//ray의 위치와 방향 계산
		double cameraX = 2 * x / (double)width - 1; //for문의 x값이 카메라평면에서 차지하는 x좌표
		// for문의 x값이 0이면 (스크린의 왼쪽 끝이면) cameraX = -1
		// for문의 x값이 w/2이면 (스크린의 중앙이면) cameraX = 0
		// for문의 x값이 w이면 (스크린의 오른쪽 끝이면) cameraX = 1

		// 광선의 방향벡터
		// 광선의 방향 = ( 방향벡터 ) + ( 카메라평면 x 배수 )
		double rayDirX = dirX + planeX * cameraX;
		double rayDirY = dirY + planeY * cameraX;


		// DDA 알고리즘
		//현재 광선의위치, 광선이 있는 한 칸
		int mapX = (int)posX;
		int mapY = (int)posY;

		// sideDistX: '시작점 ~ 첫번째 x면을 만나는 점'까지의 광선의 이동거리
		// sideDistY: '시작점 ~ 첫번째 y면을 만나는 점'까지의 광선의 이동거리
		double sideDistX;
		double sideDistY;

		// deltaDistX: '첫번째 x면 ~ 바로 다음 x면'까지의 광선의 이동거리 (이때 x는 1만큼 이동)
		// deltaDistY: '첫번째 y면 ~ 바로 다음 y면'까지의 광선의 이동거리 (이때 y는 1만큼 이동)
		double deltaDistX = fabs(1 / rayDirX);
		double deltaDistY = fabs(1 / rayDirY);
		// perpWallDist: 나중에 광선의 이동거리를 계산하는 데 사용
		double perpWallDist;

		//DDA 알고리즘은 반복문을 실행할 때마다 x방향 또는 y방향으로 딱 한 칸(square)씩 점프
		// 광선의 방향에 따라 어느 방향으로 건너뛰는지 달라지는데
		// 그 정보는 stepX, stepY 에 +1 또는 -1 로 저장
		int stepX;
		int stepY;

		int hit = 0; // 벽에 부딪혔는지 확인
		int side; // 부딪힌 벽이 북남쪽 벽인지 동서쪽 벽인지 확인


		//stepX, stepY의 초기값 구하기
		// 광선의 x방향 rayDirX의 값이 양수라면, stepX의 값은 +1, 음수라면 -1
		// rayDirX의 값이 0이라면, stepX는 사용되지 않으므로 어떤 값을 갖든 상관없음
		// sideDistX: 광선의 시작점부터 오른쪽/왼쪽 으로 이동하다 처음 만나는 x면까지의 거리
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - posX) * deltaDistX;
		}
		// stepY의 값도 똑같이 함
		// sideDistX: 광선의 시작점부터 위쪽/아래쪽 으로 이동하다 처음 만나는 x면까지의 거리
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - posY) * deltaDistY;
		}


		//DDA 알고리즘 시작
		while (hit == 0)
		{
			// 벽에 부딪힐 때까지 매번 한 칸씩 광선을 이동시킴
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			// ray가 벽에 맞았는지 확인
			if (worldMap[mapX][mapY] > 0) hit = 1;
		}


		// printf("mapY: %d posY: %lf stepY: %d rayDirY: %lf ", mapY, posY, stepY, rayDirY);
		// 카메라 평면까지의 거리 계산
		if (side == 0) perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
		else           perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;

		// printf("dist:%lf ", perpWallDist);
		// printf("rayDir: %lf %lf\n", rayDirX, rayDirY);

		// 화면에 그릴 높이 계산
		int lineHeight = (int)(height / perpWallDist);

		// 가장 작은 픽셀과 가장 큰 픽셀 크기 보정
		int drawStart = -lineHeight / 2 + height / 2;
		if(drawStart < 0)drawStart = 0;
		int drawEnd = lineHeight / 2 + height / 2;
		if(drawEnd >= height)drawEnd = height - 1;


		// 텍스쳐 계산
		// 텍스쳐 선택

		// wallX: 벽에서 부딪힌 정확한 위치 계산
		double	wallX;
		if (side == 0)
			wallX = posY + perpWallDist * rayDirY;
		else
			wallX = posX + perpWallDist * rayDirX;
		wallX -= floor(wallX);
		
		// 텍스쳐의 x좌표 계산
		int	texX = (int)(wallX * (double)texWidth);
		if (side == 0 && rayDirX > 0)
			texX = texWidth - texX - 1;
		if (side == 1 && rayDirY < 0)
			texX = texWidth - texX - 1;

		// 아핀 텍스처매핑 - 선형보간법
		double step = 1.0 * texHeight / lineHeight;
		double texPos = (drawStart - height / 2 + lineHeight / 2) * step;
		for (int y = drawStart; y < drawEnd; y++)
		{
			int texY = (int)texPos % texHeight;
			texPos += step;

			unsigned int color = ((unsigned int *)img.data)[texHeight * texY + texX];
			print_dot_int(*mlx, x, y, color);
		}
	}
}


void	player_move(int keycode)
{
	//speed modifiers
    double moveSpeed = 0.1 * 5.0; //the constant value is in squares/second
    double rotSpeed = 0.1 * 1.0; //the constant value is in radians/second

	//move forward if no wall in front of you
	if (keycode == KEY_UP)
	{
		if(worldMap[(int)(posX + dirX * moveSpeed)][(int)(posY)] == 0) posX += dirX * moveSpeed;
		if(worldMap[(int)(posX)][(int)(posY + dirY * moveSpeed)] == 0) posY += dirY * moveSpeed;
	}
	//move backwards if no wall behind you
	if (keycode == KEY_DOWN)
	{
		if(worldMap[(int)(posX - dirX * moveSpeed)][(int)(posY)] == 0) posX -= dirX * moveSpeed;
		if(worldMap[(int)(posX)][(int)(posY - dirY * moveSpeed)] == 0) posY -= dirY * moveSpeed;
	}
	//rotate to the right
	if (keycode == KEY_RIGHT)
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = dirX;
		dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
		dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
		double oldPlaneX = planeX;
		planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
		planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
	}
	//rotate to the left
	if (keycode == KEY_LEFT)
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = dirX;
		dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
		dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
		double oldPlaneX = planeX;
		planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
		planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
	}
}

int	press_xbox(t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx, mlx->win);
	exit(0);
	return (0);
}

static void	press_esc(t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx, mlx->win);
	exit(0);
}

int	hooks(int keycode, t_mlx *mlx)
{
	if (keycode == KEY_ESC)
		press_esc(mlx);
	else if (keycode == KEY_UP || keycode == KEY_DOWN || \
	keycode == KEY_LEFT || keycode == KEY_RIGHT)
		player_move(keycode);
	render_screen(mlx, screenWidth, screenHeight);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	return (1);
}


int	main(void)
{
	//mlx 초기화
	t_mlx	mlx;

	const int	width = screenWidth;
	const int	height = screenHeight;

	init_mlx(&mlx, width, height);

	img.path = "so.xpm";
	img.ptr = mlx_xpm_file_to_image(mlx.mlx, img.path, &(img.w), &(img.h));
	img.data = mlx_get_data_addr(img.ptr, &img.bpp, &img.lsize, &img.end);

	texWidth = img.w;
	texHeight = img.h;

	render_screen(&mlx, screenWidth, screenHeight);

	mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img, 0, 0);

	mlx_key_hook(mlx.win, hooks, &mlx);
	mlx_hook(mlx.win, 2, 0, hooks, &mlx); // key press
	mlx_hook(mlx.win, 17, 0, press_xbox, &mlx); // xbox exit
	mlx_loop(mlx.mlx);

	return (0);
}
