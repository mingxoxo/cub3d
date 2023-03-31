
#include <cmath>
#include <string>
#include <vector>
#include <iostream>

#include "quickcg.h"
using namespace QuickCG;

/*
g++ *.cpp -lSDL -O3 -W -Wall -ansi -pedantic
g++ *.cpp -lSDL
*/


#define screenWidth 640
#define screenHeight 480
#define texWidth 64 // 반드시 2의 배수여야 함
#define texHeight 64 // 반드시 2의 배수여야 함
#define mapWidth 24
#define mapHeight 24

int worldMap[mapWidth][mapHeight] =
{
  {8,8,8,8,8,8,8,8,8,8,8,4,4,6,4,4,6,4,6,4,4,4,6,4},
  {8,0,0,0,0,0,0,0,0,0,8,4,0,0,0,0,0,0,0,0,0,0,0,4},
  {8,0,3,3,0,0,0,0,0,8,8,4,0,0,0,0,0,0,0,0,0,0,0,6},
  {8,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
  {8,0,3,3,0,0,0,0,0,8,8,4,0,0,0,0,0,0,0,0,0,0,0,4},
  {8,0,0,0,0,0,0,0,0,0,8,4,0,0,0,0,0,6,6,6,0,6,4,6},
  {8,8,8,8,0,8,8,8,8,8,8,4,4,4,4,4,4,6,0,0,0,0,0,6},
  {7,7,7,7,0,7,7,7,7,0,8,0,8,0,8,0,8,4,0,4,0,6,0,6},
  {7,7,0,0,0,0,0,0,7,8,0,8,0,8,0,8,8,6,0,0,0,0,0,6},
  {7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,6,0,0,0,0,0,4},
  {7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,6,0,6,0,6,0,6},
  {7,7,0,0,0,0,0,0,7,8,0,8,0,8,0,8,8,6,4,6,0,6,6,6},
  {7,7,7,7,0,7,7,7,7,8,8,4,0,6,8,4,8,3,3,3,0,3,3,3},
  {2,2,2,2,0,2,2,2,2,4,6,4,0,0,6,0,6,3,0,0,0,0,0,3},
  {2,2,0,0,0,0,0,2,2,4,0,0,0,0,0,0,4,3,0,0,0,0,0,3},
  {2,0,0,0,0,0,0,0,2,4,0,0,0,0,0,0,4,3,0,0,0,0,0,3},
  {1,0,0,0,0,0,0,0,1,4,4,4,4,4,6,0,6,3,3,0,0,0,3,3},
  {2,0,0,0,0,0,0,0,2,2,2,1,2,2,2,6,6,0,0,5,0,5,0,5},
  {2,2,0,0,0,0,0,2,2,2,0,0,0,2,2,0,5,0,5,0,0,0,5,5},
  {2,0,0,0,0,0,0,0,2,0,0,0,0,0,2,5,0,5,0,5,0,5,0,5},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5},
  {2,0,0,0,0,0,0,0,2,0,0,0,0,0,2,5,0,5,0,5,0,5,0,5},
  {2,2,0,0,0,0,0,2,2,2,0,0,0,2,2,0,5,0,5,0,0,0,5,5},
  {2,2,2,2,1,2,2,2,2,2,2,1,2,2,2,5,5,5,5,5,5,5,5,5}
};

// 스프라이트의 위치와 텍스처를 포함하는 구조체 Sprite
struct Sprite
{
  double x;
  double y;
  int texture;
};

// 스프라이트의 수
#define numSprites 19

Sprite sprite[numSprites] =
{
  {20.5, 11.5, 10}, // 플레이어 시작 앞에 녹색 불빛
  // 방 전체의 녹색 불빛
  {18.5,4.5, 10},
  {10.0,4.5, 10},
  {10.0,12.5,10},
  {3.5, 6.5, 10},
  {3.5, 20.5,10},
  {3.5, 14.5,10},
  {14.5,20.5,10},

  //벽 앞의 기둥 줄: 어안 테스트
  {18.5, 10.5, 9},
  {18.5, 11.5, 9},
  {18.5, 12.5, 9},

  //지도 주위에 몇 개의 통
  {21.5, 1.5, 8},
  {15.5, 1.5, 8},
  {16.0, 1.8, 8},
  {16.2, 1.2, 8},
  {3.5,  2.5, 8},
  {9.5, 15.5, 8},
  {10.0, 15.1,8},
  {10.5, 15.8,8},
};

// 스캔 라인별로 작동하므로 Y좌표가 먼저
Uint32 buffer[screenHeight][screenWidth];

//1D Zbuffer
double ZBuffer[screenWidth];

// 스프라이트를 정렬하는데 사용될 배열
int spriteOrder[numSprites];
double spriteDistance[numSprites];

// 스프라이트를 정렬하는데 사용될 함수
void sortSprites(int* order, double* dist, int amount);

int main(int /*argc*/, char */*argv*/[])
{
  double posX = 22.0, posY = 11.5; //x and y start position
  double dirX = -1.0, dirY = 0.0; //initial direction vector
  double planeX = 0.0, planeY = 0.66; //the 2d raycaster version of camera plane

  double time = 0; //time of current frame
  double oldTime = 0; //time of previous frame

  std::vector<Uint32> texture[11];
  for(int i = 0; i < 11; i++) texture[i].resize(texWidth * texHeight);

  screen(screenWidth,screenHeight, 0, "Raycaster");

  //load some textures
  unsigned long tw, th, error = 0;
  error |= loadImage(texture[0], tw, th, "pics/eagle.png");
  error |= loadImage(texture[1], tw, th, "pics/redbrick.png");
  error |= loadImage(texture[2], tw, th, "pics/purplestone.png");
  error |= loadImage(texture[3], tw, th, "pics/greystone.png");
  error |= loadImage(texture[4], tw, th, "pics/bluestone.png");
  error |= loadImage(texture[5], tw, th, "pics/mossy.png");
  error |= loadImage(texture[6], tw, th, "pics/wood.png");
  error |= loadImage(texture[7], tw, th, "pics/colorstone.png");
  if(error) { std::cout << "error loading images" << std::endl; return 1; }

  //load some sprite textures
  error |= loadImage(texture[8], tw, th, "pics/barrel.png");
  error |= loadImage(texture[9], tw, th, "pics/pillar.png");
  error |= loadImage(texture[10], tw, th, "pics/greenlight.png");
  if(error) { std::cout << "error loading images" << std::endl; return 1; }

  //start the main loop
  while(!done())
  {
    //FLOOR CASTING
    for(int y = screenHeight / 2 + 1; y < screenHeight; ++y)
    {
      // rayDir for leftmost ray (x = 0) and rightmost ray (x = w)
      float rayDirX0 = dirX - planeX;
      float rayDirY0 = dirY - planeY;
      float rayDirX1 = dirX + planeX;
      float rayDirY1 = dirY + planeY;

      // Current y position compared to the center of the screen (the horizon)
      int p = y - screenHeight / 2;

      // Vertical position of the camera.
      float posZ = 0.5 * screenHeight;

      // Horizontal distance from the camera to the floor for the current row.
      // 0.5 is the z position exactly in the middle between floor and ceiling.
      float rowDistance = posZ / p;

      // calculate the real world step vector we have to add for each x (parallel to camera plane)
      // adding step by step avoids multiplications with a weight in the inner loop

      // real world coordinates of the leftmost column. This will be updated as we step to the right.
      float floorX = posX + rowDistance * rayDirX0;
      float floorY = posY + rowDistance * rayDirY0;
    }

    // WALL CASTING
    for(int x = 0; x < w; x++)
    {
      //calculate ray position and direction
      double cameraX = 2 * x / double(w) - 1; //x-coordinate in camera space
      double rayDirX = dirX + planeX * cameraX;
      double rayDirY = dirY + planeY * cameraX;

      //which box of the map we're in
      int mapX = int(posX);
      int mapY = int(posY);

      //length of ray from current position to next x or y-side
      double sideDistX;
      double sideDistY;

      //length of ray from one x or y-side to next x or y-side
      double deltaDistX = (rayDirX == 0) ? 1e30 : std::abs(1 / rayDirX);
      double deltaDistY = (rayDirY == 0) ? 1e30 : std::abs(1 / rayDirY);
      double perpWallDist;

      //what direction to step in x or y-direction (either +1 or -1)
      int stepX;
      int stepY;

      int hit = 0; //was there a wall hit?
      int side; //was a NS or a EW wall hit?

      //calculate step and initial sideDist
      //perform DDA
      while (hit == 0)
      {
        //jump to next map square, either in x-direction, or in y-direction
        if(sideDistX < sideDistY)
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
        //Check if ray has hit a wall
        if(worldMap[mapX][mapY] > 0) hit = 1;
      }

      //Calculate distance of perpendicular ray (Euclidean distance would give fisheye effect!)
      

      //Calculate height of line to draw on screen
      //calculate lowest and highest pixel to fill in current stripe
      //texturing calculations
      int texNum = worldMap[mapX][mapY] - 1; //1 subtracted from it so that texture 0 can be used!

      //calculate value of wallX
      double wallX; //where exactly the wall was hit
      if (side == 0) wallX = posY + perpWallDist * rayDirY;
      else           wallX = posX + perpWallDist * rayDirX;
      wallX -= floor((wallX));

      //x coordinate on the texture
      int texX = int(wallX * double(texWidth));
      if(side == 0 && rayDirX > 0) texX = texWidth - texX - 1;
      if(side == 1 && rayDirY < 0) texX = texWidth - texX - 1;

      // TODO: an integer-only bresenham or DDA like algorithm could make the texture coordinate stepping faster
      // How much to increase the texture coordinate per screen pixel
      double step = 1.0 * texHeight / lineHeight;
      // Starting texture coordinate
      double texPos = (drawStart - h / 2 + lineHeight / 2) * step;
      for(int y = drawStart; y < drawEnd; y++)
      {
        // Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
        int texY = (int)texPos & (texHeight - 1);
        texPos += step;
        Uint32 color = texture[texNum][texHeight * texY + texX];
        //make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
        if(side == 1) color = (color >> 1) & 8355711;
        buffer[y][x] = color;
      }

      //SET THE ZBUFFER FOR THE SPRITE CASTING
      ZBuffer[x] = perpWallDist; //perpendicular distance is used
    }


    //SPRITE CASTING
    // 스프라이트를 멀리서부터 가까운 순으로 정렬
    for(int i = 0; i < numSprites; i++)
    {
      spriteOrder[i] = i;
      //sqrt 취하지 않음, 필요 없음
      spriteDistance[i] = ((posX - sprite[i].x) * (posX - sprite[i].x) + (posY - sprite[i].y) * (posY - sprite[i].y)); 
    }
    sortSprites(spriteOrder, spriteDistance, numSprites);

    //스프라이트를 정렬한 뒤, 투영을 수행하고 그리기
    for(int i = 0; i < numSprites; i++)
    {
      //스프라이트 위치를 카메라 기준으로 변환
      double spriteX = sprite[spriteOrder[i]].x - posX;
      double spriteY = sprite[spriteOrder[i]].y - posY;

      //카메라 행렬의 역행렬로 스프라이트 변환
      // [ planeX   dirX ] -1                                       [ dirY      -dirX ]
      // [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
      // [ planeY   dirY ]                                          [ -planeY  planeX ]

      //올바른 행렬 곱셈을 위해 필요
      double invDet = 1.0 / (planeX * dirY - dirX * planeY);

      double transformX = invDet * (dirY * spriteX - dirX * spriteY);
      // 실제 화면 내부의 깊이, 즉 3D에서 Z는 스프라이트와 플레이어의 거리, sqrt(spriteDistance[i])와 일치하는 값
      double transformY = invDet * (-planeY * spriteX + planeX * spriteY);

      int spriteScreenX = int((w / 2) * (1 + transformX / transformY));

      // 스프라이트 크기 조정 및 이동을 위한 파라미터
      #define uDiv 1
      #define vDiv 1
      #define vMove 0.0
      int vMoveScreen = int(vMove / transformY);

      //화면에서 스프라이트의 높이 계산
      //실제 거리 대신 "transformY"를 사용하면 어안 현상을 방지할 수 있습니다.
      int spriteHeight = abs(int(h / (transformY))) / vDiv;
      //현재 스프라이트를 채울 최저, 최고 픽셀을 계산합니다.
      int drawStartY = -spriteHeight / 2 + h / 2 + vMoveScreen;
      if(drawStartY < 0) drawStartY = 0;
      int drawEndY = spriteHeight / 2 + h / 2 + vMoveScreen;
      if(drawEndY >= h) drawEndY = h - 1;

      //스프라이트의 너비 계산
      // 정사각형일 경우 스프라이트의 높이와 동일합니다.
      int spriteWidth = abs(int (h / (transformY))) / uDiv;
      int drawStartX = -spriteWidth / 2 + spriteScreenX;
      if(drawStartX < 0) drawStartX = 0;
      int drawEndX = spriteWidth / 2 + spriteScreenX;
      if(drawEndX > w) drawEndX = w;

      //화면에서 스프라이트의 모든 세로 줄무늬를 반복
      for(int stripe = drawStartX; stripe < drawEndX; stripe++)
      {
        int texX = int(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * texWidth / spriteWidth) / 256;
        //if문의 조건은 다음과 같습니다:
        //1) 카메라 평면의 앞에 있어 뒤의 사물이 보이지 않는 경우
        //2) ZBuffer, 수직거리 포함
        if(transformY > 0 && transformY < ZBuffer[stripe])
        {
          //현재 스프라이트의 모든 픽셀에 대해
          for(int y = drawStartY; y < drawEndY; y++)
          {
            //부동 소수점을 피하기 위한 256 및 128 요소
            int d = (y - vMoveScreen) * 256 - h * 128 + spriteHeight * 128;
            int texY = ((d * texHeight) / spriteHeight) / 256;
            //현재 텍스쳐의 색상을 가져옴
            Uint32 color = texture[sprite[spriteOrder[i]].texture][texWidth * texY + texX]; 
            //페인트 픽셀이 검은색아 아닌 경우 검은색은 보이지 않는 색상
            if((color & 0x00FFFFFF) != 0) buffer[y][stripe] = color;
          }
        }
      }
    }

    drawBuffer(buffer[0]);
    // No need to clear the screen here, since everything is overdrawn with floor and ceiling

  }
}

//거리를 기준으로 스프라이트 정렬
void sortSprites(int* order, double* dist, int amount)
{
  std::vector<std::pair<double, int>> sprites(amount);
  for(int i = 0; i < amount; i++) {
    sprites[i].first = dist[i];
    sprites[i].second = order[i];
  }
  std::sort(sprites.begin(), sprites.end());
  // 가장 먼 곳에서 가장 가까운 곳으로 역순으로 복원
  for(int i = 0; i < amount; i++) {
    dist[i] = sprites[amount - i - 1].first;
    order[i] = sprites[amount - i - 1].second;
  }
}