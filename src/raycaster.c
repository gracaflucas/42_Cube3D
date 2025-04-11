/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufiguei <lufiguei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 09:42:07 by lufiguei          #+#    #+#             */
/*   Updated: 2025/04/11 10:41:58 by lufiguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/* ray starts at player position, the looking direction matters
 * when it hits a wall, calculate the distance of this point to the player
 * and use this distance to calculate wall height
 * 
 * DDA checks every wall the ray reaches, if Y or X, and checks if its a wall
 * when rendering a wall, use perpendicular vision, so, the shortest ray defines
 * perpWallDist
 * Use FOV to cast all rays in the vision of player?
 * if player rotates, camera rotates, so both direction vector and plane vector
 * to rotate a vector -> cos(a) - sin(a), sin(a) cos(a) ( IS IT *?)
 * estudar vetores e matrizes
 * FOV is 2 * atan(0.66/1) or 66 graus.
 * time for each frame? so it fixes the movement independent of machine
 * raycasting is a for loop on the X, so it doesnt calc every pixel
 * for (int x = 0; x < w; x++)
 * double cameraX = 2 * x / double(w) - 1;
 * double rayDirX = dirX + planeX * cameraX;
 * double rayDirY = dirY + planeY * cameraX;
 * sideDistX and sideDistY is the distance between player and the first wall
 * deltaDistX and deltaDistY is the distance between first wall and second
 * deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX))
 * deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY))
 * or can also use the deltaDistX = abs(1 / rayDirX) && deltaDistY = abs(1 / RayDirY)
 * caution if delta distances are 0 in case of this division
 * use a flag for hit a wall or not
 * a flag for what side was hit? stepX and stepY?
 * To calculate the initial sideDistX and sideDistY
 * if (rayDirX < 0)
 * 	stepX = -1;
 * 	sideDistX = (posX - mapX) * deltaDistX;
 * else
 * 	setX = 1;
 * 	sideDistX = (mapX + 1 - posX) * deltaDistX;
 * the same for Y, but x is -1 for left, 1 for right, and Y is -1 for bottom, 1 for top
 * now for DDA
 * while (!hit)
 * 	if (sideDistX < sideDistY)
 * 		sideDistX += deltaDistX
 * 		mapX += stepX
 * 		side = 0;
 * 	else
 * 		sideDistY += deltaDistY
 * 		mapY += stepY
 * 		side = 1;
 * 	if (map[x][y] > 0)
 * 		hit = 1;
 * to calc perpWallDist
 * if (!side)
 * 	perpWallDist = (sideDistX - deltaDistX)
 * else
 * 	perpWallDist = (sideDistY - deltaDistY)
 * THis is easier to visualize when the player is directly in front of a wall
 * What if its not like this? so a player is diagonaly to a wall?
 *
 * check the graph for more detailed info
 *
 * the height of wall is inverse of perpWallDist and multiplied by the height of pixels on screen
 * the center of the wall should be in the center of the screen
 * if these points lie outside the screen, theyre capped to 0 or h - 1
 * 
 * lineHeight = h / perpWallDist
 * drawStart = -lineHeight / 2 + h / 2
 * if (drawStart < 0) 
 * 	drawStart = 0;
 * drawEnd = lineHeight / 2 + h / 2
 * if (drawEnd >= h)
 * 	drawEnd = h - 1;
 *
 * finally, if any side is hit, add texture/color to it depending on which side
 * verLine(x, drawStart, drawEnd, color);
 *
 * after raycasting is done looping, get time of current and previous frame 
 * oldTime = time;
 * time = getTicks()??
 * double frameTime = (time - oldTime) / 1000
 * double moveSpeed = frameTime * 5;
 * double rotSpeed = frameTime * 3;
 * 
 * keyhook()
 * if (key arrow up)
 * 	if (map[posX + dirX * moveSpeed)][posY] == false
 * 		posX += dirX * moveSpeed;
 * 	if (map[posX][posY + dirY * moveSpeed] == false)
 * 		posY += dirY * moveSpeed
 * in case of key arrow down, the same but -= instead of +=;
 *
 * now to rotate
 * if (key arrow right)
 * 	double oldDirX = dirX;
 * 	dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed)
 * 	dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed)  
 * 	double oldPlaneX = planeX
 * 	planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed)
 *	planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
 *
 * for arrow left, its the same, but instead use positive rot speed.
 * 
 * 
 * 
 * IMPORTANT CASES:
 * 	max ray distance to avoid infinite loops(although this could possibly be renegated by hitting wall, and ensuring the map has a wall)
 * 	shading?
 * */
